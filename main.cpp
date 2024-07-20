
#include "interface_system.h"

int main()
{
    interfaceSystemInit();
    while (true) {
        interfaceSystemUpdate();
    }
}