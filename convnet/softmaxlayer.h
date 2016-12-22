#pragma once

#include "alosslayer.h"

class SoftmaxLayer : public ALossLayer {
    std::vector<double> es;

public:
    SoftmaxLayer(int sx, int sy, int depth);

    void forward();
    void backward();
    void getParamsAndGrads(std::vector<Tensor3 *> &params);
};
