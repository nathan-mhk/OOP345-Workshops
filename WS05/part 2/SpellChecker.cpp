/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-08
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#include "SpellChecker.h"

#define SENECA_BOOK_H
#include "Book.h"

#include <fstream>

namespace seneca {
    SpellChecker::SpellChecker(const char* filename) {
        std::fstream file(filename, std::ios::in);

        if (!file.is_open()) {
            throw "Bad file name!";
        }

        size_t i = 0;
        while (file.good() && i < MAX_SIZE) {
            std::string line;
            std::getline(file, line);

			size_t start = 0;
            size_t end = line.find(' ');

            m_badWords[i] = trim(line.substr(start, end - start));
            
            start = end + 1;
            end = line.find("\r\n", start);

            m_goodWords[i++] = trim(line.substr(start, end - start));
		}
    }

    void SpellChecker::operator()(std::string& text) {
        for (size_t i = 0; i < MAX_SIZE; i++) {
            const std::string& badWord = m_badWords[i];

            size_t j = text.find(badWord, 0);

            while (j != std::string::npos) {
                const std::string& goodWord = m_goodWords[i];

                text.replace(j, badWord.length(), goodWord);
                ++m_replaceCount[i];

                j += goodWord.length();
                j = text.find(badWord, j);
            }
        }
    }

    void SpellChecker::showStatistics(std::ostream& out) const {
        out << "Spellchecker Statistics" << std::endl;

        for (size_t i = 0; i < MAX_SIZE; ++i) {
            out.width(15);
            out << std::right << m_badWords[i] << ": " << m_replaceCount[i] << " replacements" << std::endl;
        }
    }
}
