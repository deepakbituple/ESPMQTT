#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Change the credentials below, so your ESP8266 connects to your router
#ifndef STASSID
#define STASSID "dlink3202"
#define STAPSK "123a3202"
#define DEVICE_ID "EC-LB-100-5110-01"
#endif

const char *mqtt__broker_ip = "db1rp5.local";
const int mqtt__broker_port = 1883;
// MQTT broker credentials (set to NULL if not required)
const char *MQTT_username = NULL;
const char *MQTT_password = NULL;

const char *mqtt_topic_pub = "loadbnk/DEV01_STATUS";
const char *mqtt_topic_subopc1 = "loadbnk/DEV01_OPCOMMAND1";
const char *mqtt_topic_subopc2 = "loadbnk/DEV01_OPCOMMAND2";
const char *mqtt_topic_subopc3 = "loadbnk/DEV01_OPCOMMAND3";
const char *mqtt_topic_subopc4 = "loadbnk/DEV01_OPCOMMAND4";
const char *mqtt_topic_subopc5 = "loadbnk/DEV01_OPCOMMAND5";
const char *mqtt_topic_subopc6 = "loadbnk/DEV01_OPCOMMAND6";
const char *mqtt_topic_subopc7 = "loadbnk/DEV01_OPCOMMAND7";
const char *mqtt_topic_subopc8 = "loadbnk/DEV01_OPCOMMAND8";
const char *mqtt_topic_subopc9 = "loadbnk/DEV01_OPCOMMAND9";

// Initializes the espClient. You should change the espClient name if you have multiple ESPs running in your home automation system
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

long now = millis();
long lastMeasure = 0;

// This functions connects your ESP8266 to your router
void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(STASSID);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

// This function is executed when some device publishes a message to a topic that your ESP8266 is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that
// your ESP8266 is subscribed you can actually do something
void callback(String topic, byte *message, unsigned int length)
{
  // Serial.print("Message arrived on topic: ");
  // Serial.print(topic);
  // Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    // Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  if (topic == mqtt_topic_subopc1)
  {
    Serial.println("{'OPCOMMAND1': '" + messageTemp + "'}");
  }
  else if (topic == mqtt_topic_subopc2)
  {
    Serial.println("{'OPCOMMAND2': '" + messageTemp + "'}");
  }
  else if (topic == mqtt_topic_subopc3)
  {
    Serial.println("{'OPCOMMAND3': '" + messageTemp + "'}");
  }
  else if (topic == mqtt_topic_subopc4)
  {
    Serial.println("{'OPCOMMAND4': '" + messageTemp + "'}");
  }
  else if (topic == mqtt_topic_subopc5)
  {
    Serial.println("{'OPCOMMAND5': '" + messageTemp + "'}");
  }
  else if (topic == mqtt_topic_subopc6)
  {
    Serial.println("{'OPCOMMAND6': '" + messageTemp + "'}");
  }
  else if (topic == mqtt_topic_subopc7)
  {
    Serial.println("{'OPCOMMAND7': '" + messageTemp + "'}");
  }
  else if (topic == mqtt_topic_subopc8)
  {
    Serial.println("{'OPCOMMAND8': '" + messageTemp + "'}");
  }
  else if (topic == mqtt_topic_subopc9)
  {
    Serial.println("{'OPCOMMAND9': '" + messageTemp + "'}");
  }
}

// This functions reconnects your ESP8266 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP8266
void reconnectMQTTClient()
{
  // Loop until we're reconnected
  while (!mqttClient.connected())
  {
    Serial.print("Attempting MQTT connection..." + String(DEVICE_ID));
    // Attempt to connect

    if (mqttClient.connect(DEVICE_ID, MQTT_username, MQTT_password))
    {
      Serial.println("connected");
      // You can subscribe to more topics (to control more LEDs in this example)
      mqttClient.subscribe(mqtt_topic_subopc1);
      mqttClient.subscribe(mqtt_topic_subopc2);
      mqttClient.subscribe(mqtt_topic_subopc3);
      mqttClient.subscribe(mqtt_topic_subopc4);
      mqttClient.subscribe(mqtt_topic_subopc5);
      mqttClient.subscribe(mqtt_topic_subopc6);
      mqttClient.subscribe(mqtt_topic_subopc7);
      mqttClient.subscribe(mqtt_topic_subopc8);
      mqttClient.subscribe(mqtt_topic_subopc9);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 3 seconds");
      // Wait 3 seconds before retrying
      delay(3000);
    }
  }
}

// The setup function sets your ESP GPIOs to Outputs, starts the serial communication at a baud rate of 115200
// Sets your mqtt broker and sets the callback function
// The callback function is what receives messages and actually controls the LEDs
void setup()
{

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); // Main LED

  setup_wifi();
  mqttClient.setServer(mqtt__broker_ip, mqtt__broker_port);
  mqttClient.setCallback(callback);
}

void blinkMainLed()
{
  digitalWrite(LED_BUILTIN, LOW);
  delay(10);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(10);
}

// For this project, you don't need to change anything in the loop function. Basically it ensures that you ESP is connected to your broker
void loop()
{

  if (!mqttClient.connected())
  {
    reconnectMQTTClient();
  }

  //
  if (!mqttClient.loop())
    mqttClient.connect(DEVICE_ID, MQTT_username, MQTT_password);

  if (Serial.available() > 0)
  {
    // printDebug("inside seriel available");
    blinkMainLed();

    String jsonString = Serial.readStringUntil('\n');
    String debug = "Got something on serial" + jsonString;
    // printDebug(debug);

    // callAPI(jsonString);

    mqttClient.publish(mqtt_topic_pub, jsonString.c_str());
    blinkMainLed();
  }
}