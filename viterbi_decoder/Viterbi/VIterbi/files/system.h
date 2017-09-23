#ifndef VITREBI_SYSTEM_H
#define VITREBI_SYSTEM_H

#include"channel.h"
#include"modulator.h"
#include"coder.h"
#include"receiver.h"
#include"generator.h"
#include"results.h"

class System
{
public:
  System(int number_of_simulation, int end_condition, int seeds[2], double lambda);
  ~System();
  double MainLoop();

private:
  Channel *p_channel_;
  Modulator *p_modulator_;
  Coder *p_coder_;
  Receiver *p_receiver_;
  Generator *p_generator_;
  Results *p_results_;
  int end_condition_;
};

#endif //VITREBI_SYSTEM_H