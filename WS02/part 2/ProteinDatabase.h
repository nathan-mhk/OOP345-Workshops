/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-05-18
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider
*/

#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H

#include <string>

namespace seneca {

    class ProteinDatabase {
        std::string* proteinSequences {};
        size_t numProteinSequences {};

    public:
        ProteinDatabase();
        ProteinDatabase(std::string fileName);

        ~ProteinDatabase();

        // Copy
        ProteinDatabase(const ProteinDatabase&);
        ProteinDatabase& operator=(const ProteinDatabase&);

        // Move
        ProteinDatabase(ProteinDatabase&&);
        ProteinDatabase& operator=(ProteinDatabase&&);

        size_t size() const;
        std::string operator[](size_t);
    };

}

#endif
