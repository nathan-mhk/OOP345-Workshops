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

namespace seneca {
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
        void setSmallestItem(const T& item);

        void setLargestItem(const T& item);
    
    public:
        // Class Members
        static T getSmallestItem();
        static T getLargestItem();

        // Instance Members
        unsigned int size() const;
        unsigned int capacity() const;

        bool operator+=(const T& item);

        void print(std::ostream& os) const;
    };
}

#include "Collection.tpp"

#endif // SENECA_COLLECTION_H
