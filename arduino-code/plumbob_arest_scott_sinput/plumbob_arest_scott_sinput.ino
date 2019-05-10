// Import required libraries
#include <ESP8266WiFi.h>
#include <aREST.h>

// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid = "bort";
const char* password = "34tingisnice";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Define emotion as 5 ("Ok") intitially (Other emotions go from 1-4)
int emotion = 5;

// Define RGB pins
int redPin = 2;
int greenPin = 5;
int bluePin = 4;

// If RGB LED is Common Anode
#define COMMON_ANODE

// Declare custom functions
int getEmotion(String emptyCommand);
int lightEmotion(String emotion); // This one takes in an int (1-5) value

void setup(void)
{
  // Start Serial
  Serial.begin(9600);

  // Set RGB pins as output pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Function to be exposed
  // http://myip/get?params=r
  rest.function("get", getEmotion);
  // http://myip/light?params=value
  rest.function("light", lightEmotion);

  // Give name & ID to the device (ID should be 6 characters long)
  rest.set_id("1");
  rest.set_name("esp8266");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {

  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  rest.handle(client); // This should handle the "loop" checking for input values; aREST handles this for us
}

int getEmotion(String emptyCommand) {

  // If data is available to read,
  if (Serial.available() > 0) {

    // find the int within it
    int inByte = Serial.parseInt();

    // if its more than 0, cut up the inbound message
    if (inByte > 0) {
      emotion = inByte;
      Serial.println();
      Serial.print(emotion);
    }
  }
  return emotion;

}

// Corresponding Sims 4 plumbob colors
int lightEmotion(String emotion) {
  int emo = emotion.toInt();
  
  if (emo == 1) {
    setColor(1024, 0, 0); // Red (Angry)
    Serial.println("angry");
  } else if (emo == 2) {
    setColor(1024, 400, 0);  // Orange (Sad)
    Serial.println("sad");
  } else if (emo == 3) {
    setColor(512, 512, 512); // White (Surprised)
    Serial.println("normal");
  } else if (emo == 4) {
    setColor(0, 1024, 0); // Green (Happy)
    Serial.println("happy");
  } else if (emo == 5) {
    setColor(1024, 840, 0);  // Yellow (Ok)
    Serial.println("ok");
  }
  return 1;
}

// ACTUALLY set the color
void setColor(int red, int green, int blue) {

  red = 1023 - red;
  green = 1023 - green;
  blue = 1023 - blue;

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
 
}
