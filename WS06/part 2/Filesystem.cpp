/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-24
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#include "Filesystem.h"
#include "File.h"
#include <fstream>
#include <vector>

namespace seneca {
    // Helper Functions
    std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \r\n\t");
        size_t last = str.find_last_not_of(" \r\n\t");

        if (start == std::string::npos) start = 0;
        if (last == std::string::npos) last = str.length() - 1;

        // [start, last - start + 1) == [start, last - start]
        return str.substr(start, last - start + 1);
    }

    Filesystem::Filesystem(const std::string& fileName, const std::string& rootName) {
        m_root = new Directory(rootName);
        m_current = m_root;

        std::ifstream file(fileName);
        if (!file) {
            delete m_root;
            m_root = nullptr;
            throw "Cannot open file.";
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line == "") {
                continue;
            }

            size_t pos = line.find_first_of('|');
            bool isDir = pos == std::string::npos;

            std::string dirName{};
            if (isDir) {
                // Current line represents a directory
                dirName = trim(line);
            } else {
                // Current line represents a file
                dirName = trim(line.substr(0, pos));
            }

            // Construct the sub-paths
            std::vector<std::string> paths;
            size_t start = 0;
            while (start < dirName.length()) {
                size_t end = dirName.find_first_of('/', start);
                if (end == std::string::npos) {
                    // The last part of a path, should be the file name
                    paths.push_back(trim(dirName.substr(start)));
                    break;
                }
                // + 1 to include the `/` char ~~~~~~~~~~~~~~~~~~~~~~~~~~v
                paths.push_back(trim(dirName.substr(start, end - start + 1)));
                start = end + 1;
            }

            // Add each sub-path/file into the file system
            for (const std::string& path : paths) {
                Resource* res = m_current->find(path);

                if (res) {
                    // Resource exists
                    if (res->type() == NodeType::DIR) {
                        // Resource is a directory
                        m_current = dynamic_cast<Directory*>(res);
                    } else {
                        // Resource is a file
                        throw std::string("File ") + path + " already exists!";
                    }
                } else {
                    // Resource DNE
                    //           v~~~ Parts before the last part of FILE_PATH are directories
                    if (isDir || &path != &paths.back()) {
                        // Resource is a directory
                        Directory* newDir = new Directory(path);

                        newDir->update_parent_path(m_current->path());

                        *m_current += newDir;
                        m_current = newDir;
                    } else {
                        // Resource is a file
                        // + 1 to exclude the `|` char ~~~~~~~~~~~~~~~~~~~~~~~v
                        File* newFile = new File(path, trim(line.substr(pos + 1)));

                        newFile->update_parent_path(m_current->path());

                        *m_current += newFile;
                    }
                }
            }
            m_current = m_root;
        }
    }

    Filesystem::Filesystem(Filesystem&& other) {
        m_root = other.m_root;
        m_current = other.m_current;
        other.m_root = nullptr;
        other.m_current = nullptr;
    }

    Filesystem& Filesystem::operator=(Filesystem&& other) {
        if (this != &other) {
            delete m_root;
            m_root = other.m_root;
            m_current = other.m_current;
            other.m_root = nullptr;
            other.m_current = nullptr;
        }
        return *this;
    }

    Filesystem& Filesystem::operator+=(Resource* resource) {
        *m_current += resource;
        return *this;
    }

    Directory* Filesystem::change_directory(const std::string& dirName) {
        if (dirName == "") {
            m_current = m_root;
            return m_current;
        }
        Resource* res = m_current->find(dirName);
        if (!res || res->type() != NodeType::DIR) {
            throw std::invalid_argument(std::string("Cannot change directory! ") + dirName + " not found!");
        } else {
            m_current = dynamic_cast<Directory*>(res);
            return m_current;
        }
    }

    Directory* Filesystem::get_current_directory() const { return m_current; }

    Filesystem::~Filesystem() {
        delete m_root;
        m_root = nullptr;
        m_current = nullptr;
    }
}