/*
Copyright 2014 DoNothingBox LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

#include "BaseState.h"
#ifndef SSD1306_128_64//Always check Class files with Actual #define strings!
#include <Adafruit_SSD1306.h>
#endif

#ifndef BLUETOOTHMANAGER_H//Always check Class files with Actual #define strings!
  #include "BluetoothManager.h";
#endif


#include <avr/pgmspace.h>


static const unsigned char load_wheel_1[] PROGMEM={
0x06, 0x00, 0x1E, 0x00, 0x18, 0x00, 0x60, 0x06, 0x60, 0x04, 0xC0, 0x03, 0xC0, 0x03, 0x00, 0x00,
0x00, 0x00, 0xC0, 0x03, 0xC0, 0x03, 0x60, 0x06, 0x60, 0x06, 0x18, 0x18, 0x18, 0x08, 0x04, 0x60
};

static const unsigned char load_wheel_2[] PROGMEM={
0x06, 0x60, 0x1E, 0x78, 0x18, 0x18, 0x60, 0x00, 0x60, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x00, 0xC0, 0x03, 0xC0, 0x03, 0x60, 0x06, 0x60, 0x06, 0x18, 0x18, 0x18, 0x08, 0x04, 0x60
};

static const unsigned char load_wheel_3[] PROGMEM={
0x06, 0x60, 0x1E, 0x78, 0x18, 0x18, 0x60, 0x06, 0x60, 0x06, 0xC0, 0x03, 0xC0, 0x03, 0x00, 0x00,
0x00, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0x60, 0x00, 0x60, 0x00, 0x18, 0x18, 0x18, 0x08, 0x04, 0x60
};

static const unsigned char load_wheel_4[] PROGMEM={
0x06, 0x60, 0x1E, 0x78, 0x18, 0x18, 0x60, 0x06, 0x60, 0x06, 0xC0, 0x03, 0xC0, 0x03, 0x00, 0x00,
0x00, 0x00, 0xC0, 0x03, 0xC0, 0x03, 0x60, 0x06, 0x60, 0x06, 0x18, 0x00, 0x18, 0x00, 0x04, 0x00
};

static const unsigned char load_wheel_5[] PROGMEM={
0x06, 0x60, 0x1E, 0x78, 0x18, 0x18, 0x60, 0x06, 0x60, 0x06, 0xC0, 0x03, 0xC0, 0x03, 0x00, 0x00,
0x00, 0x00, 0xC0, 0x03, 0xC0, 0x03, 0x60, 0x06, 0x60, 0x06, 0x00, 0x18, 0x00, 0x78, 0x00, 0x60
};

static const unsigned char load_wheel_6[] PROGMEM={
0x06, 0x60, 0x1E, 0x78, 0x18, 0x18, 0x60, 0x06, 0x60, 0x06, 0xC0, 0x03, 0xC0, 0x03, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x06, 0x00, 0x06, 0x18, 0x18, 0x1E, 0x78, 0x06, 0x60
};

static const unsigned char load_wheel_7[] PROGMEM={
0x06, 0x60, 0x1E, 0x78, 0x18, 0x18, 0x00, 0x06, 0x00, 0x06, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00,
0x00, 0x00, 0xC0, 0x03, 0xC0, 0x03, 0x60, 0x06, 0x60, 0x06, 0x18, 0x18, 0x1E, 0x78, 0x06, 0x60
};

static const unsigned char load_wheel_8[] PROGMEM={
0x00, 0x60, 0x00, 0x78, 0x00, 0x18, 0x60, 0x06, 0x60, 0x06, 0xC0, 0x03, 0xC0, 0x03, 0x00, 0x00,
0x00, 0x00, 0xC0, 0x03, 0xC0, 0x03, 0x60, 0x06, 0x60, 0x06, 0x18, 0x18, 0x1E, 0x78, 0x06, 0x60
};

static const unsigned char *wheelAnimated[8] = {load_wheel_1, load_wheel_2, load_wheel_3, load_wheel_4, load_wheel_5, load_wheel_6, load_wheel_7, load_wheel_8};



static stateChangeCallback changeRequestCallback;
static boolean isDisplayDimmed = false;

static BluetoothManager *bleManager = 0;

char *STATE_ID = "";

boolean isDirty = false;

boolean isLoading = false;


BaseState::BaseState(Adafruit_SSD1306 *screen){
  _screen =  screen;
}

BaseState::~BaseState(){
}

void BaseState::render(){
 
}

void BaseState::btnInterruptAction(boolean isDimmed){
  Serial.println("Class btn action");
}

void BaseState::btnUpAction(boolean isDimmed){
  Serial.println("Class btn Up");
}

void BaseState::btnDownAction(boolean isDimmed){
  Serial.println("Class btn Down");
}

void BaseState::btnBackAction(boolean isDimmed){
  Serial.println("Class btn Down");
}

void BaseState::setStateChangeRequestCallback(stateChangeCallback f){
  changeRequestCallback = f;
}

void BaseState::makeChangeRequest(char *stateID){
  changeRequestCallback(stateID);
}

boolean BaseState::getDisplayDimStatus(){
  return isDisplayDimmed;
}
void BaseState::setDisplayDimStatus(boolean isDimmed){
    isDisplayDimmed = isDimmed;
}

BluetoothManager BaseState::getBluetoothManager(){
  return *bleManager;
}
void BaseState::setBluetoothManager(BluetoothManager *bluetoothManager){
    bleManager = bluetoothManager;
}

void BaseState::incomingMessageCallback(const struct ble_msg_attributes_value_evt_t *msg){
  
}

void BaseState::updateDisplay(long lastUpdateTime){
  
}

void BaseState::sync(){
  
}

void BaseState::showLoadingWheel(){
    isLoading = true;
}

void BaseState::hideLoadingWheel(){
    isLoading = false;
}

void BaseState::renderLoadingWheel(){
  //_screen->clearDisplay();
  //_screen->drawBitmap(30, 16,  load_wheel_1, 15, 15, 1);
  //_screen->display();
}

/*
const unsigned char BaseState::getLoadingWheel(){
  //return *wheelAnimated;
}*/


void BaseState::integerToBytes(long val, byte b[4]) {
  b[0] = (byte )((val >> 24) & 0xff);
  b[1] = (byte )((val >> 16) & 0xff);
  b[2] = (byte )((val >> 8) & 0xff);
  b[3] = (byte )(val & 0xff);
}

long BaseState::bytesToInteger(byte b[4]) {
  long val = 0;
  val = ((long )b[3]) << 24;
  val |= ((long )b[2]) << 16;
  val |= ((long )b[1]) << 8;
  val |= b[0];
  return val;
}


long BaseState::byteToInteger(byte b) {
  long val = 0;
  val |= b;
  return val;
}





