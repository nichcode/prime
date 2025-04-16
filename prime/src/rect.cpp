
#include "pch.h"
#include "prime/rect.h"

b8 prRectCollide(const prRect a, const prRect b)
{
    if (
        a.x < b.x + b.x  &&
        a.x + a.x > b.x  &&
        a.y < b.y + b.y  &&
        a.y + a.y > b.y
    ) { 
        return true; 
    }
    return false;
}