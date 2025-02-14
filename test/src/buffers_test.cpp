
#include "prime/prime.h"

b8
buffersTestGL()
{
    primeDevice* device = primeDeviceCreate(primeDeviceTypeGL);
    primeLayout* layout = primeLayoutCreate(device);
    primeLayoutAdd(layout, primeTypeFloat3);

    primeDeviceDestroy(device);
    return true;
}