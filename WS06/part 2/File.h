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
