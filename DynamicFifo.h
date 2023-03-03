#ifndef DYNAMIC_FIFO_H
#define DYNAMIC_FIFO_H

#include "Shared.h"

template<class T>
class DynamicFifo { /// essentially a circular fifo
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
    explicit DynamicFifo(int s);

/*    *//**
     * @brief Construct a new Fifo object from an initializer list
     * @param lst
     *//*
    Fifo(std::initializer_list<T> lst);*/


    /**
     * @brief Copy constructor for DynamicFifo
     * @param a
     */
    DynamicFifo(const DynamicFifo& a); // copy constructor

    /**
     * @brief Copy assignment constructor for DynamicFifo
     * @param a
     * @return DynamicFifo&
     */
    DynamicFifo& operator=(const DynamicFifo& a); // copy assignment

    /**
     * @brief Move constructor for DynamicFifo
     * @param a
     */
    DynamicFifo(DynamicFifo&& a) noexcept ; // move constructor

    /**
     * @brief Move assignment constructor for DynamicFifo
     * @param a
     * @return DynamicFifo&
     */
    DynamicFifo& operator=(DynamicFifo&& a) noexcept; // move assignment


    /**
     * @brief C-style cast operator for DynamicFifo. Does not resize the fifo. Usage: e.g.
     * @example DynamicFifo\<double\> g;\n  DynamicFifo\<float\> f = (DynamicFifo\<float\>) g;
     * @return Fifo_STATUS
     */
    template <typename D>
        explicit operator DynamicFifo<D>() const;

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
     * @brief Get the T at index i of the DynamicFifo
     * @param i
     * @return The T at index i of the DynamicFifo (not elem)
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


    ~DynamicFifo() { delete[] elem; } // destructor
};

#include "DynamicFifo.tpp" // implementation file


#endif //DYNAMIC_FIFO_H
