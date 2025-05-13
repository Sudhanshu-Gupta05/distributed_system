#include "storage_service.hpp"
#include "in_memory_storage_strategy.hpp"
#include "s3_object.hpp"
#include "notification_service.hpp"
#include <iostream>
#include <string>

class User : public EventListener {
public:
    User(const std::string& userId, const std::string& name, const std::string& password)
        : userId_(userId), name_(name), password_(password) {}

    const std::string& getUserId() const { return userId_; }
    const std::string& getName() const { return name_; }

    void update(const std::string& eventType, const std::string& message) override {
        std::cout << "User " << name_ << " received " << eventType 
                  << " notification: " << message << std::endl;
    }

private:
    std::string userId_;
    std::string name_;
    std::string password_;
};

int main() {
    // Initialize storage service with in-memory strategy
    auto strategy = std::make_unique<InMemoryStorageStrategy>();
    auto& storageService = StorageService::getInstance(strategy.get());

    // Create a user
    User user("user1", "Alice", "password1");

    // Subscribe to notifications
    storageService.subscribe("upload", &user);
    storageService.subscribe("delete", &user);

    // Create a bucket
    storageService.createBucket("my-bucket", user);

    // Upload an object
    std::string data = "Hello, S3!";
    std::vector<uint8_t> dataVec(data.begin(), data.end());
    storageService.putObject("my-bucket", "my-object", dataVec);

    // Create a versioned object
    auto object = std::make_shared<S3Object>("versioned-object", dataVec);
    auto versionedObject = std::make_shared<VersionedObjectDecorator>(object);
    
    // Update the versioned object
    std::string newData = "Updated content";
    std::vector<uint8_t> newDataVec(newData.begin(), newData.end());
    auto updatedObject = std::make_shared<S3Object>("versioned-object", newDataVec);
    versionedObject = std::make_shared<VersionedObjectDecorator>(updatedObject);

    // Create an access-controlled object
    auto accessControlledObject = std::make_shared<AccessControlledObjectDecorator>(object);
    accessControlledObject->grantReadPermission("user1");
    accessControlledObject->grantWritePermission("user1");

    // List objects
    auto objects = storageService.listObjects("my-bucket");
    std::cout << "Objects in bucket:" << std::endl;
    for (const auto& obj : objects) {
        std::cout << "- " << obj->getKey() << std::endl;
    }

    // Download an object
    auto downloadedObject = storageService.getObject("my-bucket", "my-object");
    if (downloadedObject) {
        std::string downloadedData(downloadedObject->getData().begin(), 
                                 downloadedObject->getData().end());
        std::cout << "Downloaded data: " << downloadedData << std::endl;
    }

    // Delete an object
    storageService.deleteObject("my-bucket", "my-object");

    // List buckets
    auto buckets = storageService.listBuckets(user);
    std::cout << "Buckets owned by " << user.getName() << ":" << std::endl;
    for (const auto& bucketName : buckets) {
        std::cout << "- " << bucketName << std::endl;
    }

    return 0;
} 