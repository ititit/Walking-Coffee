#include <Ethernet.h>
#include <SPI.h>


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

IPAddress ip(192, 168, 0, 2);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);


String readString;
int led = 8;

void setup() {

pinMode(8, OUTPUT);

  
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

  EthernetClient client = server.available();

 if (client) {
   while(client.connected()) {
     if (client.available()) {
       char c = client.read() ;
       Serial.print(c);


      if(readString.length() <100) {
         readString += c;
         }

      if(c == '\n') {
       Serial.print(readString);
       client.println("<HTTP/1.1 200 OK>");
       client.println("<Connection-Type:text/texthtml>");
       client.println("<Connection: close>");
       client.println("");

       client.println("<!DOCTYPE html>");
       client.println("<html>");
       client.println("<head>");
       client.println("<title>ITITITinc Labs</title>");
       client.println("<title>ITITITinc Labs</title>");
       client.println("</head>");
       client.println("<body>");
       client.println("<a href=\"/?buttonon\"\"><button>LED ON</button></a>");
       client.println("<a href=\"/?buttonoff\"\"><button>LED off</button></a>");
         client.println("<FORM ACTION='/' method=get >");

          client.println("Pin 4 'on' or 'off': <INPUT TYPE=TEXT NAME='LED' VALUE='' SIZE='25' MAXLENGTH='50'><BR>");

          client.println("<INPUT TYPE=SUBMIT NAME='submit' VALUE='Change Pin 4!'>");

          client.println("</FORM>");
       client.println("<body style=background-color:#1f1f1f;color=white>");



       if (readString.indexOf("buttonon")>=0) {
        client.println("Making LED high.");
         digitalWrite(led, HIGH);
       
       }
        if (readString.indexOf("buttonoff")>=0) {
        client.println("Making LED low.");

         digitalWrite(led, LOW);
       }

       delay(1);
       client.stop();
       readString = "";
      }
     }
   }
 }
}
