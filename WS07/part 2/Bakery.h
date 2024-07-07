/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-07-06
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H

#include <string>
#include <vector>
#include <list>
#include <iostream>

namespace seneca {
    enum class BakedType {
        BREAD, PASTERY
    };

    struct BakedGood {
        BakedType type;
        std::string description;
        size_t shelfLife;
        size_t qty;
        double price;
    };
    
    class Bakery {
        std::vector<BakedGood> m_bakedGoods{};

    public:
        Bakery(const std::string& fileName);
        void showGoods(std::ostream& os) const;
        void sortBakery(const std::string& fieldName);
        std::vector<BakedGood> combine(Bakery& other);
        bool inStock(const std::string description, const BakedType bakedType) const;
        std::list<BakedGood> outOfStock(const BakedType bakedType) const;
    };
    
    std::ostream& operator<<(std::ostream& os, const BakedGood& b);
}

#endif
