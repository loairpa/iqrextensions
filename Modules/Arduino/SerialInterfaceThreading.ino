// Serial Interface with threading 
// Author: Lovisa Irpa Helgadottir

#include <SoftwareSerial.h>
#include <havimo.h>
#include <pt.h>

// Havimo
#define rxPin 2
#define txPin 3

HaViMo havimo(rxPin,txPin,115200);

// Threads
static struct pt pt1, pt2;

// Instructions
int const PIN_MODE = 0;
int const DIGITAL_READ = 1;
int const DIGITAL_WRITE = 2;
int const ANALOG_REFERENCE = 3;
int const ANALOG_READ = 4;
int const ANALOG_WRITE = 5;


int const H = 1;
int const L = 0;
byte com, pin, start, value ;

static int serialInterfaceThread(struct pt *pt){
   
  PT_BEGIN(pt);
  
    if(Serial.available()>0){

      start=getCommand();
      while(start !=0){start=getCommand();}

      com=getCommand();      
      getCommand();
      pin=getCommand(); 
      

      
      if(com==PIN_MODE || com==DIGITAL_WRITE) {
        getCommand();
        value=getCommand();
        Serial.print(start);
        Serial.print(com); 
        Serial.print(start);  
        Serial.print(pin);
        Serial.print(value);
        allFunc(com,pin,value);
        }
     
     if(com==DIGITAL_READ || com==ANALOG_READ){
     Serial.print(start);
        Serial.print(com); 
        Serial.print(start);  
        Serial.print(pin);  
     Serial.print(start);
     Serial.print(allFunc(com,pin,0));}

   
     
     if(com==ANALOG_WRITE){
     getCommand();
             Serial.print(start);
        Serial.print(start);
        Serial.print(com); 
        Serial.print(start);  
        Serial.print(pin);
     Serial.print(start);
     value=getCommand(); 
     if(value<100){Serial.print(start);}
     if(value<10){Serial.print(start);}
     Serial.print(value);
      allFunc(com,pin,value);
        }

    }

  PT_END( pt );

}

static int havimoThread(struct pt *pt){

  PT_BEGIN(pt); 
   
   int c[16], d[16];  
  
   havimo.captureRegion();  
   havimo.readRegion(1,c);
  havimo.readRegion(2,d);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);

  // Find color 2
  if((c[1]==2 && c[2]+c[3]>100) || (d[1]==2 && d[2]+d[3]>100 ) ){
   allFunc(DIGITAL_WRITE,12,1);
  }
  else{
    allFunc(DIGITAL_WRITE,12,0);
  }
  
  // Find color 1
  if((c[1]==1 && c[2]+c[3]>100)  ||(d[1]==1 && d[2]+d[3]>100)){
    allFunc(DIGITAL_WRITE,13,1);

  }
  else{
    allFunc(DIGITAL_WRITE,13,0);
  }
    
   PT_END( pt );
}




int getCommand(){
  int m=Serial.read();
  return m;
}


int allFunc(int com,int pin,int value){
    int val;
    switch(com){
    case PIN_MODE:
       pinMode(pin,value);
    case DIGITAL_READ:
        return digitalRead(pin);
        break;   
    case DIGITAL_WRITE:
       digitalWrite(pin,value);
       break;
    case ANALOG_READ:
        val= analogRead(pin);       
       if (val <100){Serial.print(0);}
       if (val<10){Serial.print(0);}
       return val;
       break;
    case ANALOG_WRITE:
       analogWrite(pin,value); 
       break;
    
    default:
       break;
   }
}

void setup(){
  Serial.begin(115200);
  Serial.flush();
  PT_INIT(&pt1);     
  PT_INIT(&pt2);
}

void loop(){
 havimoThread(&pt2);
 serialInterfaceThread(&pt1);
  
  
  
}

