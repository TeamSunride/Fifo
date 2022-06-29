#ifndef FIFO_H
#define FIFO_H

#include <iostream>


enum FIFO_STATUS {
    FIFO_FULL,
    FIFO_EMPTY,
    FIFO_GOOD
};

template<typename T>
class FIFO { /// essentially a circular queue
public:
    explicit FIFO(int s);

    FIFO<T>& operator[](int i);
    FIFO_STATUS push(T item);
    FIFO_STATUS push(T item[]);


    T pop();
    T* pop(int num);

    FIFO_STATUS fifo_status();

private:
    T* elem;
    int startPointer;
    int endPointer;
    int sz;
};

template<typename T>
FIFO<T>::FIFO(int s) {
    elem = new T[s];
    sz = s;
    startPointer=0;
    endPointer=0;
}

template<typename T>
FIFO<T> &FIFO<T>::operator[](int i) {
    return elem[i%sz]; // if the index is larger than the sz, it wraps around;
}

template<typename T>
FIFO_STATUS FIFO<T>::push(T item) {
    if (fifo_status()==FIFO_FULL) {
        // throw std::length_error("NA"); // throw does not work with arduino :(
        return FIFO_FULL; // status code
    }
    // otherwise:
    elem[startPointer] = item;
    startPointer = (++startPointer) % sz; // wrap around /:)
    return FIFO_GOOD;
}

template<typename T>
T FIFO<T>::pop() {
    if (fifo_status()==FIFO_EMPTY) {
        return FIFO_EMPTY;
    }
    // otherwise
    T r = elem[endPointer];
    endPointer = (++endPointer) % sz; // wrap around /:)
    return r;
}

template<typename T>
FIFO_STATUS FIFO<T>::fifo_status() {
    if (startPointer==endPointer) {
        return FIFO_EMPTY; // fifo empty
    }
    else if (((startPointer+1) % sz) == endPointer) {
        return FIFO_FULL; // fifo full
    }
    // otherwise, return FIFO_GOOD
    return FIFO_GOOD;
}


#endif //FIFO_H
