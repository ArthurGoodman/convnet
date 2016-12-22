#pragma once

#include "tensor3.h"

class ILayer {
public:
    struct ParamsAndGrads {
        Tensor3 *pg;
        double l2DecayMul;
    };

public:
    Tensor3 in_act, out_act;
    int out_sx, out_sy, out_depth;

public:
    ILayer();
    virtual ~ILayer();

    virtual void forward() = 0;
    virtual void backward() = 0;

    virtual void getParamsAndGrads(std::vector<ParamsAndGrads> &pglist);
    virtual void init();
};
