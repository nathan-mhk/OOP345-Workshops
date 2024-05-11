#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H

#include <iostream>

#define CUSTOMER_NAME_LEN 10
#define DESCRIPTION_LEN 25

extern double g_taxrate;
extern double g_dailydiscount;

namespace seneca {
    class FoodOrder {
        char m_customerName[CUSTOMER_NAME_LEN] {};
        char m_description[DESCRIPTION_LEN] {};

        double m_price {};
        bool m_dailySpecial {};

    public:
        FoodOrder();
        void read(std::istream& istr);
        void display() const;
    };
}

#endif
