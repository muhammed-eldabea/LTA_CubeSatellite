/************************************************************/ 
/* [AUTHER] : MUHAMMED ELDABEA HASHEM                       */ 
/* [DATE]   : 17 OCT 2020                                   */ 
/*************************************************************/ 


/*********Include all nedded Libraries  ********/
#include <Arduino_FreeRTOS.h>
#include <semphr.h>  
#include <Wire.h> 

#include<SoftwareSerial.h>


/******* SHARED DEFINATION  ******/
#define MasterAddress   9 
#define ControlAddress  10 
#define INITIAL_MODE_SELECT     44 
#define IMAGING_MODE_SELECT     55 
#define DOWNLOAD_MODE_SELECT    66 
#define FALL_MODE_SELECT        77 


#define Synch_Pin               11 



/**********************/

#define Fall_pin 9 
int fall_State = 0 ; 
/***********************/

/*creat an Wire Semaphore */
SemaphoreHandle_t xSerialSemaphore;

/*==================== Application Based Function Defination ===================================*/

void OBC_CommandHandler( void *pvParameters )  ; 
void OBC_FaluiarMode( void *pvParameters ) ; 
void SynchWithControl()  ; 


/*==================== Driver Based Function Defination ===================================*/

void MasterWrite( int  data ) ;  
int MasterRead( )  ; 



/*================================================================================================*/


/*Defination for command array that  by which OBC can Control the Control ECU */
int Command_array[3] = {INITIAL_MODE_SELECT,IMAGING_MODE_SELECT,DOWNLOAD_MODE_SELECT} ; 

 SoftwareSerial bt(2,3);
void setup() {
  // put your setup code here, to run once:
   Wire.begin(MasterAddress); 
   Serial.begin(9600);  /*Baaud Rate for BlueTooth module*/ 
   pinMode(Synch_Pin,INPUT) ; 
    bt.begin(9600);   
       xTaskCreate(
    OBC_CommandHandler
    ,  "CommandHandler"  // A name just for humans
    ,  356  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL ); 


 xTaskCreate(
    OBC_FaluiarMode
    ,  "FaluiarMode"  // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  0  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );



}



void loop() {
  // put your main code here, to run repeatedly:
}  




/*=================================================================*/ 

void OBC_CommandHandler( void *pvParameters __attribute__((unused))  )   

{
char command = 0 ; 

for(;;) 
{

if(bt.available() > 0)  // Send data only when you receive data:
{

command = bt.read() ; 
delay(100) ; 
Serial.print(command);        //Print Value inside data in Serial monitor

switch(command) 
{
case 'a' : 
        MasterWrite(Command_array[0]);  
        SynchWithControl()  ; 
        break ; 
case 'b' : 
        MasterWrite(Command_array[1]);  
        SynchWithControl()  ; 
         break ;
 case 'd' : 
        MasterWrite(Command_array[2]);  
        SynchWithControl()  ; 
         break ;
default : 
command = 0 ; 

  
}

}

  vTaskDelay(50);

}

}
  


/*=================================================================*/ 

void OBC_FaluiarMode( void *pvParameters __attribute__((unused)) ) 
{


digitalWrite(Fall_pin,OUTPUT) ; 
for (;;)
{

if (fall_State == 1 ) 
{
  digitalWrite(Fall_pin,HIGH) ; 
}

  vTaskDelay(700);
}
  
}

/*=================================================================*/ 




void MasterWrite( int data ) 
{
    Wire.beginTransmission(ControlAddress); 
    Wire.write(data);              
    Wire.endTransmission();    // stop transmitting
    delay(500);
}

/*=================================================================*/ 

int MasterRead( ) 
{
  int data = 0 ;  
   Wire.requestFrom(ControlAddress, 4);    // request 6 bytes from slave device #8
   data = Wire.read(); 
   return data ; 

} 
/*=================================================================*/ 
void SynchWithControl() 
{
  while(digitalRead(Synch_Pin) != HIGH) 
  {} 
}
