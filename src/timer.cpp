#include <timer.hpp>

Timer::Timer(bool toStart) {
    if (toStart) {
        start();
    }
}

void Timer::start() {
    m_start = std::chrono::high_resolution_clock::now();
}

std::chrono::duration<double> Timer::stop() {
    m_stop = std::chrono::high_resolution_clock::now();
    return m_stop - m_start;
}