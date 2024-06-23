/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-08
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>

namespace seneca {
    class SpellChecker {
        static const int MAX_SIZE{6};
        std::string m_badWords[MAX_SIZE]{};
        std::string m_goodWords[MAX_SIZE]{};
        size_t m_replaceCount[MAX_SIZE]{};

    public:
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const;
    };
}

#endif