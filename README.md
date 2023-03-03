# FIFO
A FIFO class that comes in both static and dynamic forms.

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
// otherwise, the push was successful, continue.
```

Popping from a Fifo should be done after a check of the Fifo status to avoid unexpected behaviour.
If the Fifo is not empty, the `pop()` function returns the value popped, otherwise it returns 0. 
For this reason, a check before popping is vital.
```cpp
// You MUST check the status of the Fifo before calling pop()
(exampleFifo.fifo_status() == Fifo_STATUS::Fifo_EMPTY) ? /* Handle the fact that it's empty. */ : exampleFifo.pop();
```

See `example.cpp` for more examples.


### Usage with Vector
Fifo also works well with my [Vector](https://github.com/TeamSunride/Vector) class.
```cpp
#include "Fifo.h"
#include "Vector.h"
Fifo<Vector<float, 3>, 64> e1;
e1.push(v);

// C-style casts for both Vector and Fifo in one cast.
Fifo<Vector<double, 6>, 256> e2 = (Fifo<Vector<double, 6>, 256>) e1;

(e2.fifo_status() == Fifo_STATUS::Fifo_EMPTY) ? /* Handle the fact that it's empty. */ : e2.pop();
```

### Dynamic Fifo
`DynamicFifo` is an identical to `Fifo` in functionality, but uses dynamic memory allocation, not a template.
It is useful when the size of the Fifo is not known at compile time, or when writing libraries etc. (e.g. [LSM6DSO32](https://github.com/TeamSunride/Arduino-LSM6DSO32))

```cpp
#include "DynamicFifo.h"
// DynamicFifo is initialised with a template type and size as a parameter.
Fifo<float> e1 (256);
e1.push(3.14159);

// C-style casts. - does not resize the fifo.
Fifo<double> e2 = (Fifo<double>) e1;

(e2.fifo_status() == Fifo_STATUS::Fifo_EMPTY) ? /* Handle the fact that it's empty. */ : e2.pop();
std::cout << "e2 Free space: " << e2.free_space() << std::endl;
```

