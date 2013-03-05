require 'rubygems'
require 'json'
require 'fileutils'
require 'mongrel'
require 'net/http'
require 'popen4'
require 'cgi'
require 'pp'
require 'thread'

$semaphore = Mutex.new
$pid = 0
$timeout = 10
$archive = ENV['COLIRU_ARCHIVE']
puts "$archive: #{$archive}"

class SimpleHandler < Mongrel::HttpHandler
  def process(request, response)
    response.start(200) do |head, out|
      File.open('requests.log', 'a') { |f| f << PP.pp(request, '') << "\n" }
      head['Content-Type'] = 'text/html'
      location = get_location(request)

      match_data = %r(([\w-]+\.html).*).match(location)
      if match_data
        FileUtils.copy_stream(File.new(match_data[1]), out)
        return
      else
        case location
          when '' :
            FileUtils.copy_stream(File.new('index.html'), out)
          when 'compile' :
            $semaphore.synchronize { compile(request, out) }
          when 'share' :
            $semaphore.synchronize { share(request, out) }
          when 'view' :
            FileUtils.copy_stream(File.new('view.html'), out)
          when 'external' :
            load_external(request, out)
          when 'embed'
            html = File.open('embed.html', 'r').read
            query = request.params['QUERY_STRING']
            url_params = CGI::parse(query)
            video_id = url_params['v'][0]
            html['{{YOUTUBE_URL}}'] = 'http://youtube.com/embed/' + (video_id ? video_id : 'video_id_goes_here')
            out << html
          when 'favicon.ico' then
            FileUtils.copy_stream(File.new('favicon.png', 'rb'), out)
          else
            $semaphore.synchronize {
              p = Proc.new do |name|
                begin
                  File.read("#{$archive}/#{location}/#{name}")
                rescue Exception => e
                  e.to_s
                end
              end
              out.write({
                            :src => p.call('main.cpp').rstrip,
                            :cmd => p.call('cmd.sh').rstrip,
                            :output => p.call('output').rstrip
                        }.to_json)
            }
        end
      end
    end
  end

  def load_external(req, out)

    # get url params
    req_params=CGI::parse(req.params['QUERY_STRING'])

    # get external url from params
    external_url = req_params['url'][0]

    # download url
    uri = URI.parse(external_url)
    http_get_request = Net::HTTP::Get.new(uri.path)
    result = Net::HTTP.start(uri.host, uri.port) { |http| http.request(http_get_request) }

    # send to out
    out.write(result.body)
  end


  def safe_popen(cmd)
    begin
      Timeout.timeout(3) do
        @my_pipe = IO.popen(cmd)
        puts "pid #{@my_pipe.pid}"
        until @my_pipe.eof?
          line = @my_pipe.readline
          yield line
        end
        Process.wait @my_pipe.pid
      end
    rescue Timeout::Error => e
      puts "killing #{@my_pipe.pid}"
      Process.kill 9, @my_pipe.pid
      Process.wait @my_pipe.pid
      yield e.to_s
    end
  end

  def share(req, out)
    safe_popen('./share.sh 2>&1') { |line| out.write(%r(ID=(\S+)).match(line.read)[1]) }
  end

  def compile(req, out)
    obj = JSON.parse(req.body.string)
    File.open('main.cpp', 'w') { |f| f.write(obj['src']) }
    File.open('cmd.sh', 'w') { |f| f.write(obj['cmd']) }
    safe_popen("./sandbox.sh 2>&1") { |line| out.write(line) }
  end

  # Returns the location. E.g: if the URL is "http://localhost.com/compile" then "compile" will be returned.
  def get_location(req)
    req.params['REQUEST_PATH'][1..-1]
  end

end


if ARGV.length != 2
  puts 'Usage ruby webserver.rb Host Port'
  exit
end


$host = ARGV[0]
$port = ARGV[1]


puts "Start listening to #{$host}:#{$port}"
h = Mongrel::HttpServer.new($host, $port)
h.register('/', SimpleHandler.new)
h.register('/Archive', Mongrel::DirHandler.new($archive))
puts "h.num_processors: #{h.num_processors}"
h.run.join

