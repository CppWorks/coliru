#include <atomic>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>


typedef std::string RemoteId;


template<typename T>
struct RemoteObject : public std::enable_shared_from_this<T>
{
public:
    template<typename ...Args>
    static std::shared_ptr<T> Create(Args&& ...args)
    {
        auto result = std::make_shared<T>(std::forward<Args>(args)...);
        result->registerSelf();
        return result;
    }
    
    RemoteId getRemoteId() const { return mRemoteId; }
    
protected:
    RemoteObject(const RemoteId& inRemoteId) : mRemoteId(inRemoteId)
    {
    }
    
    ~RemoteObject()
    {
        this->unregisterSelf();
    }
    
    static RemoteId GetUniqueId()
    {
        static std::atomic<long> fId;
        long id = fId++;
        return std::to_string(id);
    }
    
private:    
    // noncopyable (maybe later define move operations)
    RemoteObject(const RemoteObject&) = delete;
    RemoteObject& operator=(const RemoteObject&) = delete;     
    
    void registerSelf()
    {
        std::lock_guard<std::mutex> lock(GetMutex());
        auto& objects = GetRegisteredObjects(lock);
        if (objects.count(getRemoteId()))
        {
            throw std::runtime_error("Already found");
        }
        objects.insert(std::make_pair(getRemoteId(), this->shared_from_this()));
    }
    
    void unregisterSelf()
    {
        std::lock_guard<std::mutex> lock(GetMutex());
        auto& objects = GetRegisteredObjects(lock);
        objects.erase(getRemoteId());
    }
    
    typedef std::map<RemoteId, std::weak_ptr<T>> Objects;
    
    static Objects& GetRegisteredObjects(std::lock_guard<std::mutex>&)
    {
        static std::map<RemoteId, std::weak_ptr<T>> fRegisteredObjects;
        return fRegisteredObjects;
    }

    static std::mutex& GetMutex()
    {
        static std::mutex fMutex;
        return fMutex;
    }
    
    RemoteId mRemoteId;
};


template<typename T>
struct ServerObject : RemoteObject<T>
{    
    ServerObject() : RemoteObject<T>(this->GetUniqueId()) {}
};

template<typename T>
struct ClientObject : RemoteObject<T>
{    
    // requires the remote id of the corresponding server-side object
    ClientObject(const RemoteId& inRemoteId) : RemoteObject<T>(inRemoteId) {}
};



//
// user code at the server side
//
namespace server {
struct Item : ServerObject<Item>
{
    Item(const std::string& inName) : mName(inName)
    {
    }
    
    std::string mName;
};
}


//
// user code at the client side
// 
namespace client {
struct Item : ClientObject<Item>
{
    Item(const RemoteId& inRemoteId) : ClientObject<Item>(inRemoteId)
    {
    }
};
}


int main()
{
    auto serverItem = server::Item::Create("a");
    auto clientItem = client::Item::Create(serverItem->getRemoteId());
}