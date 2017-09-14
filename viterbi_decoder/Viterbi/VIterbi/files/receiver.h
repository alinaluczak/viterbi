#ifndef VITERBI_RECEIVER_H
#define VITERBI_RECEIVER_H

#include <cmath>

struct Node
{
  int uncoded_bit[4];
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
  static const int number_of_states = 4;
  static const _complex modulator_table_[number_of_states * 2];
  static const int transition_table_[][number_of_states];
  static const int output_table_[][number_of_states];
  Node* tab[6]; // 6 = number of coder states * 3
  int tab_index;

};


#endif //VITERBI_RECEIVER_H