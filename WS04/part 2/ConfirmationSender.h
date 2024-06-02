/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-01
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#ifndef SENECA_CONFIRMATIONSENDER_H
#define SENECA_CONFIRMATIONSENDER_H

#include "Reservation.h"
#include <iostream>

namespace seneca {
    class ConfirmationSender {
        const Reservation** m_reservations{};
        size_t m_cnt{};

        void copyReservations(const Reservation* const reservations[], const size_t cnt);
        void moveReservations(const Reservation**&& reservations);

        bool exist(const Reservation& res) const;

    public:
        ConfirmationSender() = default;
        ConfirmationSender(const Reservation* const reservations[], const size_t cnt);
        ~ConfirmationSender();

        ConfirmationSender(const ConfirmationSender& other);
        ConfirmationSender(ConfirmationSender&& other);

        ConfirmationSender& operator=(const ConfirmationSender& other);
        ConfirmationSender& operator=(ConfirmationSender&& other);

        ConfirmationSender& operator+=(const Reservation& res);
        ConfirmationSender& operator-=(const Reservation& res);

        friend std::ostream& operator<<(std::ostream& ostr, const ConfirmationSender& con);
    };
}

#endif
