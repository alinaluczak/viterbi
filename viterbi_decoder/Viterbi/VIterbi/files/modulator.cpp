#include "modulator.h"
#include<iostream>;
using namespace std;

/* Output Table - representing output (complex number), basig on input            */
/*                                                             Re       Im        */
const _complex Modulator::output_table_[number_of_states] = {{ 0.7  ,  -0.7 }, //s0
                                                             { 1    ,  0    }, //s1
                                                             { 0.7  ,  0.7  }, //s2
                                                             { 0    ,  1    }, //s3
                                                             {-0.7  ,  0.7  }, //s4
                                                             { -1   ,  0    }, //s5
                                                             {-0.7  ,  -0.7 }, //s6
                                                             { 0    ,  -1 } }; //s7

Modulator::Modulator()
{
  cout << "Modulator Construcotr here " << endl;

}

Modulator::~Modulator()
{}

_complex Modulator::ModulatorFunction(int input_value)
{
  if (input_value > 7 || input_value < 0)
  {
    cout << "Oops! Input value in modulator is either greater than 7 or less than 0! Aborting." << endl;
    return{0,0};
  }
  return output_table_[input_value];
}
