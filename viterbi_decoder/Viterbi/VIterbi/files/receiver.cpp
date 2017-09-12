#include "receiver.h"

/* Output Table - representing output (complex number), basig on input            */
/*                                                             Re       Im        */
const _complex Receiver::modulator_table_[number_of_states * 2] = { { 0.7  ,  -0.7 }, //s0
                                                                { 1    ,  0    }, //s1
                                                                { 0.7  ,  0.7  }, //s2
                                                                { 0    ,  1    }, //s3
                                                                { -0.7 ,  0.7  }, //s4
                                                                { -1   ,  0    }, //s5
                                                                { -0.7 , -0.7  }, //s6
                                                                { 0    ,  -1 } }; //s7

const int Receiver::transition_table_[][number_of_states] = { { 0, 2, 0, 2 },
                                                              { 0, 2, 0, 2 },
                                                              { 1, 3, 1, 3 },
                                                              { 1, 3, 1, 3 } };

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
  int uncded_bit[4];
  int d[4];
  int d0 = 0;
  int d1 = 0;

  for (int i = 0; i < number_of_states; i++) {
    d0 = sqrt(pow(received_value.x - modulator_table_[i].x, 2) + pow(received_value.y - modulator_table_[i].y, 2));
    d1 = sqrt(pow(received_value.x - modulator_table_[i + 4].x, 2) + pow(received_value.y - modulator_table_[i + 4].y, 2));

    if (d1 < d0) {
      tab[tab_index]->dfree[i] = d1;
      tab[tab_index]->uncded_bit[i] = 1;
    }
    else
    {
      tab[tab_index]->dfree[i] = d0;
      tab[tab_index]->uncded_bit[i] = 0;
    }
  }
}
