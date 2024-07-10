#include <Adafruit_NeoPixel.h>
#include <DHT20.h>
#include <LiquidCrystal_I2C.h>

// Define your tasks here
void TaskBlink(void *pvParameters);
void TaskTemperatureHumidity(void *pvParameters);

// Define your components here
Adafruit_NeoPixel pixels3(4, D3, NEO_GRB + NEO_KHZ800);
DHT20 dht;
LiquidCrystal_I2C lcd(0x21, 16, 2);

void setup() {
  // Initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  // Initialize the DHT sensor
  dht.begin();

  //Initialize the LCD
  lcd.init();
  // Turn on the blacklight
  lcd.backlight();
  
  xTaskCreate(TaskBlink, "Task Blink", 2048, NULL, 2, NULL);
  xTaskCreate(TaskTemperatureHumidity, "Task Temperature", 2048, NULL, 2, NULL);
  
  // Now the task scheduler is automatically started.
  Serial.printf("Basic Multi Threading Arduino Example\n");
}

void loop() {
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters) {  // This is a task.
  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  while(1) {                          
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED ON
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED OFF
    delay(200);
  }
}

void TaskTemperatureHumidity(void *pvParameters) {  // This is a task.
  while(1) {        
                      
    dht.read();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperature: ");
    lcd.print((dht.getTemperature()));
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print((dht.getHumidity()));
    delay(5000);
  }
}