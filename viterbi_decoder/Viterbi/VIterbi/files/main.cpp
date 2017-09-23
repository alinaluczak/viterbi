#include<iostream>
#include<string>
using namespace std;

#include"simulation.h"
#include<cmath>

int main()
{
  Simulation *simulation = new Simulation();
  simulation->Start();
  delete simulation;
  string str;
  getline(cin, str);
  getline(cin, str);
  getline(cin, str);

}