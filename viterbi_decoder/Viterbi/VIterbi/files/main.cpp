#include<iostream>
#include<string>
#include<cmath>
#include"simulation.h"
using namespace std;

int main()
{
  Simulation *simulation = new Simulation();
  simulation->Start();
  delete simulation;
  string str;
  getline(cin, str);
  getline(cin, str);

}