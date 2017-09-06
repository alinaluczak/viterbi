#ifndef VITREBI_MODULATOR_H
#define VITREBI_MODULATOR_H

#include<cmath>

/*Class represents 8-PSK modulator.*/
class Modulator
{
public:
  Modulator();
  ~Modulator();
  _complex ModulatorFunction(int input_value);

private:
  static const int number_of_states = 8;
  static const _complex output_table_[number_of_states];

};

#endif // VITERBI_MODULATOR_H
