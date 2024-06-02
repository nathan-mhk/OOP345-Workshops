/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-01
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#include "ConfirmationSender.h"

namespace seneca {
    void ConfirmationSender::copyReservations(const Reservation* const reservations[], const size_t cnt) {
        // Responsible for copying reservations only
        m_reservations = new const Reservation*[cnt];
        for (size_t i = 0; i < cnt; ++i) {
            m_reservations[i] = reservations[i];
        }
    }

    void ConfirmationSender::moveReservations(const Reservation**&& reservations) {
        // Responsible for moving reservations only
        m_reservations = reservations;
        reservations = nullptr;
    }

    ConfirmationSender::ConfirmationSender(const Reservation* const reservations[], const size_t cnt) : m_cnt{cnt} {
        copyReservations(reservations, m_cnt);
    }

    ConfirmationSender::~ConfirmationSender() {
        delete[] m_reservations;
        m_reservations = nullptr;
        m_cnt = 0;
    }

    ConfirmationSender::ConfirmationSender(const ConfirmationSender& other) : m_cnt{other.m_cnt} {
        copyReservations(other.m_reservations, m_cnt);
    }

    ConfirmationSender::ConfirmationSender(ConfirmationSender&& other) : m_cnt{other.m_cnt} {
        moveReservations(std::move(other.m_reservations));
        other.m_cnt = 0;
    }

    ConfirmationSender& ConfirmationSender::operator=(const ConfirmationSender& other) {
        if (this != &other) {
            this->~ConfirmationSender();    // Will set m_reservations to nullptr

            // If the source object is not empty
            if (other.m_cnt > 0) {
                m_cnt = other.m_cnt;
                copyReservations(other.m_reservations, m_cnt);
            }
        }
        return *this;
    }

    ConfirmationSender& ConfirmationSender::operator=(ConfirmationSender&& other) {
        if (this != &other) {
            this->~ConfirmationSender();

            if (other.m_cnt > 0) {
                m_cnt = other.m_cnt;
                moveReservations(std::move(other.m_reservations));
                other.m_cnt = 0;
            }
        }
        return *this;
    }

    bool ConfirmationSender::exist(const Reservation& res) const {
        for (size_t i = 0; i < m_cnt; ++i) {
            if (m_reservations[i] == &res) return true;
        }
        return false;
    }

    ConfirmationSender& ConfirmationSender::operator+=(const Reservation& res) {
        if (!exist(res)) {
            // Resize with size + 1
            const Reservation** temp = new const Reservation*[m_cnt + 1];
            
            // Copy the current reservations
            for (size_t i = 0; i < m_cnt; ++i) {
                temp[i] = m_reservations[i];
            }
            // Insert the new reservation
            temp[m_cnt++] = &res;

            delete[] m_reservations;
            m_reservations = temp;
        }
        return *this;
    }

    ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res) {
        if (exist(res)) {
            // > To challenge yourself, try to actually resize the array.
            // Challenge accepted.
            
            // Resize the array
            const Reservation** temp = new const Reservation*[m_cnt - 1];

            // Copy the reservations if it does not match `res`
            for (size_t i = 0, j = 0; i < m_cnt; ++i, ++j) {
                if (m_reservations[i] != &res) {
                    temp[j] = m_reservations[i];
                } else {
                    // Decrement j to counter the `++j` for matched(skipped) reservation
                    --j;
                }
            }

            delete[] m_reservations;
            m_reservations = temp;
            --m_cnt;
        }
        return *this;
    }

    inline void line(std::ostream& ostr) {
        ostr << "--------------------------" << std::endl;
    }

    std::ostream& operator<<(std::ostream& ostr, const ConfirmationSender& con) {
        line(ostr);
        ostr << "Confirmations to Send" << std::endl;
        line(ostr);
        if (con.m_cnt <= 0) {
            ostr << "There are no confirmations to send!" << std::endl;
        } else {
            for (size_t i = 0; i < con.m_cnt; ++i) {
                ostr << *con.m_reservations[i];
            }
        }
        line(ostr);

        return ostr;
    }
}
