#include "solid_basic.h"
#include "solid_out.h"
#include "solid_read.h"
#include "solid_kernel.h"

int main()
{
    solid_read();
    solid_kernel();
    return 0;
}