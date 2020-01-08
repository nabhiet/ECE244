/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 */


#include <galaxy-explorer/AsteroidsObserver.hpp>

// Called whenever a new asteroid appears on the field
void AsteroidsObserver::onAsteroidInRange(Asteroid asteroid) {
    asteroid_list.pushFront(asteroid); // add a new asteroid to the front of the list
}

// Called when an asteroid has moved.
void AsteroidsObserver::onAsteroidUpdate(Asteroid asteroid) {
    AsteroidListItem *tptr = asteroid_list.beforeBegin();
    
    while (tptr->hasNext()) { // traverse the list until the ID is found
        if (tptr->getNext()->getData().getID() == asteroid.getID()) {
            asteroid_list.eraseAfter(tptr); // erase the moved asteroid from the list
            asteroid_list.insertAfter(tptr, asteroid); // insert the updated asteroid
            break;
        }
        else
            tptr = tptr->getNext();
    }
}

// Called when an asteroid leaves the field without being destroyed
void AsteroidsObserver::onAsteroidOutOfRange(Asteroid asteroid) {
    AsteroidListItem *tptr = asteroid_list.beforeBegin();
    
    while (tptr->hasNext()) { // traverse the list until the ID is found
        if (tptr->getNext()->getData().getID() == asteroid.getID()) {
            asteroid_list.eraseAfter(tptr); // erase the destroyed asteroid from the list
            break;
        }
        else
            tptr = tptr->getNext();
    }
}

// Called when an asteroid is destroyed by a phaser shot
void AsteroidsObserver::onAsteroidDestroy(Asteroid asteroid) {
    this->onAsteroidOutOfRange(asteroid); // erase the destroyed asteroid
}
