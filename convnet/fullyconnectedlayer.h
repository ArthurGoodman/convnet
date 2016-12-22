#pragma once

#include "ilayer.h"

class FullyConnectedLayer : public ILayer {
    std::vector<Tensor3> filters;
    int numInputs;
    Tensor3 biases;

public:
    FullyConnectedLayer(int sx, int sy, int depth);

    void forward();
    void backward();
    void getParamsAndGrads(std::vector<Tensor3 *> &params);
};
