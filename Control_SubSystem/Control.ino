
#include <Wire.h>

/******* SHARED DEFINATION  ******/
#define MasterAddress   9 
#define ControlAddress  10  

#define INITIAL_MODE_SELECT     44 
#define IMAGING_MODE_SELECT     55 
#define DOWNLOAD_MODE_SELECT    66 
#define FALL_MODE_SELECT        77



/*** Application Based Defination ***/

#define sendData  6 
#define GetData   7 

/********Application Based  Defination ********/

#define InitialModeLed   4 
#define ImagingModeLed   5
#define DownLoadModeLed  6
#define FallModeLed      7 
#define MotorPin         8 
#define LaserBeamPin     9  



/* GLOBAL DATA */

int SLAVE_SEND_DATA = 0 ; 
int SLAVE_Recived_DATA = 0 ; 
int Mode =  0 ; 
byte StateFlag = GetData ; 

/****** Application  FUNCTION Decleartions *********/
void CONTROL_IntialMode( )  ; 
void CONTROL_ImagingMode( ) ; 
void CONTROL_DownloadnMode( ) ; 
void CONTROL_FinishTask( )  ; 
void FaluairMode () ;  


/***********Drivers Based Function **************/
void requestEvent() ; 
void SlaveWrite(int data )  ; 
int SlaveRead()  ; 



 
void setup() {
  // put your setup code here, to run once:
 
}

void loop() {
  // put your main code here, to run repeatedly:

Mode = SlaveRead() ; 

switch (Mode ) 
{
   case INITIAL_MODE_SELECT : 
        CONTROL_IntialMode( )  ;
   break ;
   
   case IMAGING_MODE_SELECT : 
        CONTROL_ImagingMode( ) ; 
   break ;
   
   case DOWNLOAD_MODE_SELECT : 
        CONTROL_DownloadnMode( ) ; 
        CONTROL_FinishTask( )  ;
   break ;  

   case FALL_MODE_SELECT :  
        FaluairMode () ; 
   break ;
} 
} 







/******** FUNCTION DEFINATION********/


void CONTROL_IntialMode( ) 
{ 
  Wire.begin(ControlAddress);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  /* inital all needded pins*/
  pinMode( InitialModeLed ,OUTPUT ) ; 
  pinMode( ImagingModeLed ,OUTPUT ) ; 
  pinMode( DownLoadModeLed ,OUTPUT) ;
  pinMode (MotorPin , OUTPUT) ; 
  pinMode(LaserBeamPin,OUTPUT) ; 

  /*initial Mode indicator*/
  digitalWrite(InitialModeLed , HIGH) ; 
  
} 

/*=======================================================*/

void CONTROL_ImagingMode( )
{

/*control the motor move */
 digitalWrite(MotorPin , HIGH) ;
 delay(4000) ; 
 digitalWrite(MotorPin , LOW) ;  

/*turn on the laser beam */
 digitalWrite(LaserBeamPin , HIGH) ;
 delay(4000) ; 
 digitalWrite(LaserBeamPin , LOW) ;  

 /*imaging Mode indicator*/
  digitalWrite(ImagingModeLed , HIGH) ;


  
} 


/*=======================================================*/

void CONTROL_DownloadnMode( )
{



SlaveWrite( 78 )  ; 


/*Download Mode Indicator */
digitalWrite(ImagingModeLed , HIGH) ;

}

void CONTROL_FinishTask( ) 
{
  for (int inc = 0 ; inc <4 ; inc++) 
  {
  digitalWrite( InitialModeLed ,HIGH ) ; 
  digitalWrite( ImagingModeLed ,HIGH ) ; 
  digitalWrite( DownLoadModeLed ,HIGH) ;
delay(2000) ; 
  digitalWrite( InitialModeLed ,LOW ) ; 
  digitalWrite( ImagingModeLed ,LOW ) ; 
  digitalWrite( DownLoadModeLed ,LOW) ;
 
}



} 



/*=======================================================*/

void FaluairMode ()  
{
    for (int inc = 0 ; inc <4 ; inc++) 
  {
  digitalWrite( FallModeLed ,HIGH ) ; 
  
delay(2000) ; 
  digitalWrite( FallModeLed ,LOW ) ; 
  
 
}
}


/*=======================================================*/





/**********Function Based ON Drivers  ************/

void requestEvent() {

/*this funtion iw will change it state depending on the 
state flag value fron send to get data */ 

if (StateFlag == sendData ) 
{ 
  Wire.write(SLAVE_SEND_DATA ) ;   
} 
else if (StateFlag == GetData ) 
{
  SLAVE_Recived_DATA = Wire.read();    // receive byte as an integer
}
 delay(100);
    
}


/*=======================================================*/
void SlaveWrite(int data ) 
{ 
  StateFlag = sendData ; 
  SLAVE_SEND_DATA = data ; 
  delay (400)  ;  
} 


/*=======================================================*/
int SlaveRead() 
{ 
  StateFlag = GetData ; 
  delay (400) ; 
  return SLAVE_Recived_DATA ; 
}  
