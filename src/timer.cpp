#include <chrono>
#include <iostream>

#include <timer.hpp>

Timer::Timer(){
    start();
}

Timer::Timer(bool toStart){
    if(toStart){
        start();
    }
}

void Timer::start(){
    m_start = std::chrono::high_resolution_clock::now();
}

std::chrono::duration<double> Timer::stop(){
    m_stop = std::chrono::high_resolution_clock::now();
    return m_stop - m_start;
    //std::cout << "Time: " << (duration.count() * 1000.0f) << "ms" << std::endl;
}

void Timer::reset(){
   //
}

Timer::~Timer(){
    stop();
}
