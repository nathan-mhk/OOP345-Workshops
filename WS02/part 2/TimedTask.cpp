/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-05-18
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider
*/

#include "TimedTask.h"
#include <cstring>

namespace seneca {
    TimedTask::TimedTask() {};

    void TimedTask::startClock() {
        startTime = std::chrono::steady_clock::now();
    }

    void TimedTask::stopClock() {
        endTime = std::chrono::steady_clock::now();
    }

    void TimedTask::addTask(const char* name) {
        if (numRecords >= MAX_EVENTS) return;

        tasks[numRecords].name = name;
        tasks[numRecords].unit = "nanoseconds";

        std::chrono::nanoseconds duration = endTime - startTime;
        tasks[numRecords].duration = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);

        ++numRecords;
    }

    inline void line(std::ostream& ostr) { ostr << "--------------------------" << std::endl; }

    std::ostream& operator<<(std::ostream& ostr, const TimedTask& timedTask) {
        ostr << "Execution Times:" << std::endl;
        line(ostr);

        for (size_t i = 0; i < timedTask.numRecords; ++i) {
            const Task& task = timedTask.tasks[i];

            ostr.width(21);
            ostr << std::left << task.name;

            ostr.width(13);
            ostr << std::right << task.duration.count();

            ostr << " " << task.unit << std::endl;
        }
        line(ostr);
        return ostr;
    }
}
