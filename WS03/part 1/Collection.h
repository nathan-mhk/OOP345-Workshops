/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-05-24
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider
*/

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include "Book.h"

namespace seneca {
    // Helper Function
    template<typename T>
    inline void printItem(std::ostream& os, const T& item) {
        os << item;
    }

    // Template Specialization
    template<>
    inline void printItem(std::ostream& os, const double& item) {
        os.precision(1);
        os << std::fixed << item;
    }
    
    template<typename T, unsigned int C>
    class Collection {
        T m_items[C]{};
        unsigned int m_capacity{C};
        unsigned int m_size{};

        // Class Memebers
        static T m_smallestItem;
        static T m_largestItem;
    
    protected:
        // Instance Members
        void setSmallestItem(const T& item) {
            if (item < m_smallestItem)
                m_smallestItem = item;
        };

        void setLargestItem(const T& item) {
            if (item > m_largestItem)
                m_largestItem = item;
        };
    
    public:
        // Class Members
        static T getSmallestItem() { return m_smallestItem; };
        static T getLargestItem() { return m_largestItem; };

        // Instance Members
        unsigned int size() const { return m_size; };
        unsigned int capacity() const { return m_capacity; };

        bool operator+=(const T& item) {
            if (m_size == m_capacity) return false;

            setSmallestItem(item);
            setLargestItem(item);

            m_items[m_size++] = item;
            return true;
        };

        void print(std::ostream& os) const {
            os << "[";

            for (unsigned int i = 0; i < m_size; ++i) {
                printItem<T>(os, m_items[i]);
                if (i < m_size - 1)
                    os << ",";
            }

            os << "]" << std::endl;
        };
    };

    template<typename T, unsigned int C>
    T Collection<T, C>::m_smallestItem{9999};

    template<typename T, unsigned int C>
    T Collection<T, C>::m_largestItem{-9999};

    // Template Specialization
    template<>
    Book Collection<Book, 10>::m_smallestItem{"", 1, 10000};

    template<>
    Book Collection<Book, 10>::m_largestItem{"", 10000, 1};
}

#endif // SENECA_COLLECTION_H
