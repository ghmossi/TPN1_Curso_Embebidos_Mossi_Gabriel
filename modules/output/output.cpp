#include "mbed.h"
#include "arm_book_lib.h"

#include "output.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut LD1(LED1);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void outputUpdate(int stateOutput0){

    if (stateOutput0==0) LD1=0;
    if (stateOutput0==1) LD1=1;
    
}

//=====[Implementations of private functions]==================================