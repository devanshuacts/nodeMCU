#include<ESP8266WiFi.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin("ACTS-CR006-AP4","abcdefghi",true);
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.isConnected())
  {
  Serial.println(WiFi.localIP());
}

}
