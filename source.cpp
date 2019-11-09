#include "source.h"
#include <QApplication>

Morozov::Source::Source()
{
    this->alpha = 0;
    this->beta = 0;
    this->sourcesAmount = 0;

    this->currentSource = 0;
    this->requestNumbers = new int[0];
}

Morozov::Source::Source(int alpha, int beta, int sourcesAmount)
{
    this->alpha = alpha;
    this->beta = beta;
    this->sourcesAmount = sourcesAmount;

    this->currentSource = 0;
    this->requestNumbers = new int[sourcesAmount];
    for (int i = 0; i < sourcesAmount; i++) {
        this->requestNumbers[i] = 0;
    }
}

Morozov::Request Morozov::Source::getNextRequest()
{
    float tmpTimeOfWait = ((float)qrand()/(float)RAND_MAX)*(beta - alpha) + alpha;
    int tmpCS = incrementCurrentSource();
    if (sourcesAmount == 0)
        return Request();
    return Request(tmpTimeOfWait, tmpCS + 1, requestNumbers[tmpCS]++);
}

int Morozov::Source::incrementCurrentSource()
{
    int tmpCS = currentSource;
    if (currentSource + 1 >= sourcesAmount) {
        currentSource = 0;
    } else {
        currentSource++;
    }
    return tmpCS;
}
