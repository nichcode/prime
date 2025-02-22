
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

    Them* ptr = Platform::alloc<Them>();
    char* ptr2 = Platform::alloc<char>();
    u32* ptr3 = Platform::alloc<u32>(12);
    char* ptr4 = Platform::alloc<char>();

    *ptr2 = 'A';

    Platform::copy(ptr4, ptr2, sizeof(char));

    Platform::free(ptr);
    Platform::free(ptr2);
    Platform::free(ptr3, 12);
    Platform::free(ptr4);

    Platform::shutdown();
    return 0;
}