#include "coder.h"

/* Transition Table - representing present state, basing on input (column) and prevoius state (row) */
const int Coder::transition_table_[][number_of_states] = {{0,2,0,2},
                                                          {0,2,0,2},
                                                          {1,3,1,3},
                                                          {1,3,1,3}};

/* Output Table - representing output, basig on current state (row) and input (column) */
const int Coder::output_table_[][number_of_states] = {{0,2,4,6},
                                                      {2,0,6,4},
                                                      {1,3,5,7},
                                                      {3,1,7,5}};

Coder::Coder()
{
  previous_state_ = 0;
  current_state_ = 0;
}


Coder::~Coder()
{
}

int Coder::CoderFunction(int input_value)
{
  if (input_value > 3 || input_value < 0)
  {
    cout << "Oops! Input value in coder is either greater than 3 or less than 0! Aborting." << endl;
    return -1;
  }
  previous_state_ = current_state_;
  current_state_ = transition_table_[previous_state_][input_value];
  int output_value = output_table_[previous_state_][input_value];
  return output_value;
}