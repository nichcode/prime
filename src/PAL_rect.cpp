
#include "PAL_pch.h"
#include "PAL/PAL_rect.h"

b8 PAL_RectCollide(const PAL_Rect a, const PAL_Rect b)
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