#ifndef VITERBI_RECEIVER_H
#define VITERBI_RECEIVER_H

#include <cmath>
#include"results.h"

class Node
{
public:
  Node();
  ~Node();
  int uncoded_bit_tab[4];
  double dfree_tab[4];
  int prevoius_state_tab[4];

};

class Receiver
{
public:
  Receiver();
  ~Receiver();
  int ReceiverFunction(_complex);

private:
  static const int number_of_states = 4;
  static const int size_of_buffer_table = 9; // 9 = (number of coder states + 1) * 3
  static const _complex modulator_table_[number_of_states * 2];
  static const int transition_table_[][number_of_states];
  static const int reversed_transition_table_[][number_of_states];
  static const int output_table_[][number_of_states];
  int is_reday_for_decision; //if this variable >= 9 - then it is ready
  Node* buffer_table[size_of_buffer_table];
  int tab_index;

};


#endif //VITERBI_RECEIVER_H