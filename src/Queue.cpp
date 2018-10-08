#include "Queue.h"
#include "Logger.h"
#include <string>
#include <stdlib.h>
#include <time.h>

#define TOURIST 1
#define BUY_TICKET_PROBABILITY 0.87

std::string s = "test";
Logger logger(s);

Queue::Queue(const char *filename, int id) : semaforo_prod(filename, id), semaforo_cons(filename, id) {

}

void Queue::enqueueNewPassenger(int id) {
    this->semaforo_prod.p();
    Passenger passenger = this->createNewPassenger(id);
    this->buyTicket(passenger);
    this->writePassenger(passenger);
    this->semaforo_cons.v();
    this->pos++;
}

void Queue::enqueueWalkingTourist(int touristId, int destinationDock, int hasTicket) {
    this->semaforo_prod.p();
    Passenger passenger;
    passenger.destination = destinationDock;
    passenger.id = touristId;
    passenger.ticket = hasTicket;
    passenger.tourist = TOURIST;
    std::string str("Dock : Tourist walk to next city.");
    logger.write(str);
    this->writePassenger(passenger);
    this->semaforo_cons.v();
    this->pos++;
}

Passenger Queue::getNextPassenger() {
    this->semaforo_cons.p();
    Passenger passenger = this->readPassenger();
    this->semaforo_prod.v();
    this->pos++;
    return passenger;
}

void Queue::buyTicket(Passenger passenger) {
  if (passenger.ticket == 0 && rand() > BUY_TICKET_PROBABILITY) {
    //add id of dock
    std::string str("Dock : Passenger buy a ticket.");
    logger.write(str);
    passenger.ticket = 1;
  }
}

Passenger Queue::createNewPassenger(int id) {
    Passenger passenger;
    passenger.id = id;
    passenger.destination = rand() % 4 + 1;
    passenger.tourist = rand() % 1;
    return passenger;
}

void Queue::writePassenger(Passenger passenger) {
  this->buffer.escribir(passenger, this->pos);
  this->pos++;
  std::string str("Dock : Passenger pass through turnstile.");
  logger.write(str);
}
