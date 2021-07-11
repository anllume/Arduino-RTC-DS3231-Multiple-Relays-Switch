//  Edited/Written by: Ainolnaim Azizol (2021) for a sound installation project.
//  Download the latest Wire and RTC library via Arduino IDE or Git Hub (Zip file). 
//  Add the downloaded library files in Arduino Library folder directory on your PC.


#include <Wire.h>            //  upload Wire library for I2C communication protocol A4 & A5 i/o for Arduino Nano/UNO
#include <RTC.h>             //  upload RTC library by Manjunath CV et al., GitHub 2021. 
  
static DS3231 RTC;           //  activate 'all the time' our DS3231 RTC variables

const int S1 = 3;            //  store read-only variables to Ardunio Nano analog output number 3, 4 and 5 as S1, S2, S3. 
const int S2 = 4;
const int S3 = 5;



void setup()
{
 
  Serial.begin(9600);
  RTC.begin();
  
  RTC.setHourMode(CLOCK_H24);           //  use 24h clock for straightforward numbering data assign and recall (00-23)  
  /*RTC.setHourMode(CLOCK_H12);
    if (RTC.getHourMode() == CLOCK_H12)
    {
    RTC.setMeridiem(HOUR_PM);
     }*/

  RTC.setDateTime(__DATE__, __TIME__);  //  assign time setting automatically the same as your PC clock time during 
                                        //  sketch upload.
  /*RTC.setDay(10);                     //  you can assign manually here for each time calendar parameter for different 
  RTC.setMonth(7);                      //  Time Zone.
  RTC.setYear(2021);

  RTC.setHours(23);
  RTC.setMinutes(19);
  RTC.setSeconds(00);

  RTC.setWeek(1);

  //RTC.setDate(10,07,21);              // not so accurate (it becomes 10-07-1921), so skip.
  //RTC.setTime(23,24,00);*/

  pinMode(S1, OUTPUT);                  // setup arduino Nano outputs assigned as S1, S2 and S3.
  digitalWrite(S1, LOW);
  pinMode(S2, OUTPUT);
  digitalWrite(S2, LOW);
  pinMode(S3, OUTPUT);
  digitalWrite(S3, LOW);

}



void loop()                    // assign loop tasks which are timeCalendar task, TimeGroupA or any additional set TimeGroups
{
  timeCalendar();             // we will assign specific task command (including conditions) 
  TimeGroupA();               // in each void as follows.              
}


void timeCalendar()            // assign timeCalendar task for Serial print data (recall serial print data to 
                               // activate task SetA, think/imagine alarm set switcher)
{
  switch (RTC.getWeek())
  {
    case 1:
      Serial.print("SAT");    // set today's day! as initial RTC date Serial monitor print display, 
      break;                  // then followed by other days of the week. eg. if today's day is Monday, 
    case 2:                   // put ("MON") in case 1 and then replace other cases 2-7 with ("SAT"),("SUN") etc.
      Serial.print("SUN");
      break;
    case 3:
      Serial.print("MON");
      break;
    case 4:
      Serial.print("TUE");
      break;
    case 5:
      Serial.print("WED");
      break;
    case 6:
      Serial.print("THU");
      break;
    case 7:
      Serial.print("FRI");
      break;
  }
  Serial.print(" ");          // assign serial print monitor to display RTC data set 
  Serial.print(RTC.getDay()); // individually: day, month, year etc (as opposed to RTC.now data format)
  Serial.print("-");          // with this data we can recall it to set trigger the HIGH and LOW command in each void tasks.
  Serial.print(RTC.getMonth());
  Serial.print("-");
  Serial.print(RTC.getYear());

  Serial.print(" ");
  Serial.print(RTC.getHours());
  Serial.print(":");
  Serial.print(RTC.getMinutes());
  Serial.print(":");
  Serial.print(RTC.getSeconds());
  //Serial.print(" ");
  Serial.println();
  delay(1000);
  /* if (RTC.getHourMode() == CLOCK_H12)
  {
    if(RTC.getMeridiem() == HOUR_AM)
      Serial.println(" AM");
    if (RTC.getMeridiem() == HOUR_PM)
      Serial.println(" PM");     
  }*/
}
  
 

void TimeGroupA()                // assign the TimeGroupA task structure to trigger void SwitchPattern sets  
{                                
 if (RTC.getHours() == 12 &&              // 'if' argument for data matching/ compare ('=='): recall from 
     RTC.getMinutes() == 13 &&            // void timeCalendar data and compare with assigned time set hours, minutes etc.
     RTC.getSeconds() == 10)              // to trigger following commands (SwichPattern1) if (x == y) matched (true).
     {
      SwitchPattern1();     
     }
 else if (RTC.getHours() == 12 &&         // we set different time to trigger assigned void SwitchPattern. 
          RTC.getMinutes() == 13 &&       // at minute 26 and 27 will be compared.   
          RTC.getSeconds() == 15) 
         {
          SwitchPattern1();
          SwitchPattern2();
         }
}

void SwitchPattern1()           // assign pinMode S1-3 ouput task
{                                                     
  digitalWrite(S1, HIGH);       //will be looped here but it will not triggered as assigned void TimeGroupA conditions
  Serial.println("A_S1 ON 0");
  delay(500);
  digitalWrite(S1, LOW);
  delay(500);

  digitalWrite(S2, HIGH);
  Serial.println("A_S2 ON 1"); 
  delay(500);
  digitalWrite(S2, LOW);
  delay(500);

  digitalWrite(S3, HIGH);
  Serial.println("A_S3 ON 2");
  delay(500);
  digitalWrite(S3, LOW);
  delay(500);   
}

void SwitchPattern2()            
{
  digitalWrite(S2, HIGH);
  Serial.println("B_S2 ON 0");
  delay(500);
  digitalWrite(S2, LOW);
  delay(500);  

  digitalWrite(S1, HIGH);
  Serial.println("B_S1 ON 1"); 
  delay(500);
  digitalWrite(S1, LOW);
  delay(500);  

  digitalWrite(S1, HIGH);
  Serial.println("B_S2 ON 2");
  delay(500);
  digitalWrite(S1, LOW);
  delay(500);  
} 
