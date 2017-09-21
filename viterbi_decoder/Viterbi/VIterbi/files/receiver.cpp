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
  for (int node = 0; node < size_of_buffer_table; node++)
  {
    buffer_table[node] = new Node();
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

  /*Firstly fill the output buffer table basic on newly-come value*/

  for (int i = 0; i < number_of_states; i++)
  {
    double cost = 1 << 15;
    buffer_table[tab_index]->uncoded_bit_tab[i] = 0;
    switch (i)
    {
      case 0:
      { 
        for (int k = 0; k < 8; k += 2)
        {
          d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (d0 < cost)
          {
            cost = d0;
            if (k >= 4)
            {
              buffer_table[tab_index]->uncoded_bit_tab[i] = 1;
            }
            if (k == 0 || k == 4)
            {
              buffer_table[tab_index]->prevoius_state_tab[i] = 0;
            }
            else
            {
              buffer_table[tab_index]->prevoius_state_tab[i] = 1;
            }
          }
        }
        buffer_table[tab_index]->dfree_tab[i] += cost;
        break;
      }
      case 1:
      {
        for (int k = 1; k < 8; k += 2)
        {
          d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (d0 < cost)
          {
            cost = d0;
            if (k >= 4)
            {
              buffer_table[tab_index]->uncoded_bit_tab[i] = 1;
            }
            if (k == 1 || k == 5)
            {
              buffer_table[tab_index]->prevoius_state_tab[i] = 2;
            }
            else
            {
              buffer_table[tab_index]->prevoius_state_tab[i] = 3;
            }
          }
        }
        buffer_table[tab_index]->dfree_tab[i] += cost;
        break;
      }
      case 2:
      {
        for (int k = 0; k < 8; k += 2)
        {
          d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (d0 < cost)
          {
            cost = d0;
            if (k >= 4)
            {
              buffer_table[tab_index]->uncoded_bit_tab[i] = 1;
            }
            if (k == 0 || k == 4)
            {
              buffer_table[tab_index]->prevoius_state_tab[i] = 1;
            }
            else
            {
              buffer_table[tab_index]->prevoius_state_tab[i] = 0;
            }
          }
        }
        buffer_table[tab_index]->dfree_tab[i] += cost;
        break;
      }
      case 3:
      {
        for (int k = 1; k < 8; k += 2)
        {
          d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (d0 < cost)
          {
            cost = d0;
            if (k >= 4)
            {
              buffer_table[tab_index]->uncoded_bit_tab[i] = 1;
            }
            if (k == 1 || k == 5)
            {
              buffer_table[tab_index]->prevoius_state_tab[i] = 3;
            }
            else
            {
              buffer_table[tab_index]->prevoius_state_tab[i] = 2;
            }
          }
        }
        buffer_table[tab_index]->dfree_tab[i] += cost;
        break;
      }
      default:
      {
        break;
      }
    }//end of switch
  }//end of for()

  int return_value = 0;

  /*Secondly make desition about last node in the buffer table basing on next 8 states if those are already received*/
  if (is_reday_for_decision <= 8)
  {
    ++is_reday_for_decision;
  }
  else
  {

    /*check every state looking for lowest cost*/
    double lowest_dfree = buffer_table[tab_index]->dfree_tab[0];
    int which_state = 0;
    for (int j = 1; j < 4; j++)
    {
      if (buffer_table[tab_index]->dfree_tab[j] < lowest_dfree)
      {
        lowest_dfree = buffer_table[tab_index]->dfree_tab[j];
        which_state = j;
      }
    }
    /*search for the lowest-cost path and decide what was sent 9 tacts ago*/
    for (int i = (size_of_buffer_table + tab_index); i > tab_index; i--)
    {
      int index = i % size_of_buffer_table;
      which_state = buffer_table[index]->prevoius_state_tab[which_state];
    }
    int return_value_coded_bit = reversed_transition_table_[buffer_table[(tab_index + size_of_buffer_table - 1) % size_of_buffer_table]->prevoius_state_tab[which_state]][which_state];
    if (return_value_coded_bit < 0)
    {
      cout << "Revested transition table fail. " << endl;
      return -1;
    }
    int return_value_uncoded_bit = buffer_table[(tab_index + size_of_buffer_table - 1) % size_of_buffer_table]->uncoded_bit_tab[which_state];
    return_value = (return_value_uncoded_bit << 1) + return_value_coded_bit;
  }
  return return_value;
}

Node::Node()
{
  for (int i = 0; i < 4; i++)
  {
    uncoded_bit_tab[i] = 0;
    dfree_tab[i] = 0;
    prevoius_state_tab[i] = 0;
  }
}

Node::~Node()
{

}

