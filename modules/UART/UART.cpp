#include "mbed.h"
#include "arm_book_lib.h"

#include "UART.h"

#include "interface_system.h"
#include "adc.h"
#include "input.h"
#include "output.h"
#include "spi.h"

//=====[Declaration of private defines]========================================

#define NUMBER_TIME_MS_UART                      3000
#define NUMBER_TIME_TEMPERATURE_UART            4000

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

static UnbufferedSerial serial_port(USBTX, USBRX);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static int accumulatedTimeUART = 0;
static int lastStateButton0=0;
static int lastStateButton1=0;
static char receivedChar;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void on_rx_interrupt()
{
    
    if (serial_port.read(&receivedChar, 1)) {
        if ( receivedChar == '0' ) {
            //LD1=1;
        }
    }
    
}

void initUART()
{
    serial_port.baud(9600);
    serial_port.format(
        /* bits */ 8,
        /* parity */ SerialBase::None,
        /* stop bit */ 1
    );
    serial_port.attach(&on_rx_interrupt, SerialBase::RxIrq);

}

void UARTUpdate(){
    char str[100];
    int stringLength;
    float temperature =0.0;
  
    accumulatedTimeUART = accumulatedTimeUART + SYSTEM_TIME_INCREMENT_MS;
    // se envia datos cada 3 segundos o cuando se produce uan cambio en la entrada button.
    if (accumulatedTimeUART== NUMBER_TIME_MS_UART || lastStateButton0 !=readStateButton())
    {
        lastStateButton0 = readStateButton();
        accumulatedTimeUART=0;
        sprintf ( str, "{adc0: %.3f,adc1: %.3f,temperature: %.2f,input0: %d,input1: %d}", readADC0(),readADC1(),readTemperatureSPI(),lastStateButton0,lastStateButton1 );
        stringLength = strlen(str);
        serial_port.write( str, stringLength );
    }
    if ( receivedChar == '0' )
        {
            // activo LD1  
            outputUpdate(1);
        }
    if ( receivedChar == '1' )
        {
            // activo LD1  
            outputUpdate(0);
        }
} 

//=====[Implementations of private functions]==================================

