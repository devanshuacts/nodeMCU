#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"//is generic for api of adafruit MQTT
#include "Adafruit_MQTT_Client.h"//Specific to board

WiFiClient client1;

Adafruit_MQTT_Client mqtt(&client1,"io.adafruit.com",1883,"kgm12345","7d962435198d4a65b7261ea233a53b27");

Adafruit_MQTT_Publish pub = Adafruit_MQTT_Publish(&mqtt,"kgm12345/feeds/status");

Adafruit_MQTT_Subscribe switch1 = Adafruit_MQTT_Subscribe(&mqtt,"kgm12345/feeds/switch");


void setup()
{

  pinMode(LED_BUILTIN, OUTPUT);
  
  /*  each GPIO pins can be configured as output or input...  
    here we are using above provided pin as output  */
          


  Serial.begin(115200);
  delay(10);

  /* setting baudrate 115200 for serial monitor connection */



  //Serial.print("SSID : ");
  //Serial.println("TP-LINK_631A");


  WiFi.begin("pass","123456789");      //enter your wifi details

  /* all transport layer details like ssid and password here to connect to internet!   */



  while(WiFi.status() != WL_CONNECTED)  //on successful connection WL_CONNECTED is status return value
  {
    delay(500);     //if not connected we stay in this loop with delay
            // or else, eventually sw watchdog reset may occur
    Serial.print(" :)");
  }

  Serial.println("Wifi connected.....");

  mqtt.subscribe(&switch1);    // this subscription detail should be given before attempt to connect
            // thanks to Kaushal we came to know about this yesterday with proof
          
  /* if subscribing to more feeds add lines accordingly

    eg. mqtt.subscribe(&sub1);
        mqtt.subscribe(&sub2); ...so on */

  
}

void loop()
{
  int i;

  while((i=mqtt.connect()) != 0)
  {
    Serial.println("retrying..");
    mqtt.disconnect();
    delay(4000);
  }

  Serial.println("Connected to MQTT broker..");

  Adafruit_MQTT_Subscribe *s;

  while((s = mqtt.readSubscription(500)))
  {
    if(s == &switch1)
    {
      if(strcmp((char *)switch1.lastread,"ON")==0)
      {
        pub.publish("LED ON");
        digitalWrite(LED_BUILTIN, HIGH);  // try it out!
        Serial.println("ON");
      }
  
      else if(strcmp((char *)switch1.lastread,"OFF")==0)
      {
        pub.publish("LED OFF");
        digitalWrite(LED_BUILTIN,LOW);  // try it out!
        Serial.println("OFF");
      }       
    } 
  }
}



