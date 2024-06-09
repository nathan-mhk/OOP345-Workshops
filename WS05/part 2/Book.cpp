/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-08
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#include "Book.h"

namespace seneca {
    // Helper Functions
    std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \r\n\t");
        size_t last = str.find_last_not_of(" \r\n\t");

        if (start == std::string::npos) start = 0;
        if (last == std::string::npos) last = str.length() - 1;

        // [start, last - start + 1) == [start, last - start]
        return str.substr(start, last - start + 1);
    }

    Book::Book(const std::string& strBook) {
        /**
         * Format:
         * AUTHOR,TITLE,COUNTRY,PRICE,YEAR,DESCRIPTION
         */
        // AUTHOR
        size_t start = 0;
        size_t end = strBook.find(',');
        m_author = trim(strBook.substr(start, end - start));

        // TITLE
        start = end + 1;
        end = strBook.find(',', start);
        m_title = trim(strBook.substr(start, end - start));

        // COUNTRY
        start = end + 1;
        end = strBook.find(',', start);
        m_country = trim(strBook.substr(start, end - start));

        // PRICE
        start = end + 1;
        end = strBook.find(',', start);
        m_price = std::stod(trim(strBook.substr(start, end - start)));

        // YEAR
        start = end + 1;
        end = strBook.find(',', start);
        m_year = std::stoi(trim(strBook.substr(start, end - start)));

        // DESCRIPTION
        start = end + 1;
        m_description = trim(strBook.substr(start));
    }
    
    const std::string& Book::title() const { return m_title; }

    const std::string& Book::country() const { return m_country; }

    const size_t& Book::year() const { return m_year; }

    double& Book::price() { return m_price; }

    std::ostream& operator<<(std::ostream& ostr, const Book& book) {
        ostr.width(20);
        ostr << std::right << book.m_author << " | ";

        ostr.width(22);
        ostr << std::right << book.m_title << " | ";

        ostr.width(5);
        ostr << std::right << book.m_country << " | ";

        ostr.width(4);
        ostr << std::right << book.m_year << " | ";

        ostr.width(6);
        ostr.precision(2);
        ostr << std::right << std::fixed << book.m_price << " | ";

        ostr << book.m_description << std::endl;

        return ostr;
    }
}
