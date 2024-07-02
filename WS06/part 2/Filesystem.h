/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-24
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

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