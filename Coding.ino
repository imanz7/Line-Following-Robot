//BLUETOOTH
int EN = 2;     // initialize pin for bluetooth
char button;     // variable data for bluetooth to receive
int TIMEOUT = 100;       // initialize TIMEOUT to 0.1 sec
unsigned long startTime = 0;  // initialize startTime variable
//MOTOR - pin initialization for motor
int ML = 7; // Direction Motor 1
int PWML = 6; //PWM Motor 1
int MR = 4; // Direction Motor 1
int PWMR = 5; //PWM Motor 2
//SERVO
#include <Servo.h>    // include servo library
Servo myservo;      // create servo object to control a servo
int servoPin = 9;     // declare servo pin to pin 9
//LINE SENSOR
const int LS1 = A0;
const int LS2 = A1;
const int LS3 = A2;
const int LS4 = A3;
const int LS5 = A4;  // initialize all pins for line sensors
int DS_1 = 0; 
int DS_2 = 0;
int DS_3 = 0;
int DS_4 = 0;
int DS_5 = 0; // declare all sensors value to 0
int memory; // variable to store last data memory of sensor
//PROXIMITY SENSOR
 const int sensorPin = 3; // declare sensor pin to pin 3
int sensorVal; // variable to store value of sensor




void forward( int pwm_left, int pwm_right){ //right tyre
  digitalWrite(MR, HIGH);  //direction
  analogWrite(PWMR, pwm_right);   //speed control
  //left tyre
  digitalWrite(ML, HIGH);   //direction
  analogWrite(PWML, pwm_left);  //speed control}
void backward( int pwm_left,int pwm_right){ //right tyre
  digitalWrite(MR, LOW);  //direction
  analogWrite(PWMR, pwm_right);    //speed control
  //left tyre
  digitalWrite(ML, LOW);  //direction
  analogWrite(PWML, pwm_left);  //speed control}
void left( int pwm_left,  int pwm_right){ //right tyre
  digitalWrite(MR, LOW);   //direction
  analogWrite(PWMR, pwm_right);   //speed control
  //left tyre
  digitalWrite(ML, HIGH);   //direction
  analogWrite(PWML, pwm_left);  //speed control}
void right( int pwm_left,  int pwm_right){ //right tyre
  digitalWrite(MR,HIGH);  //direction
  analogWrite(PWMR, pwm_right);    //speed control
  //left tyre
  digitalWrite(ML, LOW);  //direction
  analogWrite(PWML, pwm_left);  //speed control}
void stops() { //right tyre
  digitalWrite(MR, LOW); //direction
  analogWrite(PWMR, 0); //speed control
  //left tyre
  digitalWrite(ML, LOW); //direction
  analogWrite(PWML, 0); //speed control}




void FOLLOWLINE() { do  { //LS
    DS_1 = digitalRead(LS1);
    DS_2 = digitalRead(LS2);
    DS_3 = digitalRead(LS3);
    DS_4 = digitalRead(LS4);
    DS_5 = digitalRead(LS5);
    //PROXIMITY SENSOR
    sensorVal = digitalRead(sensorPin);     // sensorVal = read state of sensor (LOW or HIGH)
    if (sensorVal == LOW) 
{ // if sensor detects obstacle, enter this condition
      // Stop
      digitalWrite(MR, LOW);     //direction
      analogWrite(PWMR, 0);   //speed control
      digitalWrite(ML, LOW);  //direction
      analogWrite(PWML, 0);    //speed control
      delay(1000);     //delay for 1 sec
      //Left
      left(130,30);
      delay(1000);       //delay for 1 sec
      //Forward
      forward(110,80);
      delay(1000);      //delay for 1 sec  }
       else  { // if sensor detects no obstacle, enter this condition
      if(DS_1 == 1)   //10000     {
        left(180,100);
        memory=1;}
      else if(DS_2 == 1)  //01000 {
        forward(210,180);
        memory=2;}
      else if(DS_1 == 1 && DS_2 == 1 )  //11000{
        forward(210,180);
        memory=2;}


      else if(DS_1 == 1 && DS_2 == 1 && DS_3 == 1 )   //11100{
        forward(210,180);
        memory=2;}
      else if(DS_3 == 1)    //00100{
        forward(190,210);
        memory=2;}
      else if(DS_2 == 1 && DS_3 == 1)   //01100{
        forward(220,190) ;
        memory=2; }
      else if(DS_3 ==1 && DS_4 ==1  //00110{
        forward(180,220) ;
        memory=2; }
      else if(DS_1 == 1 && DS_2 == 1 && DS_3 == 1 && DS_4 == 1 && DS_5 == 1)    //11111{
        forward(220,190) ;
        memory=2; }
      else if(DS_2 == 1 && DS_3 == 1 && DS_4 == 1)    //01110{
        forward(180,220) ;
        memory=2;}
      else if(DS_5 == 1   //00001 {
        right(60,180);
        memory=3;}
      else if(DS_4 == 1)    //00010{
        right(180,210);
        memory=3; }
      else if(DS_3 == 1 && DS_4 == 1)   //00110{
        forward(190,220);
        memory=2;}
      else if(DS_4 == 1 && DS_5 == 1)   //00011 {
        forward(180,210);
        memory=2;}
      else if(DS_3 == 1 && DS_4 == 1 && DS_5 == 1)    //00111{
        forward(190,210);
        memory=2;}

      else if(DS_1 == 0 && DS_2 == 0 && DS_3 == 0 && DS_4 == 0 && DS_5 == 0)    //00000
{        if(memory==1) { left(160,30); }
        else if(memory==2){ backward(200,170); }
        else if(memory==3){ right(30,160);}}}} while(1);     // continue to loop while the condition is true}

void setup() { //BLUETOOTH
  pinMode(EN, OUTPUT);    // set bluetooth as output
  Serial.begin(38400);
  //MOTOR
  pinMode(MR,OUTPUT);     // set right motor as output
  pinMode(PWMR, OUTPUT);
  pinMode(ML, OUTPUT);    // set left motor as output
  pinMode(PWML, OUTPUT);
  //SERVO
  myservo.attach(servoPin); 
  // attaches the servo on pin 3 to the servo object
 //LSS05
  pinMode(LS1, INPUT);
  pinMode(LS2, INPUT);
  pinMode(LS3, INPUT);
  pinMode(LS4, INPUT);
  pinMode(LS5, INPUT);    //declare pins as INPUT for line sensors
  //PROXIMITY SENSOR
  pinMode(sensorPin, INPUT);    // initialize the sensor pin as an input}
void loop() { //forward(100,100);
  //BLUETOOTH
  digitalWrite(EN, LOW);    // enable receiving data
  //LineFollow();
  if (Serial.available() > 0)   // condition when receiving data{ button = Serial.read();   // button = read the incoming data
    startTime = millis();
   //MANUAL MODE
    if( button == 'W' )   {   //if data received equal to 'W', MOVE FORWARD
        forward(200, 190); }
    else if( button == 'S' )  {   //if data received equal to 'S', MOVE BACKWARD
        backward(250, 240); }
    else if( button == 'A' ) {   //if data received equal to 'A', MOVE LEFT
        left(200, 0); }
   else if( button == 'D' ) {   //if data received equal to 'D', MOVE RIGHT
        right(0, 250); }
    else if( button == 'F'){  FOLLOWLINE();}
    else if (button == 'Z') {   //if data received equal to 'Z', servo moves up at angle 90°
        myservo.write(0);}
    else if (button == 'X') {   //if data received equal to 'X', servo moves down at angle 45°
        myservo.write(45); }
    else if (button == 'C'){   //if data received equal to 'C', servo moves down at angle 90°
        myservo.write(90); } }
  else if((millis()-startTime) >= TIMEOUT) {   //if no data received within 0.1 sec, motor stop     
     forward(0, 0);}
