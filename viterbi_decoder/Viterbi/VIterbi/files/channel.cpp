#include "channel.h"
#include <iostream>
using namespace std;

Channel::Channel(int seed, double lambda)
{
  generator = new Generator(seed, lambda);
}


Channel::~Channel()
{
  delete generator;
}

_complex Channel::ChannelFunction(_complex &input_value)
{
  //randomly selected sign for the noise
  int random_sign_re = generator->RandomBit();
  int random_sign_im = generator->RandomBit();

  if (random_sign_re > 0)
  {
    input_value.x -= generator->Expotential01();
  }
  else
  {
    input_value.x += generator->Expotential01();
  }

  if (random_sign_im > 0)
  {
    input_value.y -= generator->Expotential01();
  }
  else
  {
    input_value.y += generator->Expotential01();
  }

  return input_value;
}
