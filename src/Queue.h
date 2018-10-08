#ifndef QUEUE_H_
#define QUEUE_H_

#define TOURIST 1
#define HAS_TICKET 1

#include "Semaforo.h"
#include "MemoriaCompartida.h"

struct Passenger {
    int id;
    short int ticket;
    short int origin;
    short int destination;
    short int tourist;
};

class Queue {
  public:
    static char const* goQueueFilename;
    static char const* backQueueFilename;
    static char const* newPassengerOrder;
    static char const* walkingTouristOrder;
    static const int size = 10;

    Queue(const char* filename, int id);
    void enqueueNewPassenger(int id);
    void enqueueWalkingTourist(int touristId, int destinationDock, int hasTicket);
    Passenger getNextPassenger();
    void flush();
    ~Queue();

  private:
    int pos = 0;
    Semaforo semaforo_prod;
    Semaforo semaforo_cons;
    MemoriaCompartida<Passenger> buffer;
    void buyTicket(Passenger passenger);
    void writePassenger(Passenger passenger);
    Passenger createNewPassenger(int id);
};


#endif /* QUEUE_H_ */
