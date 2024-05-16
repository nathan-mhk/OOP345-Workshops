/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-05-12
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider
*/

#include "FoodOrder.h"
#include <cstring>
#include <string>
#include <limits>

#define COMMA ','

double g_taxrate = 0;
double g_dailydiscount = 0;

namespace seneca {
    // Helper function
    inline void ignore(std::istream& istr, const char delim) {
        istr.ignore(std::numeric_limits<std::streamsize>::max(), delim);
    }

    void FoodOrder::copy(const FoodOrder& that) {
        // m_customerName is not dynamically allocated. Length is fixed as well
        std::strcpy(m_customerName, that.m_customerName);

        delete[] m_description;
        m_description = new char[std::strlen(that.m_description) + 1];
        std::strcpy(m_description, that.m_description);

        m_price = that.m_price;
        m_dailySpecial = that.m_dailySpecial;
    }

    FoodOrder::FoodOrder() {}

    FoodOrder::~FoodOrder() {
        delete[] m_description;
        m_description = nullptr;
    }

    FoodOrder::FoodOrder(const FoodOrder& that) {
        copy(that);
    }

    FoodOrder& FoodOrder::operator=(const FoodOrder& that) {
        // Prevent self-assignment
        if (this != &that)
            copy(that);
            
        return *this;
    }

    void FoodOrder::read(std::istream& istr) {
        if (istr.good()) {

            istr.get(m_customerName, CUSTOMER_NAME_LEN, COMMA);   // Delim is NOT extracted for get()
            ignore(istr, COMMA);

            // Allows a C-style null-terminated string of any length
            std::string description;
            std::getline(istr, description, COMMA);    // Delim IS extracted in getline()

            delete[] m_description;
            m_description = new char[description.length() + 1];
            std::strcpy(m_description, description.c_str());

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
