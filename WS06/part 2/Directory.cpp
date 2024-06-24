#include "Directory.h"

namespace seneca {
    Directory::Directory(const std::string& dirName) { m_name = dirName; }

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
            if (content->name() == name) return content;

            if (recursive && content->type() == NodeType::DIR) {
                Resource* found = dynamic_cast<Directory*>(content)->find(name, flags);
                if (found) return found;
            }
        }
        return nullptr;
    }

    void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags) {
        for (std::vector<Resource*>::iterator itr = m_contents.begin(); itr != m_contents.end(); ++itr) {
            if ((*itr)->name() != name) continue;

            // Name matches
            if ((*itr)->type() == NodeType::DIR) {
                if (flags.size() <= 0 || flags[0] != OpFlags::RECURSIVE) {
                    throw std::invalid_argument(std::string(name) + " is a directory. Pass the recursive flag to delete directories.");
                }
                // Invoke Directory::~Directory();
                Directory* dir = dynamic_cast<Directory*>(*itr);
                delete dir;
            } else {
                delete *itr;
            }
            // Remove from the vector
            m_contents.erase(itr);
            return;
        }
        throw std::string(name) + " does not exist in " + m_name;
    }

    void Directory::display(std::ostream& ostr, const std::vector<FormatFlags>& flags) const {
        ostr << "Total size: " << size() << " bytes\n";

        bool detailed = flags.size() > 0 && flags[0] == FormatFlags::LONG;
        for (const Resource* content : m_contents) {
            bool isDir = content->type() == NodeType::DIR;
            
            if (isDir) {
                ostr << "D | ";
            } else {
                ostr << "F | ";
            }

            ostr.width(15);
            ostr << std::left << content->name() << " |";

            if (detailed) {
                ostr << " ";
                if (isDir) {
                    ostr.width(2);
                    ostr << std::right << content->count() << " | ";
                } else {
                    ostr << "   | ";
                }
                ostr.width(10);
                ostr << std::right << (std::to_string(content->size()) + " bytes") << " | ";
            }
            ostr << std::endl;
        }
    }

    Directory::~Directory() {
        for (Resource*& content : m_contents) {
            delete content;
            content = nullptr;
        }
        m_contents.clear();
    }
}
