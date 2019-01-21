/*
Version   : 1.0
Project   : Home Automation
Developer : Nurman Hariyanto 
Date      : 01/18/2019
*/


///////////////////////////////////////////////////////////////////////////////////////////
//Library
//#include <Arduino.h>
//#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <Ticker.h>

#include <DNSServer.h>
//#include <ESP8266WebServer.h>
#include <WiFiManager.h> 
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>          //json library
#include <PubSubClient.h>         //publish & subscribe library


#include <config.h>
/////////////////////////////////////////////////////////////////////////////////////////////



/*param IO*/

//Pin on nodemcu
int iomap[8]={1,2,3,4,5,6,7,8};
// status device(on/off)
char* Device[8] = {stateDevice1,stateDevice2,stateDevice3,stateDevice4,stateDevice5,stateDevice6,stateDevice7,stateDevice8};




/*setup IO*/
void setup() {
  //ResetSettings();
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
  Serial.begin(115200);
  

  Serial.println(F("Booting...."));  
  ReadConfigFile(); // Read Config File if it is exist
  setup_wifi();
  SaveConfigFile();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  Serial.println(F("Ready!"));
  Serial.println(F("======================================================")); 

}

/*setup wifi */
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
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


/*callback*/
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  String sTopic = topic;

  if(sTopic == mqtt_keywords2)
  {
    Serial.println("Sense Control Command");
    if ((char)payload[1] == '1') 
    {
      ResetSettings();
    }
    
    if ((char)payload[0] == '1') 
    {
      delay(2000);
      ESP.reset();
      delay(5000);
    }
  }
}

/*Reconnec*/
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...%s");
    Serial.println(mqtt_server);
    // Attempt to connect
    if (client.connect(MAC_char,mqtt_user, mqtt_password)) {
      Serial.println("connected");
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

/*loop parsing json*/
void loop(){
 if (!client.connected()) {
    reconnect();
  }

  for (int m=0; m<=7; m++){
      for (int n=0; n<=1; n++){
          if (n==0){
            Serial.print("device");
            Serial.Print(iomap[m])
            Serial.print("off")
          }

          if (n==1){
              Serial.print("device");
              Serial.print(iomode[m])
              Serial.Print("on")
          }

      }
  }
  JSONencoder["UserID"]       = "userId";
  JSONencoder["MacAddress"]   = macAddress;
  JSONencoder["Processor"]    = "arduino";
  JSONencoder["Type"]         = "IO";
  JSONencoder["TimeStamp"]    = "timestamp";
  JsonArray& values = JSONencoder.createNestedArray("Payloads");
  payload.add(iomap[]

  if (client.publish(mqtt_keywords2, JSONmessageBuffer) == true) {
    Serial.println("Success sending message");
  } else {
    Serial.println("Error sending message");
  }

    client.loop();
  Serial.println("-------------");
 
  delay(10000);
 

}



