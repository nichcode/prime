
#include "prime/prime.h"

b8 windowTest(void* user_data);
b8 contextTest(void* user_data);

int main(int argc, char** argv)
{
    prime_device_type device_type;
    device_type = PRIME_DEVICE_TYPE_OPENGL;
    prime_init(device_type);

    prime_set_tests_data(nullptr);
    prime_add_test(windowTest, "windowTest");
    prime_add_test(contextTest, "contextTest");

    prime_run_tests();
    prime_shutdown();
    
    return 0;
}