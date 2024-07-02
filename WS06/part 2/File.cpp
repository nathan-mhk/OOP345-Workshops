/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-24
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#include "File.h"

namespace seneca {
    File::File(const std::string& fileName, const std::string& contents)
        : m_contents(contents) { m_name = fileName; }

    void File::update_parent_path(const std::string& parentPath) {
        m_parent_path = parentPath;
    }

    NodeType File::type() const { return NodeType::FILE; }

    std::string File::path() const { return m_parent_path + m_name; }

    std::string File::name() const { return m_name; }

    int File::count() const { return -1; }

    size_t File::size() const { return m_contents.size(); }
}
