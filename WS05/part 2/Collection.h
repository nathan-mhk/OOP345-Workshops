/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-08
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <string>

namespace seneca {
    template <typename T>
    class Collection {
        std::string m_name{};
        T* m_items{};
        size_t m_size{};
        void (*m_observer) (const Collection<T>&, const T&) {nullptr};

    public:

        Collection(const std::string& name) : m_name(name), m_items(nullptr), m_size(0), m_observer(nullptr) {};

        Collection(const Collection& src) = delete;
        Collection& operator=(const Collection& src) = delete;

        ~Collection() { 
            delete[] m_items;
            m_items = nullptr;

            m_name = "";
            m_size = 0;
            m_observer = nullptr;
        };

        const std::string& name() const { return m_name; };

        size_t size() const { return m_size; };

        void setObserver(void (*observer) (const Collection<T>&, const T&)) {
            m_observer = observer;
        };

        Collection<T>& operator+=(const T& item) {
            // Check if `item` exists in `m_items`
            if ((*this)[item.title()]) return *this;

            // Create a new container with size + 1
            T* temp = new T[m_size + 1];

            for (size_t i = 0; i < m_size; i++) {
                temp[i] = m_items[i];
            }

            temp[m_size++] = item;

            delete[] m_items;
            m_items = temp;

            if (m_observer) {
                m_observer(*this, item);
            }

            return *this;
        };

        T& operator[](size_t idx) const {
            if (idx >= m_size) {
                throw std::out_of_range(
                    "Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_size) + "] items."
                );
            }
            return m_items[idx];
        };

        T* operator[](const std::string& title) const {
            for (size_t i = 0; i < m_size; i++) {
                if (m_items[i].title() == title) return &m_items[i];
            }
            return nullptr;
        };

        friend std::ostream& operator<<(std::ostream& ostr, const Collection<T>& collection) {
            for (size_t i = 0; i < collection.size(); ++i) {
                ostr << collection[i];
            }
            return ostr;
        };
    };
}

#endif
