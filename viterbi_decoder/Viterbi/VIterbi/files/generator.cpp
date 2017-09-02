#include "generator.h"
#include<iostream>
using namespace std;

Generator::Generator(int seed, double lambda):
seed_(seed),lambda_(lambda){}

Generator::~Generator(){}

int Generator::RandomNumber()
{
  int h = seed_ / Q;
  seed_ = A*(seed_ - Q*h) - R*h;
  if (seed_ < 0)
    seed_ = seed_ + static_cast<int>(M);
  return seed_;
}

double Generator::Random01()
{
  return ((RandomNumber()%99)+1)/100.0;
}

/*Expotential Distribution*/
double Generator::Expotential()
{
  double k = Random01();
  return -(1.0/lambda_)*log(k);
}
