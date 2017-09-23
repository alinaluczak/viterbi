#ifndef VITERBI_RECEIVER_H
#define VITERBI_RECEIVER_H

#include <cmath>
#include"results.h"

/*Auxiliary class that holds three tables*/
class Node
{
public:
  Node();
  ~Node();
  int uncoded_bit_tab_[4];    //holds the values of the uncoded bits (MSB)
  double cost_tab_[4];        //holds the values of cost of the lowes - cost path that leads to state 
  int previous_state_tab_[4]; //holds the values of the prevous states so that the path back can be reconstructed

};

/*Class that represents receiver in system - it is soft-decision TCM decoder.       */
/*Receiver saves lowest-cost path 9 tact back to make decision about received value.*/
class Receiver
{
public:
  Receiver();
  ~Receiver();
  int ReceiverFunction(_complex);

private:
  static const int number_of_states_ = 4;
  static const int size_of_buffer_table_ = 9;                      // 9 = (number of coder flip-flops + 1) * 3
  static const _complex modulator_table_[number_of_states_ * 2];
  static const int reversed_transition_table_[][number_of_states_];
  int is_reday_for_decision_;                                      //if this variable is >= 8 - then it is ready (counting from 0)
  Node* buffer_table_[size_of_buffer_table_];                      //buffer that holds all the results (described in class Node) 9 tacts back
  int tab_index_;                                                  //index of the buffer table

};


#endif //VITERBI_RECEIVER_H