/*
Version   : 1.0
Project   : Home Automation
Developer : Nurman Hariyanto & fahmi 
Date      : 01/11/2019
*/


///////////////////////////////////////////////////////////////////////////////////////////
//Library
//#include <Arduino.h>
#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <Ticker.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>          //json library
#include <PubSubClient.h>         //publish & subscribe library


#include <config.h>
/////////////////////////////////////////////////////////////////////////////////////////////



void (setup){

 //ResetSettings();
  
  int in1 = 1;
  int in2 = 2;
  int in3 = 3;
  int in4 = 4;
  int in5 = 5;
  int in6 = 6;
  int in7 = 7;
  int in8 = 8;

  char stateDevice[] = {stateDevice1,stateDevice2,stateDevice3,stateDevice4,stateDevice5,stateDevice6,stateDevice7,stateDevice8};
 
  Serial.begin(115200);
  Serial.println(F("Booting...."));  
  
  //ReadConfigFile(); // Read Config File if it is exist
  setup_wifi();
  //SaveConfigFile();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback); 
}


void setup_wifi() {
 WiFi.macAddress(MAC_array);
 for (int i = 0; i < sizeof(MAC_array)-1; ++i){
      sprintf(MAC_char,"%s%02x:",MAC_char,MAC_array[i]);
    } 
    sprintf(MAC_char,"%s%02x",MAC_char,MAC_array[sizeof(MAC_array)-1]);

  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
  String(mqtt_port).toCharArray(smqtt_port,5); 
  WiFiManagerParameter custom_mqtt_port("port", "mqtt port", smqtt_port, 5);
  WiFiManagerParameter custom_mqtt_user("user", "mqtt user", mqtt_user, 40);
  WiFiManagerParameter custom_mqtt_password("password", "mqtt password", mqtt_password, 40);
  WiFiManagerParameter custom_mqtt_keywords1("keyword1", "mqtt keyword1", mqtt_keywords1, 40);
  WiFiManagerParameter custom_mqtt_keywords2("keyword2", "mqtt keyword2", mqtt_keywords2, 40);

  WiFiManager wifiManager;
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_mqtt_user);
  wifiManager.addParameter(&custom_mqtt_password);
  wifiManager.addParameter(&custom_mqtt_keywords1);
  wifiManager.addParameter(&custom_mqtt_keywords2);
  
  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect(MAC_char, "password")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }
}


void callback(char* topic, byte* payload, unsigned int length){
string  userId      = "node1";
string macAddress   = MAC_char;
string processor    = "arduino";
string type         = "I/O"; 
string timeStamp    = "";

Serial.print("Message arrived [");
Serial.print(topic);
Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  stateDevice = (char)payload[0];

  //condition input for subscribe from MQTT
  if (stateDevice[0] == 'dev1on')
  {
    digitalWrite(in1, HIGH);
    client.publish("/output", "off");
    Serial.print(stateDevice[0]);
  }
  if (stateDevice[0] == 'dev1off')
  {
    digitalWrite(in1, LOW);
    client.publish("/output", "on");
    Serial.print(stateDevice[0]);
  }

   if (stateDevice[1] == 'dev2on')
  {
    digitalWrite(in2, HIGH);
    client.publish("/output", "off");
    Serial.print(stateDevice);
  }
  if (stateDevice[1] == 'dev2off')
  {
    digitalWrite(in2, LOW);
    client.publish("/output", "on");
    Serial.print(stateDevice);
  }
 
   if (stateDevice[2] == 'dev3on')
  {
    digitalWrite(in3, HIGH);
    client.publish("/output", "off");
    Serial.print(stateDevice);
  }
  if (stateDevice[2] == 'dev3off')
  {
    digitalWrite(in3, LOW);
    client.publish("/output", "on");
    Serial.print(stateDevice);
  }

   if (stateDevice[3] == 'dev4on')
  {
    digitalWrite(in4, HIGH);
    client.publish("/output", "off");
    Serial.print(stateDevice);
  }
  if (stateDevice[3] == 'dev4off')
  {
    digitalWrite(in4, LOW);
    client.publish("/output", "on");
    Serial.print(stateDevice);
  }

   if (stateDevice[4] == 'dev5on')
  {
    digitalWrite(in5, HIGH);
    client.publish("/output", "off");
    Serial.print(stateDevice);
  }
  if (stateDevice[4] == 'dev5off')
  {
    digitalWrite(in5, LOW);
    client.publish("/output", "on");
    Serial.print(stateDevice);
  }

   if (stateDevice[5]== 'dev6on')
  {
    digitalWrite(in6, HIGH);
    client.publish("/output", "off");
    Serial.print(stateDevice);
  }
  if (stateDevice[5] == 'dev6off')
  {
    digitalWrite(in6, LOW);
    client.publish("/output", "on");
    Serial.print(stateDevice);
  }

   if (stateDevice[6] == 'dev7on')
  {
    digitalWrite(in7, HIGH);
    client.publish("/output", "off");
    Serial.print(stateDevice);
  }
  if (stateDevice[6] == 'dev7off')
  {
    digitalWrite(in7, LOW);
    client.publish("/output", "on");
    Serial.print(stateDevice);
  }

   if (stateDevice[7] == 'dev8on')
  {
    digitalWrite(in8, HIGH);
    client.publish("/output", "off");
    Serial.print(stateDevice);
  }
  if (stateDevice[8] == 'dev8off')
  {
    digitalWrite(in8, LOW);
    client.publish("/output", "on");
    Serial.print(stateDevice);
  }
 
}



void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // digitalWrite(LED1, LOW);
    // digitalWrite(BUZZER, HIGH);
    // delay(500);
    // digitalWrite(BUZZER, LOW);
    // delay(1500);
    //Serial.println(mqtt_server);
    // Attempt to connect
    if (client.connect(MAC_char,mqtt_user, mqtt_password)) {
      Serial.println("connected");
      //digitalWrite(LED1, HIGH);
      // Once connected, publish an announcement...
      client.publish(mqtt_keywords1, MAC_char);
      client.subscribe(mqtt_keywords2);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      if(client.state()==4) ESP.restart();
      else {
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
  }
}


/////////////////////////////////////////////////////
//Create Json File
/////////////////////////////////////////////////////

void loop() {
  
  JsonObject& JSONencoder = JSONbuffer.createObject();
 
  JSONencoder["UserID"]       = userId;
  JSONencoder["MacAddress"]   = macAddress;
  JSONencoder["Processor"]    = processor;
  JSONencoder["Type"]         = type;
  JSONencoder["TimeStamp"]    = timestamp;
  JsonArray& values = JSONencoder.createNestedArray("Payloads");
 
  Payloads.add("device 1",stateDevice[0]);
  Payloads.add("device 1",stateDevice[1]);
  Payloads.add("device 1",stateDevice[2]);
  Payloads.add("device 1",stateDevice[3]);
  Payloads.add("device 1",stateDevice[4]);
  Payloads.add("device 1",stateDevice[5]);
  Payloads.add("device 1",stateDevice[6]);
  Payloads.add("device 1",stateDevice[7]);

  char JSONmessageBuffer[200];
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println("Sending message to MQTT topic..");
  Serial.println(JSONmessageBuffer);
  
  if (client.publish("input/", JSONmessageBuffer) == true) {
    Serial.println("Success sending message");
  } else {
    Serial.println("Error sending message");
  }
 
  client.loop();
  Serial.println("-------------");
 
      
  }
}
