#ifndef DYNAMIC_FIFO_H
#define DYNAMIC_FIFO_H

#include <iostream>


enum class Fifo_STATUS {
    Fifo_FULL,
    Fifo_EMPTY,
    Fifo_GOOD
};

template<class T>
class Fifo { /// essentially a circular fifo
private:
    T* elem;
    int nextFree;
    int endPointer;
    unsigned int sz;
public:
    /**
     * @brief Construct a new Fifo object
     * @param s
     */
    explicit Fifo(int s);

/*    *//**
     * @brief Construct a new Fifo object from an initializer list
     * @param lst
     *//*
    Fifo(std::initializer_list<T> lst);*/


    /**
     * @brief Copy constructor for Fifo
     * @param a
     */
    Fifo(const Fifo& a); // copy constructor

    /**
     * @brief Copy assignment constructor for Fifo
     * @param a
     * @return Fifo&
     */
    Fifo& operator=(const Fifo& a); // copy assignment

    /**
     * @brief Move constructor for Fifo
     * @param a
     */
    Fifo(Fifo&& a) noexcept ; // move constructor

    /**
     * @brief Move assignment constructor for Fifo
     * @param a
     * @return Fifo&
     */
    Fifo& operator=(Fifo&& a) noexcept; // move assignment


    /**
     * @brief C-style cast operator for dynamicFifo. Does not resize the fifo. Usage: e.g.
     * @example Fifo\<double\> g;\n  Fifo\<float\> f = (Fifo\<float\>) g;
     * @return Fifo_STATUS
     */
    template <typename D>
        explicit operator Fifo<D>() const;

    /**
     * @brief operator []
     * @param i
     * @return T&
     */
    T& operator[](int i);

    /**
     * @brief operator [] const
     * @param i
     * @return const T&
     */
    T& operator[](int i) const;

    /**
     * @brief Get the T at index i of the Fifo
     * @param i
     * @return The T at index i of the Fifo (not elem)
     */
    T& atFifoIndex(int i);

    /**
     * @brief Get the T at index i of the Fifo
     * @param i
     * @return The T at index i of the Fifo (not elem)
     */
    T& atFifoIndex(int i) const;

    /**
     * @brief Push an item to the Fifo
     * @param item
     * @return Fifo Status enum class of state of push (FULL, GOOD, etc)
     */
    Fifo_STATUS push(const T& item);

    /**
     * @brief Pop an item off the Fifo
     * @return the item popped off the Fifo
     */
    T pop();

    // end
    /**
     * @brief Peek at the back of the Fifo (the next thing to be popped)
     * @return the next thing to be popped
     */
    T peekBack() const;

    /**
     * @brief Peek at the back of the Fifo i times in
     * @param i
     * @return The item i times from the back of the Fifo
     */
    T peekBack(int i) const;

    // front
    /**
     * @brief Peek at the front of the Fifo (the thing you just pushed)
     * @return The item at the front of the fifo (the thing you just pushed)
     */
    T peekFront() const;

    /**
     * @brief Peek at the front of the Fifo i times in.
     * @param i
     * @return The item i times in from the Front of the Fifo.
     */
    T peekFront(int i) const;

    /**
     * @brief Get the status of the Fifo, (GOOD, EMPTY, FULL)
     * @return The status of the Fifo (of type: Fifo_STATUS)
     */
    Fifo_STATUS fifo_status() const;

    /**
     * @brief Get the size of the Fifo
     * @return The size of the Fifo
     */
    int size() const;

    /**
     * @brief Get the free space left in the Fifo
     * @return The free space in the Fifo
     */
    int free_space() const;

    /**
     * @brief Get the used space in the Fifo
     * @return The used space in the Fifo
     */
    int used_space() const;


    ~Fifo() { delete[] elem; } // destructor
};

#include "dynamicFifo.tpp" // implementation file


#endif //DYNAMIC_FIFO_H
