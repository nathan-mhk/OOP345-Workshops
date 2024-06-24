#include "Directory.h"

namespace seneca {
    Directory::Directory(const std::string& dirName) {
        m_name = dirName;
    }

    void Directory::update_parent_path(const std::string& parentPath) {
        m_parent_path = parentPath;
        for (Resource*& content : m_contents) {
            content->update_parent_path(path());
        }
    }

    NodeType Directory::type() const { return NodeType::DIR; }

    std::string Directory::path() const { return m_parent_path + m_name; }

    std::string Directory::name() const { return m_name; }

    int Directory::count() const { return m_contents.size(); }

    size_t Directory::size() const {
        size_t total = 0u;
        for (const Resource* content : m_contents) {
            total += content->size();
        }
        return total;
    }

    Directory& Directory::operator+=(Resource* resource) {
        for (const Resource* content : m_contents) {
            if (content->name() == resource->name()) {
                throw "Resource exists in the directory.";
            }
        }
        m_contents.push_back(resource);
        resource->update_parent_path(path());

        return *this;
    }

    Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags) {
        bool recursive = flags.size() > 0 && flags[0] == OpFlags::RECURSIVE;

        for (Resource* content : m_contents) {
            if (content->name() == name) {
                return content;
            }
            if (content->type() == NodeType::DIR && recursive) {
                Resource* found = dynamic_cast<Directory*>(content)->find(name, flags);
                if (found) {
                    return found;
                }
            }
        }
        return nullptr;
    }
}
