#pragma once

#include "tensor3.h"

class ILayer {
public:
    Tensor3 in_act, out_act;
    int out_sx, out_sy, out_depth;

public:
    ILayer();
    virtual ~ILayer();

    virtual void forward() = 0;
    virtual void backward() = 0;
    virtual void getParamsAndGrads(std::vector<Tensor3 *> &params) = 0;
};
