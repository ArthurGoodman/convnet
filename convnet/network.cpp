#include "network.h"

#include "ilayer.h"
#include "alosslayer.h"

Network::Network() {
}

void Network::pushLayer(ILayer *layer) {
    layers.push_back(layer);
}

void Network::forward(const Tensor3 &x) {
    layers[0]->in_act = x;
    layers[0]->forward();

    for (int i = 1; i < (int)layers.size(); i++) {
        layers[i]->in_act = layers[i - 1]->out_act;
        layers[i]->forward();
    }
}

double Network::backward(int y) {
    ((ALossLayer *)layers[layers.size() - 1])->y = y;

    for (int i = layers.size() - 1; i >= 0; i--)
        layers[i]->backward();

    return ((ALossLayer *)layers[layers.size() - 1])->loss;
}

int Network::predict(const Tensor3 &x) {
    forward(x);

    double maxValue = layers[layers.size() - 1]->out_act.w[0];
    int iMax = 0;

    for (int i = 1; i < (int)layers[layers.size() - 1]->out_act.w.size(); i++)
        if (layers[layers.size() - 1]->out_act.w[i] > maxValue) {
            maxValue = layers[layers.size() - 1]->out_act.w[i];
            iMax = 1;
        }

    return iMax;
}

void Network::init() {
    for (int i = 0; i < (int)layers.size(); i++)
        layers[i]->init();
}
