#include "mbed.h"
#include "arm_book_lib.h"

#include "input.h"

#include "interface_system.h"

//=====[Declaration of private defines]========================================

#define NUMBER_SAMPLES                          10
#define NUMBER_OF_AVG_SAMPLES                   100
#define DEBOUNCE_BUTTON_TIME_MS                 40

//=====[Declaration of private data types]=====================================

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} buttonState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalIn input0(BUTTON1);
buttonState_t enterButtonState;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static int newStateButton = 0;
static int accumulatedTimeInput = 0;
static int accumulatedDebounceButtonTime = 0;

//=====[Declarations (prototypes) of private functions]========================

static void debounceButtonInit();
static void debounceButtonUpdate();

//=====[Implementations of public functions]===================================

void initInput()
{
    debounceButtonInit();
}

void inputUpdate()
{
    debounceButtonUpdate();
}

void debounceButtonInit()
{
    if( input0 ) {
        enterButtonState = BUTTON_DOWN;
    } else {
        enterButtonState = BUTTON_UP;
    }
}

void debounceButtonUpdate()
{
    bool enterButtonReleasedEvent = false;
    switch( enterButtonState ) {

    case BUTTON_UP:
        if( input0 ) {
            enterButtonState = BUTTON_FALLING;
            accumulatedDebounceButtonTime = 0;
        }
        break;

    case BUTTON_FALLING:
        if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
            if( input0 ) {
                enterButtonState = BUTTON_DOWN;
                newStateButton=1;
            } else {
                enterButtonState = BUTTON_UP;
                newStateButton=0;
            }
            //sendInputUART();
        }
        accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
                                        SYSTEM_TIME_INCREMENT_MS;
        break;

    case BUTTON_DOWN:
        if( !input0 ) {
            enterButtonState = BUTTON_RISING;
            accumulatedDebounceButtonTime = 0;
        }
        break;

    case BUTTON_RISING:
        if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
            if( !input0 ) {
                enterButtonState = BUTTON_UP;
                enterButtonReleasedEvent = true;
                newStateButton=0;
            } else {
                enterButtonState = BUTTON_DOWN;
                newStateButton=1;
            }
            //sendInputUART();
        }
        accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
                                        SYSTEM_TIME_INCREMENT_MS;
        break;

    default:
        debounceButtonInit();
        break;
    }
}

int readStateButton()
{
    return newStateButton;
}

//=====[Implementations of private functions]==================================