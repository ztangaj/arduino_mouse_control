#include <adk.h>
#include <KeyboardController.h>
#include <address.h>
#include <usb_ch9.h>
#include <hid.h>
#include <MouseController.h>
#include <parsetools.h>
#include <hidusagestr.h>
#include <Usb.h>
#include <confdescparser.h>
#include <hidboot.h>

/*
 Mouse Controller Example

 Shows the output of a USB Mouse connected to 
 the Native USB port on an Arduino Due Board.

 created 8 Oct 2012
 by Cristian Maglie

 http://arduino.cc/en/Tutorial/MouseController

 This samlple code is part of the public domain.
 */

// Require mouse control library
//#include <MouseController.h>

// Initialize USB Controller
USBHost usb;

// Attach mouse controller to USB
MouseController mouse(usb);

// variables for mouse button states
boolean leftButton = false;
boolean middleButton = false;
boolean rightButton = false;

int16_t x = 0;
int16_t y = 0;

// This function intercepts mouse movements
void mouseMoved() {
  x += mouse.getXChange();
  y += mouse.getYChange();
  //Serial.print("Move: ");
  //Serial.print(x);
  //Serial.print(", ");
  Serial.println(y);
}

// This function intercepts mouse movements while a button is pressed
void mouseDragged() {
  Serial.print("DRAG: ");
  Serial.print(mouse.getXChange());
  Serial.print(", ");
  Serial.println(mouse.getYChange());
}

// This function intercepts mouse button press
void mousePressed() {
  Serial.print("Pressed: ");
  if (mouse.getButton(LEFT_BUTTON)){
    Serial.print("L");
    leftButton = true;
  }
  if (mouse.getButton(MIDDLE_BUTTON)){
    Serial.print("M");
    middleButton = true;
  }
  if (mouse.getButton(RIGHT_BUTTON)){
    Serial.print("R");
    Serial.println();
    rightButton = true;
  }
}

// This function intercepts mouse button release
void mouseReleased() {
  Serial.print("Released: ");
  if (!mouse.getButton(LEFT_BUTTON) && leftButton==true) {
    Serial.print("L");
    leftButton = false;
  }
  if (!mouse.getButton(MIDDLE_BUTTON) && middleButton==true) {
    Serial.print("M");
    middleButton = false;
  }
  if (!mouse.getButton(RIGHT_BUTTON) && rightButton==true) {
    Serial.print("R");
    rightButton = false;
  }
  Serial.println();
}

void setup()
{
  Serial.begin(9600);
  //Serial.println("Program started");
  delay(200);
}

void loop()
{
  // Process USB tasks
  usb.Task();
  
}
