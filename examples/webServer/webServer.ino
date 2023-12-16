#include "WiFiS3.h"
#include <ArduinoJson.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "FRITZ!Box 7530 QR";        // your network SSID (name)
char pass[] = "";        // your network password (use for WPA, or use as key for WEP)

// Allocate the JSON document
//
// Inside the brackets, 200 is the capacity of the memory pool in bytes.
// Don't forget to change this value to match your JSON document.
// Use arduinojson.org/v6/assistant to compute the capacity.
StaticJsonDocument<100> doc;

int led =  LED_BUILTIN;
int status = WL_IDLE_STATUS;
WiFiServer server(8080);

void setup() {
  Serial.begin(9600);      // initialize serial communication
  pinMode(led, OUTPUT);      // set the LED pin mode

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    // delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
}


void loop() {
  WiFiClient client = server.available();   // listen for incoming clients
  String json = "";

  if (client) {                             // if you get a client,
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && client.available()) {            // loop while the client's connected
      char c = client.read();
      if(c == '\n') {
        c = client.read();
        if(c == '\r') {
          c = client.read();
          json += c;
          while(c != '}') {
            c = client.read();
            json += c;
          }
        }
      }
    }
    // //Responds with 204 ok no content
    client.println("HTTP/1.1 204 No Content");
    client.println("Content-type: application/json");
    client.println();
    client.print("");
    client.println();
    // close the connection:
    client.stop();
    Serial.println("client disconnected");

    if(json.length() > 0) {
      Serial.println("JSON response was: " + json);
      DeserializationError error = deserializeJson(doc, json);

      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }

      Serial.println("Light must be turned: " + doc["light"].as<String>());
    }
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To communicate to this device, use the API: http://");
  Serial.print(ip);
  Serial.print(":8080/");
}
