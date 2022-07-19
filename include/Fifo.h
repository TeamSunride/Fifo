#ifndef Fifo_H
#define Fifo_H

#include <iostream>

//#define FIFO_FULL
//#define FIFO_EMPTY
//#define FIFO_GOOD


enum class Fifo_STATUS {
    Fifo_FULL,
    Fifo_EMPTY,
    Fifo_GOOD
};

template<class T, unsigned int sz>
class Fifo { /// essentially a circular fifo
protected:
    T elem[sz];
    unsigned int nextFree;
    unsigned int endPointer;
public:
    explicit Fifo();
    Fifo(std::initializer_list<T> lst);

    // TODO: copy and move constructors

    T& operator[](int i);
    Fifo_STATUS push(const T& item);
    //Fifo& operator=(const Fifo& a);

    // TODO: iterators?
    T pop();

    Fifo_STATUS fifo_status();

    int size();
    int free_space();
    ~Fifo() = default; // destructor
};

#include "Fifo.tpp" // implementation file


#endif //Fifo_H
