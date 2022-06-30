#ifndef Fifo_H
#define Fifo_H

#include <iostream>


enum Fifo_STATUS {
    Fifo_FULL,
    Fifo_EMPTY,
    Fifo_GOOD
};

template<class T>
class Fifo { /// essentially a circular fifo
public:
    explicit Fifo(int s);

    T& operator[](int i);
    Fifo_STATUS push(const T& item); // copy constructor
    //Fifo& operator=(const Fifo& a);

    // TODO: iterators?
    T pop();

    Fifo_STATUS fifo_status();

    int size();
    int free_space();
    ~Fifo() { delete[] elem; } // destructor

private:
    T* elem;
    int nextFree;
    int endPointer;
    int sz;
};

#include "Fifo.tpp" // implementation file


#endif //Fifo_H
