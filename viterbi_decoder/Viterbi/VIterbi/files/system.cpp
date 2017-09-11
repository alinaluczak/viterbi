#include "system.h"

System::System()
{
  p_channel_ = new Channel();
  p_modulator_ = new Modulator();
  p_coder_ = new Coder();
  p_receiver_ = new Receiver();
  p_generator_ = new Generator(123);
}


System::~System()
{
  delete p_channel_;
  delete p_coder_;
  delete p_modulator_;
  delete p_receiver_;
  delete p_generator_;
}

void System::MainLoop(int)
{
  int BER = p_receiver_->ReceiverFunction(p_channel_->ChannelFunction(p_modulator_->ModulatorFunction(p_coder_->CoderFunction(p_generator_->RandomNumber % 4))));
}
