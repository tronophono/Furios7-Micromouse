/*
 * Dispatch.cpp
 *
 *  Created on: Dec 29, 2016
 *      Author: lasantos
 *
 *      This library contains all the functions you can use to an object of type Dispatch.
 *
 *		This functions include setting up the pins in which the IR sensors are connected, and be able to read
 *
 *		the analog values of the sensor.
 */

#include "Dispatch.h"
#include "Arduino.h"

/*This is the constructor, it is code that will be executed when you make an object in C++.
 * In this case we are setting up the IR sensors.
 */

long int IR_leftavg = 0;
long int IR_rightavg = 0;
long int IR_middleavg = 0;

int irArray[3];

Dispatch::Dispatch(byte front_in, byte left_in, byte right_in, byte diagonalL_in, byte diagonalR_in) {
  //MiddelWallPoint = 20;

  pinMode(front_in, INPUT);
  pinMode(left_in, INPUT);
  pinMode(right_in, INPUT);
  pinMode(diagonalL_in, INPUT);
  pinMode(diagonalR_in, INPUT);

  irArray[0] = front_in;
  irArray[1] = left_in;
  irArray[2] = right_in;
  irArray[3] = diagonalL_in;
  irArray[4] = diagonalR_in;
}

void Dispatch::AverageTolly() {

  if (!Averagestate) {
    unsigned int IR_left = 0;
    unsigned int IR_right = 0;
    unsigned int IR_middle = 0;
    for (byte i = 0; i < 100; i++) {
      IR_left += analogRead(A0);
      IR_right += analogRead(A2);
      IR_middle += analogRead(A1);
    }

    IR_leftavg = IR_left / 100;
    IR_rightavg = IR_right / 100;
    IR_middleavg = IR_middle / 100;

    if (IR_leftavg != IR_rightavg and IR_leftavg != IR_middleavg) {
      if (IR_rightavg != IR_leftavg) {
        IR_rightavg = IR_leftavg;
      }
      if (IR_rightavg != IR_middleavg) {
        IR_middleavg = IR_rightavg;
      }
    }
  } else {
    //  Serial.print("Average already taken");
  }

  Averagestate = true;
}

void Dispatch::CheckFront() {

  int IR_middle;
  IR_middle = analogRead(irArray[0]);

  if (IR_middle >= MiddleWallPoint) {
    //   Serial.println("There is a wall in the front");
    state_mid = 1;
  } else {
    //   Serial.println("There is space in front");
    state_mid = 0;

  }

}

void Dispatch::CheckSides() {
  int IR_left, IR_right;
  IR_left = analogRead(irArray[1]);
  IR_right = analogRead(irArray[2]);

  if (IR_left >= MiddleWallPoint) {
//    Serial.println("There is a wall at left");
    state_left = 1;
  } else {
//    Serial.println("There is space at left");
    state_left = 0;
  }

  if (IR_right >= MiddleWallPoint) {
    //   Serial.println("There is a wall at right");
    state_right = 1;
  } else {
    //  Serial.println("There is a space at right");
    state_right = 0;
  }
}

void Dispatch::RawValues() {
  unsigned long int front;
  unsigned long int left;
  unsigned long int right;
  unsigned long int diagonalL;
  unsigned long int diagonalR;

  front = analogRead(irArray[0]);
  left = analogRead(irArray[1]);
  right = analogRead(irArray[2]);
  diagonalL = analogRead(irArray[3]);
  diagonalR = analogRead(irArray[4]);

  Serial.print("Front: ");
  Serial.print(front);
  Serial.print("   Left: ");
  Serial.print(left);
  Serial.print("   Right: ");
  Serial.print(right);
  Serial.print("   DiagonalL: ");
  Serial.print(diagonalL);
  Serial.print("   DiagonalR: ");
  Serial.println(diagonalR);
}

