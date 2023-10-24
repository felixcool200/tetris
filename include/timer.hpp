#pragma once
#include <chrono>
#include <iostream>

struct Timer{

    std::chrono::time_point<std::chrono::high_resolution_clock> m_start, m_stop;
    std::chrono::duration<float> m_duration;

    Timer();
    Timer(bool toStart);

    void start();
    double stop();
    void reset();

    ~Timer();

};
