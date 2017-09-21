#include<iostream>
#include<string.h>
using namespace std;

#include"simulation.h"
#include<cmath>

int main()
{
  Simulation *simulation = new Simulation();
  simulation->Start();
  delete simulation;
  
}