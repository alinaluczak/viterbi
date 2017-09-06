#include "channel.h"

Channel::Channel()
{
  generator = new Generator(123, 0.1);
}


Channel::~Channel()
{
  delete generator;
}

_complex Channel::ChannelFunction(_complex &input_value)
{
  input_value.x += generator->Expotential01();
  input_value.y += generator->Expotential01();
  return input_value;
}
