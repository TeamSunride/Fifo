//
// Created by robosam2003 on 29/06/2022.
//
#include "dynamicFifo.h"
#include <iostream>



int main() {
#ifdef FIFO_H
    // A Fifo is initialized with template <type, size>, so this is a Fifo of 256 floats.
    Fifo::Fifo<float, 256> exampleFifo;
    int sz = exampleFifo.size();

    unsigned int i = 0;
    // Push Data to fifo until it's full.
    while (true) {
        // item to push
        float item = i * 3.14159;

        // Push while checking if the fifo is full or not.
        if (exampleFifo.push(item) == Fifo::Fifo_STATUS::Fifo_FULL) {
            std::cout << "Fifo is full!\n";
            std::cout << "Free space: " << exampleFifo.free_space() << std::endl; // confirmation using free_space();
            break;
        }
        i++;
    }

    // Pop Data from fifo until it's empty.
    /// Warning: You MUST check the status before calling pop().
    /// If you pop() when the fifo is empty, pop() returns 0.
    int countPops = 0;
    std::cout << "Data popped from exampleFifo:\n";
    while (true) {
        if (exampleFifo.fifo_status() != Fifo::Fifo_STATUS::Fifo_EMPTY) {
            std::cout << exampleFifo.pop() << std::endl;
            countPops++;
        } else {
            std::cout << "Fifo is empty!\n";
            break;
        }
    }

    if (countPops == exampleFifo.size()) { // the size of the Fifo can be obtained using size();
        std::cout << "All data popped!\n";
    } else {
        std::cout << "Error: Not all data popped!\n";
    }



    // C-style casting to resize and/or change type:
    Fifo::Fifo<float, 64> smallFifo;
    Fifo::Fifo<double, 512> bigFifo = (Fifo::Fifo<double, 512>) smallFifo;

    // Copy and move constructors are also implemented (including assignment= ):
    Fifo::Fifo<float, 64> smallFifo2 = smallFifo;
    Fifo::Fifo<float, 64> smallFifo3 = std::move(smallFifo);


#endif // FIFO_H

    // Dynamic Fifo
#ifdef DYNAMIC_FIFO_H
    // dynamicFifo is initialised with a template type and a parameter template
    Fifo::dynamicFifo<float> e1 (256);
    e1.push(3.14159);

    // C-style casts. - does not resize the fifo.
    Fifo::dynamicFifo<double> e2 = (Fifo::dynamicFifo<double>) e1;

    if (e2.fifo_status() == Fifo::Fifo_STATUS::Fifo_EMPTY)
        std::cout<<"It's empty";
    else
        e2.pop();
    std::cout << "e2 Free space: " << e2.free_space() << std::endl;

#endif // DYNAMIC_FIFO_H

}
