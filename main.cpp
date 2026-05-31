#include <iostream>
#include "core/core.h"

int main()
{
    Core core(3, 3, 800, 800, "Physics Penguin");
    core.gameLoop();
    return 0;
}