#include "results.h"

Results::Results()
{
  cout << "Results Construcotr here " << endl;
  input_index = 0;
  output_index = 0;
  for (int i = 0; i < size; i++)
  {
    input[i] = 0;
    output[i] = 0;
  }
  //input = new vector <int>;
  //output = new vector <int>;
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

    error_counter = output[output_index] & input[output_index];

  }
  ++output_index;
  output_index %= size;
}

double Results::GetBER()
{
  if (bit_counter != 0)
    return error_counter / bit_counter;
  else
    return 0;
}

int Results::GetErrorValue()
{
  return error_counter;
}