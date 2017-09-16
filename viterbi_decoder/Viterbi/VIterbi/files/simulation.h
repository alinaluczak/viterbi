#ifndef VITERBI_SIMULATION_H
#define VITERBI_SIOMUALTON_H

#include "system.h"
#include "results.h"

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

