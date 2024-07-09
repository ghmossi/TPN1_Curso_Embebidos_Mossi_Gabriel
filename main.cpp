#include "mbed.h"
#include "arm_book_lib.h"


#define NUMBER_SAMPLES                          10
#define NUMBER_OF_AVG_SAMPLES                   100
#define NUMBER_TIME_ADC_UART                    3000
#define NUMBER_TIME_OUT_UART                    3000  
#define TIME_INCREMENT_MS                       10
#define DEBOUNCE_BUTTON_TIME_MS                 40

//=====[Declaration of public data types]======================================

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} buttonState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalIn input0(BUTTON1);
DigitalOut LD1(LED1);
static UnbufferedSerial serial_port(USBTX, USBRX);
AnalogIn potenciometro0(A0);
AnalogIn potenciometro1(A1);

int accumulatedTimeADCUART = 0;
int accumulatedTimeInput = 0;
int accumulatedTimeOutput = 0;
int accumulatedDebounceButtonTime     = 0;

buttonState_t enterButtonState;

float potentiometerReading0 = 0.0;
float potenciometroReadingsAverage0  = 0.0;
float potenciometroReadingsSum0      = 0.0;
float potenciometroReadingsArray0[NUMBER_OF_AVG_SAMPLES];

float potentiometerReading1 = 0.0;
float potenciometroReadingsAverage1  = 0.0;
float potenciometroReadingsSum1      = 0.0;
float potenciometroReadingsArray1[NUMBER_OF_AVG_SAMPLES];


bool newStateInput0 = 0;
bool newStateInput1 = 0;
bool stateOutput0 = false;
bool stateOutput1 = false;

void potenciometroUpdate();;
void initUART();
void inputsInit();
void outputsInit();
void potenciometroReadingsArrayInit();
void sendADCUART();
void sendInputUART();
void readOUTART();
void debounceButtonInit();
void debounceButtonUpdate();

void on_rx_interrupt()
{
    char receivedChar;
    if (serial_port.read(&receivedChar, 1)) {
        if ( receivedChar == '0' ) {
            LD1=1;
            stateOutput0=true;
            accumulatedTimeOutput=0;    
        }
    }
    
}


int main()
{
    initUART();
    inputsInit();
    outputsInit();
    serial_port.attach(&on_rx_interrupt, SerialBase::RxIrq);
    //char buffer []={"Prueba envio puerto serie\n"};
    
    while (true) {
        
        potenciometroUpdate();
        debounceButtonUpdate();
        sendADCUART() ;
        readOUTART() ;
        //LD1 = input0; // verifico input con led
     
        delay(TIME_INCREMENT_MS);
    }

}

void inputsInit()
{
    potenciometroReadingsArrayInit();
}

void outputsInit()
{
    
}

void initUART()
{
    serial_port.baud(9600);
    serial_port.format(
        /* bits */ 8,
        /* parity */ SerialBase::None,
        /* stop bit */ 1
    );

}

void potenciometroReadingsArrayInit()
{
    int i;
    for( i=0; i<NUMBER_OF_AVG_SAMPLES ; i++ ) {
        potenciometroReadingsArray0[i] = 0;
        potenciometroReadingsArray1[i] = 0;
    }
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
                newStateInput0=1;
            } else {
                enterButtonState = BUTTON_UP;
                newStateInput0=0;
            }
            sendInputUART();
        }
        accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
                                        TIME_INCREMENT_MS;
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
                newStateInput0=0;
            } else {
                enterButtonState = BUTTON_DOWN;
                newStateInput0=1;
            }
            sendInputUART();
        }
        accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
                                        TIME_INCREMENT_MS;
        break;

    default:
        debounceButtonInit();
        break;
    }
    //return enterButtonReleasedEvent;
}


void sendADCUART(){
    char str[100];
    int stringLength;
    
    accumulatedTimeADCUART = accumulatedTimeADCUART + TIME_INCREMENT_MS;
    if (accumulatedTimeADCUART== NUMBER_TIME_ADC_UART)
    {
        accumulatedTimeADCUART=0;
        sprintf ( str, "{adc0: %.3f, adc1: %.3f}", potenciometroReadingsAverage0,potenciometroReadingsAverage1 );
        stringLength = strlen(str);
        serial_port.write( str, stringLength );
    }
} 

void sendInputUART(){
    char str[100];
    int stringLength;
    bool in0 = newStateInput0;
    bool in1 = newStateInput1; // no esta definida actualmente, siempre envio 0 en input1
    
    sprintf ( str, "{input0: %d, input1: %d}", in0,in1 );
    stringLength = strlen(str);
    serial_port.write( str, stringLength );
} 


void readOUTART(){
   
    // uso interrupcion para leer uart
    if (accumulatedTimeOutput >= NUMBER_TIME_OUT_UART)
    {
        accumulatedTimeOutput=0;
        if(stateOutput0==true)
        {
            stateOutput0=false;
            LD1=0;
        }        
        
    }
    accumulatedTimeOutput=accumulatedTimeOutput+ TIME_INCREMENT_MS;
} 
