#ifndef VITERBI_RECEIVER_H
#define VITERBI_RECEIVER_H

#include <cmath>

struct Node
{
  int uncded_bit[4];
  int dfree[4];
  int prevoius_state[4];

};

class Receiver
{
public:
  Receiver();
  ~Receiver();
  int ReceiverFunction(_complex);

private:
  static const int number_of_states = 8;
  static const _complex modulator_table_[number_of_states];
  Node* tab[number_of_states /2];
  int tab_index;

};


#endif //VITERBI_RECEIVER_H