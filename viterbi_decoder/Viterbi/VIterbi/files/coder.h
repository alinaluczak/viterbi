#ifndef VITERBI_CODER_H
#define VITERBI_CODER_H

/*Class that represents coder 2/3 (2 bits on input / 3 bits on output) and has four states (two T flip-flops)*/
class Coder
{
public:
  Coder();
  ~Coder();
  int CoderFunction( int );
  
private:
  static const int number_of_states = 4;
  static const int transition_table_[][number_of_states];
  static const int output_table_[][number_of_states];
  int current_state_;
  int previous_state_;

};

#endif //VITERBI_CODER_H
