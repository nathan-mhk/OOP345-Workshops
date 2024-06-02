/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-01
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#include "Restaurant.h"

namespace seneca {
    void Restaurant::copyReservations(const Reservation* const reservations[], const size_t cnt) {
        // Responsible for copying the reservations only
        m_reservations = new Reservation*[cnt];
        for (size_t i = 0; i < cnt; ++i) {
            m_reservations[i] = new Reservation(*(reservations[i]));
        }
    }

    void Restaurant::moveReservations(Reservation**&& reservations) {
        // Responsible for moving the reservations only
        m_reservations = reservations;
        reservations = nullptr;
    }

    Restaurant::Restaurant(const Reservation* const reservations[], const size_t cnt) : m_cnt{cnt} {
        copyReservations(reservations, m_cnt);
    }

    Restaurant::~Restaurant() {
        for (size_t i = 0; i < m_cnt; ++i) {
            delete m_reservations[i];
            m_reservations[i] = nullptr;
        }
        delete[] m_reservations;
        m_reservations = nullptr;
        m_cnt = 0;
    }

    Restaurant::Restaurant(const Restaurant& other) : m_cnt{other.m_cnt} {
        copyReservations(other.m_reservations, m_cnt);
    }

    Restaurant::Restaurant(Restaurant&& other) : m_cnt{other.m_cnt} {
        moveReservations(std::move(other.m_reservations));
        other.m_cnt = 0;
    }

    Restaurant& Restaurant::operator=(const Restaurant& other) {
        if (this != &other) {
            this->~Restaurant();    // Will set m_reservations to nullptr

            // If the source object is not empty
            if (other.m_cnt > 0) {
                m_cnt = other.m_cnt;
                copyReservations(other.m_reservations, m_cnt);
            }
        }
        return *this;
    }

    Restaurant& Restaurant::operator=(Restaurant&& other) {
        if (this != &other) {
            this->~Restaurant();

            if (other.m_cnt > 0) {
                m_cnt = other.m_cnt;
                moveReservations(std::move(other.m_reservations));
                other.m_cnt = 0;
            }
        }
        return *this;
    }

    size_t Restaurant::size() const { return m_cnt; }

    inline void line(std::ostream& ostr) {
        ostr << "--------------------------" << std::endl;
    }

    std::ostream& operator<<(std::ostream& ostr, const Restaurant& res) {
        static int CALL_CNT = 0;

        line(ostr);
        ostr << "Fancy Restaurant (" << ++CALL_CNT << ")" << std::endl;
        line(ostr);

        if (res.m_cnt == 0) {
            ostr << "This restaurant is empty!" << std::endl;
        } else {
            for (size_t i = 0; i < res.m_cnt; ++i) {
                ostr << *(res.m_reservations[i]);
            }
        }
        line(ostr);

        return ostr;
    }
}
