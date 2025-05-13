#pragma once
#include <string>
#include <vector>
#include <memory>
#include "s3_object.hpp"

class User;
class Bucket;

class StorageStrategy {
public:
    virtual ~StorageStrategy() = default;
    virtual void saveBucket(const std::shared_ptr<Bucket>& bucket) = 0;
    virtual std::shared_ptr<Bucket> getBucket(const std::string& bucketName) = 0;
    virtual void deleteBucket(const std::string& bucketName) = 0;
    virtual void saveObject(const std::string& bucketName, const std::shared_ptr<IS3Object>& object) = 0;
    virtual std::shared_ptr<IS3Object> getObject(const std::string& bucketName, const std::string& objectKey) = 0;
    virtual void deleteObject(const std::string& bucketName, const std::string& objectKey) = 0;
    virtual std::vector<std::shared_ptr<Bucket>> listBuckets(const User& owner) = 0;
    virtual std::vector<std::shared_ptr<IS3Object>> listObjects(const std::string& bucketName) = 0;
}; 