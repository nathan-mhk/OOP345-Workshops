/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-07-14
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <memory>
#include <string>
#include <fstream>  // #include here as it was not #included in w8_p2.cpp

namespace seneca {
    static const size_t MAX_SIZE = 20;

    enum class Err_Status {
        Err_Success,
        Err_NotFound,
        Err_OutOfMemory,
    };

    template<typename T>
    class Database {
        static std::shared_ptr<Database<T>> m_instance;

        size_t m_size{};
        std::string m_keys[MAX_SIZE]{};
        T m_values[MAX_SIZE]{};
        std::string m_fileName{};

        Database(const std::string& fileName);

        void encryptDecrypt(T& value);

    public:
        static std::shared_ptr<Database<T>> getInstance(const std::string& fileName);
        Err_Status GetValue(const std::string& key, T& value) const;
        Err_Status SetValue(const std::string& key, const T& value);
        ~Database();

    };
}

#include "Database.tpp"

#endif
