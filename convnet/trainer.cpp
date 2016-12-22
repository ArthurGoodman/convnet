#include "trainer.h"

#include <cmath>

#include "network.h"
#include "ilayer.h"

Trainer::Trainer(Network *net)
    : net(net) {
    gatherParams();
}

void Trainer::setNetwork(Network *net) {
    this->net = net;
    gatherParams();
}

double Trainer::train(const Tensor3 &x, int y) {
    net->forward(x);

    double loss = net->backward(y);

    k++;

    if (k % batchSize == 0) {
        if (gsum.size() == 0) {
            for (int i = 0; i < (int)pglist.size(); i++) {
                gsum.push_back(std::vector<double>(pglist[i].pg->w.size()));
                xsum.push_back(std::vector<double>(pglist[i].pg->w.size()));
            }
        }

        for (int i = 0; i < (int)pglist.size(); i++) {
            ILayer::ParamsAndGrads &pg = pglist[i];

            std::vector<double> &p = pg.pg->w;
            std::vector<double> &g = pg.pg->dw;

            double l2_decay_mul = pg.l2DecayMul;
            double l2_decay = l2Decay * l2_decay_mul;

            int plen = p.size();
            for (int j = 0; j < plen; j++) {
                double l2grad = l2_decay * (p[j]);

                double gij = (l2grad + g[j]) / batchSize;

                std::vector<double> &gsumi = gsum[i];
                std::vector<double> &xsumi = xsum[i];

                gsumi[j] = ro * gsumi[j] + (1 - ro) * gij * gij;

                double dx = -sqrt((xsumi[j] + eps) / (gsumi[j] + eps)) * gij;
                xsumi[j] = ro * xsumi[j] + (1 - ro) * dx * dx;

                p[j] += dx;

                g[j] = 0.0;
            }
        }
    }

    return loss;
}

void Trainer::gatherParams() {
    if (net == nullptr)
        return;

    pglist.clear();

    for (int i = 0; i < (int)net->layers.size(); i++)
        net->layers[i]->getParamsAndGrads(pglist);
}
