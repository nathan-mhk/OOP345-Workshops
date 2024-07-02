/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-24
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#ifndef SENECA_FILE_H
#define SENECA_FILE_H

#include "Resource.h"
#include <string>

namespace seneca {
    class File : public Resource {
        std::string m_contents{};

    public:
        File(const std::string& fileName, const std::string& contents = "");
        
        void update_parent_path(const std::string& parentPath) override;
        NodeType type() const override;
        std::string path() const override;
        std::string name() const override;
        int count() const override;
        size_t size() const override;
    };
}

#endif
