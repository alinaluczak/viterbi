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

double System::MainLoop()
{
  int coder_value = 0;
  int modulator_value = 0;
  _complex channel_value = {0,0};
  _complex receiver_value = {0,0};
  int loop_counter = 1;
  int error_value = 0;
  while (error_value < 100)
  {
    int MSB = p_generator_->RandomBit();
    int LSB = p_generator_->RandomBit();
    coder_value = (MSB << 1) + LSB;
    p_results->PushInput(coder_value);
    
    switch (loop_counter)
    {
    case 0:
    {
      modulator_value = p_coder_->CoderFunction(coder_value);
      break;
    }
    case 1:
    {
      channel_value = p_modulator_->ModulatorFunction(modulator_value);
      modulator_value = p_coder_->CoderFunction(coder_value);
      break;
    }
    case 2:
    {
      receiver_value = p_channel_->ChannelFunction(channel_value);
      channel_value = p_modulator_->ModulatorFunction(modulator_value);
      modulator_value = p_coder_->CoderFunction(coder_value);
      break;
    }
    default:
    {
      p_results->PushOutput(p_receiver_->ReceiverFunction(receiver_value));
      receiver_value = p_channel_->ChannelFunction(channel_value);
      channel_value = p_modulator_->ModulatorFunction(modulator_value);
      modulator_value = p_coder_->CoderFunction(coder_value);
      break;
    }
    }

    error_value = p_results->GetErrorValue();
  }
  return p_results->GetBER();
}
