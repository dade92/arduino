#include "WiFiS3.h"
#include <ArduinoJson.h>
#include <EEPROM.h>
#include "Arduino_LED_Matrix.h"

#define RED_LIGHT 7
#define GREEN_LIGHT 6

// IMPORTANT wifi password is read from the EEPROM at startup.
// Before launching this script, make sure to write it using the proper sketch in the
// example folder!!!
// Change the ssid too
char ssid[] = "FRITZ!Box 7530 QR";
char pass[21];
ArduinoLEDMatrix matrix;
const uint32_t CONN_OK[] = {
  0x73453873,
  0x40000000,
  0x0
};



// Allocate the JSON document
// TODO: OPTIMIZE ALLOCATION

// Inside the brackets, 200 is the capacity of the memory pool in bytes.
// Don't forget to change this value to match your JSON document.
// Use arduinojson.org/v6/assistant to compute the capacity.
StaticJsonDocument<100> doc;

int status = WL_IDLE_STATUS;
const String METHOD_NOT_ALLOWED = "HTTP/1.1 405 Method Not Allowed";
const String BAD_REQUEST = "HTTP/1.1 400 Bad request";
const String OK = "HTTP/1.1 200 OK";
String lightStatus = "OFF";
WiFiServer server(8080);

void listen();
void readWifiPassword();

void setup() {
  Serial.begin(9600);
  matrix.begin();
  pinMode(RED_LIGHT, OUTPUT);
  pinMode(GREEN_LIGHT, OUTPUT);

  readWifiPassword();

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true)
      ;
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
  }

  server.begin();     // start the web server on port 80
  printWifiStatus();  // you're connected now, so print out the status
  matrix.loadFrame(CONN_OK);
}


void loop() {
  listen();

  if (lightStatus == "OFF") {
    digitalWrite(RED_LIGHT, LOW);
  } else if (lightStatus == "ON") {
    digitalWrite(RED_LIGHT, HIGH);
  }
}

void listen() {
  WiFiClient client = server.available();  // listen for incoming clients
  String json = "";
  String header = "";
  String httpResponse;
  String path = "";
  String httpMethod = "";

  if (client) {
    // HTTP REQUEST PARSING
    while (client.connected() && client.available()) {
      char c = client.read();
      header += c;
      if (c == '\n') {
        c = client.read();
        header += c;
        if (c == '\r') {
          c = client.read();
          json += c;
          c = client.read();
          if (c != '{') {
            break;
          } else {
            json += c;
            while (c != '}') {
              c = client.read();
              json += c;
            }
          }
        }
      }
    }

    if (header.length() > 0) {
      int index = header.indexOf(" ", 0);
      httpMethod = header.substring(0, index);
      int index2 = header.indexOf(" ", index + 1);
      path = header.substring(index + 1, index2);
      Serial.println("Request header was: " + header);

      // REST mapping here
      if (path.equalsIgnoreCase("/test") && httpMethod.equalsIgnoreCase("POST")) {
        if (json.length() > 0) {
          Serial.println("JSON request was: " + json);
          DeserializationError error = deserializeJson(doc, json);

          if (error) {
            // No field
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            httpResponse = BAD_REQUEST;
          } else {
            lightStatus = doc["light"].as<String>();
            httpResponse = OK;
          }
        } else {
          // No body
          httpResponse = BAD_REQUEST;
        }
      } else {
        // Wrong path
        httpResponse = METHOD_NOT_ALLOWED;
      }
    } else {
      httpResponse = BAD_REQUEST;
    }

    // Sends the final HTTP response
    client.println(httpResponse);
    client.println("Content-type: application/json");
    client.println("Connection: close");
    client.println();
    client.print("{\"data\": \"" + lightStatus + "\"}");
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
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

void readWifiPassword() {
  for (int i = 0; i < 20; i++) {
    pass[i] = EEPROM.read(i);
  }
  pass[20] = '\0';
}
