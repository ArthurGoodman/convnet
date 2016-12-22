#include "tanhlayer.h"

#include <cmath>

TanhLayer::TanhLayer(int sx, int sy, int depth) {
    out_sx = sx;
    out_sy = sy;
    out_depth = depth;
}

void TanhLayer::forward() {
    out_act = Tensor3(in_act.sx, in_act.sy, in_act.depth);

    for (int i = 0; i < (int)in_act.w.size(); i++)
        out_act.w[i] = tanh(in_act.w[i]);
}

void TanhLayer::backward() {
    for (int i = 0; i < (int)in_act.w.size(); i++)
        in_act.dw[i] = (1.0 - out_act.w[i] * out_act.w[i]) * out_act.dw[i];
}

void TanhLayer::getParamsAndGrads(std::vector<Tensor3 *> &) {
}
