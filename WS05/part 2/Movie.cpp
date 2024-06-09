/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-08
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#include "Movie.h"

#define SENECA_BOOK_H
#include "Book.h"

#include <string>

namespace seneca {
    Movie::Movie(const std::string& strMove) {
        std::string temp = strMove;
        
        size_t start = 0;
        size_t end = temp.find(',');
        m_title = trim(temp.substr(start, end - start));

        start = end + 1;
        end = temp.find(',', start);
        m_year = std::stoi(trim(temp.substr(start, end - start)));

        start = end + 1;
        end = temp.find("\r\n", start);
        m_description = trim(temp.substr(start, end - start));
    }

    const std::string& Movie::title() const { return m_title; }

    std::ostream& operator<<(std::ostream& ostr, const Movie& movie) {
        ostr.width(40);
        ostr << std::right << movie.m_title << " | ";

        ostr.width(4);
        ostr << movie.m_year << " | ";

        ostr << movie.m_description << std::endl;
    }
}
