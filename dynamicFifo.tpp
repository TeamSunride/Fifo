//
// Created by robos on 30/06/2022.
//

#include "DynamicFifo.h"
#include "Vector.h"



template<class T>
DynamicFifo<T>::DynamicFifo(int s) {
    elem = new T[s]; // allocates on the free store (the heap)
    sz = s;
    nextFree=0;
    endPointer=0;
}

/*
template<class T>
Fifo<T>::Fifo(std::initializer_list<T> lst) {
    elem = new T[lst.size()];
    sz = static_cast<unsigned int>(lst.size());
    for (int i=0;i<sz;i++)
        elem[i] = lst.begin()[i];
    nextFree=0;
    endPointer=0;
}
*/

template<class T>
T &DynamicFifo<T>::operator[](int i) {
    return elem[i%sz]; // if the index is larger than the sz, it wraps around;
}

template<class T>
T &DynamicFifo<T>::operator[](int i) const {
    return elem[i%sz]; // if the index is larger than the sz, it wraps around;
}

template<class T>
T& DynamicFifo<T>::atFifoIndex(int i) {
    return elem[(endPointer+i) % sz];
}

template<class T>
T& DynamicFifo<T>::atFifoIndex(int i) const{
    return elem[(endPointer+i) % sz];
}


template<class T>
typename DynamicFifo<T>::Fifo_STATUS DynamicFifo<T>::push(const T& item) {
    if (fifo_status()==Fifo_STATUS::Fifo_FULL) {
        // throw std::length_error("NA"); // throw does not work with arduino :(
        return Fifo_STATUS::Fifo_FULL; // status code
    }
    // otherwise:
    elem[nextFree] = item;
    if (((nextFree+1) % sz) == static_cast<unsigned int>(endPointer)) {
        nextFree = -1;
    }
    else{
        nextFree++;
        nextFree = (nextFree) % sz; // wrap around /:)
    }
    return Fifo_STATUS::Fifo_GOOD;
}

template<class T>
T DynamicFifo<T>::pop() { /// Note: You should check the status of the fifo before calling this function
    if (fifo_status()==Fifo_STATUS::Fifo_EMPTY) {
        return {0}; // return 0
    }
    // otherwise
    T r = elem[endPointer];
    if (fifo_status()==Fifo_STATUS::Fifo_FULL) {
        nextFree=endPointer;
    }
    endPointer++;
    endPointer = (endPointer) % sz; // wrap around /:)
    return r;
}


template<class T>
T DynamicFifo<T>::peekBack() const { // GitHub copilot for the win
    if (fifo_status()==Fifo_STATUS::Fifo_EMPTY) {
        return {0}; // return 0
    }
    // otherwise
    return elem[endPointer];
}

template<class T>
T DynamicFifo<T>::peekBack(int i) const {
    if (fifo_status()==Fifo_STATUS::Fifo_EMPTY) {
        return {0}; // return 0
    }
    // otherwise
    return elem[(endPointer+i) % sz];
}



template<class T>
T DynamicFifo<T>::peekFront() const {
    if (fifo_status()==Fifo_STATUS::Fifo_EMPTY) {
        return {0}; // return 0
    }
    // otherwise
    return elem[nextFree-1];
}

template<class T>
T DynamicFifo<T>::peekFront(int i) const {
    if (fifo_status()==Fifo_STATUS::Fifo_EMPTY) {
        return {0}; // return 0
    }
    // otherwise
    return elem[(nextFree-1-i) % sz];
}

template<class T>
typename DynamicFifo<T>::Fifo_STATUS DynamicFifo<T>::fifo_status() const {
    if (nextFree==endPointer) {
        return Fifo_STATUS::Fifo_EMPTY; // fifo empty
    }
    else if (nextFree == -1) { // when the Fifo is full, there is no "next free" location.
        return Fifo_STATUS::Fifo_FULL; // fifo full
    }
    // otherwise, return Fifo_GOOD
    return Fifo_STATUS::Fifo_GOOD;
}

template<class T>
int DynamicFifo<T>::size() const{
    return sz;
}

template<class T>
int DynamicFifo<T>::free_space() const{
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

template<class T>
template<typename D>
DynamicFifo<T>::operator DynamicFifo<D>() const {
    DynamicFifo<D> r(sz);
    for (int i=0;i<used_space();i++) {
        D item = static_cast<D>(elem[i]);
        r.push(item);
    }
    return r;
}

// copy constructor
template<class T>
DynamicFifo<T>::DynamicFifo(const DynamicFifo &a) {
    elem = new T[a.sz];
    sz = a.sz;
    nextFree = a.nextFree;
    endPointer = a.endPointer;
    for (int i=0;i<sz;i++) {
        elem[i] = a.elem[i];
    }
}

// copy assignment operator
template<class T>
DynamicFifo<T> &DynamicFifo<T>::operator=(const DynamicFifo &a) {
    T* p = new T[a.sz];
    for (int i=0;i<a.sz;i++) {
        p[i] = a.elem[i];
    }
    delete[] elem; // delete old elems
    elem = p; // assign new elems
    sz = a.sz;
    nextFree = a.nextFree;
    endPointer = a.endPointer;
    return *this;
}

// move constructor
template<class T>
DynamicFifo<T>::DynamicFifo(DynamicFifo &&a) noexcept {
    elem = a.elem;
    sz = a.sz;
    nextFree = a.nextFree;
    endPointer = a.endPointer;
    a.elem = nullptr;
}

// move assignment operator
template<class T>
DynamicFifo<T> &DynamicFifo<T>::operator=(DynamicFifo &&a) noexcept {
    if (this != &a) {
        delete[] elem;
        elem = a.elem;
        sz = a.sz;
        nextFree = a.nextFree;
        endPointer = a.endPointer;
        a.elem = nullptr;
    }
    return *this;
}

template<class T>
int DynamicFifo<T>::used_space() const {
    return sz-free_space();
}
