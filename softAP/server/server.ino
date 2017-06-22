
#include<ESP8266WiFi.h>
WiFiServer server(8085);
  WiFiClient client1;

void setup() {
  // put your setup code here, to run once:  
  
  Serial.begin(115200);
  WiFi.begin("freewifi","987654321");
  WiFi.softAP("test","abc123456");
  delay(5000);
  //softA
  
  while(WiFi.status()!= WL_CONNECTED)
  {
    Serial.println(WiFi.status());
    delay(500);
  }
  Serial.println("Connected: ");
  Serial.println(WiFi.localIP());  
  server.begin();
  while(!server.available())
  {
    Serial.println(server.available());
    delay(500);
  }
  
  // put your main code here, to run repeatedly:
  
  //Serial.println(client1);
  //delay(500);
        
 
   //client1.stop();    
}
void loop() {
  
  client1=server.available();
  
  if(client1)
  {
    while(client1.connected())
    {
      if(client1.available())
        {
          Serial.println(client1.read());
          Serial.println("Client Avaibale");
          server.write("Winter is coming!!");
        }
      
    }
  }
  
}
