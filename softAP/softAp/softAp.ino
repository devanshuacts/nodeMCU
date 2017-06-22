
#include<ESP8266WiFi.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.softAP("test","abc123456");//password should be minmum8 characters
  int count=0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.softAPgetStationNum()>0)
  {
    Serial.println(WiFi.softAPgetStationNum());
  }
}
