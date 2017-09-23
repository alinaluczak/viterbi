#include "receiver.h"
#include<iostream>
using namespace std;

/* Modulator Table - representing output (complex number), basig on input                */
/*                                                                    Re       Im        */
const _complex Receiver::modulator_table_[number_of_states_ * 2] = { { 0.7  ,  -0.7 }, //s0
                                                                     { 1    ,  0    }, //s1
                                                                     { 0.7  ,  0.7  }, //s2
                                                                     { 0    ,  1    }, //s3
                                                                     { -0.7 ,  0.7  }, //s4
                                                                     { -1   ,  0    }, //s5
                                                                     { -0.7 , -0.7  }, //s6
                                                                     { 0    ,  -1 } }; //s7


/* Reversed Transition Table - representing output value (decoded bit), basing on present state (column) and prevoius state (row) */
/* The -1 value means it is forbidden state - shuldn' t be accesed and will return error                                          */
const int Receiver::reversed_transition_table_[][number_of_states_] = { { 0, -1, 1, -1 },
                                                                        { 0, -1, 1, -1 },
                                                                        { -1, 0, -1, 1 },
                                                                        { -1, 0, -1, 1 } };

Receiver::Receiver()
{
  is_reday_for_decision_ = 0;
  tab_index_ = 0;
  for (int node = 0; node < size_of_buffer_table_; node++)
  {
    buffer_table_[node] = new Node();
  }
}

Receiver::~Receiver()
{
  for each (Node* node in buffer_table_)
  {
    delete node;
  }
}

int Receiver::ReceiverFunction(_complex received_value)
{

  double distance = 0;
  static int which_iteration = 0;
  int return_value = 5;

  /*Firstly fill the output buffer table basic on newly-come value*/

  if (which_iteration == 0) //it means that prevois state was 00 and not all of the states are accesible (only two) - first received value
  {
    ++which_iteration;
    for (int i = 0; i < number_of_states_; i += 2)
    {
      double cost = 1 << 15;
      buffer_table_[tab_index_]->uncoded_bit_tab_[i] = 0;
      switch (i)
      {

      case 0:
      {
        for (int k = 0; k < 8; k += 4)
        {
          /*calculate distances between received value and possible received values*/
          distance = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (distance < cost)
          {
            cost = distance;
            if (k >= 4)
            {
              buffer_table_[tab_index_]->uncoded_bit_tab_[i] = 1;
            }
            buffer_table_[tab_index_]->previous_state_tab_[i] = 0;
          }
        }
        buffer_table_[tab_index_]->cost_tab_[i] = cost;
        break;
      }

      case 2:
      {
        for (int k = 2; k < 8; k += 4)
        {
          /*calculate distances between received value and possible received values*/
          distance = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (distance < cost)
          {
            cost = distance;
            if (k >= 4)
            {
              buffer_table_[tab_index_]->uncoded_bit_tab_[i] = 1;
            }
            buffer_table_[tab_index_]->previous_state_tab_[i] = 0;
          }
        }
        buffer_table_[tab_index_]->cost_tab_[i] = cost;
        break;
      }
      }
    }
  }

  else if ( which_iteration == 1 ) //it meanes that not all of the transitions are possible becouse it is second received value
  {
    ++which_iteration;
    for (int i = 0; i < number_of_states_; i++)
    {
      double cost = 1 << 15;
      buffer_table_[tab_index_]->uncoded_bit_tab_[i] = 0;
      switch (i)
      {

      case 0:
      {
        for (int k = 0; k < 8; k += 4)
        {
          /*calculate distances between received value and possible received values*/
          distance = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (distance < cost)
          {
            cost = distance;
            if (k >= 4)
            {
              buffer_table_[tab_index_]->uncoded_bit_tab_[i] = 1;
            }
            buffer_table_[tab_index_]->previous_state_tab_[i] = 0;
          }
        }
        int tab_previous_index = ((tab_index_ - 1 ) + size_of_buffer_table_) % size_of_buffer_table_;   //in case the tab_index is zero
        /*add calculated cost to the cost of the path leading to this state*/
        buffer_table_[tab_index_]->cost_tab_[i] = cost + buffer_table_[tab_previous_index]->cost_tab_[buffer_table_[tab_index_]->previous_state_tab_[i]];
        break;
      }

      case 1:
      {
        for (int k = 1; k < 8; k += 4)
        {
          /*calculate distances between received value and possible received values*/
          distance = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (distance < cost)
          {
            cost = distance;
            if (k >= 4)
            {
              buffer_table_[tab_index_]->uncoded_bit_tab_[i] = 1;
            }
            buffer_table_[tab_index_]->previous_state_tab_[i] = 2;
          }
        }
        int tab_previous_index = ((tab_index_ - 1) + size_of_buffer_table_) % size_of_buffer_table_;   //in case the tab_index is zero
        /*add calculated cost to the cost of the path leading to this state*/
        buffer_table_[tab_index_]->cost_tab_[i] = cost + buffer_table_[tab_previous_index]->cost_tab_[buffer_table_[tab_index_]->previous_state_tab_[i]];
        break;
      }

      case 2:
      {
        for (int k = 2; k < 8; k += 4)
        {
          /*calculate distances between received value and possible received values*/
          distance = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (distance < cost)
          {
            cost = distance;
            if (k >= 4)
            {
              buffer_table_[tab_index_]->uncoded_bit_tab_[i] = 1;
            }
            buffer_table_[tab_index_]->previous_state_tab_[i] = 0;
          }
        }
        int tab_previous_index = ((tab_index_ - 1) + size_of_buffer_table_) % size_of_buffer_table_;   //in case the tab_index is zero
        /*add calculated cost to the cost of the path leading to this state*/
        buffer_table_[tab_index_]->cost_tab_[i] = cost + buffer_table_[tab_previous_index]->cost_tab_[buffer_table_[tab_index_]->previous_state_tab_[i]];
        break;
      }

      case 3:
      {
        for (int k = 3; k < 8; k += 4)
        {
          /*calculate distances between received value and possible received values*/
          distance = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (distance < cost)
          {
            cost = distance;
            if (k >= 4)
            {
              buffer_table_[tab_index_]->uncoded_bit_tab_[i] = 1;
            }
            buffer_table_[tab_index_]->previous_state_tab_[i] = 2;
          }
        }
        int tab_previous_index = ((tab_index_ - 1) + size_of_buffer_table_) % size_of_buffer_table_;   //in case the tab_index is zero
        /*add calculated cost to the cost of the path leading to this state*/
        buffer_table_[tab_index_]->cost_tab_[i] = cost + buffer_table_[tab_previous_index]->cost_tab_[buffer_table_[tab_index_]->previous_state_tab_[i]]; 
        break;
      }

      default:
      {
        break;
      }
      }//end of switch
    }//end of for()
  }

  else
  {
    for (int i = 0; i < number_of_states_; i++)
    {
      double lowest_distance = 1 << 15;
      buffer_table_[tab_index_]->uncoded_bit_tab_[i] = 0;
      switch (i)
      {

      case 0:
      {
        for (int k = 0; k < 8; k += 2)
        {
          /*calculate distances between received value and possible received values*/
          distance = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (distance < lowest_distance)
          {
            lowest_distance = distance;
            if (k >= 4)
            {
              buffer_table_[tab_index_]->uncoded_bit_tab_[i] = 1;
            }
            if (k == 0 || k == 4)
            {
              buffer_table_[tab_index_]->previous_state_tab_[i] = 0;
            }
            else
            {
              buffer_table_[tab_index_]->previous_state_tab_[i] = 1;
            }
          }
        }
        int tab_previous_index = ((tab_index_ - 1) + size_of_buffer_table_) % size_of_buffer_table_;   //in case the tab_index is zero
        /*add calculated cost to the cost of the path leading to this state*/
        buffer_table_[tab_index_]->cost_tab_[i] = lowest_distance + buffer_table_[tab_previous_index]->cost_tab_[buffer_table_[tab_index_]->previous_state_tab_[i]];
        break;
      }

      case 1:
      {
        for (int k = 1; k < 8; k += 2)
        {
          /*calculate distances between received value and possible received values*/
          distance = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (distance < lowest_distance)
          {
            lowest_distance = distance;
            if (k >= 4)
            {
              buffer_table_[tab_index_]->uncoded_bit_tab_[i] = 1;
            }
            if (k == 1 || k == 5)
            {
              buffer_table_[tab_index_]->previous_state_tab_[i] = 2;
            }
            else
            {
              buffer_table_[tab_index_]->previous_state_tab_[i] = 3;
            }
          }
        }
        int tab_previous_index = ((tab_index_ - 1) + size_of_buffer_table_) % size_of_buffer_table_;   //in case the tab_index is zero
        /*add calculated cost to the cost of the path leading to this state*/
        buffer_table_[tab_index_]->cost_tab_[i] = lowest_distance + buffer_table_[tab_previous_index]->cost_tab_[buffer_table_[tab_index_]->previous_state_tab_[i]];
        break;
      }

      case 2:
      {
        for (int k = 0; k < 8; k += 2)
        {
          /*calculate distances between received value and possible received values*/
          distance = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (distance < lowest_distance)
          {
            lowest_distance = distance;
            if (k >= 4)
            {
              buffer_table_[tab_index_]->uncoded_bit_tab_[i] = 1;
            }
            if (k == 0 || k == 4)
            {
              buffer_table_[tab_index_]->previous_state_tab_[i] = 1;
            }
            else
            {
              buffer_table_[tab_index_]->previous_state_tab_[i] = 0;
            }
          }
        }
        int tab_previous_index = ((tab_index_ - 1) + size_of_buffer_table_) % size_of_buffer_table_;   //in case the tab_index is zero
        /*add calculated cost to the cost of the path leading to this state*/
        buffer_table_[tab_index_]->cost_tab_[i] = lowest_distance + buffer_table_[tab_previous_index]->cost_tab_[buffer_table_[tab_index_]->previous_state_tab_[i]]; 
        break;
      }

      case 3:
      {
        for (int k = 1; k < 8; k += 2)
        {
          /*calculate distances between received value and possible received values*/
          distance = sqrt(pow(received_value.x - modulator_table_[k].x, 2) + pow(received_value.y - modulator_table_[k].y, 2));
          if (distance < lowest_distance)
          {
            lowest_distance = distance;
            if (k >= 4)
            {
              buffer_table_[tab_index_]->uncoded_bit_tab_[i] = 1;
            }
            if (k == 1 || k == 5)
            {
              buffer_table_[tab_index_]->previous_state_tab_[i] = 3;
            }
            else
            {
              buffer_table_[tab_index_]->previous_state_tab_[i] = 2;
            }
          }
        }
        int tab_previous_index = ((tab_index_ - 1) + size_of_buffer_table_) % size_of_buffer_table_;   //in case the tab_index is zero
        /*add calculated cost to the cost of the path leading to this state*/
        buffer_table_[tab_index_]->cost_tab_[i] = lowest_distance + buffer_table_[tab_previous_index]->cost_tab_[buffer_table_[tab_index_]->previous_state_tab_[i]];
        break;
      }

      default:
      {
        break;
      }
      }//end of switch
    }//end of for()
  }

    /*Secondly make desition about last node in the buffer table basing on next 8 states if those are already received*/
    if (is_reday_for_decision_ < 8)
    {
      ++is_reday_for_decision_;
    }
    else
    {
      /*check every state looking for lowest cost*/
      double lowest_cost = buffer_table_[tab_index_]->cost_tab_[0];
      int which_state = 0;
      for (int j = 1; j < 4; j++)
      {
        if (buffer_table_[tab_index_]->cost_tab_[j] < lowest_cost)
        {
          lowest_cost = buffer_table_[tab_index_]->cost_tab_[j];
          which_state = j;
        }
      }

      /*search for the lowest-cost path and decide what was sent 9 tacts ago*/
      for (int i = (size_of_buffer_table_ + tab_index_); i > tab_index_ + 1; i--)
      {
        int index = i % size_of_buffer_table_;
        which_state = buffer_table_[index]->previous_state_tab_[which_state];
      }
      /*check what was the coded bit - in reversed transition table*/
      int return_value_coded_bit = reversed_transition_table_
                                [buffer_table_[(tab_index_ + 1) % size_of_buffer_table_]->previous_state_tab_[which_state]]  //row
                                [which_state];                                                                               //column
      if (return_value_coded_bit < 0)
      {
        cout << "Revested transition table fail. " << endl;
        return -1;
      }
      /*check wat was the uncoded bit*/
      int return_value_uncoded_bit = buffer_table_[(tab_index_ + 1) % size_of_buffer_table_]->uncoded_bit_tab_[which_state];
      /*put together the MSB and the LSB which gives the decoded value*/
      return_value = (return_value_uncoded_bit << 1) + return_value_coded_bit;
    }

  ++tab_index_;
  tab_index_ %= size_of_buffer_table_;
  return return_value;
}

Node::Node()
{
  for (int i = 0; i < 4; i++)
  {
    uncoded_bit_tab_[i] = 0;
    cost_tab_[i] = 0;
    previous_state_tab_[i] = 0;
  }
}

Node::~Node()
{

}

