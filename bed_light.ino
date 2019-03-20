int trigPin = 11;
int echoPin = 12;
long duration, cm;
int ledPin = 10;
int threshold = 5;
int margin = 1;
int range = 182; //182 cm is about 6ft
int onTime = 0;
bool on = false;
int offTime = 25; //time to turn off 25 = 5*(seconds in this current scheme)
/*
 * turn on if:
 *     distance fluxuates for 1 second
 * turn off if:
 *     distance doesn't change by much for a minute
 */
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop()
{
    if(inRange()==1 && !on){
        turnOn();
        on = true;
        onTime = 0;
    }
    else if(on){
        onTime +=1;
        if(onTime>=offTime){
            turnOff();
            on = false;
        }
    }
    delay(200);
}

void triggerPulse(){
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    //int trigPin = dualPin;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
}

int echoReceive(){
    //int echoPin = dualPin; //echoPin
    return pulseIn(echoPin, HIGH, 32760);
}

int inRange(){
    int sum = 0;
    for(int i=0;i<threshold;++i){
      triggerPulse();
      long dur = echoReceive();
      delay(5);
      long cm = (dur/2) / 29.1;
      Serial.println(cm);
      sum += (cm<range&&cm>0?1:0);
    }
    return (sum>=threshold-margin?1:0);
}

void turnOn(){
    Serial.println("turning light on");
    digitalWrite(ledPin, HIGH);
}

void turnOff(){
    Serial.println("turning light off");
    digitalWrite(ledPin, LOW);
}

