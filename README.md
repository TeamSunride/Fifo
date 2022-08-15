# FIFO
A FIFO class.

--- 

## Usage 
`Fifo`s are initialised with a template type and a size.
```cpp
#include "FIFO.h"
// A Fifo is initialized with template <type, size>, so this is a Fifo of 256 floats.
Fifo<float, 256> exampleFifo;
float item  = 3.14159
```

Pushing to a Fifo implements error checking to avoid nasty bugs.
The `push()` function returns a status code of type `Fifo_STATUS`.
```cpp
if (exampleFifo.push(item) == Fifo_STATUS::Fifo_FULL) {
    // Handle the fact that the Fifo is full
}
```

Popping from a Fifo should be done after a check of the Fifo status to avoid unexpected behaviour.
If the Fifo is not empty, the `pop()` function returns the value popped, otherwise it returns 0. 
For this reason, a check before popping is vital.
```cpp
// You MUST check the status of the Fifo before calling pop()
(exampleFifo.fifo_status() == Fifo_STATUS::Fifo_EMPTY) ? /* Handle the fact that it's empty. */ : exampleFifo.pop();
```

See `example.cpp` for a more examples.


### Usage with Vector
Fifo also works well with my [Vector](https://github.com/robosam2003/Vector) class.
```cpp
#include "FIFO.h"
#include "Vector.h"
    Fifo<Vector<float, 3>, 64> e1;
    e1.push(v);
    
    // C-style casts for both Vector and Fifo in one cast.
    Fifo<Vector<double, 6>, 256> e2 = (Fifo<Vector<double, 6>, 256>) e1;
    
    (e2.fifo_status() == Fifo_STATUS::Fifo_EMPTY) ? /* Handle the fact that it's empty. */ : e2.pop();
```

