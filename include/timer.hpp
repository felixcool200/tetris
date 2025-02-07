#pragma once
#include <chrono>
#include <iostream>

struct Timer{

    std::chrono::time_point<std::chrono::high_resolution_clock> m_start, m_stop;

    Timer();
    Timer(bool toStart);

    void start();
    std::chrono::duration<double> stop();
    void reset();

    ~Timer();

};
