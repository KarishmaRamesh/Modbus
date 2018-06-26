#include <ModbusRtu.h>

uint16_t au16data[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}; //!< data array for modbus network sharing
uint8_t u8state; //!< machine state

Modbus master(0,0,3); // this is master and txenable pin>1 for RS-485/
modbus_t telegram;

unsigned long u32wait;

void setup() {
  telegram.u8id = 1; // slave address
  telegram.u8fct = 16; // function code (this one is write a single register)
  telegram.u16RegAdd = 0; // start address in slave
  telegram.u16CoilsNo = 16; // number of elements (coils or registers) to read
  telegram.au16reg = au16data; // pointer to a memory array in the Arduino
  
  master.begin( 9600 ); // baud-rate at 19200
  master.setTimeOut( 5000 ); // if there is no answer in 5000 ms, roll over
  u32wait = millis() + 1000;
  u8state = 0; 
}

void loop() {
  switch( u8state ) {
  case 0: 
    if (millis() > u32wait) u8state++; // wait state
    break;
  case 1: 
  master.query( telegram ); // send query (only once)
    u8state++;
    break;
  case 2:
   master.poll(); // check incoming messages
    if (master.getState() == COM_IDLE) {
      u8state = 0;
      u32wait = millis() + 2000; 
    }
    break;
  }
}

