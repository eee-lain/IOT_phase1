#include<WiFi.h>
#include<ThingSpeak.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
char ssid[]="Wokwi-GUEST";
char pass[]="";
WiFiClient client;
unsigned long  myChannelNumber=2326366;
const char* myWriteAPIKey="W99IL4JFKFZKTP7L";
int statusCode;
#define DHTPIN 2          
#define DHTTYPE DHT22     
#define light 8
DHT dht(DHTPIN, DHTTYPE); 
//Variables:
float H; //Humidity value
float T; //Temperature value

//Initialize LCD and DHT22 sensor:
void setup() {
  lcd.init();
  lcd.backlight();
  dht.begin();
  pinMode(light,OUTPUT);
  // Print some text in Serial Monitor
  Serial.begin(9600);
  Serial.println("DHT22 sensor with Arduino Uno R3!");
    ThingSpeak.begin(client);
}

void loop() {
  delay(2000);
  // Read data and store it to variables humidity and temperature
  H = dht.readHumidity();
  T = dht.readTemperature();

  // Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(H);
  Serial.println(" %; ");
  Serial.print("Temperature: ");
  Serial.print(T);
  Serial.println(" Celsius.\n");

  if (H >= 70.00 && T >= 30.00) {
    digitalWrite(light,HIGH);
    lcd.println("   Too warm!    ");
    lcd.setCursor(0, 1);
    lcd.println("   Cool down!   ");
    lcd.setCursor(0, 0);
    delay(2000);
    digitalWrite(light,LOW);
  } 
else {
    lcd.println("Temp & humi is");
    lcd.setCursor(0, 1);
    lcd.println("in normal limits");
    lcd.setCursor(0, 0);
  }
  if (H < 70.00 && T >= 30.00) {
    lcd.println("Be ware!        ");
    lcd.setCursor(0, 1);
    lcd.println("Temp. too high! ");
    lcd.setCursor(0, 0);
  }
  if (H >= 70.00 && T < 30.00) {
    lcd.println("Be ware!" );
  }
  if(WiFi.status()!=WL_CONNECTED)
  {
    Serial.println("Attempting to connect");
    while(WiFi.status()!=WL_CONNECTED)
    {
      WiFi.begin(ssid,pass);
      Serial.print(".");
      delay(5000);
    
    }

  }
   Serial.println("\nConnected");
   ThingSpeak.setField(1,H);
   ThingSpeak.setField(2,T);
   statusCode=ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey);
   if(statusCode==200)
    {
       Serial.println("Channel update successful");
    }
   else
    {   
       Serial.println("Problem waiting data:HTTp error code:"+String(statusCode));
     }
     delay((15000));
}

