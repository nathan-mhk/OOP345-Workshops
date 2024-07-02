/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-24
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#ifndef SENECA_DIRECTORY_H
#define SENECA_DIRECTORY_H

#include "Resource.h"
#include <vector>
#include <string>
#include <iostream>

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
        void remove(const std::string& name, const std::vector<OpFlags>& flags = {});

        void display(std::ostream& ostr, const std::vector<FormatFlags>& flags = {}) const;

        ~Directory();

        // Disallow copy/move operations
        Directory(const Directory&) = delete;
        Directory& operator=(const Directory&) = delete;
        Directory(Directory&&) = delete;
        Directory& operator=(Directory&&) = delete;
    };
}

#endif
