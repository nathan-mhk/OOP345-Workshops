/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-01
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#ifndef SENECA_RESTAURANT_H
#define SENECA_RESTAURANT_H

#include "Reservation.h"

namespace seneca {
    class Restaurant {
        Reservation** m_reservations{};
        size_t m_cnt{};

        void copyReservations(const Reservation* const reservations[], const size_t cnt);
        void moveReservations(Reservation**&& reservations);

    public:
        Restaurant(const Reservation* const reservations[], const size_t cnt);

        ~Restaurant();

        Restaurant(const Restaurant& other);
        Restaurant(Restaurant&& other);

        Restaurant& operator=(const Restaurant& other);
        Restaurant& operator=(Restaurant&& other);

        size_t size() const;

        friend std::ostream& operator<<(std::ostream& ostr, const Restaurant& res);
    };
}

#endif
