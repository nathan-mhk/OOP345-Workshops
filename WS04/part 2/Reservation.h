/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-01
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#ifndef SENECA_RESERVATION_H
#define SENECA_RESERVATION_H

#include <string>
#include <iostream>

namespace seneca {
    class Reservation {
        std::string m_reservation_id{};
        std::string m_name{};
        std::string m_email{};
        size_t m_numPpl{};
        unsigned int m_day{};     // [1, 28]
        unsigned int m_hour{};    // [1, 24]

    public:
        Reservation() = default;
        void update(int day, int time);
        Reservation(const std::string& res);

        friend std::ostream& operator<<(std::ostream& ostr, const Reservation& res);
    };
}

#endif
