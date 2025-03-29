#pragma once
#include <chrono>

class Timer {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_start, m_stop;
    public:
        Timer(bool toStart = true);
        void start();
        std::chrono::duration<double> stop();
    
};
