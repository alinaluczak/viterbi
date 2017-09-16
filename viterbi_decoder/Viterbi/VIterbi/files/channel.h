#ifndef VITERBI_CHANNEL_H
#define VITERBI_CHANNEL_H

#include <cmath>
#include "generator.h"
class Channel
{
public:
  Channel(int seed, double lambda);
  ~Channel();
  _complex ChannelFunction(_complex &input_value);

private:
  Generator *generator;
};

#endif //VITERBI_CHANNEL_H
