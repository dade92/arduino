// Run along with server node-example
// IMPORTANT: these read GET and POST method are the same, only thing different are the json fields to be retrieved
// This code seems to work even in case of long responses by the server, as you
// can see by the continuing blinking led

// Wifi password is read from the EEPROM at startup.
// Before launching this script, make sure to write it using the proper sketch in the
// example folder!!!
// Change the ssid too
#include "WiFiS3.h"
#include <ArduinoJson.h>
#include <EEPROM.h>
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

char ssid[] = "FRITZ!Box 7530 QR";
char pass[21];

int status = WL_IDLE_STATUS;

WiFiClient client;

// server address:
char server[] = "davides-mbp";
// IPAddress server(192, 168, 178, 21);

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 10L * 1000L;
unsigned long lastBlink = 0;
const int blinkTime = 500;
int led = LED_BUILTIN;
bool ledStatus = false;

const uint32_t CONN_OK[] = {
  0x73453873,
  0x40000000,
  0x0
};


void httpRequest();
void performGET();
void performPOST(int param);
void read_GET_response();
void read_POST_response();
void readWifiPassword();

// Allocate the JSON document
//
// Inside the brackets, 200 is the capacity of the memory pool in bytes.
// Don't forget to change this value to match your JSON document.
// Use arduinojson.org/v6/assistant to compute the capacity.
StaticJsonDocument<100> doc;

// StaticJsonDocument<N> allocates memory on the stack, it can be
// replaced by DynamicJsonDocument which allocates in the heap.
//
// DynamicJsonDocument doc();

void setup() {
  pinMode(led, OUTPUT);

  Serial.begin(9600);
  matrix.begin();

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

  readWifiPassword();

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
  }
  matrix.loadFrame(CONN_OK);
  // you're connected now, so print out the status:
  printWifiStatus();
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:

  // read_GET_response();
  read_POST_response();

  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }

  if (millis() - lastBlink > blinkTime) {
    ledStatus = !ledStatus;
    digitalWrite(led, ledStatus);
    lastBlink = millis();
  }
}

void read_GET_response() {
  String json = "";
  String header = "";
  String httpResponse = "";
  String httpVersion = "";

  while (client.available()) {
    /* actual data reception */
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
    httpVersion = header.substring(0, index);
    int index2 = header.indexOf(" ", index + 1);
    httpResponse = header.substring(index + 1, index2);
    if (httpResponse == "200") {
      if (json.length() > 0) {
        Serial.println("JSON response was: " + json);
        DeserializationError error = deserializeJson(doc, json);

        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          return;
        }

        Serial.println("User was: " + doc["name"].as<String>());
        Serial.println("Age was: " + String(doc["age"].as<int>()));
      }
    } else {
      Serial.println("Server answered with " + httpResponse);
    }
  }
}

void read_POST_response() {
  String json = "";
  String header = "";
  String httpResponse = "";
  String httpVersion = "";

  while (client.available()) {
    /* actual data reception */
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
    httpVersion = header.substring(0, index);
    int index2 = header.indexOf(" ", index + 1);
    httpResponse = header.substring(index + 1, index2);

    if (httpResponse == "200") {
      if (json.length() > 0) {
        Serial.println("JSON response was: " + json);
        DeserializationError error = deserializeJson(doc, json);

        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          return;
        }
        Serial.println("Number was: " + doc["yourNumber"].as<String>());
      }
    } else {
      Serial.println("Http response was " + httpResponse);
    }
  }
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the NINA module
  client.stop();

  // performGET();

  performPOST(random(300));
}

void performGET() {
  if (client.connect(server, 8080)) {
    Serial.println("connecting...");

    client.println("GET /findUser?name=Carlos HTTP/1.1");
    client.println("Host: example.org");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

    lastConnectionTime = millis();
  } else {
    Serial.println("connection failed");
  }
}

void performPOST(int param) {
  String requestBody = "{\"number\":" + String(param) + "}";

  if (client.connect(server, 8080)) {
    Serial.println("connecting...");
    client.println("POST /arduino/test HTTP/1.1");
    client.println("Content-Type: application/json;charset=UTF-8");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(requestBody.length());
    client.println();
    client.println(requestBody);
    lastConnectionTime = millis();
  } else {
    Serial.println("connection failed");
  }
}

void printWifiStatus() {
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
}

void readWifiPassword() {
  for (int i = 0; i < 20; i++) {
    pass[i] = EEPROM.read(i);
  }
  pass[20] = '\0';
}
