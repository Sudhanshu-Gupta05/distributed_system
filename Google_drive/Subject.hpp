#pragma once
#include "Observer.hpp"
#include <vector>
#include <memory>

class Subject {
public:
    void attach(std::shared_ptr<Observer> observer);
    void detach(std::shared_ptr<Observer> observer);
    void notifyObservers(const std::string& message);

private:
    std::vector<std::shared_ptr<Observer>> observers;
}; 