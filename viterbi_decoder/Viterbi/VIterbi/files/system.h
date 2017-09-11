#ifndef VITREBI_SYSTEM_H
#define VITREBI_SYSTEM_H

#include"channel.h"
#include"modulator.h"
#include"coder.h"
#include"receiver.h"
#include"generator.h"
//#include"results.h"

class System
{
public:
  System();
  ~System();
  void MainLoop(int);

private:
  Channel *p_channel_;
  Modulator *p_modulator_;
  Coder *p_coder_;
  Receiver *p_receiver_;
  Generator *p_generator_;
};

#endif //VITREBI_SYSTEM_H