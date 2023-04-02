//
// Created by Lavumi on 2023/04/02.
//

#include <random>
#include "Random.h"

static std::random_device rd;
static std::mt19937 gen(rd());

int VumiEngine::Random::GenRands(int min, int max) {
    std::uniform_int_distribution<int> dis(min, max);
    auto rnd = dis(gen);
    return rnd;
}


float VumiEngine::Random::GenRands(float min, float max) {
    std::uniform_real_distribution<float> dis(min, max);
    auto rnd = dis(gen);
    return rnd;
}

double VumiEngine::Random::GenRands(double min, double max) {
    std::uniform_real_distribution<double> dis(min, max);
    auto rnd = dis(gen);
    return rnd;
}