#include "storage_service.hpp"
#include "notification_service.hpp"
#include <stdexcept>

StorageService& StorageService::getInstance(StorageStrategy* strategy) {
    static StorageService instance(strategy);
    return instance;
}

StorageService::StorageService(StorageStrategy* strategy)
    : storageStrategy_(strategy) {
    std::vector<std::string> eventTypes = {"upload", "delete"};
    notificationService_ = std::make_unique<NotificationService>(eventTypes);
}

void StorageService::subscribe(const std::string& eventType, EventListener* listener) {
    notificationService_->subscribe(eventType, listener);
}

void StorageService::unsubscribe(const std::string& eventType, EventListener* listener) {
    notificationService_->unsubscribe(eventType, listener);
}

bool StorageService::createBucket(const std::string& name, const User& owner) {
    auto bucket = std::make_shared<Bucket>(name, owner);
    storageStrategy_->saveBucket(bucket);
    return true;
}

bool StorageService::deleteBucket(const std::string& name) {
    storageStrategy_->deleteBucket(name);
    return true;
}

std::vector<std::string> StorageService::listBuckets(const User& owner) {
    auto buckets = storageStrategy_->listBuckets(owner);
    std::vector<std::string> bucketNames;
    bucketNames.reserve(buckets.size());
    for (const auto& bucket : buckets) {
        bucketNames.push_back(bucket->getName());
    }
    return bucketNames;
}

bool StorageService::putObject(const std::string& bucketName, const std::string& key, 
                             const std::vector<uint8_t>& data) {
    auto object = std::make_shared<S3Object>(key, data);
    storageStrategy_->saveObject(bucketName, object);
    notificationService_->notify("upload", "Object uploaded: " + key);
    return true;
}

std::shared_ptr<IS3Object> StorageService::getObject(const std::string& bucketName, 
                                                   const std::string& key) {
    return storageStrategy_->getObject(bucketName, key);
}

bool StorageService::deleteObject(const std::string& bucketName, const std::string& key) {
    storageStrategy_->deleteObject(bucketName, key);
    notificationService_->notify("delete", "Object deleted: " + key);
    return true;
}

std::vector<std::shared_ptr<IS3Object>> StorageService::listObjects(const std::string& bucketName) {
    return storageStrategy_->listObjects(bucketName);
} 