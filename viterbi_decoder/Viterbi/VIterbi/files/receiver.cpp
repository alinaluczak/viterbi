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
  tab_index = -1;
  for each (Node* node in tab)
  {
    node = new Node();
  }
}


Receiver::~Receiver()
{
}

int Receiver::ReceiverFunction(_complex received_value)
{
  ++tab_index;
  tab_index %= 4;
  int d0 = 0;
  int d1 = 0;
  int d2 = 0;
  int d3 = 0;

  for (int i = 0; i < number_of_states; i++)
  {
    int cost = 100;
    tab[tab_index]->uncoded_bit[i] = 0;
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
            tab[tab_index]->uncoded_bit[i] = 1;
          }
          if (k == 0 || k == 4)
          {
            tab[tab_index]->prevoius_state[i] = 0;
          }
          else
          {
            tab[tab_index]->prevoius_state[i] = 1;
          }
        }
      }
      tab[tab_index]->dfree[i] += cost;
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
            tab[tab_index]->uncoded_bit[i] = 1;
          }
          if (k == 1 || k == 5)
          {
            tab[tab_index]->prevoius_state[i] = 2;
          }
          else
          {
            tab[tab_index]->prevoius_state[i] = 3;
          }
        }
      }
      tab[tab_index]->dfree[i] += cost;
      break;
    }
    case 2:
      for (int k = 0; k < 8; k += 2)
      {
        d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
        if (d0 < cost)
        {
          cost = d0;
          if (k >= 4)
          {
            tab[tab_index]->uncoded_bit[i] = 1;
          }
          if (k == 0 || k == 4)
          {
            tab[tab_index]->prevoius_state[i] = 1;
          }
          else
          {
            tab[tab_index]->prevoius_state[i] = 0;
          }
        }
      }
      tab[tab_index]->dfree[i] += cost;
      break;
    case 3:
      for (int k = 1; k < 8; k += 2)
      {
        d0 = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
        if (d0 < cost)
        {
          cost = d0;
          if (k >= 4)
          {
            tab[tab_index]->uncoded_bit[i] = 1;
          }
          if (k == 1 || k == 5)
          {
            tab[tab_index]->prevoius_state[i] = 3;
          }
          else
          {
            tab[tab_index]->prevoius_state[i] = 2;
          }
        }
      }
      tab[tab_index]->dfree[i] += cost;
      break;
    default:
      break;
    }
  }
}
