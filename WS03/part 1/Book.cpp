/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-05-24
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider
*/

#include "Book.h"

namespace seneca {

    inline bool Book::valid() const {
        return m_title.length() > 0 && m_numChapters > 0 && m_numPages > 0;
    }

    Book::Book() {}

    Book::Book(const std::string& title, unsigned nChapters, unsigned nPages)
        : m_numChapters(nChapters), m_numPages(nPages) {
            m_title = title;
            if (valid()) {
                m_ratio = (double)m_numPages / m_numChapters;
            }
        }
    
    std::ostream& Book::print(std::ostream& os) const {
        if (valid()) {
            // Left Field
            std::string field(m_title + ",");
            field += std::to_string(m_numChapters) + ",";
            field += std::to_string(m_numPages);

            os.width(56);
            os << std::right << field << " | ";

            // Right Field
            field = "(" + std::to_string(m_ratio).substr(0, 9) + ")";
            
            os.width(15);
            os << std::left << field;
        } else {
            os << "| Invalid book data";
        }
        return os;
    }

    bool Book::operator>(const Book& other) const {
        return m_ratio > other.m_ratio;
    }

    bool Book::operator<(const Book& other) const {
        return m_ratio < other.m_ratio;
    }

    std::ostream& operator<<(std::ostream& os, const Book& book) {
        return book.print(os);
    }
}
