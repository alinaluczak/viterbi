#include "simulation.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

Simulation::Simulation()
{
  number_of_simulation = 0;
}


Simulation::~Simulation()
{
}

int Simulation::Start()
{
  SeedGeneration();
  fstream seed_file;
  seed_file.open("files/seeds.txt", ios::in);
  if (seed_file.good() != true)
  {
    cout << "Error occured during seed generation. Aborting" << endl;
    return -1;
  }
  int seeds[2] = { 0 };
  System *system;

  cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "Simulation of TCM Encoder." << endl;
  cout << "10 simulations with different seeds." << endl;
  cout << "Made by Alina Luczak and Robert Kaczmarek." << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;

  int end_condition;
  cout << "Please enter the end condition: (the number of the correct bits received?)" << endl;
  cin >> end_condition;
  if (end_condition <= 0)
  {
    cout << "Wrong value for the end condition. Aborting." << endl;
    return -1;
  }
  double lambda;
  cout << "Please enter lambda parameter ( for the generaotrs )." << endl;
  cin >> lambda;
  if (lambda <= 0)
  {
    cout << "Wrong value for lambda. Aborting." << endl;
    return -1;
  }
  while (number_of_simulation < 10)
  {
    cout << endl << "*********************" << endl;
    cout << "Number of simulation: " << number_of_simulation + 1 << endl;
    cout << "*********************" << endl;
    for (int i = 0; i < 2; i++)
    {
      seed_file >> seeds[i];
    }
    system = new System(number_of_simulation, end_condition, seeds, lambda);
    system->MainLoop();
    delete system;
    ++number_of_simulation;
  }

  cout << endl << endl << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "Results form single simulation: " << endl;
 // wyniki->ObliczWartosci();
  cout << endl << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  return 0;

}

void Simulation::SeedGeneration()
{
  Generator *gen = new Generator(123);

  fstream seed_file;
  seed_file.open("files/seeds.txt", ios::out);
  int i = 0;
  int k = gen->RandomNumber();

  //20 seeds: (one for bit generator + one for channel) x 10 simulations
  for (int j = 0; j < 20; j++)
  {
    while (i > 0)
    {
      k = gen->RandomNumber();
      --i;
    }
    i = 150000;
    seed_file << k << endl;
  }
  seed_file.close();
  return;

}


