#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "Vector/Vector.h"

enum QUEUE_STATUS {
    QUEUE_FULL,
    QUEUE_EMPTY,
    QUEUE_GOOD
};

template<class T>
class QUEUE { /// essentially a circular queue
public:
    explicit QUEUE(int s);

    T& operator[](int i);
    QUEUE_STATUS push(const T& item); // copy constructor
    //QUEUE& operator=(const QUEUE& a);
    
    T pop();

    QUEUE_STATUS queue_status();

    int size();
    int free_space();

private:
    T* elem;
    int nextFree;
    int endPointer;
    int sz;
};

template<>
QUEUE<Vector<double>>::QUEUE(int s) {
    elem = new Vector<double>[s];
    sz = s;
    nextFree=0;
    endPointer=0;
}


template<class T>
QUEUE<T>::QUEUE(int s) {
    elem = new T[s];
    sz = s;
    nextFree=0;
    endPointer=0;
}

template<class T>
T &QUEUE<T>::operator[](int i) {
    return elem[i%sz]; // if the index is larger than the sz, it wraps around;
}

template<class T>
QUEUE_STATUS QUEUE<T>::push(const T& item) {
    if (queue_status()==QUEUE_FULL) {
        // throw std::length_error("NA"); // throw does not work with arduino :(
        return QUEUE_FULL; // status code
    }
    // otherwise:
    elem[nextFree] = item;
    if (((nextFree+1) % sz) == endPointer) {
        nextFree = -1;
    }
    else{
        nextFree = (++nextFree) % sz; // wrap around /:)
    }
    return QUEUE_GOOD;
}

template<class T>
T QUEUE<T>::pop() {
    if (queue_status()==QUEUE_EMPTY) {
        return QUEUE_EMPTY;
    }
    // otherwise
    T r = elem[endPointer];
    if (queue_status()==QUEUE_FULL) {
        nextFree=endPointer;
    }
    endPointer = (++endPointer) % sz; // wrap around /:)
    return r;
}

template<class T>
QUEUE_STATUS QUEUE<T>::queue_status() {
    if (nextFree==endPointer) {
        return QUEUE_EMPTY; // queue empty
    }
    else if (nextFree == -1) { // when the QUEUE is full, there is no "next free" location.
        return QUEUE_FULL; // queue full
    }
    // otherwise, return QUEUE_GOOD
    return QUEUE_GOOD;
}

template<class T>
int QUEUE<T>::size() {
    return sz;
}

template<class T>
int QUEUE<T>::free_space() {
    if (queue_status()==QUEUE_FULL){
        return 0;
    }
    else if (nextFree>=endPointer) {
        return sz-(nextFree-endPointer);
    }
    else {
        return endPointer-nextFree;
    }
}




template<>
Vector<double> &QUEUE<Vector<double>>::operator[](int i) {
    return elem[i]; // if the index is larger than the sz, it wraps around;
}

template<>
QUEUE_STATUS QUEUE<Vector<double>>::push(const Vector<double>& item) {
    if (queue_status()==QUEUE_FULL) {
        // throw std::length_error("NA"); // throw does not work with arduino :(
        return QUEUE_FULL; // status code
    }
    // otherwise:
    elem[nextFree] = item;
    if (((nextFree+1) % sz) == endPointer) {
        nextFree = -1;
    }
    else{
        nextFree = (++nextFree) % sz; // wrap around /:)
    }
    return QUEUE_GOOD;
}

template<>
Vector<double> QUEUE<Vector<double>>::pop() {
    if (queue_status()==QUEUE_EMPTY) {
        Vector<double> rv = {QUEUE_EMPTY, QUEUE_EMPTY, QUEUE_EMPTY};
        return rv;
    }
    // otherwise
    Vector<double> r = elem[endPointer];
    if (queue_status()==QUEUE_FULL) {
        nextFree=endPointer;
    }
    endPointer = (++endPointer) % sz; // wrap around /:)
    return r;
}



#endif //QUEUE_H
