#ifndef VITERBI_SIMULATION_H
#define VITERBI_SIOMUALTON_H

#include "system.h"
#include "results.h"

/*Class that creates ten systems and collects results - BER values*/
class Simulation
{
public:
  Simulation();
  ~Simulation();
  int Start();

private:
  int number_of_simulation;
  void SeedGeneration();
};

#endif //VITERBI_SIOMUALTON_H

