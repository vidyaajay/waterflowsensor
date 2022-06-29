int inputPin=2;//input from flowmeter sensor
float flowRate;

// factor = pulses generated for 1 liter of water flow;
float factor=4330;
float volume;
float currentTime;
volatile unsigned long pulseCounter=0; //varible for counting pulses generated due to water flow

void setup() {
  Serial.begin(9600);

  //configuring pin for INPUT
  pinMode(inputPin,INPUT);
  //Initially set the inputPin to HIGH 
  digitalWrite(inputPin,HIGH);

  //for continuously checking if any Rising edge came or not, if there is rising edge call IRS_Counter() function
  attachInterrupt(digitalPinToInterrupt(inputPin),IRS_Counter,RISING);

  //millis() gives the time since arduino started, setting current time to millis()
  currentTime=millis();
  volume=0; // initial volume is zero
 
}

void loop() {

  //do all the calculations every 1 second
  if(millis()-currentTime>=1000){
    //stop checking for rising edge through interrupt
    detachInterrupt(digitalPinToInterrupt(inputPin));
    currentTime=millis(); //changing the current time to millis() so millis()-currentTime=0

    // flowrate= (pulse count)/(pulses per liter) (in liter/s)
    // for milliliter/min flowrate=(pulse count)*60*1000/(pulse per liter)
    flowRate=(pulseCounter*60*1000)/factor;

    //volume=(prev volume)+(flowrate*time)
    volume+=(flowRate/60);
    
    // Serial.print("Pulse Count:");
    // Serial.println(pulseCounter);

    // printing the flowrate and volume
    Serial.print("Flow rate of water(in mL/min):");
    Serial.println(flowRate,DEC);
    Serial.print("Volume of water(mL):");
    Serial.println(volume,DEC);

    //setting pulse count to zero for another loop
      pulseCounter=0;

   // again set up the interrupt to check for rising edge
   attachInterrupt(digitalPinToInterrupt(inputPin),IRS_Counter,RISING);
  }
}

void IRS_Counter(){
  // if we hit a rising edge increse the pulse count by 1
  pulseCounter++;
}
