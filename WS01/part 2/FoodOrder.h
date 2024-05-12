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
