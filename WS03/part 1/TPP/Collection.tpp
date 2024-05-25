/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-05-24
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider
*/

#ifndef SENECA_COLLECTION_TPP
#define SENECA_COLLECTION_TPP

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
    
    // Instance Members
    template<typename T, unsigned int C>
    void Collection<T, C>::setSmallestItem(const T& item) {
        if (item < m_smallestItem)
            m_smallestItem = item;
    }

    template<typename T, unsigned int C>
    void Collection<T, C>::setLargestItem(const T& item) {
        if (item > m_largestItem)
            m_largestItem = item;
    }
    
    // Class Members
    template<typename T, unsigned int C>
    T Collection<T, C>::getSmallestItem() { return m_smallestItem; }

    template<typename T, unsigned int C>
    T Collection<T, C>::getLargestItem() { return m_largestItem; }

    // Instance Members
    template<typename T, unsigned int C>
    unsigned int Collection<T, C>::size() const { return m_size; }

    template<typename T, unsigned int C>
    unsigned int Collection<T, C>::capacity() const { return m_capacity; }

    template<typename T, unsigned int C>
    bool Collection<T, C>::operator+=(const T& item) {
        if (m_size == m_capacity) return false;

        setSmallestItem(item);
        setLargestItem(item);

        m_items[m_size++] = item;
        return true;
    }

    template<typename T, unsigned int C>
    void Collection<T, C>::print(std::ostream& os) const {
        os << "[";

        for (unsigned int i = 0; i < m_size; ++i) {
            printItem<T>(os, m_items[i]);
            if (i < m_size - 1)
                os << ",";
        }

        os << "]" << std::endl;
    }

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

#endif // SENECA_COLLECTION_TPP
