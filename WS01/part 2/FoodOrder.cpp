#include "FoodOrder.h"
#include <limits>

#define COMMA ','

double g_taxrate = 0;
double g_dailydiscount = 0;

namespace seneca {
    // Helper function
    inline void ignore(std::istream& istr, const char delim) {
        istr.ignore(std::numeric_limits<std::streamsize>::max(), delim);
    }

    FoodOrder::FoodOrder() {}

    void FoodOrder::read(std::istream& istr) {
        if (istr.good()) {

            istr.get(m_customerName, CUSTOMER_NAME_LEN, COMMA);   // Delim is NOT extracted
            ignore(istr, COMMA);

            istr.get(m_description, DESCRIPTION_LEN, COMMA);
            ignore(istr, COMMA);

            istr >> m_price;
            ignore(istr, COMMA);

            char YN = 0;
            istr >> YN;
            ignore(istr, '\n');
            
            m_dailySpecial = YN == 'Y';
        }
    }

    void FoodOrder::display() const {
        static int COUNTER = 0;

        std::cout.width(2);
        std::cout << std::left << ++COUNTER << ". ";

        if (!m_customerName[0]) {
            std::cout << "No Order" << std::endl;
            return;
        }

        std::cout.width(10);
        std::cout << std::left << m_customerName << "|";

        std::cout.width(25);
        std::cout << std::left << m_description << "|";

        double taxedPrice = m_price + m_price * g_taxrate;
        std::cout.width(12);
        std::cout.precision(2);
        std::cout << std::left << std::fixed << taxedPrice << "|";

        if (m_dailySpecial) {
            std::cout.width(13);
            std::cout << std::right << taxedPrice - g_dailydiscount;
        }
        
        std::cout << std::endl;        
    }
}
