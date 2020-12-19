#include <Arduino.h>
#include <RCSwitch.h>
#include "main.h"

#define PIN_RC 10

RCSwitch rc = RCSwitch();

// --- Lifecycle --- //

void setup() {
  setupRC();
}

void loop() {
  rcClarus1(1);
  rcClarus2(1);
  rcClarus3(1);
  rcOrno1(1);
  rcOrno2(1);
  rcOrno3(1);
  delay(2000);

  rcClarus1(0);
  rcClarus2(0);
  rcClarus3(0);
  rcOrno1(0);
  rcOrno2(0);
  rcOrno3(0);
  delay(2000);
}

// --- RC --- //

void setupRC(){
  rc.enableTransmit(PIN_RC);
  rc.setRepeatTransmit(8);
}

void rcSetProtocolOrno(){
    rc.setProtocol({ 80, {  3,  25 }, {  3,  13 }, {  11,  5 }, false }); // ORNO OR-GB-417GD
}

void rcSetProtocolClarus(){
    rc.setProtocol({ 82, {  2, 65 }, {  3,  5 }, {  7,  1 }, false }); // CLARUS BHC993BF-3
}

void rcClarus1(bool enable) {
  rcSetProtocolClarus();
  rcSend(enable ? "010100000001010100110011" : "010100000001010100111100");
}

void rcClarus2(bool enable) {
  rcSetProtocolClarus();
  rcSend(enable ? "010100000001010111000011" : "010100000001010111001100");
}

void rcClarus3(bool enable) {
  rcSetProtocolClarus();
  rcSend(enable ? "010100000001011100000011" : "010100000001011100001100");
}

void rcOrno1(bool enable) {
  rcSetProtocolOrno();
  rcSend(enable ? "110100110000111001110000" : "110110101110101000100000");
}

void rcOrno2(bool enable) {
  rcSetProtocolOrno();
  rcSend(enable ? "110100110000111001110100" : "110110110100110110010100");
}

void rcOrno3(bool enable) {
  rcSetProtocolOrno();
  rcSend(enable ? "110100101010111110111100" : "110101001100110000011100");
}

void rcSend(const char *data){
    rc.send(data); 
}
