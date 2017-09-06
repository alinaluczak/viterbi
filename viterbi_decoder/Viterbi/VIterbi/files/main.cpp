#include<iostream>
#include<string.h>
using namespace std;

#include"coder.h"
#include"channel.h"
#include<cmath>

int main()
{
  cout << "Here's our Great Project! " << endl;
  Coder *coder = new Coder();
  int result = coder->CoderFunction(1);
  cout << "Result: " << result << endl;

  _complex complex;
  Channel *channel = new Channel();
  for (int i = 0; i < 30; i++)
  {
    complex.x = 1;
    complex.y = 1;
    channel->ChannelFunction(complex);
    cout << "Complex with noise:  " << complex.x << "+ i" << complex.y << endl;
  }
  char a;
  cin >> a;
  cout << endl;
}