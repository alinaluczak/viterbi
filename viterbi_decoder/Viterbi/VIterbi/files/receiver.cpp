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

/* Output Table - representing output, basig on current state (row) and input (column) */
const int Receiver::output_table_[][number_of_states] = { { 0,2,4,6 },
                                                          { 2,0,6,4 },
                                                          { 1,3,5,7 },
                                                          { 3,1,7,5 } };

Receiver::Receiver()
{
  is_reday_for_decision = 0;
  tab_index = -1;
  for each (Node* node in buffer_table)
  {
    node = new Node();
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

  int d0 = 0;

  /*Firstly fill the output buffer table basic on newly-come value*/

  for (int i = 0; i < number_of_states; i++)
  {
    int cost = 100;
    buffer_table[tab_index]->uncoded_bit[i] = 0;
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
              buffer_table[tab_index]->uncoded_bit[i] = 1;
            }
            if (k == 0 || k == 4)
            {
              buffer_table[tab_index]->prevoius_state[i] = 0;
            }
            else
            {
              buffer_table[tab_index]->prevoius_state[i] = 1;
            }
          }
        }
        buffer_table[tab_index]->dfree[i] += cost;
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
              buffer_table[tab_index]->uncoded_bit[i] = 1;
            }
            if (k == 1 || k == 5)
            {
              buffer_table[tab_index]->prevoius_state[i] = 2;
            }
            else
            {
              buffer_table[tab_index]->prevoius_state[i] = 3;
            }
          }
        }
        buffer_table[tab_index]->dfree[i] += cost;
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
              buffer_table[tab_index]->uncoded_bit[i] = 1;
            }
            if (k == 0 || k == 4)
            {
              buffer_table[tab_index]->prevoius_state[i] = 1;
            }
            else
            {
              buffer_table[tab_index]->prevoius_state[i] = 0;
            }
          }
        }
        buffer_table[tab_index]->dfree[i] += cost;
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
              buffer_table[tab_index]->uncoded_bit[i] = 1;
            }
            if (k == 1 || k == 5)
            {
              buffer_table[tab_index]->prevoius_state[i] = 3;
            }
            else
            {
              buffer_table[tab_index]->prevoius_state[i] = 2;
            }
          }
        }
        buffer_table[tab_index]->dfree[i] += cost;
        break;
      }
      default:
      {
        break;
      }
    }//end of switch
  }//end of for()

  /*Secondly make desition about last node in the buffer table basing on next 8 states if those are already received*/
  if (is_reday_for_decision <= 8)
  {
    ++is_reday_for_decision;
  }
  else
  {
    /*search for the lowest-cost path and decide what was sent*/
    for (int i = (size_of_buffer_table + tab_index); i > tab_index; i--)
    {
      int index = i % size_of_buffer_table;

    }
  }
  return 0;
}
