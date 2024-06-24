#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H

#include "Directory.h"
#include <string>

namespace seneca {
    class Filesystem {
        Directory* m_root{};
        Directory* m_current{};

    public:
        Filesystem(const std::string& fileName, const std::string& rootName = "");

        // Disallow copying operations
        Filesystem(const Filesystem&) = delete;
        Filesystem& operator=(const Filesystem&) = delete;

        // Allow moving operations
        Filesystem(Filesystem&& other);
        Filesystem& operator=(Filesystem&& other);

        Filesystem& operator+=(Resource* resource);

        Directory* change_directory(const std::string& dirName = "");

        Directory* get_current_directory() const;

        ~Filesystem();
    };
}

#endif