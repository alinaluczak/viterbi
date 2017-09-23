#ifndef VITERBI_RESULTS_H
#define VITERBI_RESULTS_H

/*Class that holds the input and output values and compares them, counts errors and calculates BER value*/
class Results
{
public:
  Results();
  ~Results();
  void PushInput(int);
  void PushOutput(int);
  double GetBER();
  int GetErrorValue();

private:
  static const int size = 50;
  int input[size];            //buffer table that holds input values
  int output[size];           //buffer table that holds output values
  int input_index;            //index of input buffer table
  int output_index;           //index of output buffer table
  int error_counter;
  int bit_counter;

};

#endif // VITERBI_RESULTS_H
