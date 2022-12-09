#include <SoftwareSerial.h>

//______________________________________________________________________________________________
  //Create software serial object to communicate with SIM800L                                   |
  //SIM800L Tx & Rx is connected to Arduino #3 & #2                                             |
 SoftwareSerial mySerial(3, 2);  //                                                             |
//______________________________________________________________________________________________|

void setup(){
//______________________________________________________________________________________________
  //GSM Module Baud rate - communication speed                                                  |
  mySerial.begin(9600);  //                                                                     |
//______________________________________________________________________________________________|
  Serial.begin(9600); //Begin serial communication with Arduino and SIM800L
  Serial.println("Initializing..."); 
  delay(1000);
//______________________________________________________________________________________________
  //Test GSM Module if is successful,it will back to OK                                         |
  mySerial.println("AT"); //                                                                    |
  updateSerial();//                                                                             |
//______________________________________________________________________________________________|
//______________________________________________________________________________________________
  //change ZZ with country code and xxxxxxxxxxx with phone number to dial                       |
  // For exempel in Morocco +212xxxxxxxxxx                                                      |
 mySerial.println("ATD+ +ZZxxxxxxxxxx;"); //                                                    |
  updateSerial();//                                                                             |
//______________________________________________________________________________________________|
  delay(20000); // wait for 20 seconds...
//______________________________________________________________________________________________
  //hangs up the call. This command is used to end the voice call.                              |
  mySerial.println("ATH"); //                                                                   |
  updateSerial();//                                                                             |
//______________________________________________________________________________________________|
}

void loop(){
}

void updateSerial(){
  delay(500);
  while (Serial.available()) { 
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}