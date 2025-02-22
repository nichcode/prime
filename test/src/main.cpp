
#include "prime/prime.h"

#include <iostream>

class Them
{
private:
    i32 x;
public:
    Them()
    {
        x = sizeof(Them);
    }
};

int
main()
{
    using namespace prime;
    Platform::init();

    Platform::shutdown();
    return 0;
}