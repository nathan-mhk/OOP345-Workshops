/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-05-12
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider
*/

#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H

#include <iostream>

#define CUSTOMER_NAME_LEN 10

extern double g_taxrate;
extern double g_dailydiscount;

namespace seneca {
    class FoodOrder {
        char m_customerName[CUSTOMER_NAME_LEN] {};
        char* m_description {};

        double m_price {};
        bool m_dailySpecial {};

        void copy(const FoodOrder& that);

    public:
        FoodOrder();

        // Rule of 3
        ~FoodOrder();
        FoodOrder(const FoodOrder& that);
        FoodOrder& operator=(const FoodOrder& that);

        void read(std::istream& istr);
        void display() const;
    };
}

#endif
