/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-07-14
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#include "Database.h"
#include <iostream>

namespace seneca {
    template<typename T>
    std::shared_ptr<Database<T>> Database<T>::m_instance{};

    template<typename T>
    Database<T>::Database(const std::string& fileName) : m_fileName(fileName) {
        std::cout << "[" << this << "] Database(const std::string&)" << std::endl;

        std::ifstream file(m_fileName, std::ios::in);
        do {
            std::string key{};
            file >> key;

            // Replace _ with space
            for (char& c : key) { 
                if (c == '_') {
                    c = ' ';
                }
            }
            
            m_keys[m_size] = key;

            T value{};
            file >> value;
            encryptDecrypt(value);
            m_values[m_size] = value;
            
        } while (++m_size < MAX_SIZE && !file.eof());

        file.close();
    }

    template<typename T>
    void Database<T>::encryptDecrypt(T& value) {};

    template<>
    void Database<std::string>::encryptDecrypt(std::string& value) {
        const char secret[]{ "secret encryption key" };

        for (size_t i = 0; i < value.length(); ++i) {
            for (size_t j = 0; j < sizeof(secret); ++j) {
                value[i] ^= secret[j];
            }
        }
    }

    template<>
    void Database<long long>::encryptDecrypt(long long& value) {
        const char secret[]{ "super secret encryption key" };

        char* valStr = reinterpret_cast<char*>(&value);

        for (size_t i = 0; i < sizeof(value); ++i) {
            for (size_t j = 0; j < sizeof(secret); ++j) {
                valStr[i] ^= secret[j];
            }
        }
    }

    template<typename T>
    std::shared_ptr<Database<T>> Database<T>::getInstance(const std::string& fileName) {
        if (!m_instance) {
            m_instance = std::shared_ptr<Database>(new Database(fileName));
        }
        return m_instance;
    }

    template<typename T>
    Err_Status Database<T>::GetValue(const std::string& key, T& value) const {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_keys[i] == key) {
                value = m_values[i];
                return Err_Status::Err_Success;
            }
        }
        return Err_Status::Err_NotFound;
    }

    template<typename T>
    Err_Status Database<T>::SetValue(const std::string& key, const T& value) {
        if (m_size < MAX_SIZE) {
            m_keys[m_size] = key;
            m_values[m_size] = value;
            ++m_size;

            return Err_Status::Err_Success;
        }
        return Err_Status::Err_OutOfMemory;
    }

    template<typename T>
    Database<T>::~Database() {
        std::cout << "[" << m_instance << "] ~Database()" << std::endl;

        std::ofstream file(m_fileName + ".bkp.txt", std::ios::out | std::ios::trunc);
        for (size_t i = 0; i < m_size; ++i) {
            file.width(25);
            file << std::left << m_keys[i];

            encryptDecrypt(m_values[i]);
            file << " -> " << m_values[i] << std::endl;
        }
        file.close();
    }
}
