#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char *SSID = "ANITAB LAB";
const char *Pass = "Akirachix@2011";
const int LED = 2;



WebServer myserver(80);
// String page(){
//   return "<h1>Welcome to my server</h1>";
// }
String page()
{
  return "<!DOCTYPE html>"
         "<html lang=\"en\">"
         "<head>"
         "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
         "<title>ESP32 Web Server</title>"
         "<style>"

         "* { "
         " margin: 0; "
         " padding: 0; "
         " box-sizing: border-box; "
         " font-family: -apple-system, BlinkMacSystemFont, sans-serif; "
         "}"

         "body { "
         "background: linear-gradient(135deg, #4d7cc3, #254070); "
         "min-height: 100vh; "
         "display: flex; "
         "justify-content: center; "
         "align-items: center; "
         "padding: 20px; "
         "}"
         "body h1 { "
         "bottom: 60%; "
         "}"

         ".box { "
         "background: rgba(255, 255, 255, 0.08); "
         "backdrop-filter: blur(20px); "
         " -webkit-backdrop-filter: blur(20px); "
         "border-radius: 28px; "
         "padding: 32px; "
         "width: 100%; "
         "max-width: 420px; "
         "border: 1px solid rgba(255, 255, 255, 0.12); "
         "box-shadow: 0 12px 40px rgba(0, 0, 0, 0.2); "
         "color: white; "
         "text-align: center;"
         " }"

         ".box h1 {"
         " font-size: 24px;"
         " font-weight: 600;"
         " margin-bottom: 24px;"
         " }"

         " .box .container { "
         "border-top: 1px solid rgba(255, 255, 255, 0.12) !important;"
         "padding: 16px 20px !important; "
         "display: grid !important;"
         "grid-template-columns: 1fr 1fr !important; /* Fixed the broken css- prefix */"
         "gap: 16px !important; "
         "align-items: center;"
         "text-align: left;"
         "background: rgba(255, 255, 255, 0.03);"
         "border-radius: 12px;"
         "margin-bottom: 12px;"
         " }"

         ".box .container p {"
         " font-size: 14px;"
         " grid-column: span 2; "
         "  color: rgba(255, 255, 255, 0.9);"
         "}"
         "</style>"

         "</head>"
         "<body>"
         "<a href=\"/me\">Click here to turn on the LED</a>"
         "<h1>Welcome to my server:   </h1>"
         "<div class=\"box\" >"
         "<div class=\"container\">"
         "<p>This is a simple web server running on ESP32.</p>"
         "</div>"
         "<div class=\"container\">"
         "<p>Connected to WiFi: " +
         WiFi.SSID() + "</p>"
                       "</div>"
                       "<div class=\"container\">"
                       "<p>IP Address: " +
         WiFi.localIP().toString() + "</p>"
        "</div>"
        "</div>"
        "</body>"
        "</html>";
}

void handleRoot()
{
  myserver.send(200, "text/html", page());
}

void handleMe(){
  digitalWrite(LED, HIGH);
  myserver.sendHeader("Location", "/");
  myserver.send(303);
}

void setup()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, Pass);
  myserver.on("/", handleRoot);
  myserver.on("/me", handleMe);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  myserver.begin();
  Serial.begin(115200);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("connecting to WiFi.....");
  }
  Serial.println(WiFi.localIP());
}

void loop()
{
  myserver.handleClient();
}
