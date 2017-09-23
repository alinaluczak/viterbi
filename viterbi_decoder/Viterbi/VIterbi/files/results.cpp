#include "results.h"
#include <iso646.h>

Results::Results()
{
  input_index = 0;
  output_index = 0;
  error_counter = 0;
  bit_counter = 0;

  for (int i = 0; i < size; i++)
  {
    input[i] = 0;
    output[i] = 0;
  }
}


Results::~Results()
{
}

void Results::PushInput(int new_value)
{
  input[input_index] = new_value;
  ++input_index;
  input_index %= size;
}
void Results::PushOutput(int new_value)
{
  bit_counter+=2;
  output[output_index] = new_value;
  if (output[output_index] != input[output_index])
  {
    if ((output[output_index] xor input[output_index]) == 3)
    {
      error_counter += 2;
    }
    else
    {
      error_counter += 1;
    }
  }
  ++output_index;
  output_index %= size;
}

double Results::GetBER()
{
  if (bit_counter != 0)
    return (double)error_counter / bit_counter;
  else
    return 0;
}

int Results::GetErrorValue()
{
  return error_counter;
}