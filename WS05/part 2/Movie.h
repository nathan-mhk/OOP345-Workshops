/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-08
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include <string>
#include <iostream>

namespace seneca {
    class Movie {
        std::string m_title{};
        size_t m_year{};
        std::string m_description{};

    public:
        Movie() = default;
        Movie(const std::string& strMove);

        const std::string& title() const;

        template <typename T>
        void fixSpelling(T& spellChecker) {
            spellChecker(m_title);
            spellChecker(m_description);
        }

        friend std::ostream& operator<<(std::ostream& ostr, const Movie& movie);
    };
}

#endif
