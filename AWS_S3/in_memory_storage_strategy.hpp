#pragma once
#include "storage_strategy.hpp"
#include "bucket.hpp"
#include <unordered_map>

class InMemoryStorageStrategy : public StorageStrategy {
public:
    void saveBucket(const std::shared_ptr<Bucket>& bucket) override;
    std::shared_ptr<Bucket> getBucket(const std::string& bucketName) override;
    void deleteBucket(const std::string& bucketName) override;
    void saveObject(const std::string& bucketName, const std::shared_ptr<IS3Object>& object) override;
    std::shared_ptr<IS3Object> getObject(const std::string& bucketName, const std::string& objectKey) override;
    void deleteObject(const std::string& bucketName, const std::string& objectKey) override;
    std::vector<std::shared_ptr<Bucket>> listBuckets(const User& owner) override;
    std::vector<std::shared_ptr<IS3Object>> listObjects(const std::string& bucketName) override;

private:
    std::unordered_map<std::string, std::shared_ptr<Bucket>> buckets_;
}; 