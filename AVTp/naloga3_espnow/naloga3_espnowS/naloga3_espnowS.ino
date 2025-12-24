#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

// port 80
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  
  
  Serial.print("Setting AP (Access Point)…");
  
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
  //nastavili AP Mode in dobili naš IP
}

void loop(){
  WiFiClient client = server.available();   // posluša za povezavo

  if (client) {                             // če se je nov client povezu,
    Serial.println("New Client.");          // printi da se je client povezu
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop dokler je client povezan
      if (client.available()) {             // če so byte za brat od clienta,
        char c = client.read();             // beri byte od clienta
        Serial.write(c);                    // printa v serial monitor byte
        currentLine += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 2) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Send your "Hello World" HTML response
            client.println("<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
            client.println("<body><h1>Hello World</h1></body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
