#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class EventListener {
public:
    virtual ~EventListener() = default;
    virtual void update(const std::string& eventType, const std::string& message) = 0;
};

class NotificationService {
public:
    explicit NotificationService(const std::vector<std::string>& eventTypes);
    void subscribe(const std::string& eventType, EventListener* listener);
    void unsubscribe(const std::string& eventType, EventListener* listener);
    void notify(const std::string& eventType, const std::string& message);

private:
    std::unordered_map<std::string, std::vector<EventListener*>> listeners_;
}; 