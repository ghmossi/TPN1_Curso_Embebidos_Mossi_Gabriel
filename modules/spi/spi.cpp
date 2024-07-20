#include "mbed.h"
#include "arm_book_lib.h"

#include "spi.h"

#include "interface_system.h"

//=====[Declaration of private defines]========================================

#define SPI1_MOSI PA_7
#define SPI1_MISO PA_6
#define SPI1_SCK  PA_5
#define SPI1_CS   PD_14

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

SPI spiMax6675(SPI1_MOSI, SPI1_MISO, SPI1_SCK);
DigitalOut cs(SPI1_CS);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static float temperature=0.0;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void initSPI(){
    spiMax6675.format( 8, 3 );
    spiMax6675.frequency( 1000000 );
}


float readTemperatureSPI()
{
    
    uint16_t value = 0;
    // Select the device by seting chip select low
    cs = 0;
    delay(1);
    // Leer los 16 bits de datos
    value = spiMax6675.write(0x00) << 8; // Enviar y recibir el primer byte
    value |= spiMax6675.write(0x00); // Enviar y recibir el segundo byte
    cs = 1;
    value >>= 3;
    temperature = value * 0.25;
    return temperature;
}

//=====[Implementations of private functions]==================================