//
// Created by robosam2003 on 30/06/2022.
// Statically allocated fifo.

#include "Fifo.h"
#include "Shared.h"


template<class T, unsigned int sz>
Fifo<T, sz>::Fifo() {
    nextFree=0;
    endPointer=0;
}

// Removed for now, leads to ambiguous behavior.
/*template<class T, unsigned int sz>
Fifo<T, sz>::Fifo(std::initializer_list<T> lst) {
    for (int i=0;i<sz;i++)
        elem[i] = lst.begin()[i];
    nextFree=0;
    endPointer=0;
}*/

// Copy constructor
template<class T, unsigned int sz>
Fifo<T, sz>::Fifo(const Fifo &a) {
    for (int i=0;i<sz;i++)
        elem[i] = a.elem[i];
    nextFree=a.nextFree;
    endPointer=a.endPointer;
}

// Copy assignment
template<class T, unsigned int sz>
Fifo<T, sz> &Fifo<T, sz>::operator=(const Fifo &a) {
    for (int i=0;i<sz;i++)
        elem[i] = a.elem[i];
    nextFree=a.nextFree;
    endPointer=a.endPointer;
    return *this;
}

// Move constructor
template<class T, unsigned int sz>
Fifo<T, sz>::Fifo(Fifo &&a) noexcept {
    for (int i=0;i<sz;i++)
        elem[i] = a.elem[i];
    nextFree=a.nextFree;
    endPointer=a.endPointer;
}

// Move assignment
template<class T, unsigned int sz>
Fifo<T, sz> &Fifo<T, sz>::operator=(Fifo &&a) noexcept {
    for (int i=0;i<sz;i++)
        elem[i] = a.elem[i];
    nextFree=a.nextFree;
    endPointer=a.endPointer;
    return *this;
}

// Casting operator
template<class T, unsigned int sz>
template<typename D, unsigned int newsize>
Fifo<T, sz>::operator Fifo<D, newsize>() const {
    unsigned int min = sz < newsize ? sz : newsize;
    min = (min < used_space()) ? min : used_space();
    Fifo<D, newsize> r;
    for (unsigned int i=0;i<min;i++) {
        // c-style casting each element to the new type. This allows Fifos of Vectors to be cast as well!
        D item = (D) elem[i];
        r.push(item);
    }
    return r;
}


template<class T, unsigned int sz>
T &Fifo<T, sz>::operator[](int i) {
    return elem[i%sz]; // if the index is larger than the sz, it wraps around;
}

template<class T, unsigned int sz>
T &Fifo<T, sz>::operator[](int i) const {
    return elem[i%sz]; // if the index is larger than the sz, it wraps around;
}

template<class T, unsigned int sz>
T& Fifo<T, sz>::atFifoIndex(int i) {
    return elem[(endPointer+i) % sz];
}

template<class T, unsigned int sz>
T& Fifo<T, sz>::atFifoIndex(int i) const{
    return elem[(endPointer+i) % sz];
}

template<class T, unsigned int sz>
Fifo_STATUS Fifo<T, sz>::push(const T& item) { // returns the status of the fifo
    if (fifo_status()==Fifo_STATUS::Fifo_FULL) {
        // throw std::length_error("NA"); // throw does not work with arduino :(
        return Fifo_STATUS::Fifo_FULL; // status code
    }
    // otherwise:
    elem[nextFree] = item;
    if (((nextFree+1) % sz) == endPointer) {
        nextFree = -1;
    }
    else{
        nextFree = (++nextFree) % sz; // wrap around /:)
    }
    return Fifo_STATUS::Fifo_GOOD;
}

template<class T, unsigned int sz>
T Fifo<T, sz>::pop() { /// Note: You should check the status of the fifo before calling this function
    if (fifo_status()==Fifo_STATUS::Fifo_EMPTY) {
        //throw std::length_error("NA"); // throw does not work with arduino :(
        // return {Fifo_EMPTY};
        return {0}; // return nothing
    }
    // otherwise
    T r = elem[endPointer];
    if (fifo_status()==Fifo_STATUS::Fifo_FULL) {
        nextFree=endPointer;
    }
    endPointer = (++endPointer) % sz; // wrap around /:)
    return r;
}

template<class T, unsigned int sz>
T Fifo<T, sz>::peekBack() const {
    if (fifo_status()==Fifo_STATUS::Fifo_EMPTY) {
        return {0}; // return 0
    }
    // otherwise
    return elem[endPointer];
}

template<class T, unsigned int sz>
T Fifo<T, sz>::peekBack(int i) const {
    if (fifo_status()==Fifo_STATUS::Fifo_EMPTY) {
        return {0}; // return 0
    }
    // otherwise
    return elem[(endPointer+i) % sz];
}


template<class T, unsigned int sz>
T Fifo<T, sz>::peekFront() const {
    if (fifo_status()==Fifo_STATUS::Fifo_EMPTY) {
        return {0}; // return 0
    }
    // otherwise
    return elem[nextFree-1];
}

template<class T, unsigned int sz>
T Fifo<T, sz>::peekFront(int i) const {
    if (fifo_status()==Fifo_STATUS::Fifo_EMPTY) {
        return {0}; // return 0
    }
    // otherwise
    return elem[(nextFree-1-i) % sz];
}

template<class T, unsigned int sz>
Fifo_STATUS Fifo<T, sz>::fifo_status() const {
    if (nextFree==endPointer) {
        return Fifo_STATUS::Fifo_EMPTY; // fifo empty
    }
    else if (nextFree == -1) { // when the Fifo is full, there is no "next free" location.
        return Fifo_STATUS::Fifo_FULL; // fifo full
    }
    // otherwise, return Fifo_GOOD
    return Fifo_STATUS::Fifo_GOOD;
}

template<class T, unsigned int sz>
int Fifo<T, sz>::size() const {
    return sz;
}

template<class T, unsigned int sz>
int Fifo<T, sz>::free_space() const{
    if (fifo_status()==Fifo_STATUS::Fifo_FULL){
        return 0;
    }
    else if (nextFree>=endPointer) {
        return sz-(nextFree-endPointer);
    }
    else {
        return endPointer-nextFree;
    }
}

template<class T, unsigned int sz>
int Fifo<T, sz>::used_space() const {
    return sz-free_space();
}





