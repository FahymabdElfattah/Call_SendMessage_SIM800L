#include <SoftwareSerial.h>

 
//______________________________________________________________________________________________
  //Create software serial object to communicate with SIM800L                                   |
  //SIM800L Tx & Rx is connected to Arduino #2 & #3                                             |
  SoftwareSerial SIM900A(2,3);  //                                                              |
//______________________________________________________________________________________________|

void setup(){
//______________________________________________________________________________________________
  // GSM Module Baud rate - communication speed                                                 |
  SIM900A.begin(9600);  //                                                                      |
//______________________________________________________________________________________________|
  Serial.begin(9600);    // Baud rate of Serial Monitor in the IDE app

  Serial.println ("Initializing...");
  delay(100);
  Serial.println ("Type <s> to send message or <r> to receive message");
}


void loop(){
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage("Hello Fahym");
      break;
    case 'r':
      RecieveMessage();
      break;
  }

 if (SIM900A.available()>0)
   Serial.write(SIM900A.read());
}


 void SendMessage( const char *data){
  Serial.println ("Sending Message please wait....");
//______________________________________________________________________________________________
  // The AT+CMGF command sets the GSM modem in SMS Text Mode => 1 or SMS PDU Mode => 0.         |
  /*In Text Mode, SMS messages are represented as readable text. In PDU Mode,                   |
    all SMS messages are represented as binary strings encoded in hexadecimal characters like   | 
    31020B911326880736F40000A900.*///                                                           |
   SIM900A.println("AT+CMGF=1"); // Preferred Message Format                                    |                                       
//______________________________________________________________________________________________|
  delay(1000);
  Serial.println ("Set SMS Number");
//______________________________________________________________________________________________
  //Preparation of GSM modem to send a message to GSM number +91XXXXXXXXXX.                     |
   SIM900A.println("AT+CMGS=\"+91XXXXXXXXXX\"\r"); // Send message                              |
//______________________________________________________________________________________________|
  delay(1000);
  Serial.println ("Set SMS Content");
//______________________________________________________________________________________________
  //The message contents .                                                                      |
  SIM900A.println(data); //                                                                     |
//______________________________________________________________________________________________|
  delay(100);
  Serial.println ("Done");
//______________________________________________________________________________________________
  // The (char)26 is ASCII code of CTRL+Z It's equivalent to Send Button                        |
  SIM900A.println((char)26);//                                                                  |
//______________________________________________________________________________________________|
  Serial.println ("Message sent succesfully"); 
}


 void RecieveMessage(){
  Serial.println ("Receiving Messeges");
  delay (1000);
//____________________________________________________________________________________________
  //+CNMI: <mode>,<mt>,<bm>,<ds>,<bfr>                                                        |
  //The AT command +CNMI is used to specify how newly arrived SMS messages should be handled. |                                                     |
  SIM900A.println("AT+CNMI=2,2,0,0,0"); // New message indication                             |
//____________________________________________________________________________________________|
  delay(1000);
  Serial.write ("Messege Received Sucessfully");
 }