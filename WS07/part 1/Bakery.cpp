/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-07-06
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#include "Bakery.h"
#include <fstream>
#include <algorithm>

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

    Bakery::Bakery(const std::string& fileName) {
        std::ifstream file(fileName);

        if (!file) {
            throw std::string("File ") + fileName + " not found!";
        }

        do {
            std::string line;
            std::getline(file, line);

            if (file.good()) {
                BakedGood bg;
                bg.type = line[0] == 'B' ? BakedType::BREAD : BakedType::PASTERY;

                bg.description = trim(line.substr(8, 20));

                bg.shelfLife = std::stoi(trim(line.substr(28, 14)));
                bg.qty = std::stoi(trim(line.substr(43, 8)));
                bg.price = std::stod(trim(line.substr(51, 6)));

                m_bakedGoods.push_back(bg);
            }
        } while (file.good());
    }

    void Bakery::showGoods(std::ostream& os) const {
        // DO NOT USE MANUAL LOOPS
        std::for_each(m_bakedGoods.begin(), m_bakedGoods.end(), [&os](const BakedGood& bg) {
            os << bg;
        });
    }

    std::ostream& operator<<(std::ostream& os, const BakedGood& b) {
        os << "* ";

        os.width(10);
        os << std::left << (b.type == BakedType::BREAD ? "Bread" : "Pastry") << " * ";

        os.width(20);
        os << std::left << b.description << " * ";

        os.width(5);
        os << std::left << b.shelfLife << " * ";

        os.width(5);
        os << std::left << b.qty << " * ";

        os.width(8);
        os.precision(2);
        os << std::right << std::fixed << b.price << " * " << std::endl;

        return os;
    }
}
