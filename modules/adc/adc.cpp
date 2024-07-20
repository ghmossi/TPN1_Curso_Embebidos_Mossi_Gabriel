#include "mbed.h"
#include "arm_book_lib.h"

#include "adc.h"

//=====[Declaration of private defines]========================================

#define NUMBER_OF_AVG_SAMPLES                   100

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn potenciometro0(A0);
AnalogIn potenciometro1(A1);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static float potenciometroReadingsAverage0  = 0.0;
static float potenciometroReadingsAverage1  = 0.0;
static float potentiometerReading0 = 0.0;
static float potenciometroReadingsSum0      = 0.0;
static float potenciometroReadingsArray0[NUMBER_OF_AVG_SAMPLES];
static float potentiometerReading1 = 0.0;
static float potenciometroReadingsSum1      = 0.0;
static float potenciometroReadingsArray1[NUMBER_OF_AVG_SAMPLES];

//=====[Declarations (prototypes) of private functions]========================

static void potenciometroReadingsArrayInit();

//=====[Implementations of public functions]===================================

void initADC(){
    potenciometroReadingsArrayInit();
}

void potenciometroUpdate()
{
    static int potenciometroSampleIndex = 0;
    int i = 0;
    
    potenciometroReadingsArray0[potenciometroSampleIndex] = potenciometro0.read();
    potenciometroReadingsArray1[potenciometroSampleIndex] = potenciometro1.read();
    potenciometroSampleIndex++;
    if ( potenciometroSampleIndex >= NUMBER_OF_AVG_SAMPLES) {
        potenciometroSampleIndex = 0;
    
    }
    potenciometroReadingsSum0 = 0.0;
    potenciometroReadingsSum1 = 0.0;
    for (i = 0; i < NUMBER_OF_AVG_SAMPLES; i++) {
        potenciometroReadingsSum0 = potenciometroReadingsSum0 + potenciometroReadingsArray0[i];
        potenciometroReadingsSum1 = potenciometroReadingsSum1 + potenciometroReadingsArray1[i];
    }
    potenciometroReadingsAverage0 = potenciometroReadingsSum0 / NUMBER_OF_AVG_SAMPLES;
    potenciometroReadingsAverage1 = potenciometroReadingsSum1 / NUMBER_OF_AVG_SAMPLES;
    
 }

float readADC0(){
    return potenciometroReadingsAverage0;
}

float readADC1(){
    return potenciometroReadingsAverage1;
}

//=====[Implementations of private functions]==================================

static void potenciometroReadingsArrayInit() 
{
    int i;
    for( i=0; i<NUMBER_OF_AVG_SAMPLES ; i++ ) {
        potenciometroReadingsArray0[i] = 0;
        potenciometroReadingsArray1[i] = 0;
    }
}