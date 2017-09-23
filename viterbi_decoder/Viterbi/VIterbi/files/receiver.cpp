#include "receiver.h"

/* Output Table - representing output (complex number), basig on input                   */
/*                                                                    Re       Im        */
const _complex Receiver::modulator_table_[number_of_states * 2] = { { 0.7  ,  -0.7 }, //s0
                                                                    { 1    ,  0    }, //s1
                                                                    { 0.7  ,  0.7  }, //s2
                                                                    { 0    ,  1    }, //s3
                                                                    { -0.7 ,  0.7  }, //s4
                                                                    { -1   ,  0    }, //s5
                                                                    { -0.7 , -0.7  }, //s6
                                                                    { 0    ,  -1 } }; //s7

/* Transition Table - representing present state, basing on input (column) and prevoius state (row) */
const int Receiver::transition_table_[][number_of_states] = { { 0, 2, 0, 2 },
                                                              { 0, 2, 0, 2 },
                                                              { 1, 3, 1, 3 },
                                                              { 1, 3, 1, 3 } };


/* Reversed Transition Table - representing output value (decoded bits), basing on present state (column) and prevoius state (row) */
const int Receiver::reversed_transition_table_[][number_of_states] = { { 0, -1, 1, -1 },
                                                                       { 0, -1, 1, -1 },
                                                                       { -1, 0, -1, 1 },
                                                                       { -1, 0, -1, 1 } };


/* Output Table - representing output, basig on current state (row) and input (column) */
const int Receiver::output_table_[][number_of_states] = { { 0, 2, 4, 6 },
                                                          { 2, 0, 6, 4 },
                                                          { 1, 3, 5, 7 },
                                                          { 3, 1, 7, 5 } };

Receiver::Receiver()
{
  cout << "Receiver Construcotr here " << endl;
  is_reday_for_decision = 0;
  tab_index = 0;
  for (int node = 0; node < size_of_buffer_table; node++) {
    for (int i = 0; i < 4; i++) {
      buffer_table[i][node] = new Node();
    }
  }
}

Receiver::~Receiver()
{
  for each (Node* node in buffer_table)
  {
    delete node;
  }
}


int Receiver::ReceiverFunction(_complex received_value)
{

  double d0 = 0;
  static int which_iteration = 0;
  int return_value = 5;
  double cost = 1 << 15;


  /*Firstly fill the output buffer table basic on newly-come value*/

  if (which_iteration == 0) {
    buffer_table[0][tab_index]->uncoded_bit_tab[0] = 0;
    for (int k = 0; k < 8; k += 4) {
      d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
      if (d0 < cost) {
        cost = d0;
        if (k >= 4) {
          buffer_table[0][tab_index]->uncoded_bit_tab[0] = 1;
        }
      }
    }
    buffer_table[0][tab_index]->dfree_tab[0] += cost;

    cost = 1 << 15;
    buffer_table[0][tab_index]->uncoded_bit_tab[2] = 0;
    for (int k = 2; k < 8; k += 4) {
      d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
      if (d0 < cost) {
        cost = d0;
        if (k >= 4) {
          buffer_table[0][tab_index]->uncoded_bit_tab[2] = 1;
        }
      }
    }
    buffer_table[0][tab_index]->dfree_tab[2] += cost;
  }

  if (which_iteration == 1) {
    buffer_table[0][tab_index]->uncoded_bit_tab[0] = 0;
    for (int k = 0; k < 8; k += 4) {
      d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
      if (d0 < cost) {
        cost = d0;
        if (k >= 4) {
          buffer_table[0][tab_index]->uncoded_bit_tab[0] = 1;
        }
      }
    }
    buffer_table[0][tab_index]->dfree_tab[0] += cost;

    cost = 1 << 15;
    buffer_table[0][tab_index]->uncoded_bit_tab[2] = 0;
    for (int k = 2; k < 8; k += 4) {
      d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
      if (d0 < cost) {
        cost = d0;
        if (k >= 4) {
          buffer_table[0][tab_index]->uncoded_bit_tab[2] = 1;
        }
      }
    }
    buffer_table[0][tab_index]->dfree_tab[2] += cost;



    cost = 1 << 15;
    buffer_table[2][tab_index]->uncoded_bit_tab[1] = 0;
    for (int k = 1; k < 8; k += 4) {
      d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
      if (d0 < cost) {
        cost = d0;
        if (k >= 4) {
          buffer_table[2][tab_index]->uncoded_bit_tab[1] = 1;
        }
      }
    }
    buffer_table[2][tab_index]->dfree_tab[1] += cost;

    cost = 1 << 15;
    buffer_table[2][tab_index]->uncoded_bit_tab[3] = 0;
    for (int k = 3; k < 8; k += 4) {
      d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
      if (d0 < cost) {
        cost = d0;
        if (k >= 4) {
          buffer_table[2][tab_index]->uncoded_bit_tab[3] = 1;
        }
      }
    }
    buffer_table[2][tab_index]->dfree_tab[3] += cost;
  }
  if (which_iteration >= 2) {
    for (int i = 0; i < number_of_states; i++) {
      switch (i) {
      case 0: {
        buffer_table[i][tab_index]->uncoded_bit_tab[0] = 0;
        for (int k = 0; k < 8; k += 4) {
          d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (d0 < cost) {
            cost = d0;
            if (k >= 4) {
              buffer_table[i][tab_index]->uncoded_bit_tab[0] = 1;
            }
          }
        }
        buffer_table[i][tab_index]->dfree_tab[0] += cost;

        cost = 1 << 15;
        buffer_table[i][tab_index]->uncoded_bit_tab[2] = 0;
        for (int k = 2; k < 8; k += 4) {
          d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (d0 < cost) {
            cost = d0;
            if (k >= 4) {
              buffer_table[i][tab_index]->uncoded_bit_tab[2] = 1;
            }
          }
        }
        buffer_table[i][tab_index]->dfree_tab[2] += cost;
        break;
      }
      case 1: {
        buffer_table[i][tab_index]->uncoded_bit_tab[2] = 0;
        for (int k = 0; k < 8; k += 4) {
          d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (d0 < cost) {
            cost = d0;
            if (k >= 4) {
              buffer_table[i][tab_index]->uncoded_bit_tab[2] = 1;
            }
          }
        }
        buffer_table[i][tab_index]->dfree_tab[2] += cost;

        cost = 1 << 15;
        buffer_table[i][tab_index]->uncoded_bit_tab[0] = 0;
        for (int k = 2; k < 8; k += 4) {
          d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (d0 < cost) {
            cost = d0;
            if (k >= 4) {
              buffer_table[2][tab_index]->uncoded_bit_tab[0] = 1;
            }
          }
        }
        buffer_table[i][tab_index]->dfree_tab[0] += cost;
        break;
      }
      case 2: {
        buffer_table[i][tab_index]->uncoded_bit_tab[1] = 0;
        for (int k = 1; k < 8; k += 4) {
          d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (d0 < cost) {
            cost = d0;
            if (k >= 4) {
              buffer_table[1][tab_index]->uncoded_bit_tab[1] = 1;
            }
            buffer_table[1][tab_index]->next_state_tab[1] = 1;
          }
        }
        buffer_table[2][tab_index]->dfree_tab[2] += cost;

        cost = 1 << 15;
        buffer_table[3][tab_index]->uncoded_bit_tab[3] = 0;
        for (int k = 3; k < 8; k += 4) {
          d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (d0 < cost) {
            cost = d0;
            if (k >= 4) {
              buffer_table[3][tab_index]->uncoded_bit_tab[3] = 1;
            }
            buffer_table[3][tab_index]->next_state_tab[3] = 3;
          }
        }
        buffer_table[3][tab_index]->dfree_tab[3] += cost;
        break;
      }
      case 3: {
        buffer_table[i][tab_index]->uncoded_bit_tab[3] = 0;
        for (int k = 1; k < 8; k += 4) {
          d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (d0 < cost) {
            cost = d0;
            if (k >= 4) {
              buffer_table[1][tab_index]->uncoded_bit_tab[1] = 1;
            }
            buffer_table[1][tab_index]->next_state_tab[1] = 3;
          }
        }
        buffer_table[2][tab_index]->dfree_tab[2] += cost;

        cost = 1 << 15;
        buffer_table[3][tab_index]->uncoded_bit_tab[1] = 0;
        for (int k = 3; k < 8; k += 4) {
          d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (d0 < cost) {
            cost = d0;
            if (k >= 4) {
              buffer_table[3][tab_index]->uncoded_bit_tab[3] = 1;
            }
            buffer_table[3][tab_index]->next_state_tab[3] = 1;
          }
        }
        buffer_table[3][tab_index]->dfree_tab[3] += cost;
        break;
      }
      default: {
        break;
      }
      }
    }
  }

  /*Secondly make desition about last node in the buffer table basing on next 8 states if those are already received*/
  if (is_reday_for_decision <= 8) ++is_reday_for_decision;
  else {
    double lowest_dfree[4] = { 9000 };
    int which_state[4] = { 0 };
    /*check every state looking for lowest cost*/
    for (int i = 0; i < number_of_states; i++) {
      lowest_dfree[4] = { 9000 };
      which_state[4] = { 0 };

      switch (i) {
      case 0: {
        for (int j = 0; j < number_of_states; j++) {
          if (buffer_table[i][tab_index]->dfree_tab[j] < lowest_dfree[j]) {
            lowest_dfree[i] = buffer_table[i][tab_index]->dfree_tab[j];
            which_state[i] = j;
          }
          if (which_state[i] == 0 || which_state[i] == 4) {
            which_state[i] = 0;
          }
          else {
            which_state[i] = 2;
          }
        }
        break;
      }
      case 1: {
        for (int j = 0; j < number_of_states; j++) {
          if (buffer_table[i][tab_index]->dfree_tab[j] < lowest_dfree[j]) {
            lowest_dfree[i] = buffer_table[i][tab_index]->dfree_tab[j];
            which_state[i] = j;
          }
          if (which_state[i] == 2 || which_state[i] == 6) {
            which_state[i] = 0;
          }
          else {
            which_state[i] = 2;
          }
        }
        break;
      }
      case 2: {
        for (int j = 0; j < number_of_states; j++) {
          if (buffer_table[i][tab_index]->dfree_tab[j] < lowest_dfree[j]) {
            lowest_dfree[i] = buffer_table[i][tab_index]->dfree_tab[j];
            which_state[i] = j;
          }
          if (which_state[i] == 1 || which_state[i] == 5) {
            which_state[i] = 1;
          }
          else {
            which_state[i] = 3;
          }
        }
        break;
      }
      case 3: {
        for (int j = 0; j < number_of_states; j++) {
          if (buffer_table[i][tab_index]->dfree_tab[j] < lowest_dfree[j]) {
            lowest_dfree[i] = buffer_table[i][tab_index]->dfree_tab[j];
            which_state[i] = j;
          }
          if (which_state[i] == 3 || which_state[i] == 7) {
            which_state[i] = 3;
          }
          else {
            which_state[i] = 1;
          }
        }
        break;
      }
      }
    }

    double lowestest_dfree = 9000;
    int previous_state = 0;
    for (int i = 0; i < number_of_states; i++) {
      if (lowest_dfree[i] < lowestest_dfree) {
        lowestest_dfree = lowest_dfree[i];
        previous_state = which_state[i];
      }
    }

      /*search for the lowest-cost path and decide what was sent 9 tacts ago*/
    for (int i = (size_of_buffer_table + tab_index); i > tab_index; i--) {
      int index = i % size_of_buffer_table;

      int lowest_dfree = 9000;

      switch (previous_state) {
      case 0: {
        for (int j = 0; j < 8; j += 4) {
          if (buffer_table[previous_state][i]->dfree_tab[j] < lowest_dfree) {
            previous_state = 0;
          }
        }
        for (int j = 1; j < 8; j += 4) {
          if (buffer_table[previous_state][i]->dfree_tab[j] < lowest_dfree) {
            previous_state = 2;
          }
        }
        break;
      }
      case 1: {
        for (int j = 1; j < 8; j += 4) {
          if (buffer_table[previous_state][i]->dfree_tab[j] < lowest_dfree) {
            previous_state = 1;
          }
        }
        for (int j = 3; j < 8; j += 4) {
          if (buffer_table[previous_state][i]->dfree_tab[j] < lowest_dfree) {
            previous_state = 3;
          }
        }
        break;
      }
      case 2: {
        for (int j = 0; j < 8; j += 4) {
          if (buffer_table[previous_state][i]->dfree_tab[j] < lowest_dfree) {
            previous_state = 2;
          }
        }
        for (int j = 1; j < 8; j += 4) {
          if (buffer_table[previous_state][i]->dfree_tab[j] < lowest_dfree) {
            previous_state = 1;
          }
        }
        break;
      }
      case 3: {
        for (int j = 1; j < 8; j += 4) {
          if (buffer_table[previous_state][i]->dfree_tab[j] < lowest_dfree) {
            previous_state = 3;
          }
        }
        for (int j = 3; j < 8; j += 4) {
          if (buffer_table[previous_state][i]->dfree_tab[j] < lowest_dfree) {
            previous_state = 1;
          }
        }
        break;
      }
      }
    }
      //int return_value_coded_bit = reversed_transition_table_[buffer_table[0[(tab_index + size_of_buffer_table - 1) % size_of_buffer_table]->next_state_tab[which_state]][which_state];
    //  if (return_value_coded_bit < 0)
    //  {
    //    cout << "Revested transition table fail. " << endl;
    //    return -1;
    //  }
    //  int return_value_uncoded_bit = buffer_table[0][(tab_index + size_of_buffer_table - 1) % size_of_buffer_table]->uncoded_bit_tab[which_state];
     // return_value = (return_value_uncoded_bit << 1) + return_value_coded_bit;
   
    int return_value_coded_bit = reversed_transition_table_
    int return_value_uncoded_bit = buffer_table[previous_state][(tab_index + size_of_buffer_table - 1) % size_of_buffer_table]->uncoded_bit_tab[previous_state];
    return_value = (return_value_uncoded_bit << 1) + return_value_coded_bit;

    ++which_iteration;
    ++tab_index;
    tab_index %= size_of_buffer_table;
    return return_value;
  }
}

Node::Node()
{
  for (int i = 0; i < 4; i++)
  {
    uncoded_bit_tab[i] = 0;
    dfree_tab[i] = 0;
    next_state_tab[i] = -1;
  }
}

Node::~Node()
{

}

