/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-05-25
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider
*/

#ifndef SENECA_ORDEREDCOLLECTION_H
#define SENECA_ORDEREDCOLLECTION_H

namespace seneca {
    template<typename T>
    class OrderedCollection : public Collection<T, 72> {

    public:
        void operator+=(const T& item) {
            unsigned int insertIndex = this->size();

            if (insertIndex >= this->capacity()) return;

            // Items must be inserted somewhere in the array
            this->incrSize();

            this->setSmallestItem(item);
            this->setLargestItem(item);

            // Ascending Order
            // Iterating backwards to copy && insert in one pass
            for (; insertIndex >= 0; --insertIndex) {
                //                            this->operator[]()
                if (insertIndex > 0 && item < (*this)[insertIndex - 1]) {
                    (*this)[insertIndex] = (*this)[insertIndex - 1];
                } else {
                    (*this)[insertIndex] = item;
                    break;
                }
            }
        }
    };
}

#endif
