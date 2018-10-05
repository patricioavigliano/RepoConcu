#include "Pipe.h"
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

class LakeConcu{
  public:
    static const char FINED = 'F';
    static const char CONFISCATED = 'C';
    static const int N_CITIES = 5;

    LakeConcu(int, int);
    ~LakeConcu();
    void listenShips();
    void printFinedAndConfiscated();
    pid_t getGeneratorPid();


  private:
//    char** pidShips;
    pid_t generatorPid;
    int confiscatedShips;
    int finedPassengers;
    Pipe* pipe;

    void runShips(int, int);
    void runGenerator();
    int getConfiscatedShips();
    int getFinedPassengers();
};
