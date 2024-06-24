#ifndef SENECA_DIRECTORY_H
#define SENECA_DIRECTORY_H

#include "Resource.h"
#include <vector>
#include <string>

namespace seneca {
    class Directory : public Resource {
        std::vector<Resource*> m_contents{};

    public:
        Directory(const std::string& dirName);

        void update_parent_path(const std::string& parentPath) override;
        NodeType type() const override;
        std::string path() const override;
        std::string name() const override;
        int count() const override;
        size_t size() const override;

        Directory& operator+=(Resource*);

        Resource* find(const std::string& name, const std::vector<OpFlags>& flags = {});

        ~Directory() {
            for (Resource* content : m_contents) {
                delete content;
            }
        }

        // Disallow copy/move operations
        Directory(const Directory&) = delete;
        Directory& operator=(const Directory&) = delete;
        Directory(Directory&&) = delete;
        Directory& operator=(Directory&&) = delete;
    };
}

#endif
