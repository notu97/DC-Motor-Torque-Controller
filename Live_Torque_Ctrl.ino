/* live Current set point updater... Write the reverse direction PID values and
 *  change the motor direction.
 *  
 *  by Shiladitya Biswas.
*/

float filterVal=0.85; /// this determines smoothness  - .0001 is max  1 is off (no smoothing)
float smoothedVal;

int motor=9;
int power=7;
int dir=8;
int mVperAmp=66;
int sensor=0;
int ACSoffset=2451.17;
float voltage=0;
float Amps=0;
float curr_SP=0;
float e_curr=0;
int count=0;
float Amp_avg=0;
float kp=0.0,ki=0.0,kd=0.0;
//float kp=100,ki=0.0,kd=0.0;
float kpC=12,kiC=0.02,kdC=0.0;
float kpA=-22.5,kiA=-0.01,kdA=-2;
//float kp=75,ki=0.01,kd=0.0;
float e_curr_sum,e_curr_pre;

void setup() {
  // put your setup code here, to run once:
pinMode(motor,OUTPUT);
pinMode(dir,OUTPUT);

pinMode(power,OUTPUT);
digitalWrite(power,HIGH);
Serial.begin(9600);
}

void loop() {
if(Serial.available())
 {
  curr_SP=Serial.parseFloat();
//float  A=round(curr_SP);
  if(curr_SP>=0)
    { digitalWrite(dir,LOW);
      kp=kpC;
      ki=kiC;
      kd=kdC;
      //analogWrite(motor,10);
    Serial.print((PID(curr_SP)));
    //Serial.print(count++);
    Serial.print(" ");
    Serial.println(curr_SP);}
  else if(curr_SP<0)
    {
     digitalWrite(dir,HIGH);
     kp=kpA;
     ki=kiA;
     kd=kdA;
     //analogWrite(motor,10);
     Serial.print(PID(curr_SP));
     //Serial.print(count++);
     Serial.print(" ");
     Serial.println(curr_SP);}
    
   }
//Serial.print(PID(1.5));
  //  Serial.print(" ");
    //Serial.println(1.5);
 //delay(100);
//Serial.println(PID(2));
delay(250);
}


float PID(float curr_SP){    
    sensor=analogRead(A1);
    
    smoothedVal =  smooth(sensor, 0.85, smoothedVal);
    voltage=((smoothedVal/1024.0)*5000);
    //Amps=((voltage-ACSoffset)/mVperAmp)+0.43+0.22;
 Amps=((voltage-ACSoffset)/mVperAmp);

  //------- PID Program begin---------- 
float e_curr=curr_SP-Amps;
int    pwm_pulse=e_curr*kp+ e_curr_sum*ki+(e_curr-e_curr_pre)*kd;
    e_curr_pre=e_curr;
    e_curr_sum +=e_curr;
    if(e_curr_sum>100)
     {
        e_curr_sum=100;
      }
    if(e_curr_sum<-100)
      {
        e_curr_sum=-100;
      }      
//  //------- PID Program end---------- 
//if(pwm_pulse<150 & pwm_pulse>=0)
//   analogWrite(motor,pwm_pulse);
//else if(pwm_pulse>150)
//   analogWrite(motor,150);
//else
//   analogWrite(motor,150);
//--------------------------------------
if(pwm_pulse<150 & pwm_pulse>=0)
   analogWrite(motor,pwm_pulse);
else if(pwm_pulse>150)
   analogWrite(motor,150);
else
   analogWrite(motor,0);
return (Amps);
  //return 0;
}



int smooth(float data, float filterVal, float smoothedVal){


  if (filterVal > 1){      // check to make sure param's are within range
    filterVal = .99;
  }
  else if (filterVal <= 0){
    filterVal = 0;
  }

  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);

  return (float)smoothedVal;
}
