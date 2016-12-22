#pragma once

#include "tensor3.h"

class ILayer;

class Network {
public:
    std::vector<ILayer *> layers;

public:
    Network();

    void pushLayer(ILayer *layer);

    void forward(const Tensor3 &x);
    double backward(int y);

    int predict(const Tensor3 &x);
    void init();
};
