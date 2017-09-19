#ifndef VITERBI_RESULTS_H
#define VITERBI_RESULTS_H

#include<iostream>
using namespace std;
#include <vector>

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
  static const int size = 20;
  vector<int> input;
  vector<int> output;
  int input_index;
  int output_index;
  int error_counter;
  int bit_counter;

};

#endif // VITERBI_RESULTS_H
