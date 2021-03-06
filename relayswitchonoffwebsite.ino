/*
  Web  Server
 
 A simple web server that shows the value of the analog and digital input pins
 using a WiFi BoosterPack.
 
 This example is written for a network using WPA encryption. For 
 WEP or WPA, change the Wifi.begin() call accordingly.
 
 Circuit:
 * WiFi BoosterPack
 
 Created: October 16, 2013 by Robert Wessels (http://energia.nu)
 Derived from example Sketch by Hans Scharler (http://www.iamshadowlord.com)
 
 */

#include "Ethernet.h"
// Prototypes
void printConfig();
void printEthernetData();
void printIndex();
void printHelp();

EthernetServer server(80);
int statusConfig = 0;


void setup() {
  Serial.begin(115200);    

  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  Serial.println("Connecting to Ethernet....");  
  IPAddress ip = IPAddress(146,252,242,129);
  IPAddress dns = IPAddress(146,252,242,12);
  IPAddress gw = IPAddress(146,252,242,254);
  IPAddress mask = IPAddress(255,255,255,0);

  Ethernet.begin(0);
  //  Ethernet.begin(0, ip, dns, gw);

  server.begin();

  printEthernetData();
}

EthernetClient client;

void loop() {
  client = server.available();

  if (client) {                             // if you get a client,
    Serial.print("new client on port ");           // print a message out the serial port
    Serial.println(client.port());
    String currentLine = "";                // make a String to hold incoming data from the client
    boolean newConnection = true;     // flag for new connections
    unsigned long connectionActiveTimer;  // will hold the connection start time

    while (client.connected()) {       // loop while the client's connected
      if (newConnection){                 // it's a new connection, so
        connectionActiveTimer = millis(); // log when the connection started
        newConnection = false;          // not a new connection anymore
      }
      if (!newConnection && connectionActiveTimer + 1000 < millis()){ 
        // if this while loop is still active 1000ms after a web client connected, something is wrong
        break;  // leave the while loop, something bad happened
      }


      if (client.available()) {             // if there's bytes to read from the client,    
        char c = client.read();             // read a byte, then
        // This lockup is because the recv function is blocking.
        Serial.print(c);
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {  
            break;         
          } 
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }     
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        if (currentLine.endsWith("GET / ")) {
          statusConfig = 0;
          printIndex();
        }
        if (currentLine.endsWith("GET /config.html ")) {
          statusConfig = 1;
          printConfig();
        }
        if (currentLine.endsWith("GET /status.html")){
          statusConfig = 0;
          printStatus();
        }
        if (currentLine.endsWith("GET /index.html ")) {
          statusConfig = 0;
          printIndex();
        }
        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /Relay1_H")) {
          digitalWrite(2, HIGH);
          printConfig();
        }         
        if (currentLine.endsWith("GET /Relay1_L")) {
          digitalWrite(2, LOW);
          printConfig();
        }     
        if (currentLine.endsWith("GET /Relay2_H")) {
          digitalWrite(3, HIGH);
          printConfig();
        }       
        if (currentLine.endsWith("GET /Relay2_L")) {
          digitalWrite(3, LOW);
          printConfig();
        }
        if (currentLine.endsWith("GET /Relay3_H")) {
          digitalWrite(4, HIGH);
          printConfig();
        }       
        if (currentLine.endsWith("GET /Relay3_L")) {
          digitalWrite(4, LOW);
          printConfig();
        }
        if (currentLine.endsWith("GET /Relay4_H")) {
          digitalWrite(5, HIGH);
          printConfig();
        }       
        if (currentLine.endsWith("GET /Relay4_L")) {
          digitalWrite(5, LOW);
          printConfig();
        }
        if (currentLine.endsWith("GET /Relay5_H")) {
          digitalWrite(6, HIGH);
          printConfig();
        }       
        if (currentLine.endsWith("GET /Relay5_L")) {
          digitalWrite(6, LOW);
          printConfig();
        }
        if (currentLine.endsWith("GET /Relay6_H")) {
          digitalWrite(43, HIGH);
          printConfig();
        }       
        if (currentLine.endsWith("GET /Relay6_L")) {
          digitalWrite(43, LOW);
          printConfig();
        }     
        if (currentLine.endsWith("GET /Relay7_H")) {
          digitalWrite(12, HIGH);
          printConfig();
        }       
        if (currentLine.endsWith("GET /Relay7_L")) {
          digitalWrite(12, LOW);
          printConfig();
        }
        if (currentLine.endsWith("GET /Relay8_H")) {
          digitalWrite(11, HIGH);
          printConfig();
        }       
        if (currentLine.endsWith("GET /Relay8_L")) {
          digitalWrite(11, LOW);
          printConfig();
        }
      }
    }
    // close the connection:
    client.stop();
    //Serial.println("client disonnected");
  }
}

void printIndex()
{
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:    
  //  Serial.println("Index");
  client.println("HTTP/1.1 200 OK");

  client.println("Content-type:text/html");
  client.println();
  client.println("<html><head><title>Energia Ethernet Web Server</title></head><body align=center>");
  client.println("<h1 align=center><font color=\"red\">Welcome To Ethernet Web Server</font></h1>");
  client.println("</br><font size=\"4px\"><table border=\"0\" align=center width=1200px height=590px>");
  client.println("<tr><td align=center width=375></td><td width=450px align=left valign=\"top\">");


  client.println("<p>The Ethernet Web Server provides the");
  client.println("capability to remotely read and write GPIOs ");
  client.println("on/off.</p></br></br>");
  client.println("<p><a href=\"/status.html\">Click here</a> ");
  client.println("to check status</p>");
  client.println("<p><a href=\"/config.html\">Click here</a> ");
  client.println("to turn relays on and off</p>");
  client.println("<td align=cneter width=375></td></tr></table></font></body></html>");
  


  client.println();

}

void printConfig()
{
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:    
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.println("<html><head><title>Energia Ethernet Web Server</title></head><body align=center>");
  client.println("<h1 align=center><font color=\"red\">Welcome to the Ethernet Web Server</font></h1>");

  // the content of the HTTP response follows the header:
  // Added: nicer buttons
  client.print("<font color=\"red\">Relay 1 </font><button onclick=\"location.href='/Relay1_H'\">ON</button>");
  client.println(" <button onclick=\"location.href='/Relay1_L'\">OFF</button><br><br>");
  client.print("<font color=\"orange\">Relay 2 </font><button onclick=\"location.href='/Relay2_H'\">ON</button>");
  client.println(" <button onclick=\"location.href='/Relay2_L'\">OFF</button><br><br>");
  client.print("<font color=\"black\">Relay 3 </font><button onclick=\"location.href='/Relay3_H'\">ON</button>");
  client.println(" <button onclick=\"location.href='/Relay3_L'\">OFF</button><br><br>");
  client.print("<font color=\"green\">Relay 4 </font><button onclick=\"location.href='/Relay4_H'\">ON</button>");
  client.println(" <button onclick=\"location.href='/Relay4_L'\">OFF</button><br><br>");
  client.print("<font color=\"blue\">Relay 5 </font><button onclick=\"location.href='/Relay5_H'\">ON</button>");
  client.println(" <button onclick=\"location.href='/Relay5_L'\">OFF</button><br><br>");
  client.print("<font color=\"indigo\">Relay 6 </font><button onclick=\"location.href='/Relay6_H'\">ON</button>");
  client.println(" <button onclick=\"location.href='/Relay6_L'\">OFF</button><br><br>");
  client.print("<font color=\"violet\">Relay 7 </font><button onclick=\"location.href='/Relay7_H'\">ON</button>");
  client.println(" <button onclick=\"location.href='/Relay7_L'\">OFF</button><br><br>");
  client.print("Relay 8 <button onclick=\"location.href='/Relay8_H'\">ON</button>");
  client.println(" <button onclick=\"location.href='/Relay8_L'\">OFF</button><br><br>");
  

  client.println("<a href=\"/status.html\" >status</a><br>");
  client.println("<a href=\"/config.html\" >refresh</a> <br>");
  client.println("<a href=\"/index.html\" >home</a> <br>");
  client.println("</body></html>");
  // The HTTP response ends with another blank line:
  client.println();
  // break out of the while loop:
}
void printStatus(){
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  if(digitalRead(2))client.print("1 ");
  if(digitalRead(3))client.print("2 ");
  if(digitalRead(4))client.print("3 ");
  if(digitalRead(5))client.print("4 ");
  if(digitalRead(6))client.print("5 ");
  if(digitalRead(43))client.print("6 ");
  if(digitalRead(12))client.print("7 ");
  if(digitalRead(11))client.print("8");
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    switch(inChar) {
    case 'h':
      printHelp();
      break;
    case 'i':
      printEthernetData();
      break;
    default:
      Serial.println();
      Serial.println("Invalid menu option");
    }
  } 
}

void printHelp() {
  Serial.println();
  Serial.println("+++++++++++++++++++++++++++++++++++++");
  Serial.println("Help menu:");
  Serial.println("\th: This help menu");
  Serial.println("\ti: IP address information");
  Serial.println("+++++++++++++++++++++++++++++++++++++");
}

void printHex(int num, int precision) {
  char tmp[16];
  char format[128];

  sprintf(format, "%%.%dX", precision);

  sprintf(tmp, format, num);
  Serial.print(tmp);
}

void printEthernetData() {
  // print your IP address:
  Serial.println();
  Serial.println("IP Address Information:");  
  IPAddress ip = Ethernet.localIP();
  Serial.print("IP Address:\t");
  Serial.println(ip);

  // print your MAC address:

  IPAddress subnet = Ethernet.subnetMask();
  Serial.print("NetMask:\t");
  Serial.println(subnet);

  // print your gateway address:
  IPAddress gateway = Ethernet.gatewayIP();
  Serial.print("Gateway:\t");
  Serial.println(gateway);

  // print your gateway address:
  IPAddress dns = Ethernet.dnsServerIP();
  Serial.print("DNS:\t\t");
  Serial.println(dns);

}
