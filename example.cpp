//
// Created by robosam2003 on 29/06/2022.
//
#include "Fifo.h"
#include <iostream>
#include "Vector.h"

int main() {

    // A Fifo is initialized with template <type, size>, so this is a Fifo of 256 floats.
    Fifo<float, 256> exampleFifo;
    int sz = exampleFifo.size();

    unsigned int i = 0;
    // Push Data to fifo until it's full.
    while (true) {
        // item to push
        float item = i*3.14159;

        // Push while checking if the fifo is full or not.
        if (exampleFifo.push(item) == Fifo_STATUS::Fifo_FULL) {
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
    std::cout<< "Data popped from exampleFifo:\n";
    while (true) {
        if (exampleFifo.fifo_status() != Fifo_STATUS::Fifo_EMPTY) {
            std::cout << exampleFifo.pop() << std::endl;
            countPops++;
        }
        else  {
            std::cout << "Fifo is empty!\n";
            break;
        }
    }

    if (countPops==exampleFifo.size()) { // the size of the Fifo can be obtained using size();
        std::cout << "All data popped!\n";
    }
    else {
        std::cout << "Error: Not all data popped!\n";
    }



    // C-style casting to resize and/or change type:
    Fifo<float, 64> smallFifo;
    Fifo<double, 512> bigFifo = (Fifo<double, 512>) smallFifo;

    // Copy and move constructors are also implemented (including assignment= ):
    Fifo<float, 64> smallFifo2 = smallFifo;
    Fifo<float, 64> smallFifo3 = std::move(smallFifo);


#ifdef VECTOR_LIBRARY_H
    // If you are using my Vector class (https://github.com/robosam2003/Vector), be aware that you can use it with Fifos as well!
    Fifo<Vector<float, 3>, 256> exampleVectorFifo;
    Vector<float, 3> v = {1.2, 2.2, 3.3};
    exampleVectorFifo.push(v);

    // C-style casts to new Fifo and Vector types are possible:
    Fifo<Vector<float, 3>, 64> e1;
    e1.push(v);
    std::cout<< "e1 Free space: " << e1.free_space() << std::endl;
    Fifo<Vector<double, 6>, 256> e2 = (Fifo<Vector<double, 6>, 256>) e1;
    std::cout << "e2 Free space: " << e2.free_space() << std::endl;

#endif // VECTOR_LIBRARY_H

}
