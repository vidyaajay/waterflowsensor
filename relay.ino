int controlInput=5;// output pin for sending signal from arduino to turn ON or OFF the pump

// here we used relay with NO- normally open mode, so when the controlInput is LOW, pump is ON and when the controlInput is HIGH, pump is OFF
void setup() {
  Serial.begin(9600);

  //configuring OUTPUT pin
  pinMode(controlInput,OUTPUT);

  //switch OFF the pump initially
  digitalWrite(controlInput,HIGH);
}

void loop() {
  // wait for 1 second
  delay(1000);
  //switch ON the pump for 3 second
  digitalWrite(controlInput,LOW);
  delay(3000);
  //switch OFF the pump 
  digitalWrite(controlInput,HIGH);
}
