//
// Created by Lavumi on 2023/04/02.
//

#ifndef WASM_RANDOM_H
#define WASM_RANDOM_H

#include <random>
namespace VumiEngine {


    class Random {
    private:

    public:
        static int GenRands(int min, int max);
        static float GenRands(float min, float max);
        static double GenRands(double min, double max);
    };
}

#endif //WASM_RANDOM_H
