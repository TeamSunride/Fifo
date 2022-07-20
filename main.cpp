//
// Created by robos on 29/06/2022.
//
#include "Fifo.h"
#include <iostream>
#include "Vector.h"



Fifo<Vector<double, 3>> accFifo(256);
Fifo<double> dFifo(256);


int main() {
//    for (int i=0;i<256;i++) {
//        Vector<double, 3> v = {1.1+(0.1*i), 2.2, 2.3};
//        accFifo.push(v);
//    }
//    for (int i=0;i<256;i++) {
//        accFifo.pop();
//        std::cout<<"FREE SPACE:"<<accFifo.free_space()<<std::endl;
//    }
//    std::cout<<"NOW AGAIN---------------------------------------\n";
//    for (int i=0;i<256;i++) {
//        Vector<double, 3> v = {1.1+(0.1*i), 2.2, 2.3};
//        accFifo.push(v);
//    }
//    for (int i=0;i<256;i++) {
//        Vector<double, 3> a = accFifo.pop();
//        std::cout<<"FREE SPACE:"<<accFifo.free_space()<<"   "<<a[0]<<std::endl;
//    }
//
//    if (accFifo.fifo_status()!=Fifo_STATUS::Fifo_EMPTY)  {
//        std::cout<<"NOT EMPTY"<<std::endl;
//        Vector<double, 3> r = accFifo.pop();
//        std::cout<<r[0]<<"\n"<<r[1]<<"\n"<<r[2]<<std::endl;
//    }
//    else {
//        std::cout<<"EMPTY"<<std::endl;
//    }
//
//
//    dFifo.push(12.2);
//    /// Warning: You MUST check the status before calling pop(), otherwise you may get a segfault and/or be writing to unallocated memory
//    if (dFifo.fifo_status() != Fifo_STATUS::Fifo_EMPTY) {
//        std::cout<<"\n"<<dFifo.pop();
//    }

    dFifo.push(12.2);
    dFifo.push(3.1415);
    dFifo.push(0.1);
    std::cout<<"free space: "<<dFifo.free_space()<<std::endl;
    std::cout<<"\n"<<dFifo.peekBack(1)<<std::endl;
    std::cout<<"free space: "<<dFifo.free_space()<<std::endl;
    std::cout<<"\n"<<dFifo.peek();


}
