/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-07-14
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#include "Database.h"
#include <fstream>
#include <iostream>

namespace seneca {
    std::shared_ptr<Database> Database::m_instance{};

    Database::Database(const std::string& fileName) : m_fileName(fileName) {
        std::cout << "[" << this << "] Database(const std::string&)" << std::endl;

        std::ifstream file(m_fileName);
        do {
            std::string key{};
            file >> key >> m_values[m_size];

            // Replace _ with space
            for (char& c : key) { 
                if (c == '_') {
                    c = ' ';
                }
            }

            m_keys[m_size] = key;
            
        } while (++m_size < MAX_SIZE && !file.eof());
    }

    std::shared_ptr<Database> Database::getInstance(const std::string& fileName) {
        if (!m_instance) {
            m_instance = std::shared_ptr<Database>(new Database(fileName));
        }
        return m_instance;
    }

    Err_Status Database::GetValue(const std::string& key, std::string& value) const {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_keys[i] == key) {
                value = m_values[i];
                return Err_Status::Err_Success;
            }
        }
        return Err_Status::Err_NotFound;
    }

    Err_Status Database::SetValue(const std::string& key, const std::string& value) {
        if (m_size < MAX_SIZE) {
            m_keys[m_size] = key;
            m_values[m_size] = value;
            ++m_size;

            return Err_Status::Err_Success;
        }
        return Err_Status::Err_OutOfMemory;
    }

    Database::~Database() {
        std::cout << "[" << m_instance << "] ~Database()" << std::endl;

        std::ofstream file(m_fileName + ".bkp.txt");
        for (size_t i = 0; i < m_size; ++i) {
            file.width(20);
            file << std::left << m_keys[i];

            file << " -> " << m_values[i] << std::endl;
        }
    }
}
