echo -e '\n\n*** g++ 4.9 ***' && g++-4.9 --version && g++-4.9 -std=c++11 -O3 -Wall -Wextra -pedantic-errors -c main.cpp && echo 'ok compiled cleanly' || echo '*** not ok ***'
echo -e '\n\n*** g++ 4.8 ***' && g++-4.8 --version &&  g++-4.8 -std=c++11 -O3 -Wall -Wextra -pedantic-errors -c main.cpp && echo 'ok compiled cleanly' || echo '*** not ok (errors) ***'