    
//__________________ pumps initialization __________________
  const int pumpPin1 = 3;  //pin numbers
  const int pumpPin2 = 5; 
  const int pumpPin3 = 7; 
  
  //bool flagPump1 = true;  were true in last working version
  //bool flagPump2 = true;
  //bool flagPump3 = true;
  bool flagPump1 = true; 
  bool flagPump2 = true;
  bool flagPump3 = true;
  
  //"unsigned long" for variables that hold time
  unsigned long previousMillisPump1 = 0;    // will store last time pump1 was updated
  unsigned long previousMillisPump2 = 0;    // will store last time pump2 was updated
  unsigned long previousMillisPump3 = 0;    // will store last time pump3 was updated
  
  int pumpState1 = LOW; 
  int pumpState2 = LOW;
  int pumpState3 = LOW;

  unsigned long currentMillisPump1 = 0;
  unsigned long currentMillisPump2 = 0;
  unsigned long currentMillisPump3 = 0;
//__________________END OF pumps initialization __________________

//__________________ fans initialization __________________
  const int fansPin = 9;
  unsigned long previousMillisFans = 0;
  unsigned long currentMillisFans = 0;
  unsigned long previousMillisFansManual = 0;
  unsigned long currentMillisFansManual = 0;
  int fansState = LOW;
  bool flagFans = false;
//__________________ END OF fans initialization _________________

//__________________ soil moisture sensors initialization __________________
  const int hygrometer1 = A0;
  const int hygrometer2 = A1;
  const int hygrometer3 = A2;
  int hygrometerValue1;
  int hygrometerValue2;
  int hygrometerValue3;

  unsigned long previousMillisHygroRead1 = 0;
  unsigned long previousMillisHygroRead2 = 0;
  unsigned long previousMillisHygroRead3 = 0;
//__________________ END OF soil moisture sensors initialization __________________

//__________________ stepper motor initialization __________________
  #include <Stepper.h>
  const int stepsPerRevolution = 200;  // number of steps per revolution
  Stepper myStepper(stepsPerRevolution, 10, 11, 12, 13);
  bool flagStepper = true;
//__________________ END OF stepper motor initialization __________________

//__________________ temperature sensor initialization __________________
  int temperatureSensorPin = A3;
  unsigned long previousMillisTemperature = 0;    // will store last time temperature was read
  int Vo;
  float R1 = 10000;
  float logR2, R2, T, Tcelsius, Tfahrenheit;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
//__________________ END OF temperature sensor initialization __________________

//__________________ luminosity sensor initialization __________________
  int photocellPin = A4;     // the cell and 10K pulldown are connected to a5
  int photocellReading;     // the analog reading from the sensor divider
//__________________ END OF luminosity sensor initialization __________________

//__________________ ESP8266 wifi module initialization __________________
  #include "SoftwareSerial.h"
  SoftwareSerial ESP8266(4, 2);// RX, TX
  
  String server = "cgesmartgarden.azurewebsites.net"; 
  
  unsigned long previousMillisReq2 = 0;
  unsigned long previousMillisReq3 = 0;
  unsigned long previousMillisReq4 = 0;
  unsigned long previousMillisReq5 = 0;
  unsigned long previousMillisReq6 = 0;
  unsigned long previousMillisReq7 = 0;
  unsigned long previousMillisReq8 = 0;
  unsigned long previousMillisReq9 = 0;
  unsigned long previousMillisReq10 = 0;

//__________________ END OF ESP8266 wifi module initialization __________________

//__________________ general usage pins and variables __________________
  unsigned long previousMillis = 0;
  bool manualStartFansState = false;
  bool manualStartAirVentState = false;
  bool manualStartHygrosState = false;
  int steps = 0; //steps used by stepper
//__________________ END OF general usage pins and variables __________________


//__________________ general limits & intervals initialization __________________
  const long pumpInterval = 5000;      // interval for pump cycle (milliseconds)
  int humidityLowLevel = 40;           // the level of humidity below which the pumps start
  float temperatureHighLevel = 30.00;  // the level of temperature above which the fans start
  const long stepperMaintainInterval = 300000; // interval for air vent cycle (milliseconds)
  const long fansInterval = 30000;     // interval for fans cycle (milliseconds)
//__________________ END OF general limits & intervals initialization __________________

bool checker = true;
  
void setup() {
  // set the digital pin as output:
  pinMode(pumpPin1, OUTPUT);
  pinMode(pumpPin2, OUTPUT);
  pinMode(pumpPin3, OUTPUT);
  pinMode(fansPin, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
  myStepper.setSpeed(150);
  
  ESP8266.begin(115200); 
  Serial.begin(115200);

  
  Serial.println("Start");
  reset();
  ESP8266.println("AT+CWMODE=1");
  delay("1000");
  ESP8266.println("AT+CIPMUX=1");
  delay("1000");
  
  connectWifi();
  
}
                                        
void loop() {

  
  //esp8266 wifi module controller
  unsigned long currentMillisReq10 = millis();
   if (currentMillisReq10 - previousMillisReq10 >= 7000) {              //it takes at least 7 seconds to acces the link and get the response, otherwise calls overwrite and malfunction
     // save the last time req was read
     previousMillisReq10 = currentMillisReq10;       
     
     //timed code executes below
       Serial.println("loops..");
        String cmd;
        cmd = "AT+CIPSTART=1,\"TCP\",\"";
        unsigned long currentMillisReq2 = millis();
         if (currentMillisReq2 - previousMillisReq2 >= 100) {
           // save the last time req was read
           previousMillisReq2 = currentMillisReq2;       
           
           //timed code executes below
           cmd += server;
        }
        unsigned long currentMillisReq3 = millis();
         if (currentMillisReq3 - previousMillisReq3 >= 100) {
           // save the last time req was read
           previousMillisReq3 = currentMillisReq3;       
           
           //timed code executes below
          cmd += "\",80";
        }
          unsigned long currentMillisReq4 = millis();
         if (currentMillisReq4 - previousMillisReq4 >= 100) {
           // save the last time req was read
           previousMillisReq4 = currentMillisReq4;       
           
           //timed code executes below
          ESP8266.println(cmd);
        }
            unsigned long currentMillisReq5 = millis();
         if (currentMillisReq5 - previousMillisReq5 >= 100) {
           // save the last time req was read
           previousMillisReq5 = currentMillisReq5;       
           
           //timed code executes below
          if(ESP8266.find("OK")) 
          {
          Serial.println("Connected to the web!");
          }
        }
        
        
        
        //int temperature = 34;
        float temperatureVal = Tcelsius;
        int luminosity = photocellReading;
        int soilMoisture1 = hygrometerValue1;
        int soilMoisture2 = hygrometerValue2;
        int soilMoisture3 = hygrometerValue3;
        
        cmd =  "GET /Api/add?temperature=" + (String)temperatureVal + "&luminosity=" + (String)luminosity + "&soilMoisture1=" + (String)soilMoisture1 +"&soilMoisture2=" + (String)soilMoisture2 +"&soilMoisture3=" + (String)soilMoisture3 +" HTTP/1.1\r\n";  
        unsigned long currentMillisReq6 = millis();
         if (currentMillisReq6 - previousMillisReq6 >= 500) {
           // save the last time req was read
           previousMillisReq6 = currentMillisReq6;       
           
           //timed code executes below
          cmd += "Host: www.example-website.com\r\n\r\n"; 
        }
        
        unsigned long currentMillisReq7 = millis();
         if (currentMillisReq7 - previousMillisReq7 >= 500) {
           // save the last time req was read
           previousMillisReq7 = currentMillisReq7;       
           
           //timed code executes below
          ESP8266.print("AT+CIPSEND=1,");
        } 
        unsigned long currentMillisReq8 = millis();
         if (currentMillisReq8 - previousMillisReq8 >= 1000) {
           // save the last time req was read
           previousMillisReq8 = currentMillisReq8;       
           
           //timed code executes below
          ESP8266.println(cmd.length());
        } 
        unsigned long currentMillisReq9 = millis();
         if (currentMillisReq9 - previousMillisReq9 >= 1000) {
           // save the last time req was read
           previousMillisReq9 = currentMillisReq9;       
           
           //timed code executes below
            if(ESP8266.find(">")) 
            {
              Serial.println(">");
            }
        
            ESP8266.println(cmd);
            
        } 

    if(ESP8266.find("OK")) 
    {
      Serial.println("sent!");
    }
    
    
  } // end of 9 seconds loop

  //check if systems manually started
      if(ESP8266.find("sfx")){
        Serial.println("FANS STARTED");
        manualStartFansState = true;
      }
      if(ESP8266.find("shx")){
        Serial.println("HYGROS STARTED");
        manualStartHygrosState = true;
      }
      if(ESP8266.find("ovx")){
        Serial.println("AIR VENT OPENNED");
        manualStartAirVentState = true;
      }
    // ^^^ check if systems manually started
  
//END OF: esp8266 wifi module controller
  

  
  //Hygro1 data read
  unsigned long currentMillisHygroRead1 = millis();
  if (currentMillisHygroRead1 - previousMillisHygroRead1 >= 1000) {
     // save the last time hygros were read
     previousMillisHygroRead1 = currentMillisHygroRead1;       

       //hygrometer 1 READ
    hygrometerValue1 = analogRead(hygrometer1);    //Read analog value 
    hygrometerValue1 = constrain(hygrometerValue1,400,1023);  //Keep the ranges!
    hygrometerValue1 = map(hygrometerValue1,400,1023,100,0);  //Map value : 400 will be 100 and 1023 will be 0
  }
  //END OF: Hygro1 data read

  //Hygro2 data read
  unsigned long currentMillisHygroRead2 = millis();
  if (currentMillisHygroRead2 - previousMillisHygroRead2 >= 1000) {
      // save the last time hygros were read
     previousMillisHygroRead2 = currentMillisHygroRead2;   
    
    //hygrometer 2 READ
    hygrometerValue2 = analogRead(hygrometer2);    //Read analog value 
    hygrometerValue2 = constrain(hygrometerValue2,400,1023);  //Keep the ranges!
    hygrometerValue2 = map(hygrometerValue2,400,1023,100,0);  //Map value : 400 will be 100 and 1023 will be 0
  }
  //END OF: Hygro2 data read

  //Hygro3 data read
  unsigned long currentMillisHygroRead3 = millis();
  if (currentMillisHygroRead3 - previousMillisHygroRead3 >= 1000) {
     // save the last time hygros were read
     previousMillisHygroRead3 = currentMillisHygroRead3;       

      //hygrometer 3 READ
    hygrometerValue3 = analogRead(hygrometer3);    //Read analog value 
    hygrometerValue3 = constrain(hygrometerValue3,400,1023);  //Keep the ranges!
    hygrometerValue3 = map(hygrometerValue3,400,1023,100,0);  //Map value : 400 will be 100 and 1023 will be 0      
  }
  //END OF: Hygro3 data read
  
  
  
  //Display higro's values
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > 1000) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
 
  Serial.print("hygro1: ");
    Serial.print(hygrometerValue1);
    Serial.print("%");
    Serial.print("     ");
    Serial.print("hygro2: ");
    Serial.print(hygrometerValue2);
    Serial.println("%");
    Serial.print("     ");
    Serial.print("hygro3: ");
    Serial.print(hygrometerValue3);
    Serial.println("%");
 
  }
  //END OF: Display higro's values
  




            
  //pump1 start
  if(hygrometerValue1 <= humidityLowLevel && flagPump1==false){
    digitalWrite(pumpPin1, HIGH);
    flagPump1 = true;
  }
  unsigned long currentMillisPump1 = millis();
  if(currentMillisPump1 - previousMillisPump1 >= pumpInterval){
      // save the last time pump was on
          previousMillisPump1 = currentMillisPump1;

          digitalWrite(pumpPin1, LOW);
          flagPump1 = false;
  }  
  //END OF: pump1 start

  //pump2 start
  if(hygrometerValue2 <= humidityLowLevel && flagPump2==false){
    digitalWrite(pumpPin2, HIGH);
    flagPump2 = true;
  }
  unsigned long currentMillisPump2 = millis();
  if(currentMillisPump2 - previousMillisPump2 >= pumpInterval){
      // save the last time pump was on
          previousMillisPump2 = currentMillisPump2;

          digitalWrite(pumpPin2, LOW);
          flagPump2 = false;
  } 
  //END OF: pump2 start

  //pump3 start
  if(hygrometerValue3 <= humidityLowLevel && flagPump3==false){
    digitalWrite(pumpPin3, HIGH);
    flagPump3 = true;
  }
  unsigned long currentMillisPump3 = millis();
  if(currentMillisPump3 - previousMillisPump3 >= pumpInterval){
      // save the last time pump was on
          previousMillisPump3 = currentMillisPump3;

          digitalWrite(pumpPin3, LOW);
          flagPump3 = false;
  } 
  //END OF: pump3 start
  



  
    
    
  
    /*
    //stepper controller
    steps = -10000;
    myStepper.step(steps);
    delay(500);

    steps = 10000;
    myStepper.step(steps);
    delay(500); //Semicolon added
    //END OF: stepper controller
    */




    
  
  // temperature sensor controller
  Vo = analogRead(temperatureSensorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tcelsius = T - 273.15;
  //Tfahrenheit = (Tcelsius * 9.0)/ 5.0 + 32.0; 
  
  
  unsigned long currentMillisTemperature = millis();
  if(currentMillisTemperature - previousMillisTemperature > 1000) {
    // save the last time you blinked the LED 
    previousMillisTemperature = currentMillisTemperature;   
  //display temp on serial
  Serial.print("Temperature: ");
  Serial.print(Tcelsius);
  Serial.println(" C");
  }
  //END OF: temperature sensor controller    
  

  /*
  //fans - controller 
    unsigned long currentMillisFans = millis();
      
      if (currentMillisFans - previousMillisFans >= 8000) {
          // save the last time pump was on
          previousMillisFans = currentMillisFans;
      
            if(fansState == LOW){
        fansState = HIGH;
            }else{
              fansState = LOW;
            }
            
          digitalWrite(fansPin, fansState);
      }
    //END OF: fans - controller 
    */


    //fans controller
    if(Tcelsius >= temperatureHighLevel && flagFans==false){
        
        
        
        //steps = -10000;
        //myStepper.step(steps);

        
      
        digitalWrite(fansPin, HIGH);
        flagFans = true;
        flagStepper = true;
    }
  unsigned long currentMillisFans = millis();  //cuz stepper blocks thread
  if(currentMillisFans - previousMillisFans >= fansInterval){
      // save the last time pump was on
      previousMillisFans = currentMillisFans;
      digitalWrite(fansPin, LOW);
      flagFans = false;  
      

  }  

  if(flagStepper == false){
         //steps = 10000;
         //myStepper.step(steps);
         flagStepper = false;
      }
  
  //END OF: fans controller



  
  //luminosity sensor read
  photocellReading = analogRead(photocellPin); // read the value from the sensor
  
  
 /*
  Serial.print("Luminosity: ");
  Serial.println(photocellReading);
  delay(1000); 
  */
  //END OF: luminosity sensor read





//manual systems commands controller 

  //fans
  if(manualStartFansState == true){
      digitalWrite(fansPin, HIGH);
      flagFans = true;
  }
  currentMillisFansManual = millis();
  if(currentMillisFansManual - previousMillisFansManual >= fansInterval){
          // save the last time pump was on
              previousMillisFansManual = currentMillisFansManual;
              
              digitalWrite(fansPin, LOW);
              flagFans = false;
              manualStartFansState = false;
      }     
  //END OF fans
  
  if(manualStartAirVentState){


    manualStartAirVentState = false;
  }
  
  if(manualStartHygrosState){


    manualStartHygrosState = false;
  }

//END OF manual systems commands controller
  
} // end of loop

void connectWifi() 
{

  String cmd = "AT+CWJAP=\"yourSSID\",\"yourSSIDpassword\"";
  ESP8266.println(cmd);
  delay(4000);
  
  if(ESP8266.find("OK")) 
  {
    Serial.println("Connected!");
  }else{
    Serial.println("Could not connect to wifi. Retrying..."); 
    connectWifi();
  }
}

void reset()
{
  
  ESP8266.println("AT+RST");
  delay(1000);
  if(ESP8266.find("OK")) Serial.println("Module Reset");
}














