#ifndef FIFO_H
#define FIFO_H

#include <iostream>
#include "Vector/Vector.h"

enum FIFO_STATUS {
    FIFO_FULL,
    FIFO_EMPTY,
    FIFO_GOOD
};

template<class T>
class FIFO { /// essentially a circular queue
public:
    explicit FIFO(int s);

    T& operator[](int i);
    FIFO_STATUS push(const T& item); // copy constructor
    //FIFO& operator=(const FIFO& a);
    
    T pop();

    FIFO_STATUS fifo_status();

    int size();
    int free_space();

private:
    T* elem;
    int nextFree;
    int endPointer;
    int sz;
};

template<>
FIFO<Vector<double>>::FIFO(int s) {
    elem = new Vector<double>[s];
    sz = s;
    nextFree=0;
    endPointer=0;
}


template<class T>
FIFO<T>::FIFO(int s) {
    elem = new T[s];
    sz = s;
    nextFree=0;
    endPointer=0;
}

template<class T>
T &FIFO<T>::operator[](int i) {
    return elem[i%sz]; // if the index is larger than the sz, it wraps around;
}

template<class T>
FIFO_STATUS FIFO<T>::push(const T& item) {
    if (fifo_status()==FIFO_FULL) {
        // throw std::length_error("NA"); // throw does not work with arduino :(
        return FIFO_FULL; // status code
    }
    // otherwise:
    elem[nextFree] = item;
    if (((nextFree+1) % sz) == endPointer) {
        nextFree = -1;
    }
    else{
        nextFree = (++nextFree) % sz; // wrap around /:)
    }
    return FIFO_GOOD;
}

template<class T>
T FIFO<T>::pop() {
    if (fifo_status()==FIFO_EMPTY) {
        return FIFO_EMPTY;
    }
    // otherwise
    T r = elem[endPointer];
    if (fifo_status()==FIFO_FULL) {
        nextFree=endPointer;
    }
    endPointer = (++endPointer) % sz; // wrap around /:)
    return r;
}

template<class T>
FIFO_STATUS FIFO<T>::fifo_status() {
    if (nextFree==endPointer) {
        return FIFO_EMPTY; // fifo empty
    }
    else if (nextFree == -1) { // when the FIFO is full, there is no "next free" location.
        return FIFO_FULL; // fifo full
    }
    // otherwise, return FIFO_GOOD
    return FIFO_GOOD;
}

template<class T>
int FIFO<T>::size() {
    return sz;
}

template<class T>
int FIFO<T>::free_space() {
    if (fifo_status()==FIFO_FULL){
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
Vector<double> &FIFO<Vector<double>>::operator[](int i) {
    return elem[i]; // if the index is larger than the sz, it wraps around;
}

template<>
FIFO_STATUS FIFO<Vector<double>>::push(const Vector<double>& item) {
    if (fifo_status()==FIFO_FULL) {
        // throw std::length_error("NA"); // throw does not work with arduino :(
        return FIFO_FULL; // status code
    }
    // otherwise:
    elem[nextFree] = item;
    if (((nextFree+1) % sz) == endPointer) {
        nextFree = -1;
    }
    else{
        nextFree = (++nextFree) % sz; // wrap around /:)
    }
    return FIFO_GOOD;
}

template<>
Vector<double> FIFO<Vector<double>>::pop() {
    if (fifo_status()==FIFO_EMPTY) {
        Vector<double> rv = {FIFO_EMPTY, FIFO_EMPTY, FIFO_EMPTY};
        return rv;
    }
    // otherwise
    Vector<double> r = elem[endPointer];
    if (fifo_status()==FIFO_FULL) {
        nextFree=endPointer;
    }
    endPointer = (++endPointer) % sz; // wrap around /:)
    return r;
}



#endif //FIFO_H
