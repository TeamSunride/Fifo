//
// Created by robos on 30/06/2022.
//

#include "Fifo.h"



template<class T>
Fifo<T>::Fifo(int s) {
    elem = new T[s];
    sz = s;
    nextFree=0;
    endPointer=0;
}

template<class T>
T &Fifo<T>::operator[](int i) {
    return elem[i%sz]; // if the index is larger than the sz, it wraps around;
}

template<class T>
Fifo_STATUS Fifo<T>::push(const T& item) {
    if (fifo_status()==Fifo_FULL) {
        // throw std::length_error("NA"); // throw does not work with arduino :(
        return Fifo_FULL; // status code
    }
    // otherwise:
    elem[nextFree] = item;
    if (((nextFree+1) % sz) == endPointer) {
        nextFree = -1;
    }
    else{
        nextFree = (++nextFree) % sz; // wrap around /:)
    }
    return Fifo_GOOD;
}

template<class T>
T Fifo<T>::pop() {
    if (fifo_status()==Fifo_EMPTY) {
        return Fifo_EMPTY;
    }
    // otherwise
    T r = elem[endPointer];
    if (fifo_status()==Fifo_FULL) {
        nextFree=endPointer;
    }
    endPointer = (++endPointer) % sz; // wrap around /:)
    return r;
}

template<class T>
Fifo_STATUS Fifo<T>::fifo_status() {
    if (nextFree==endPointer) {
        return Fifo_EMPTY; // fifo empty
    }
    else if (nextFree == -1) { // when the Fifo is full, there is no "next free" location.
        return Fifo_FULL; // fifo full
    }
    // otherwise, return Fifo_GOOD
    return Fifo_GOOD;
}

template<class T>
int Fifo<T>::size() {
    return sz;
}

template<class T>
int Fifo<T>::free_space() {
    if (fifo_status()==Fifo_FULL){
        return 0;
    }
    else if (nextFree>=endPointer) {
        return sz-(nextFree-endPointer);
    }
    else {
        return endPointer-nextFree;
    }
}


//#ifdef VECTOR_LIBRARY_H
#include "Vector.h"


template<> inline
Vector<double> &Fifo<Vector<double>>::operator[](int i) {
    return elem[i]; // if the index is larger than the sz, it wraps around;
}

template<> inline
Fifo_STATUS Fifo<Vector<double>>::push(const Vector<double>& item) {
    if (fifo_status()==Fifo_FULL) {
        // throw std::length_error("NA"); // throw does not work with arduino :(
        return Fifo_FULL; // status code
    }
    // otherwise:
    elem[nextFree] = item;
    if (((nextFree+1) % sz) == endPointer) {
        nextFree = -1;
    }
    else{
        nextFree = (++nextFree) % sz; // wrap around /:)
    }
    return Fifo_GOOD;
}

template<> inline
Vector<double> Fifo<Vector<double>>::pop() {
    if (fifo_status()==Fifo_EMPTY) {
        Vector<double> rv = {Fifo_EMPTY, Fifo_EMPTY, Fifo_EMPTY};
        return rv;
    }
    // otherwise
    Vector<double> r = {0,0,0};
    r = {elem[endPointer][0], elem[endPointer][1], elem[endPointer][2]};
    if (fifo_status()==Fifo_FULL) {
        nextFree=endPointer;
    }
    endPointer = (++endPointer) % sz; // wrap around /:)

    return r;
}

//#endif
