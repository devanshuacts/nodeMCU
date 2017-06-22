

#include <ESP8266WiFi.h> 

/* Set these to your desired credentials. */
const char *ssid = "hello";
const char *password = "helloqwerty"; 
WiFiClient client;
IPAddress server(192,168,43,187);

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println(WiFi.localIP());
  client.setNoDelay(true);
  client.connect(server,80);
}

void loop() {
    delay(200);
    client.write("pinky biswas");
    Serial.println(client.readStringUntil('\r'));
    //client.flush();

}
