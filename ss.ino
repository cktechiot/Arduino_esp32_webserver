#include <WiFi.h>


const char* ssid = "AP solar";
const char* password = "123456789";

WiFiServer server(80);
// AsyncWebServer server(80);
String header;

String output26State = "off";

//----------------------------------
const int SolarPin = 34;
const int BattPin = 35;
int pirPin = 19;
int pir = 0;

int SolarValue = 0;
int BattValue = 0;
//---------------------------------------------------
const int ledPin2 = 2;
const int ledPin = 26;
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
//---------------------------------------------
unsigned long startTime;
unsigned long stopTime;
int hours, minutes, seconds;
boolean stopCounting = false;
//--------------------------------------------------
int dim = 0;
int t1 = 60;
int t2 = 55;
int t3 = 50;
int t4 = 40;
int t5 = 0;
int t11 = t1 + 50;
int t22 = t2 + 50;
int t33 = t3 + 50;
int t44 = t4 + 50;

int value = 0;
String st = "off";
String tx = " ";
String ma = "off";

int solar_off = 700;


void setup() {

  Serial.begin(115200);
  startTime = millis();
  // Initialize the output variables as outputs
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);
  pinMode(ledPin2, HIGH);
  pinMode(pirPin, INPUT);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);


  server.begin();
}

void setLEDBrightness(int dim1) {
  ledcWrite(ledChannel, dim1);
}

void pirx() {
  if (pir != 0) {
    dim = dim - 100;

    delay(50000);
  } else {
    dim = dim;
  }
  setLEDBrightness(dim);
}

void web() {
  WiFiClient client = server.available();  // Listen for incoming clients

  if (client) {                     // If a new client connects,
    Serial.println("New Client.");  // print a message out in the serial port
    String currentLine = "";        // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client's connected
      if (!client.available()) {
        client.stop();
        break;
      }
      if (client.available()) {  // if there's bytes to read from the client,
        char c = client.read();  // read a byte, then
        Serial.write(c);         // print it out the serial monitor
        header += c;

        if (c == '\n') {  // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            action();


            // setLEDBrightness(dim);

            client.println("<head>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<title>Ck Web Server</title>");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>");
            client.println("html { ");
            client.println("    font-family: Helvetica;");
            client.println("    display: inline-block;");
            client.println("    margin: 0px auto;");
            client.println("    text-align: center;");
            client.println("    }");
            client.println("h1 { ");
            client.println("    color: #0f3376;");
            client.println("    padding: 2vh;");
            client.println("    }");
            client.println("p { ");
            client.println("    font-size: 1.5rem;");
            client.println("    }");
            client.println(".button { ");
            client.println("    display: inline-block;");
            client.println("    background-color: #e7bd3b;");
            client.println("    border: none;");
            client.println("    border-radius: 4px;");
            client.println("    color: white;");
            client.println("    padding: 16px 40px;");
            client.println("    text-decoration: none;");
            client.println("    font-size: 30px;");
            client.println("    margin: 2px");
            client.println("    cursor: pointer;");
            client.println("    }");
            client.println(".button2 { ");
            client.println("    display: inline-block;");
            client.println("    background-color: #4286f4;");
            client.println("    border: none;");
            client.println("    border-radius: 4px;");
            client.println("    color: white;");
            client.println("    padding: 16px 40px;");
            client.println("    text-decoration: none;");
            client.println("    font-size: 30px;");
            client.println("    margin: 2px");
            client.println("    cursor: pointer;");
            client.println("    }");
            client.println(".button3 { ");
            client.println("    display: inline-block;");
            client.println("    background-color: #41d80c;");
            client.println("    border: none;");
            client.println("    border-radius: 4px;");
            client.println("    color: white;");
            client.println("    padding: 16px 40px;");
            client.println("    text-decoration: none;");
            client.println("    font-size: 30px;");
            client.println("    margin: 2px");
            client.println("    cursor: pointer;");
            client.println("    }");
            client.println(".button5 { ");
            client.println("    display: inline-block;");
            client.println("    background-color: #3dfa16;");
            client.println("    border: none;");
            client.println("    border-radius: 4px;");
            client.println("    color: white;");
            client.println("    padding: 16px 40px;");
            client.println("    text-decoration: none;");
            client.println("    font-size: 30px;");
            client.println("    margin: 2px");
            client.println("    cursor: pointer;");
            client.println("    }");
            client.println(".button6 { ");
            client.println("    display: inline-block;");
            client.println("    background-color: #aaa4aa;");
            client.println("    border: none;");
            client.println("    border-radius: 4px;");
            client.println("    color: white;");
            client.println("    padding: 16px 40px;");
            client.println("    text-decoration: none;");
            client.println("    font-size: 30px;");
            client.println("    margin: 2px");
            client.println("    cursor: pointer;");
            client.println("    }");
            client.println(".button7 { ");
            client.println("    display: inline-block;");
            client.println("    background-color: #ff0000;");
            client.println("    border: none;");
            client.println("    border-radius: 4px;");
            client.println("    color: white;");
            client.println("    padding: 16px 40px;");
            client.println("    text-decoration: none;");
            client.println("    font-size: 30px;");
            client.println("    margin: 2px");
            client.println("    cursor: pointer;");
            client.println("    }");
            client.println(".button8 { ");
            client.println("    display: inline-block;");
            client.println("    background-color: #5800ff;");
            client.println("    border: none;");
            client.println("    border-radius: 4px;");
            client.println("    color: white;");
            client.println("    padding: 16px 40px;");
            client.println("    text-decoration: none;");
            client.println("    font-size: 30px;");
            client.println("    margin: 2px");
            client.println("    cursor: pointer;");
            client.println("    }");
            client.println("input[type=text] { ");
            client.println("    width: 25%;");
            client.println("    padding: 12px 20px;");
            client.println("    margin: 8px 0;");
            client.println("    border-box;");
            client.println("    border: 2px solid green;");
            client.println("    border-radius: 4px;");
            client.println("    }");
            client.println("input[type=submit] { ");
            client.println("    display: inline-block;");
            client.println("    background-color: #059862;");
            client.println("    border: none;");
            client.println("    border-radius: 4px;");
            client.println("    color: white;");
            client.println("    padding: 4px 20px;");
            client.println("    text-decoration: none;");
            client.println("    font-size: 15px;");
            client.println("    margin: 2px");
            client.println("    cursor: pointer;");
            client.println("    }");
            client.println("</style>");
            client.println("</head>");
            
            // Web Page Heading
            client.println("<body><h1>CK Solar Lamp</h1>");
            client.println("<img src=\"data:image/png;base64,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\">");

//            client.println("<img src=\"\">");
            client.println("<img src=\" \">");
            // Display current state, and ON/OFF buttons for GPIO 26
            if (dim >= 1) {
              tx = "ON";
            } else if (dim == 0) {
              tx = "OFF";
            }
            client.println("<p>LED " + tx + "</p>");
            client.println("<p>Brightness " + String(dim) + "</p>");
            if (st == "off") {
              client.println(" ");
            } else {
              client.println("<p>Batt " + String(BattValue) + "</p>");
              client.println("<p>Solar " + String(SolarValue) + "</p>");
            }

            if (output26State == "off") {
              client.println("<p><a href=\"/led/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/led/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("<p><a href=\"/dim/up\"><button class=\"button button8\">UP</button></a>");
            client.println("<a href=\"/dim/down\"><button class=\"button button6\">DOWN</button></a></p>");
            // client.println("<p><a href=\"/status/on\"><button class=\"button button5\">STATUS</button></a></p>");

            if (st == "off") {
              client.println("<p><a href=\"/status/on\"><button class=\"button button5\">STATUS ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/status/off\"><button class=\"button button7\">STATUS OFF</button></a></p>");
            }

            client.println("<p><a href=\"/reset/on\"><button class=\"button button7\">RESET</button></a></p>");
            client.println("<p>---------------------------------------------</p>");

            // client.println("<a href=\"/man/on\"><button class=\"button button7\">MANUAL</button></a></p>");
            if (ma == "off") {
              client.println("<a href=\"/man/on\"><button class=\"button button7\">MANUAL</button></a></p>");
            } else {
              client.println("<a href=\"/man/off\"><button class=\"button button7\">MANUAL</button></a></p>");
              client.println("<form method='get'>");
              client.println("<label>Time 1 </label>");
              client.println("<input type='text' name='t1'><label> Last : " + String(t1) + "</label><br><br>");
              client.println("<label>Time 2 </label>");
              client.println("<input type='text' name='t2'><label> Last : " + String(t2) + "</label><br><br>");
              client.println("<label>Time 3 </label>");
              client.println("<input type='text' name='t3'><label> Last : " + String(t3) + "</label><br><br>");
              client.println("<label>Time 4 </label>");
              client.println("<input type='text' name='t4'><label> Last : " + String(t4) + "</label><br><br>");
              client.println("<label>Solar_LOW </label>");
              client.println("<input type='text' name='t5'><label> Last : " + String(solar_off) + "</label><br><br>");
              client.println("<input type='submit' value='SAVE'>");
              client.println("</form>");
            }
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else {  // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void ti() {
  if (Serial.available() > 0) {
    int stopVal = Serial.parseInt();
    if (stopVal == 2) {
      stopCounting = true;
      Serial.println("Time counting stopped!");
    } else if (stopVal == 5) {
      stopCounting = false;
      startTime = stopTime;
      Serial.println("Time counting resumed!");
    } else if (stopVal == 8) {
      stopCounting = false;
      startTime = millis();
      Serial.println("Time counting started!");
    }
  }
  if (stopCounting) {
    return;
  }
}

void action() {
  // turns the GPIOs on and off
  if (header.indexOf("GET /led/on") >= 0) {
    Serial.println("GPIO 26 on");
    output26State = "on";
    dim = 60;
    t1 = 60;
    t2 = 55;
    t3 = 50;
    t4 = 40;

  } else if (header.indexOf("GET /led/off") >= 0) {
    Serial.println("GPIO 26 off");
    output26State = "off";
    dim = 0;
    t1 = 0;
    t2 = 0;
    t3 = 0;
    t4 = 0;

  } else if (header.indexOf("GET /dim/up") >= 0) {
    Serial.println("dim up");
    dim = dim + 10;
    t1 = t1 + 10;
    t2 = t2 + 10;
    t3 = t3 + 10;
    t4 = t4 + 10;

  } else if (header.indexOf("GET /dim/down") >= 0) {
    Serial.println("dim down");
    dim = dim - 10;
    t1 = t1 - 10;
    t2 = t2 - 10;
    t3 = t3 - 10;
    t4 = t4 - 10;

  } else if (header.indexOf("GET /status/on") >= 0) {
    Serial.println("status ON");
    st = "on";

  } else if (header.indexOf("GET /status/off") >= 0) {
    Serial.println("status OFF");
    st = "off";

  } else if (header.indexOf("GET /reset/on") >= 0) {
    Serial.println("reset ON");
    delay(500);
    ESP.restart();

  } else if (header.indexOf("GET /man/on") >= 0) {
    Serial.println("man ON");
    ma = "on";

  } else if (header.indexOf("GET /man/off") >= 0) {
    Serial.println("man OFF");
    ma = "off";
  }
  if (header.indexOf("GET /man/on?t1=") >= 0) {
    int t1Index = header.indexOf("t1=") + 3;
    int t2Index = header.indexOf("&t2=");
    t1 = header.substring(t1Index, t2Index).toInt();
    t2Index += 4;
    int t3Index = header.indexOf("&t3=");
    t2 = header.substring(t2Index, t3Index).toInt();
    t3Index += 4;
    int t4Index = header.indexOf("&t4=");
    t3 = header.substring(t3Index, t4Index).toInt();
    t4Index += 4;
    int t5Index = header.indexOf("&t5=");
    t4 = header.substring(t4Index, t5Index).toInt();
    t5Index += 4;
    int endIndex = header.indexOf(" HTTP");
    t5 = header.substring(t5Index, endIndex).toInt();



    Serial.println("t1: " + String(t1));
    Serial.println("t2: " + String(t2));
    Serial.println("t3: " + String(t3));
    Serial.println("t4: " + String(t4));
    Serial.println("Solar_off: " + String(t5));
    solar_off = t5;
  }
  setLEDBrightness(dim);
}

void ct() {
  // ti();
  action();
  if (stopCounting) {
    dim = 0;

    return;
  }

  unsigned long currentTime = millis();
  hours = (currentTime - startTime) / 3600000;
  minutes = ((currentTime - startTime) % 3600000) / 60000;
  seconds = ((currentTime - startTime) % 60000) / 1000;
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);

  if ((hours >= 0) && (hours <= 2)) {
    dim = t1;
    Serial.println("time 1 : Brightness " + String(dim));
    output26State = "on";
    action();
    // ti();

  } else if ((hours >= 3) && (hours < 5)) {
    dim = t2;
    Serial.println("time 2 : Brightness " + String(dim));
    output26State = "on";
    action();
    // ti();

  } else if ((hours >= 5) && (hours < 6)) {
    dim = t3;
    if (pir != 0) {
      dim = t33;
      delay(50000);
    }
    Serial.println("time 3 : Brightness " + String(dim));
    output26State = "on";
    action();
    // ti();


  } else if (hours > 6) {
    dim = t4;
    if (pir != 0) {
      dim = t44;
      delay(50000);
    }
    Serial.println("time 4 : Brightness " + String(dim));
    output26State = "on";
    action();
    // ti();
  }
  setLEDBrightness(dim);
}

void input() {
  SolarValue = analogRead(SolarPin);
  BattValue = analogRead(BattPin);
  pir = digitalRead(pirPin);
  Serial.print("Solar : ");
  Serial.println(SolarValue);
  Serial.print("Batt : ");
  Serial.println(BattValue);
  Serial.print("Pir : ");
  Serial.println(pir);
  Serial.print("Dim : ");
  Serial.println(dim);
  Serial.print("solar_off : ");
  Serial.println(solar_off);
  Serial.println(" ");
  delay(300);
}

void loop() {
  input();
  web();

  if (stopCounting) {
    startTime = millis();
    dim = 0;
    stopCounting = false;
  }
  if (SolarValue <= solar_off) {
    ct();
    web();

  } else if (SolarValue > solar_off) {
    stopCounting = true;
    // dim = 0;

  } else if (BattValue <= 1000) {
    stopCounting = true;
    // dim = 0;
  }
  setLEDBrightness(dim);
}
