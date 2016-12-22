#include "softmaxlayer.h"

#include <cmath>

SoftmaxLayer::SoftmaxLayer(int sx, int sy, int depth) {
    out_sx = 1;
    out_sy = 1;
    out_depth = sx * sy * depth;
}

void SoftmaxLayer::forward() {
    out_act = Tensor3(out_sx, out_sy, out_depth);

    double amax = in_act.w[0];
    for (int i = 1; i < out_depth; i++)
        if (in_act.w[i] > amax)
            amax = in_act.w[i];

    es.resize(out_depth);

    double esum = 0.0;
    for (int i = 0; i < out_depth; i++) {
        double e = exp(in_act.w[i] - amax);
        esum += e;
        es[i] = e;
    }

    for (int i = 0; i < out_depth; i++) {
        es[i] /= esum;
        out_act.w[i] = es[i];
    }
}

void SoftmaxLayer::backward() {
    for (int i = 0; i < out_depth; i++) {
        int indicator = i == y ? 1.0 : 0.0;
        int mul = -(indicator - es[i]);
        in_act.dw[i] = mul;
    }

    loss = -log(es[y]);
}

void SoftmaxLayer::getParamsAndGrads(std::vector<Tensor3 *> &) {
}
