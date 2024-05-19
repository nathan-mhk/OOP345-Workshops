/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-05-18
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider
*/

#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <string>
#include <chrono>
#include <iostream>

namespace seneca {

    struct Task {
        std::string name {};
        std::string unit {};
        std::chrono::steady_clock::duration duration {};
    };

    class TimedTask {
        static const unsigned int MAX_EVENTS {10};
        unsigned int numRecords {};
        std::chrono::steady_clock::time_point startTime {};
        std::chrono::steady_clock::time_point endTime {};
        Task tasks[MAX_EVENTS] {};
    
    public:
        TimedTask();
        void startClock();
        void stopClock();
        void addTask(const char* name);
        friend std::ostream& operator<<(std::ostream& ostr, const TimedTask& timedTask);
    };
}

#endif
