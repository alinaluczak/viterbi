#ifndef VITERBI_GENERATOR_H_
#define VITERBI_GENERATOR_H_
#include<cmath>

/*Class represents a pseudo-random number generator*/
class Generator
{
public:
  Generator(int seed, double lambda = 0.02);
  ~Generator();
  int RandomNumber();
  unsigned int RandomBit();
  double Random01();
  double Expotential();

private:
  int seed_;
  double lambda_;
  const double M = 2147483647.0;
  const int A = 16807;
  const int Q = 127773;
  const int R = 2836;

};
#endif //VITERBI_GENERATOR_H_
