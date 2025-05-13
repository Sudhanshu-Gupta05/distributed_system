#pragma once
#include <string>
#include <vector>
#include <memory>
#include "storage_strategy.hpp"
#include "s3_object.hpp"

class NotificationService;
class EventListener;
class User;
class Bucket;

class StorageService {
public:
    static StorageService& getInstance(StorageStrategy* strategy);
    
    void subscribe(const std::string& eventType, EventListener* listener);
    void unsubscribe(const std::string& eventType, EventListener* listener);
    
    bool createBucket(const std::string& name, const User& owner);
    bool deleteBucket(const std::string& name);
    std::vector<std::string> listBuckets(const User& owner);
    
    bool putObject(const std::string& bucketName, const std::string& key, 
                  const std::vector<uint8_t>& data);
    std::shared_ptr<IS3Object> getObject(const std::string& bucketName, 
                                       const std::string& key);
    bool deleteObject(const std::string& bucketName, const std::string& key);
    std::vector<std::shared_ptr<IS3Object>> listObjects(const std::string& bucketName);

private:
    StorageService(StorageStrategy* strategy);
    StorageStrategy* storageStrategy_;
    std::unique_ptr<NotificationService> notificationService_;
}; 