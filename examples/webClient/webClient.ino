/*
  Repeating WiFi Web Client

 This sketch connects to a a web server and makes a request
 using a WiFi equipped Arduino board.

 created 23 April 2012
 modified 31 May 2012
 by Tom Igoe
 modified 13 Jan 2014
 by Federico Vanzati

 This code is in the public domain.

  Find the full UNO R4 WiFi Network documentation here:
  https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples#wi-fi-web-client-repeating
 */

#include "WiFiS3.h"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "FRITZ!Box 7530 QR";        // your network SSID (name)
char pass[] = "06989642165939857128";    // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;

// Initialize the WiFi client library
WiFiClient client;

// server address:
char server[] = "davides-mbp";
// IPAddress server(192, 168, 178, 21);

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds

void performGET();
void performPOST(int param);

/* -------------------------------------------------------------------------- */
void setup() {
/* -------------------------------------------------------------------------- */  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  randomSeed(analogRead(0));

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
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    //delay(10000);
  }
  // you're connected now, so print out the status:
  printWifiStatus();
}

/* just wrap the received data up to 80 columns in the serial print*/
/* -------------------------------------------------------------------------- */
void read_request() {
/* -------------------------------------------------------------------------- */  
  uint32_t received_data_num = 0;

  while (client.available()) {
    /* actual data reception */
    char c = client.read();
    /* print data to serial port */
    Serial.print(c);
    /* wrap data to 80 columns*/
    received_data_num++;
    if(received_data_num % 80 == 0) { 
      
    } 
  }
}

/* -------------------------------------------------------------------------- */
void loop() {
/* -------------------------------------------------------------------------- */  
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  read_request();
  
  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }

}

// this method makes a HTTP connection to the server:
/* -------------------------------------------------------------------------- */
void httpRequest() {
/* -------------------------------------------------------------------------- */  
  // close any connection before send a new request.
  // This will free the socket on the NINA module
  client.stop();

  // performGET();

  performPOST(random(300));
}

void performGET() {
    // if there's a successful connection:
  if (client.connect(server, 8080)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    client.println("GET /findUser?name=Francesca HTTP/1.1");
    client.println("Host: example.org");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

void performPOST(int param) {
    String requestBody = "{\"number\":" + String(param) + "}";

  // if there's a successful connection:
  if (client.connect(server, 8080)) {
    Serial.println("connecting...");
    // send the HTTP POST request:
    client.println("POST /arduino/test HTTP/1.1");
    client.println("Content-Type: application/json;charset=UTF-8");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(requestBody.length());
    client.println();
    client.println(requestBody);
    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

/* -------------------------------------------------------------------------- */
void printWifiStatus() {
/* -------------------------------------------------------------------------- */  
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
}
