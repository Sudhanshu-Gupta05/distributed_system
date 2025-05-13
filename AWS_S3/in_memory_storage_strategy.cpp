#include "in_memory_storage_strategy.hpp"
#include <algorithm>

void InMemoryStorageStrategy::saveBucket(const std::shared_ptr<Bucket>& bucket) {
    buckets_[bucket->getName()] = bucket;
}

std::shared_ptr<Bucket> InMemoryStorageStrategy::getBucket(const std::string& bucketName) {
    auto it = buckets_.find(bucketName);
    if (it != buckets_.end()) {
        return it->second;
    }
    return nullptr;
}

void InMemoryStorageStrategy::deleteBucket(const std::string& bucketName) {
    buckets_.erase(bucketName);
}

void InMemoryStorageStrategy::saveObject(const std::string& bucketName, 
                                       const std::shared_ptr<IS3Object>& object) {
    auto bucket = getBucket(bucketName);
    if (bucket) {
        bucket->addObject(object->getKey(), object->getData());
    }
}

std::shared_ptr<IS3Object> InMemoryStorageStrategy::getObject(const std::string& bucketName, 
                                                            const std::string& objectKey) {
    auto bucket = getBucket(bucketName);
    if (bucket) {
        return bucket->getObject(objectKey);
    }
    return nullptr;
}

void InMemoryStorageStrategy::deleteObject(const std::string& bucketName, 
                                         const std::string& objectKey) {
    auto bucket = getBucket(bucketName);
    if (bucket) {
        bucket->deleteObject(objectKey);
    }
}

std::vector<std::shared_ptr<Bucket>> InMemoryStorageStrategy::listBuckets(const User& owner) {
    std::vector<std::shared_ptr<Bucket>> result;
    for (const auto& [name, bucket] : buckets_) {
        if (bucket->getOwner().getUserId() == owner.getUserId()) {
            result.push_back(bucket);
        }
    }
    return result;
}

std::vector<std::shared_ptr<IS3Object>> InMemoryStorageStrategy::listObjects(
    const std::string& bucketName) {
    auto bucket = getBucket(bucketName);
    if (bucket) {
        return bucket->listObjects();
    }
    return {};
} 