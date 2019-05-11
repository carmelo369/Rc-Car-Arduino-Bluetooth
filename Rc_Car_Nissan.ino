/************************************
 *Author: Carmelo Hernandez
 *Date modified: 08 March 2019
 *Date finished: 21 March 2019
 *Project: RC Car Nissan Skyline 
 *controled by Arduino Uno R3 board, 
 *Bluetooth, and Android smarthphone
 ************************************
 */
 
//L298N Connection   
  const int motorA1  = 5;  // Pin  2 of L298N
  const int motorA2  = 6;  // Pin  7 of L298N
  const int motorB1  = 10; // Pin 10 of L298N
  const int motorB2  = 9;  // Pin 14 of L298N
//Leds connected to Arduino UNO Pin 12
  const int lights  = 12;
//Buzzer / Speaker to Arduino UNO Pin 3
  const int buzzer = 3 ;   
//Bluetooth (HC-05) State pin on pin 2 of Arduino
  const int BTState = 2;
//Variables for speed control
  int i=0;
  int j=0;
  int state;
  int vSpeed=200;     // Default speed, from 0 to 255

// Void to setup the input and output values 
void setup() {
    // Set pins as outputs:
    pinMode(motorA1, OUTPUT); // Positive driver motor to L298N
    pinMode(motorA2, OUTPUT); // Negative driver motor to L298N
    pinMode(motorB1, OUTPUT); // Positive steering motor to L298N
    pinMode(motorB2, OUTPUT); // Negative steering motor to L298N
    pinMode(lights, OUTPUT); // Positive energy to breadboard to turn on/off LED's
    pinMode(BTState, INPUT); // Information from Bluetooth transmitter
    Serial.begin(9600); // Initialize serial communication between HC-05 Bluetooth and Arduino board at 9600 bits per second
}

// Loop for controller speed, light, sound, and direction of the car
void loop() {
  //Save income data to variable 'state'
    if(Serial.available() > 0){     
      state = Serial.read();   
    }
  
  //Statements to change speed in android application 
    if (state == '0'){
      vSpeed=0;}
    else if (state == '1'){
      vSpeed=100;}
    else if (state == '2'){
      vSpeed=180;}
    else if (state == '3'){
      vSpeed=200;}
    else if (state == '4'){
      vSpeed=255;}
     
  /***********************Forward****************************/
  //If state is equal with letter 'F', car will go forward!
    if (state == 'F') {
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
        analogWrite(motorB1, 0);      analogWrite(motorB2, 0); 
    }
  /**********************Forward Left************************/
  //If state is equal with letter 'G', car will go forward left
    else if (state == 'G') {
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);  
        analogWrite(motorB1, 200);    analogWrite(motorB2, 0); 
    }
  /**********************Forward Right************************/
  //If state is equal with letter 'I', car will go forward right
    else if (state == 'I') {
        analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);      analogWrite(motorB2, 200); 
    }
  /***********************Backward****************************/
  //If state is equal with letter 'B', car will go backward
    else if (state == 'B') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, 0); 
    }
  /**********************Backward Left************************/
  //If state is equal with letter 'H', car will go backward left
    else if (state == 'H') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 200); analogWrite(motorB2, 0); 
    }
  /**********************Backward Right************************/
  //If state is equal with letter 'J', car will go backward right
    else if (state == 'J') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, 200); 
    }
  /***************************Left*****************************/
  //If state is equal with letter 'L', wheels will turn left
    else if (state == 'L') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        analogWrite(motorB1, 200); analogWrite(motorB2, 0); 
    }
  /***************************Right*****************************/
  //If state is equal with letter 'R', wheels will turn right
    else if (state == 'R') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, 200);     
    }
  /************************Lights*****************************/
  //If state is equal with letter 'W', turn leds on or of off
    else if (state == 'W') {
      if (i==0){  
         digitalWrite(lights, HIGH); 
         i=1;
      }
      else if (i==1){
         digitalWrite(lights, LOW); 
         i=0;
      }
      state='n';
    }
  /**********************Horn sound***************************/
  //If state is equal with letter 'V', play (or stop) horn sound
    else if (state == 'V'){
      if (j==0){  
         tone(buzzer, 1000);//Speaker on 
         j=1;
      }
      else if (j==1){
         noTone(buzzer);    //Speaker off 
         j=0;
      }
      state='n';  
    }
  /************************Stop*****************************/
  //If state is equal with letter 'S', stop the car
    else if (state == 'S'){
        analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
    }   
}
