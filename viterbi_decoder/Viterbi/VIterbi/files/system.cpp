#include "system.h"
#include<string>
#include<iostream>
using namespace std;

System::System(int number_of_simulation, int end_condition, int seeds[2], double lambda)
{
  p_channel_ = new Channel(seeds[0], lambda);
  p_modulator_ = new Modulator();
  p_coder_ = new Coder();
  p_receiver_ = new Receiver();
  p_generator_ = new Generator(seeds[1]);
  p_results_ = new Results();
  end_condition_ = end_condition;
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
  string wait_for_sign;            //string to getline function
  int coder_value = 0;             //value that will be passed to coder
  int modulator_value = 0;         //value that will be passed to modulator
  _complex channel_value = {0,0};  //value that will be passed to channel
  _complex receiver_value = {0,0}; //value that will be passed to receiver
  int result_value = 0;            //value that will be passed to result - decoded value
  int loop_counter = 0;            //value that handles first 
  int error_value = 0;             //value that represents number of detected errors

  while (error_value < end_condition_)
  {
    //generate new bits
    int MSB = p_generator_->RandomBit();
    int LSB = p_generator_->RandomBit();

    //merge them into new input value
    coder_value = (MSB << 1) + LSB;
    
    //put it to input table
    p_results_->PushInput(coder_value);
    
    switch (loop_counter)
    {
    //first value taah appeares in system - goes to coder
    case 0:
    {
      modulator_value = p_coder_->CoderFunction(coder_value);
      break;
    }
    //second value appeares, first go to modulator
    case 1:
    {
      channel_value = p_modulator_->ModulatorFunction(modulator_value);
      modulator_value = p_coder_->CoderFunction(coder_value);
      break;
    }
    //third value appeares - first goes to channel
    case 2:
    {
      receiver_value = p_channel_->ChannelFunction(channel_value);
      channel_value = p_modulator_->ModulatorFunction(modulator_value);
      modulator_value = p_coder_->CoderFunction(coder_value);
      break;
    }
    //first value appears in receiver - system works poroperly form now on
    default:
    {
      result_value = p_receiver_->ReceiverFunction(receiver_value);
      if (result_value < 0) { cout << "Abort" << endl; return -1; }  //error handling, return error code
      if (result_value >= 0 && result_value < 4)                     //checking if the system is ready to decode and if there was no error
      {
        p_results_->PushOutput(result_value);
      }
      receiver_value = p_channel_->ChannelFunction(channel_value);
      channel_value = p_modulator_->ModulatorFunction(modulator_value);
      modulator_value = p_coder_->CoderFunction(coder_value);
      break;
    }
    }
    ++loop_counter;
    error_value = p_results_->GetErrorValue();
  }
  return p_results_->GetBER();
}
