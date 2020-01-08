#include <galaxy-explorer/AsteroidList.hpp>

AsteroidListItem::AsteroidListItem() {
    this->next = nullptr;
    this->data = nullptr;
}

AsteroidListItem::AsteroidListItem(Asteroid a) {
    this->next = nullptr;
    this->data = new Asteroid(a); // create a new asteroid
}

AsteroidListItem::~AsteroidListItem() {
}

// Creates an empty list
AsteroidList::AsteroidList() {
    (this->head).setNext(nullptr);
}

// Creates an independent copy of `src`. This means that there is NO shared data or pointers.
AsteroidList::AsteroidList(const AsteroidList& src) {
    const AsteroidListItem* tptr = &(src.head);
    AsteroidListItem* last = &head;

    while (tptr->hasNext()) { // keep inserting asteroids until the list has ended
        tptr = tptr->getNext();
        last = this->insertAfter(last, tptr->getData());
    }
}

// Frees all memory associated with this list
AsteroidList::~AsteroidList() {
    this->clear(); 
}

// Add an asteroid at the beginning of this list
void AsteroidList::pushFront(Asteroid e) {
    this->insertAfter(&head, e); // inserts asteroid after the head
}

// Return a reference to the first asteroid
Asteroid& AsteroidList::front() {
    if (this->isEmpty())
        return *(Asteroid*)nullptr;
    return head.getNext()->getData(); // returns the asteroid after the head
}

// Return a reference to the first asteroid
const Asteroid& AsteroidList::front() const {
    if (this->isEmpty())
        return *(Asteroid*)nullptr;
    return head.getNext()->getData(); // returns the asteroid after the head
}

// Are there no entities in this list?
bool AsteroidList::isEmpty() const {
    return (!(head.hasNext())); // returns true if there is nothing after the head
}

// The number of entities in this list
int AsteroidList::size() const {
    if (this->isEmpty())
        return 0;

    int count = 1; // starts at once since there is at least 1 asteroid that exists
    const AsteroidListItem* tptr = head.getNext();
    while (tptr->hasNext()) { // increment count until there is no asteroid after the current
        count++;
        tptr = tptr->getNext();
    }
    return count;
}

// Return an item corresponding to the position immediately before the first asteroid.
AsteroidListItem* AsteroidList::beforeBegin() {
    if (this->isEmpty())
        this->beforeEnd();
    return &head; // return the head if the list isn't empty
}

// Return an item corresponding to the position immediately before the first asteroid.
const AsteroidListItem* AsteroidList::beforeBegin() const {
    if (this->isEmpty())
        this->beforeEnd();
    return &head; // return the head if the list isn't empty
}

// Return an item corresponding to the first asteroid.
AsteroidListItem* AsteroidList::begin() {
    if (this->isEmpty())
        this->end();
    return head.getNext(); // returns the item after the head if the list isn't empty
}

// Return an item corresponding to the first asteroid.
const AsteroidListItem* AsteroidList::begin() const {
    if (this->isEmpty())
        this->end();
    return head.getNext(); // returns the item after the head if the list isn't empty
}

// Return an item corresponding to the position of the last asteroid.
AsteroidListItem* AsteroidList::beforeEnd() {
    if (this->isEmpty())
        return nullptr;

    AsteroidListItem* tptr = &head;
    while (tptr->hasNext()) { // traverse the list and return the last item if the list isn't empty
        tptr = tptr->getNext(); 
    }
    return tptr;
}

// Return an item corresponding to the position of the last asteroid.
const AsteroidListItem* AsteroidList::beforeEnd() const {
    if (this->isEmpty())
        return nullptr;

    const AsteroidListItem* tptr = &head;
    while (tptr->hasNext()) { // traverse the list and return the last item if the list isn't empty
        tptr = tptr->getNext();
    }
    return tptr;
}

// Return an item corresponding to the position immediately after the last asteroid.
AsteroidListItem* AsteroidList::end() {
    return nullptr;
}

// Return an item corresponding to the position immediately after the last asteroid.
const AsteroidListItem* AsteroidList::end() const {
    return nullptr;
}

// Add a single asteroid to this list, in the position immediately after `prev`.
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    AsteroidListItem* nptr = new AsteroidListItem(e);

    if (prev->hasNext()) {
        AsteroidListItem* old = prev->getNext(); // old item points to the item after the previous
        prev->setNext(nptr); // previous points to the new item
        nptr->setNext(old);  // the new item points to the item after the previous
    } 
    else
        prev->setNext(nptr);
    return nptr; // returns the item that was inserted
}

// Add independent copies of the entities in `others` to this list, placed immediately after `insertion_point`,
// in the same order as `others`.
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    const AsteroidListItem* tptr = &(others.head);
    
    while (tptr->hasNext()) {
        tptr = tptr->getNext();
        prev = this->insertAfter(prev, tptr->getData());
    }
    return prev; // Returns the last item that was inserted
}

// Given a position in this list, delete the following asteroid.
AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    if (prev->hasNext()) {
        AsteroidListItem* old = prev->getNext(); // old item points to the asteroid after the previous
        prev->setNext(prev->getNext()->getNext()); // previous points to 2 items after the previous
        delete old; // list item that followed the erased item
        return prev->getNext(); // return the list item that followed the erased item
    }
    else 
        return this->end();
}

// Make this list empty, free all nodes.
void AsteroidList::clear() {
    while (head.hasNext()) // erase everything after the head
        this->eraseAfter(&head); 
}

// Makes this list an independent copy of `src`. This means that there is NO shared data or pointers.
AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    if (this == &src) return (*this); // return this list if src is equal to this list
    // clear the list and then create a copy from src into this list
    this->clear();
    this->insertAfter(&head, src);
    return(*this);
}
