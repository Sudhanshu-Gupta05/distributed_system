#include "notification_service.hpp"
#include <algorithm>

NotificationService::NotificationService(const std::vector<std::string>& eventTypes) {
    for (const auto& eventType : eventTypes) {
        listeners_[eventType] = std::vector<EventListener*>();
    }
}

void NotificationService::subscribe(const std::string& eventType, EventListener* listener) {
    auto it = listeners_.find(eventType);
    if (it != listeners_.end()) {
        it->second.push_back(listener);
    }
}

void NotificationService::unsubscribe(const std::string& eventType, EventListener* listener) {
    auto it = listeners_.find(eventType);
    if (it != listeners_.end()) {
        auto& listeners = it->second;
        listeners.erase(
            std::remove(listeners.begin(), listeners.end(), listener),
            listeners.end()
        );
    }
}

void NotificationService::notify(const std::string& eventType, const std::string& message) {
    auto it = listeners_.find(eventType);
    if (it != listeners_.end()) {
        for (auto listener : it->second) {
            listener->update(eventType, message);
        }
    }
} 