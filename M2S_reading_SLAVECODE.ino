/**
 *  Modbus slave example 3:
 *  The purpose of this example is to read a data array
 *  from the Slave Arduino to an external device through RS485.
 *
 *  Recommended Modbus Master: QModbus
 *  http://qmodbus.sourceforge.net/
 */

#include <ModbusRtu.h>

// assign the Arduino pin that must be connected to RE-DE RS485 transceiver
#define TXEN  3 

// data array for modbus network sharing
uint16_t au16data[16] = {
  1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

/**
 *  Modbus object declaration
 *  u8id : node id = 0 for master, = 1..247 for slave
 *  u8serno : serial port (use 0 for Serial)
 *  u8txenpin : 0 for RS-232 and USB-FTDI 
 *               or any pin number > 1 for RS-485
 */
Modbus slave(1,0,TXEN); // this is slave @1 and RS-485

void setup() {
  slave.begin( 9600 ); // baud-rate at 19200
}

void loop() {
  slave.poll( au16data, 16 );
}
