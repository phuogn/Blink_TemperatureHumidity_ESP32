#include <Adafruit_NeoPixel.h>
#include <DHT20.h>
#include <LiquidCrystal_I2C.h>

// Define your tasks here
void TaskBlink(void *pvParameters);
void TaskTemperatureHumidity(void *pvParameters);
void TaskSoilMoistureAndRelay(void *pvParameters);
void TaskLightAndLED(void *pvParameters);

// Define your components here
Adafruit_NeoPixel pixels3(4, D5, NEO_GRB + NEO_KHZ800);
DHT20 dht;
LiquidCrystal_I2C lcd(0x21, 16, 2);

void setup() {
  // Initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  dht.begin();
  lcd.begin();
  pixels3.begin();
  
  xTaskCreate(TaskBlink, "Task Blink", 2048, NULL, 2, NULL);
  xTaskCreate(TaskTemperatureHumidity, "Task Temperature", 2048, NULL, 2, NULL);
  xTaskCreate(TaskSoilMoistureAndRelay, "Task Soild Relay", 2048, NULL, 2, NULL);
  xTaskCreate(TaskLightAndLED, "Task Light LED", 2048, NULL, 2, NULL);
  
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
                      
    Serial.println("Task Temperature and Humidity");
    dht.read();
    Serial.println(dht.getTemperature());
    Serial.println(dht.getHumidity());

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

void TaskSoilMoistureAndRelay(void *pvParameters) {  // This is a task.
  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(D3, OUTPUT);

  while(1) {   
    Serial.println("Task Soild and Relay");
    // Serial.println(analogRead(A0));

    if (analogRead(A0) > 500) {
      digitalWrite(D3, LOW);
    }                       
    if (analogRead(A0) < 50) {
      digitalWrite(D3, HIGH);
    }
   
    delay(1000);
  }
}

void TaskLightAndLED(void *pvParameters) {  // This is a task.
  while(1) {        
                      
    Serial.println("Task Light and LED");
    Serial.println(analogRead(A1));

    if (analogRead(A1) > 550) {
      pixels3.setPixelColor(0, pixels3.Color(0,0,0));
      pixels3.setPixelColor(1, pixels3.Color(0,0,0));
      pixels3.setPixelColor(2, pixels3.Color(0,0,0));
      pixels3.setPixelColor(3, pixels3.Color(0,0,0));
      pixels3.show();
    }
    if (analogRead(A1) < 350) {
      pixels3.setPixelColor(0, pixels3.Color(255,0,0));
      pixels3.setPixelColor(1, pixels3.Color(255,0,0));
      pixels3.setPixelColor(2, pixels3.Color(255,0,0));
      pixels3.setPixelColor(3, pixels3.Color(255,0,0));
      pixels3.show();
    }

    delay(5000);
  }
}