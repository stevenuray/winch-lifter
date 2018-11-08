const int enablePin = 3;
const int inputAPin = 4;
const int inputBPin = 5;
const int directionButtonOutputPin = 8;
const int clockwiseDirectionButtonInputPin = A0;
const int counterClockwiseDirectionButtonInputPin = A2;
const int maxAnalogInputForNoPress = 1000;

enum RotationDirection {
  CLOCKWISE,
  COUNTER_CLOCKWISE
};

RotationDirection rotationDirection = COUNTER_CLOCKWISE;

void setup() {
  Serial.begin(9600);  
  setupEnablePin();
  setupDirectionSwitch();
}

void loop() {
  setRotationFromInputs();
  setRotationDirectionFromDirectionButton();
  Serial.println();
  delay(250);  
}

void setRotationDirectionFromDirectionButton(){
  int clockwiseInputVal = analogRead(clockwiseDirectionButtonInputPin);
  int counterClockwiseInputVal = analogRead(counterClockwiseDirectionButtonInputPin);
  Serial.println("clockwiseInputVal is: " + (String) clockwiseInputVal);
  Serial.println("counterClockwiseInputVal is: " + (String) counterClockwiseInputVal);

  if(clockwiseInputVal > counterClockwiseInputVal){
    rotateClockwiseDependingOnDirectionButtonState(clockwiseInputVal);
  } else {
    rotateCounterClockwiseDependingOnDirectionButtonState(counterClockwiseInputVal);
  }  

  Serial.println("rotationDirection is: " + (String) rotationDirection);
}

void rotateClockwiseDependingOnDirectionButtonState(int clockwiseInputVal){
  Serial.println("Clockwise Rotation Check");
  if(clockwiseInputVal > maxAnalogInputForNoPress){
    Serial.println("Rotating clockwise");
    rotateClockwise();
  }
}

void rotateCounterClockwiseDependingOnDirectionButtonState(int counterClockwiseInputVal){
  Serial.println("Counter Clockwise Rotation Check");
  if(counterClockwiseInputVal > maxAnalogInputForNoPress){
    Serial.println("Rotating counter-clockwise");
    rotateCounterClockwise();
  }
}

void rotateClockwise() {
  pinMode(inputAPin, OUTPUT);
  digitalWrite(inputAPin, LOW);
  
  pinMode(inputBPin, OUTPUT);
  digitalWrite(inputBPin, HIGH);

  rotationDirection = CLOCKWISE;    
}

void rotateCounterClockwise() {
  pinMode(inputAPin, OUTPUT);
  digitalWrite(inputAPin, HIGH);
  
  pinMode(inputBPin, OUTPUT);
  digitalWrite(inputBPin, LOW);

  rotationDirection = COUNTER_CLOCKWISE;  
}

void setupDirectionSwitch() {
  pinMode(directionButtonOutputPin, OUTPUT);
  digitalWrite(directionButtonOutputPin, HIGH);
}

void setRotationFromInputs(){
  int clockwiseInputVal = analogRead(clockwiseDirectionButtonInputPin);
  int counterClockwiseInputVal = analogRead(counterClockwiseDirectionButtonInputPin);
  if(clockwiseInputVal > maxAnalogInputForNoPress || counterClockwiseInputVal > maxAnalogInputForNoPress){
    startRotation();
  } else{
    stopRotation();
  }  
}

void setupEnablePin() {
  pinMode(enablePin, OUTPUT);
}

void startRotation() {  
  Serial.println("Rotation");
  digitalWrite(enablePin, HIGH);
}

void stopRotation(){
  Serial.println("No rotation");
  digitalWrite(enablePin, LOW);
}

