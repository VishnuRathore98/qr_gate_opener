#include <Arduino.h>
#include <ESP32QRCodeReader.h>


ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);

String valid1 = "12345";
String valid2 = "67890";
int led_flash = 4;

int motor_in_1 = 14;
int motor_in_2 = 15;
int motor_en = 13;

void onQrCodeTask(void *pvParameters) {
  struct QRCodeData qrCodeData;

  while (true) {
    if (reader.receiveQrCode(&qrCodeData, 100)) {
      Serial.println("Scanned new QRCode");
      if (qrCodeData.valid) {
        if(String((const char *)qrCodeData.payload)==valid1 || String((const char *)qrCodeData.payload)==valid2){
        Serial.print("Valid payload: ");
        digitalWrite(led_flash, HIGH);
        delay(1000);
        digitalWrite(led_flash, LOW);

     digitalWrite(motor_in_1, LOW);
  digitalWrite(motor_in_2, LOW);
  digitalWrite(motor_en, LOW);  

 digitalWrite(motor_in_1, HIGH);
  digitalWrite(motor_in_2, LOW);
  delay(500);

  // Stop
  digitalWrite(motor_in_1, LOW);
  digitalWrite(motor_in_2, LOW);
  delay(500);

          // Test reverse
  digitalWrite(motor_in_1, LOW);
  digitalWrite(motor_in_2, HIGH);
  delay(500);

  // Stop
  digitalWrite(motor_in_1, LOW);
  digitalWrite(motor_in_2, LOW);
        Serial.println((const char *)qrCodeData.payload);
        }


      }
      else {
        Serial.print("Invalid payload: ");


        Serial.println((const char *)qrCodeData.payload);
      }
      // always stop motor if not matching
digitalWrite(motor_in_1, LOW);
digitalWrite(motor_in_2, LOW);

    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(motor_in_1, OUTPUT);
  pinMode(motor_in_2, OUTPUT);
  pinMode(motor_en, OUTPUT);

  pinMode(led_flash, OUTPUT);

  digitalWrite(motor_in_1, LOW);
  digitalWrite(motor_in_2, LOW);

  // Test forward
  digitalWrite(motor_in_1, HIGH);
  digitalWrite(motor_in_2, LOW);
  digitalWrite(motor_en, HIGH);
  delay(1000);

  // Stop
  digitalWrite(motor_in_1, LOW);
  digitalWrite(motor_in_2, LOW);
  digitalWrite(motor_en, LOW);
  delay(500);

  // Test reverse
  digitalWrite(motor_in_1, LOW);
  digitalWrite(motor_in_2, HIGH);
  digitalWrite(motor_en, HIGH);
  delay(1000);

  // Stop
  digitalWrite(motor_en, LOW);
  digitalWrite(motor_in_1, LOW);
  digitalWrite(motor_in_2, LOW);

  Serial.println();

  reader.setup();
  Serial.println("Setup QRCode Reader");

  reader.beginOnCore(1);
  Serial.println("Begin on Core 1");

  xTaskCreate(onQrCodeTask, "onQrCode", 4 * 1024, NULL, 4, NULL);
}

void loop() {
  delay(100);
}
