/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-05-18
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider
*/

#include "ProteinDatabase.h"
#include <fstream>
#include <limits>

namespace seneca {
    // Helper function
    inline void ignore(std::fstream& file, const char delim) {
        // `delim` will be discarded
        file.ignore(std::numeric_limits<std::streamsize>::max(), delim);
    }

    ProteinDatabase::ProteinDatabase() {}

    ProteinDatabase::ProteinDatabase(const std::string fileName) {
        std::fstream file(fileName, std::fstream::in);

        // Count the number of protein sequence present in the file
        while (file.good()) {
            ignore(file, '>');
            if (!file.eof())
                ++numProteinSequences;
        }

        // Allocate memory for that number of protein sequences in the array
        proteinSequences = new std::string[numProteinSequences];

        // Re-reads the file
        file.seekg(0);

        for (size_t i = 0; file.good() && i < numProteinSequences; ++i) {
            ignore(file, '\n');

            while (file.good() && file.peek() != '>') {
                std::string tmp {};
                std::getline(file, tmp);    // `\n` will be discarded
                proteinSequences[i] += tmp;
            }
        }
        file.close();
    }

    ProteinDatabase::~ProteinDatabase() {
        delete[] proteinSequences;
        proteinSequences = nullptr;
    }

    ProteinDatabase::ProteinDatabase(const ProteinDatabase& other) {
        *this = other;
    }

    ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& other) {
        if (this != &other) {
            numProteinSequences = other.numProteinSequences;

            delete[] proteinSequences;
            proteinSequences = new std::string[numProteinSequences];

            for (size_t i = 0; i < numProteinSequences; ++i) {
                proteinSequences[i] = other.proteinSequences[i];
            }

        }
        return *this;
    }

    size_t ProteinDatabase::size() const {
        return numProteinSequences;
    }

    std::string ProteinDatabase::operator[](size_t index) {
        if (index >= numProteinSequences) return {};
        return proteinSequences[index];
    }
}
