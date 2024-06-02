/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-06-01
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#include "Reservation.h"

namespace seneca {
    void Reservation::update(int day, int time) {
        m_day = day;
        m_hour = time;
    }

    // Helper Functions
    std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');

        if (start == std::string::npos) start = 0;
        if (last == std::string::npos) last = str.length() - 1;

        // [start, last - start + 1) == [start, last - start]
        return str.substr(start, last - start + 1);
    }

    // Conversion Constructor
    Reservation::Reservation(const std::string& res) {
        /**
         * Format:
         * ID:NAME,EMAIL,PARTY_SIZE,DAY,HOUR
         */
        // ID
        size_t start = 0;
        size_t end = res.find(':', start);
        m_reservation_id = trim(res.substr(start, end - start));    // Omit the + 1 to skip the end char

        // NAME
        start = end + 1;
        end = res.find(',', start);
        m_name = trim(res.substr(start, end - start));

        // EMAIL
        start = end + 1;
        end = res.find(',', start);
        m_email = trim(res.substr(start, end - start));

        // PARTY_SIZE
        start = end + 1;
        end = res.find(',', start);
        m_numPpl = std::stoi(trim(res.substr(start, end - start)));

        // DAY
        start = end + 1;
        end = res.find(',', start);
        m_day = std::stoi(trim(res.substr(start, end - start)));

        // HOUR
        start = end + 1;
        end = res.find_first_of("\r\n", start);     // Use find_first_of for CRLF and LF
        m_hour = std::stoi(trim(res.substr(start, end - start)));
    }

    std::ostream& operator<<(std::ostream& ostr, const Reservation& res) {
        std::string meal{"Drinks"};

        if (res.m_hour >= 6 && res.m_hour <= 9) meal = "Breakfast";
        else if (res.m_hour >= 11 && res.m_hour <= 15) meal = "Lunch";
        else if (res.m_hour >= 17 && res.m_hour <= 21) meal = "Dinner";

        ostr << "Reservation ";
        ostr.width(10);
        ostr << std::right << res.m_reservation_id << ": ";

        ostr.width(20);
        ostr << std::right << res.m_name << "  ";

        ostr.width(20);
        ostr << std::left << ("<" + res.m_email + ">") << "    ";

        ostr << meal << " on day " << res.m_day << " @ " << res.m_hour << ":00 for ";
        ostr << res.m_numPpl << (res.m_numPpl == 1 ? " person." : " people.") << std::endl;

        return ostr;
    }
}
