#pragma once

#include "tensor3.h"
#include "ilayer.h"

class Network;

class Trainer {
    Network *net;

    std::vector<ILayer::ParamsAndGrads> pglist;

    std::vector<std::vector<double>> gsum;
    std::vector<std::vector<double>> xsum;

public:
    double learningRate = 0.01;
    double l2Decay = 0.00001;
    int batchSize = 1;

    double momentum = 0.9;
    double ro = 0.9;
    double eps = 1e-8;

    int k = 0;

public:
    Trainer(Network *net = nullptr);

    void setNetwork(Network *net);

    double train(const Tensor3 &x, int y);

private:
    void gatherParams();
};
