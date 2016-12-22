#include "fullyconnectedlayer.h"

FullyConnectedLayer::FullyConnectedLayer(int sx, int sy, int depth) {
    out_sx = 1;
    out_sy = 1;
    out_depth = depth;

    numInputs = sx * sy * depth;

    for (int i = 0; i < out_depth; i++)
        filters.push_back(Tensor3(sx, sy, depth));

    biases = Tensor3(1, 1, out_depth, 0);
}

void FullyConnectedLayer::forward() {
    out_act = Tensor3(out_sx, out_sy, out_depth);

    for (int i = 0; i < out_depth; i++) {
        out_act.w[i] = 0;

        for (int j = 0; j < numInputs; j++)
            out_act.w[i] += in_act.w[j] * filters[i].w[j];

        out_act.w[i] += biases.w[i];
    }
}

void FullyConnectedLayer::backward() {
    std::fill_n(in_act.dw.data(), numInputs, 0);

    for (int i = 0; i < out_depth; i++) {
        for (int j = 0; j < numInputs; j++) {
            in_act.dw[j] += filters[i].w[j] * out_act.dw[i];
            filters[i].dw[j] += in_act.w[j] * out_act.dw[i];
        }

        biases.dw[i] += out_act.dw[i];
    }
}

void FullyConnectedLayer::getParamsAndGrads(std::vector<ParamsAndGrads> &pglist) {
    for (int i = 0; i < out_depth; i++)
        pglist.push_back({&filters[i], 1.0});

    pglist.push_back({&biases, 0.0});
}

void FullyConnectedLayer::init() {
    for (int i = 0; i < out_depth; i++)
        filters[i].init();

    biases.init();
}
