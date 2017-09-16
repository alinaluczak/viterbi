#include "system.h"

System::System(int number_of_simulation, int end_condition, int seeds[2], double lambda)
{
  p_channel_ = new Channel(seeds[0], lambda);
  p_modulator_ = new Modulator();
  p_coder_ = new Coder();
  p_receiver_ = new Receiver();
  p_generator_ = new Generator(seeds[1]);
}


System::~System()
{
  delete p_channel_;
  delete p_coder_;
  delete p_modulator_;
  delete p_receiver_;
  delete p_generator_;
}

void System::MainLoop()
{
  int BER = p_receiver_->ReceiverFunction(p_channel_->ChannelFunction(p_modulator_->ModulatorFunction(p_coder_->CoderFunction((p_generator_->RandomNumber()) % 4))));
}
