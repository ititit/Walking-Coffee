
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

IPAddress ip(192, 168, 0, 2);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

int ledPin = 4;
String readString;
void setup() {

pinMode(ledPin, OUTPUT);

  
 //pinMode(2, INPUT);
//digitalWrite(4, HIGH);
 // You can use Ethernet.init(pin) to configure the CS pin
 Ethernet.init(10);  // Most Arduino shields
 //Ethernet.init(5);   // MKR ETH shield
 //Ethernet.init(0);   // Teensy 2.0
 //Ethernet.init(20);  // Teensy++ 2.0
 //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
 //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

 // Open serial communications and wait for port to open:
 Serial.begin(9600);
 while (!Serial) {
   // wait for serial port to connect. Needed for native USB port only
 }
 Serial.println("Ethernet WebServer Example");

 // start the Ethernet connection and the server:
 Ethernet.begin(mac, ip);

 // Check for Ethernet hardware present
 if (Ethernet.hardwareStatus() == EthernetNoHardware) {
   Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
   while (true) {
     delay(1); // do nothing, no point running without Ethernet hardware
   }
 }
 Serial.println(Ethernet.linkStatus());
 if (Ethernet.linkStatus() == LinkOFF) {
   Serial.println("Ethernet cable is not connected.");
 }

 // start the server
 server.begin();
 Serial.print("server is at ");
 Serial.println(Ethernet.localIP());
}


void loop() {

  
 // listen for incoming clients
 EthernetClient client = server.available();
 if (client) {
   Serial.println("new client");
   // an http request ends with a blank line
   bool currentLineIsBlank = true;
   while (client.connected()) {
     if (client.available()) {
       char c = client.read();
       Serial.write(c);
       // if you've gotten to the end of the line (received a newline
       // character) and the line is blank, the http request has ended,
       // so you can send a reply
       if (c == '\n' && currentLineIsBlank) {
         // send a standard http response header
         client.println("HTTP/1.1 200 OK");
         client.println("Content-Type: text/html");
         client.println("Connection: close");  // the connection will be closed after completion of the response
         client.println("Refresh: 15");  // refresh the pageautomatically every 5 sec
         client.println();
         client.println("<!DOCTYPE HTML>");
         client.println("<html>");


      client.println("<head>");
      client.println("<title>Webserver</title>");
      client.println("</head>");
      client.println("<body>");
      client.println("<H1>HTML form GET example</H1>");

          client.println("<FORM ACTION='/' method=get >");

          client.println("Pin 4 'on' or 'off': <INPUT TYPE=TEXT NAME='LED' VALUE='' SIZE='25' MAXLENGTH='50'><BR>");

          client.println("<INPUT TYPE=SUBMIT NAME='submit' VALUE='Change Pin 4!'>");

          client.println("</FORM>");

    
      client.println("<body style=background-color:grey>");


         // output the value of each analog input pin
         for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
           int sensorReading = analogRead(analogChannel);
           client.print("analog input ");
           client.print(analogChannel);
           client.print(" is ");
           client.print(sensorReading);
           client.println("<br />");
         }
         client.println("</html>");
         break;
       }
       if (c == '\n') {
         // you're starting a new line
         currentLineIsBlank = true;
       } else if (c != '\r') {
         // you've gotten a character on the current line
         currentLineIsBlank = false;
       }
     }
   }
   // give the web browser time to receive the data
   delay(1);
   // close the connection:
   client.stop();
   Serial.println("client disconnected");

   if(readString.indexOf("on") >0)//checks for on
          {
            digitalWrite(4, HIGH);    // set pin 4 high
            Serial.println("Led On");
          }
          if(readString.indexOf("off") >0)//checks for off
          {
            digitalWrite(4, LOW);    // set pin 4 low
            Serial.println("Led Off");
          }
          //clearing string for next read
          readString="";

 }
}
