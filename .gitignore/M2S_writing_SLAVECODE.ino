
#include <ModbusRtu.h>

Modbus slave(1, 0, 3);//slave id :1-247, serial port :0, tx enable pinany pin number > 1 for RS-485

void setup() {
  slave.begin( 9600 );
}

void loop() {
  uint16_t au16data[16];
  slave.poll(au16data,16);
  for(int i=0;i<16;i++)
    Serial.println(au16data[i]);
} 

