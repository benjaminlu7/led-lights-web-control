/*
================================================================================================
LED Lights (Web Control)
================================================================================================
This project deals with LED Lights which is controlled by GPIO at pins 3, 4, and 5. It uses the 
web server to control the LED from Off to On.

@package        LED Light (Web Control)
@copyright      Copyright (C) 2018. Benjamin Lu
@license        GNU General Public License v2 or later (http://www.gnu.org/licenses/gpl-2.0.html)
@author         Benjamin Lu (https://www.benjlu.com/)
================================================================================================
*/

/*
================================================================================================
Table of Content
================================================================================================
 1.0 - Required Files
 2.0 - Variables
 3.0 - Setup
 4.0 - Loop
 5.0 - redLED Checkbox
 6.0 - yellowLED Checkbox
 7.0 - greenLED Checkbox
================================================================================================
*/

/*
================================================================================================
 1.0 - Required Files
================================================================================================
*/
#include <SPI.h>
#include <Ethernet.h>

/*
================================================================================================
 2.0 - Variables
================================================================================================
*/
byte mac[] = { 0x00, 0x1B, 0xEB, 0x41, 0x25, 0x06 };  // Enter MAC Address of 86Duino (Educake)
IPAddress ip(192, 168, 100, 47);                      // Enter Static IP Address of 86Duino (Educake)
EthernetServer web_server(80);                        // Creating a Web Server Using Port 80

String http_request;                                  // This will stored the http request
boolean redLED_status = 0;                            // Set Red LED to 0, off by default
boolean yellowLED_status = 0;                         // Set Yellow LED to 0, off by default
boolean greenLED_status = 0;                          // Set Green LEd to 0, off by default

int redLED = 3;                                       // Set redLED to GPIO Pin 3
int yellowLED = 4;                                    // Set yellowLED to GPIO Pin 4
int greenLED = 5;                                     // Set greenLED to GPIO Pin 5

/*
================================================================================================
 3.0 - Setup
================================================================================================
*/
void setup() {
  Ethernet.begin(mac, ip);                            // Initializing Ethernet Communications
  web_server.begin();                                 // Start to Lisen for clients
  Serial.begin(9600);                                 // Open Serial Communications for Diagnostics

  pinMode(redLED, OUTPUT);                            // Set redLED to Pin 3 as Output
  pinMode(yellowLED, OUTPUT);                         // Set yellowLED to Pin 4 as Output
  pinMode(greenLED, OUTPUT);                          // Set greenLED to Pin 5 as Output
}

/*
================================================================================================
 4.0 - Loop
================================================================================================
*/
void loop() { 
  EthernetClient client = web_server.available();       // Try to get a client

  if (client) {                                         // Got Client
    boolean currentLineIsBlank = true;

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        http_request += c;

        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: Closed");
          client.println();

          /*
          ======================================================================================
          Start the Web Page that contains all information for the LED Lights to display.
          ======================================================================================
          */
          client.println("<!DOCTYPE html");
          client.println("<html lang=\"en-US\">");
          client.println("<head>");
          client.println("<title>LED Lights (Web Control)</title>");
          client.println("<meta charset=\"UTF-8\" />");
          client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<link href=\"https://gmpg.org/xfn/11\" rel=\"profile\">");
          client.println("<style type=\"text/css\">");
          client.println("body { background: #eeeeee; font-family: Trebuchet MS; margin: 1.125em 0; padding: 0; }");
          client.println("h1 { display: block; font-size: 2em; font-weight: 700; margin: 0.67em 0; }");
          client.println("h2 { display: block; font-size: 1.5em; font-weight: 700; margin: 0.83em 0; }");
          client.println("h3 { display: block; font-size: 1.17em; font-weight: 700; margin: 1em 0; }");
          client.println("h4 { display: block; font-size: 1em; font-weight: 700; margin: 1.33em 0; }");
          client.println("h5 { didplay: block; font-size: 0.83em; font-weight: 700; margin: 1.67em; }");
          client.println("h6 { display: block; font-size: 0.67em; font-weight: 700; margin: 2.33em 0; }");
          client.println(".site-container { background: #ffffff; border: 0.063em solid #cccccc; clear: both; content: ""; display: table; margin: 0 auto; padding: 1.125em; width: 70.875em }");
          client.println(".site-header { margin-bottom: 1.125em; padding: 1.125em; }");
          client.println(".site-title, .site-description { margin: 0; padding: 0; text-align: center; }");
          client.println(".led-grid-system { text-align: center; }");
          client.println(".led-grid-system ul { float: left; list-style: none; margin: 0; padding: 0; width: 100%; }");
          client.println(".led-grid-system li { float: left; list-style: none; margin: 0; padding: 0; width: 33.33333333333333%; }");
          client.println(".led-lights { margin: 0;  padding: 0; }");
          client.println("</style>");
          client.println("</head>");
          client.println("<body>");
          client.println("<section class=\"site-container\">");
          client.println("<header class=\"site-header\">");
          client.println("<h1 class=\"site-title\">86Duino (Educake)</h1>");
          client.println("<h3 class=\"site-description\">LED Lights (Web Control)</h3>");
          client.println("</header>");
          client.println("<div class=\"led-grid-system\">");
          client.println("<ul>");
          client.println("<li>");
          client.println("<h2 class=\"led-lights\">Red LED Light</h2>");
          client.println("<p>Click to turn on and off the Red LED Light.</p>");
          client.println("<form method=\"get\">");
          redLED_Checkbox(client);          
          client.println("</form>");
          client.println("</li>");
          client.println("<li>");
          client.println("<h2 class=\"led-lights\">Yellow LED Light</h2>");
          client.println("<p>Click to turn on and off the Yellow LED Light.</p>");
          client.println("<form method=\"get\">");
          yellowLED_Checkbox(client);          
          client.println("</form>");
          client.println("</li>");
          client.println("<li>");
          client.println("<h2 class=\"led-lights\">Green LED Light</h2>");
          client.println("<p>Click to turn on and off the Green LED Light.</p>");
          client.println("<form method=\"get\">");
          greenLED_Checkbox(client);          
          client.println("</form>");
          client.println("</li>");
          client.println("</ul>");
          client.println("</div>");
          client.println("</section>");
          client.println("</body>");
          client.println("</html>");
          Serial.print(http_request);
          http_request = "";
          break;
        }

        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
  }
}

/*
================================================================================================
 5.0 - redLED Checkbox
================================================================================================
*/
void redLED_Checkbox(EthernetClient cl) {
    if (http_request.indexOf("redLED=2") > -1) {
        if (redLED_status) {
            redLED_status = 0;
        }
        else {
            redLED_status = 1;
        }
    }
    
    if (redLED_status) {
        digitalWrite(redLED, HIGH);
        cl.println("<input type=\"checkbox\" name=\"redLED\" value=\"2\" \onclick=\"submit();\" checked>LED ON");
    }
    else {
        digitalWrite(redLED, LOW);
        cl.println("<input type=\"checkbox\" name=\"redLED\" value=\"2\" \onclick=\"submit();\">LED OFF");
    }
}

/*
================================================================================================
 6.0 - yellowLED Checkbox
================================================================================================
*/
void yellowLED_Checkbox(EthernetClient cl) {
    if (http_request.indexOf("yellowLED=2") > -1) {
        if (yellowLED_status) {
            yellowLED_status = 0;
        }
        else {
            yellowLED_status = 1;
        }
    }
    
    if (yellowLED_status) {
        digitalWrite(yellowLED, HIGH);
        cl.println("<input type=\"checkbox\" name=\"yellowLED\" value=\"2\" \onclick=\"submit();\" checked>LED ON");
    }
    else {
        digitalWrite(yellowLED, LOW);
        cl.println("<input type=\"checkbox\" name=\"yellowLED\" value=\"2\" \onclick=\"submit();\">LED OFF");
    }  
}

/*
================================================================================================
 7.0 - greenLED Checkbox
================================================================================================
*/
void greenLED_Checkbox(EthernetClient cl) {
    if (http_request.indexOf("greenLED=2") > -1) {
        if (greenLED_status) {
            greenLED_status = 0;
        }
        else {
            greenLED_status = 1;
        }
    }
    
    if (greenLED_status) {
        digitalWrite(greenLED, HIGH);
        cl.println("<input type=\"checkbox\" name=\"greenLED\" value=\"2\" \onclick=\"submit();\" checked>LED ON");
    }
    else {
        digitalWrite(greenLED, LOW);
        cl.println("<input type=\"checkbox\" name=\"greenLED\" value=\"2\" \onclick=\"submit();\">LED OFF");
    }  
}
