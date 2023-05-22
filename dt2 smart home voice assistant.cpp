#include <UbidotsESPMQTT.h>

#define RELAY 25

#define TOKEN "BBFF-MYmH7HuZvdmMZhBjd8EUYFfOBNcez2"   // Your Ubidots TOKEN

#define WIFISSID "Joker" // Your SSID

#define WIFIPASS "Joker@tenda" // Your Wifi Pass

Ubidots client(TOKEN);

void callback(char* topic, byte* payload, unsigned int length) {

 Serial.print("Message arrived [");

 Serial.print(topic);

 Serial.print("] ");

 for (int i = 0; i < length; i++) {

  Serial.print((char)payload[i]);

 }

 Serial.println();

 Serial.print("Command: ");

 bool command = *payload - 48;

 Serial.println(command);

 digitalWrite(RELAY, !command);

}

void setup() {

 Serial.begin(9600);

 Serial.println("Init... T4_Smart_Home");

 pinMode(RELAY, OUTPUT);

 Serial.print("Connecting to SSID: ");

 Serial.print(WIFISSID);

 Serial.print(", Password: ");

 Serial.println(WIFIPASS);

 client.wifiConnection(WIFISSID, WIFIPASS);

 Serial.println("Done");

 Serial.println(" Initializing Ubidots Connection...");

 client.ubidotsSetBroker("industrial.api.ubidots.com"); // Sets the broker properly for the business account

 client.setDebug(true);            // Pass a true or false bool value to activate debug messages

 client.begin(callback);

 client.ubidotsSubscribe("smart-home-voice-assistant","bulb"); //Insert the Device and Variable's Labels

 Serial.println("Done");

 Serial.println("DONE");

}

void loop() {

   // Establising connection with Ubidots

 if (!client.connected()) {

  client.reconnect();

  client.ubidotsSubscribe("smart-home-voice-assistant","bulb"); //Insert the Device and Variable's Labels }

 client.loop();

 delay(1000);

}

