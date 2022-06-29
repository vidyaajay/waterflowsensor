int controlInput=5;
int trigger =4;
int echo=3;
long duration;
float distance;
int inputPin=2;
float flowRate;
// factor = pulses in 1 liter of water flow;
float factor=4330;
float volume;
float currentTime;
int counterStart=0,counterStop=0;
volatile unsigned long pulseCounter=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(controlInput,OUTPUT);
  pinMode(inputPin,INPUT);
  digitalWrite(inputPin,HIGH);
  pinMode(trigger, OUTPUT);
  pinMode(echo,INPUT);
  digitalWrite(trigger,LOW);
  digitalWrite(controlInput,HIGH);
  attachInterrupt(digitalPinToInterrupt(inputPin),IRS_Counter,RISING);
  currentTime=millis();
  volume=0;
  counterStart=0;
  counterStop=0;
}

void loop() {
//  Serial.print("milis:");
//  Serial.println(millis());
  
  if(millis()-currentTime>=1000){
    detachInterrupt(digitalPinToInterrupt(inputPin));
    currentTime=millis();
    flowRate=(pulseCounter*60*1000)/factor;
    volume+=(flowRate/60);
      Serial.print("Pulse Count:");
      Serial.println(pulseCounter);
    Serial.print("Flow rate of water(in mL/min):");
    Serial.println(flowRate,DEC);
    Serial.print("Volume of water(mL):");
    Serial.println(volume,DEC);
      pulseCounter=0;
   attachInterrupt(digitalPinToInterrupt(inputPin),IRS_Counter,RISING);
    dist();
  }
 
}

void IRS_Counter(){
  pulseCounter++;
//  Serial.print("Pulse Count:");
//  Serial.println(pulseCounter);
}
void dist() {
  //delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  duration = pulseIn(echo,HIGH);
  distance=1.0*333*duration*100*(1e-6)/2;
  //print out the value of the pushbutton
  Serial.print("Duration:");
  Serial.println(duration);
  Serial.print("Distance(in cm):");
  Serial.println(distance);

  //maintain the level of water 4.25cm from sensor
  if(distance>4.25){
    counterStop=0;
    counterStart++;
    if(counterStart>=3)
      digitalWrite(controlInput,LOW);
  }
  else{
    counterStart=0;
    counterStop++;
    if(counterStop>=2)
      digitalWrite(controlInput,HIGH);
  
  }
}
