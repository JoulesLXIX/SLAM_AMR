#define ENCA 2 
#define ENCB 6
#define IN1 4
#define IN2 5

int pwm = 0;
int pos = 0;
long prevT = 0;
int target = 0;
long currT = 0;
float deltaT = 0;
float u = 0;
float rot = 0;
float eprev = 0;
float eintegral = 0;

float kp = 5;
float kd = 0.025;
float ki = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
}

void loop(){

  rot = -1;
  convertRotation();
  currT = micros();
  deltaT = ((float)(currT - prevT))/1.0e6;
  prevT = currT;
  
  //
  pidControl();
  printDesAngle();
}

void convertRotation(){
  target = rot * 1380;
}

void setMotor(int dir, int pwmVal, int in1, int in2){
  if (dir == 1){
    analogWrite(IN1, pwmVal);
  }
  if (dir == -1){
    analogWrite(IN2, pwmVal);
  }
  else{
    
  }
}

void pidControl(){
  int e = target - pos; 
  float dedt = (e-eprev) / (deltaT);
  eintegral = eintegral + e*deltaT;

  u = kp*e + kd*dedt + ki*eintegral;

  float pwr = fabs(u);
  if (pwr >255){
    pwr = 255;
  }
  int dir = 1;
  if (u<0){
    dir = -1;
  }
  
  setMotor(dir,pwr,IN1,IN2);
  eprev = e;
}

void printDesAngle(){
  Serial.print(F("-1:"));
  Serial.print(-0);
  Serial.print(",");
  Serial.print(F("1:"));
  Serial.print(1500);
  Serial.print(",");
  Serial.print(F("e:"));
  Serial.print(u);
  Serial.print(",");
  Serial.print(F("target:"));
  Serial.print(target);
  Serial.print(",");
  Serial.print(F("pos:"));
  Serial.println(pos);
}

void readEncoder(){
  int b = digitalRead(ENCB);
  if(b>0){
    pos++;
  }
  else{
    pos--;
  }
}