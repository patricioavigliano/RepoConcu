#include <iostream>
#include <unistd.h>

using namespace std;

class Ship{
  public:
    static const char FINED = 'F';
    static const char CONFISCATED = 'C';

    Ship();
    ~Ship();

  private:
    int finedPassengers;
};
