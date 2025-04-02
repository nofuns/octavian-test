#pragma once

#include <random>


class Random {
public:
    Random(int min, int max)
        : m_engine(createSeededEngine()), m_dist(min, max)
    {}

    int getInt() {
        return m_dist(m_engine);
    }

    std::mt19937& getEngine() {
        return m_engine;
    }

private:
    std::mt19937 m_engine;  
    std::uniform_int_distribution<int> m_dist;  

    std::mt19937 createSeededEngine() {
        std::random_device rd;  
        std::seed_seq seed{ rd(), rd(), rd(), rd() }; 
        return std::mt19937(seed);
    }
};