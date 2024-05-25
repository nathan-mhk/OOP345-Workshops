/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-05-24
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider
*/

#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <string>
#include <iostream>

namespace seneca {
    class Book {
        std::string m_title{};
        unsigned int m_numChapters{};
        unsigned int m_numPages{};
        double m_ratio{};           // Additional data members

        inline bool valid() const;  // Additional member functions

    public:
        Book();
        Book(const std::string& title, unsigned nChapters, unsigned nPages);

        std::ostream& print(std::ostream& os) const;

        // Necessary member prototypes for the Collection template
        bool operator<(const Book& other) const;
        bool operator>(const Book& other) const;
    };

    std::ostream& operator<<(std::ostream& os, const Book& book);
}

#endif // SENECA_BOOK_H
