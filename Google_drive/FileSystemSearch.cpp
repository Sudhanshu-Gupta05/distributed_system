#include "FileSystemSearch.hpp"
#include "Folder.hpp"

FileSystemComponent* FileSystemSearch::search(FileSystemComponent* component, const std::string& name) {
    if (component->getName() == name) {
        return component;
    }

    if (auto folder = dynamic_cast<Folder*>(component)) {
        for (const auto& [childName, child] : folder->getChildren()) {
            if (auto found = search(child, name)) {
                return found;
            }
        }
    }
    return nullptr;
} 