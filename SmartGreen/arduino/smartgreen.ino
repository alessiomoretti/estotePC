#include <SPI.h>
#include <Ethernet.h>

/* definitions of the soil moisture pins - 2*digital + 3*analog */
#define voltageFlipPin1   6
#define voltageFlipPin2   7
// voltage flip to prevent the electrolitical defiance
#define sensorPinA        0
#define sensorPinB        1
#define sensorPinC        2

/* definitions of the temperature sensors pins - 3*analog */
#define temperaturePinA   3
#define temperaturePinB   4
#define temperaturePinC   5

/* soil moisture mapping - may change due to soil characteristics */
#define GREEN             500
#define YELLOW            800
/* soil moisture led alert - the led will be turned on if humidity is on "red" condition */
#define alertA            8
#define alertB            9
#define alertC            10

/* sleeping time for the EthernetShield and for the temperature retrieving */
#define ETHERNET_SETUP    5000
#define ETHERNET_CLIENT   1000
#define SENSOR_READ		    3000

/* other useful constants */
#define BAUD_RATE 		    9600
#define ANALOG_MOIST_MAP  1023
#define MOIST_FLIP_TIMER  3000
#define TEMP_CONVERSION   0.488

#define ETHERNET_DEBUG    false
#define SERVER_PORT       8080

/* initializing useful variables for moisture reading */
int moistA;
int moistB;
int moistC;

/* initializing useful variables for temperature reading */
float temperatureA;                  // final temperature reading
float temperatureB; 
float temperatureC;
int analogTemperatureA;              // temperature retrieved from the sensor
int analogTemperatureB;
int analogTemperatureC;

/* initializing useful variables for client operations */
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,104);
IPAddress server(192,168,1,100);
EthernetClient client;

String data = "";
char inChar;

/* SETUP */
void setup() {
	Serial.begin(BAUD_RATE);

	// soil moisture sensor 
	pinMode(voltageFlipPin1, OUTPUT);
  	pinMode(voltageFlipPin2, OUTPUT);
  	pinMode(sensorPinA     , INPUT);
  	pinMode(sensorPinB     , INPUT);
  	pinMode(sensorPinC     , INPUT);

  	// temperature sensor 
  	pinMode(temperaturePinA, INPUT);
  	pinMode(temperaturePinB, INPUT);
  	pinMode(temperaturePinC, INPUT);


  	// EthernetShield setup delay
  	delay(ETHERNET_SETUP);
  	// EthernetShield setup
  	Ethernet.begin(mac, ip);
}


/* LOOP */
void loop() {
	// NB: all the cycle in a flip_timer range
	// resetting data
	data = "";

	// soil moisture polarity - electrolitical avoidance
	setSensorPolarity(true);
    
  // soil moisture 
  moistA = analogRead(sensorPinA);
  moistB= analogRead(sensorPinB);
  moistC = analogRead(sensorPinC);
    
  data += "moistA=" + moistureValue(moistA, alertA) 
    	 + "&moistB=" + moistureValue(moistB, alertB) 
    	 + "&moistC=" + moistureValue(moistC, alertC);

  // temperature
  analogTemperatureA = analogRead(temperaturePinA);
  analogTemperatureB = analogRead(temperaturePinB);
  analogTemperatureC = analogRead(temperaturePinC);
  
  temperatureA = analogTemperatureA * TEMP_CONVERSION;
  temperatureB = analogTemperatureB * TEMP_CONVERSION;
  temperatureC = analogTemperatureC * TEMP_CONVERSION;

  data += "&tempA=" + String(temperatureA) 
  	   + "&tempB=" + String(temperatureB) 
  	   + "&tempC=" + String(temperatureC);

  // soil moisture polarity - electrolitical avoidance
  setSensorPolarity(false);

  // ethernet
  HTTP_POSTRequest(data);

  // serial monitoring
  Serial.println(String(moistA) + "\t\t" 
  		         + String(moistB) + "\t\t" 
  		         + String(moistC) + "\t\t");
  Serial.println(String(temperatureA) + "\t\t" 
  		         + String(temperatureB) + "\t\t" 
  		         + String(temperatureC) + "\t\t");
  Serial.println();
}

/* SENSOR POLARITY */
void setSensorPolarity(boolean flip){
  if (flip) {
    digitalWrite(voltageFlipPin1, HIGH);
    digitalWrite(voltageFlipPin2, LOW);
  }  else {
    digitalWrite(voltageFlipPin1, LOW);
    digitalWrite(voltageFlipPin2, HIGH);
  }
}

/* MOISTURE VALUE */
String moistureValue(int moist, int alertPin) {
	if (moist <= GREEN)
    // humidity value is "green"
		return "G";
	if (moist <= YELLOW)
    // humidity value is "yellow" 
		return "Y";
	else {
    // humidity value is "red" -> turn on the led and feed the plant!
    digitalWrite(alertPin, HIGH);
		return "R";
  }
}

/* HTTP POST REQUEST */
void HTTP_POSTRequest(String params) {
    
  if (client.connect(server, SERVER_PORT)) {
    if (ETHERNET_DEBUG) 
    	Serial.println("CONNECTION");

    client.println("POST /gamerland/data.php HTTP/1.1");
    client.println("Host: 192.168.1.100");
    client.println("User-Agent: arduino-ethernet");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.print(params.length());
    client.println();
    client.print(params);
  }
  
  delay(ETHERNET_CLIENT);
  while(client.available())
    {
      
      if (ETHERNET_DEBUG) {
      	Serial.write(inChar);
      	inChar = client.read();
      }
    }
  if (client.connected()) {
    client.stop();
  }
}
