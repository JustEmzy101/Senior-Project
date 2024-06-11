
#define in1 2
#define in2 3  
#define in3 4
#define in4 5
#define enA 9 
#define enB 10 
const int triggerPin = 6;
const int echoPin = 7;
const int buzz = 8;
int  xAxis, yAxis;
int motorSpeedA = 0;
int motorSpeedB = 0;
long duration;
int dist;


void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzz, OUTPUT);
  
}

void loop() {
 
  xAxis = analogRead(A0); // Read Joysticks X-axis   
  yAxis = analogRead(A1); // Read Joysticks Y-axis    
  Serial.println(xAxis);
  Serial.println(yAxis);
  


  // Y-axis used for forward and backward control
  if (0 <= xAxis <= 1023 && yAxis > 1000  ) {   // Testing for mapping 
    // Set Motor backward

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = 120;
    motorSpeedB = 120;
    analogWrite(enA, motorSpeedA); 
    analogWrite(enB, motorSpeedB);
    
  }
  else if (0 <= xAxis <= 1023 && yAxis < 20 ) {
    // Set Motor forward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 550, 1023, 0, 255);
    motorSpeedB = map(yAxis, 550, 1023, 0, 255);
    analogWrite(enA, motorSpeedA); 
    analogWrite(enB, motorSpeedB);
        

  }
  // If joystick stays in middle the motors are not moving
  else {
    motorSpeedA = 0;
    motorSpeedB = 0;

}
// X-axis used for left and right control
  if (xAxis <20 && 0 <= yAxis <= 1023 ) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Convert the declining X-axis readings
    motorSpeedA = map(yAxis, 470, 0, 0, 255);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
    analogWrite(enA, motorSpeedA); 
    analogWrite(enB, motorSpeedB);
  }

  if ( xAxis > 1000 && 0 <= yAxis <= 1023 ) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    // Convert the declining X-axis readings
    motorSpeedA = map(yAxis, 470, 0, 0, 255);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
    analogWrite(enA, motorSpeedA); 
    analogWrite(enB, motorSpeedB);
  }

  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist = duration * 0.034 / 2;
  delay(500);
  Serial.print("Distance: ");
  Serial.println(dist);

  if (dist < 200) {
    digitalWrite(buzz,HIGH);
  for (int i=dist; i>0; i--)
    delay(15);
  
    for (int i=dist; i>0; i--)
    delay(15);

  digitalWrite(buzz,LOW);
  for (int i=dist; i>0; i--)
    delay(15);
 
    for (int i=dist; i>0; i--)
    delay(15);   
  }
  if (dist < 20) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

}
}
