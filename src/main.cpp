#include <Arduino.h>

#define RS485_RX_PIN 10 
#define RS485_TX_PIN 9                                                                                                                                                         // Chân đọc tín hiệu RS485
#define CONTROL_PIN 4                                                                                                                                                           // Chân xuất tín hiệu điều khiển
#define BAUD_RATE 9600                                                                                                                                                          // Tốc độ truyền của RS485
#define KEY_C "9f1c3b5e7f3e4d9b2a1f8c3d5b6a7e8c3f2e1d4c5b6a7e8f9a1b2c3d4e5f6a7"                                                                                                 // Giá trị close key cần so sánh
#define KEY_O "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9eyJ1c2VyX2lkIjoxMjMsInVzZXJuYW1lIjoiZXhhbXBsZV91c2VyIiwiZXhwIjoxNjgzOTkwNjk2fQLB"                                             // Giá trị open key cần so sánh
HardwareSerial RS485Serial(1);                                                                                                                                                  // Khởi tạo UART1

String receivedData = "";

void setup()
{
  RS485Serial.begin(BAUD_RATE, SERIAL_8N1, RS485_RX_PIN, RS485_TX_PIN);
  Serial.begin(9600);
  Serial.println("RS485 Listener Started");
  pinMode(CONTROL_PIN, OUTPUT);
  pinMode(8, OUTPUT); // Chân LED tích hợp
  digitalWrite(CONTROL_PIN, LOW); // Ban đầu xuất mức thấp
}

void loop()
{
  if (RS485Serial.available())
  {
    char incomingByte = RS485Serial.read();
    if (incomingByte == '\0')
    {
      if (receivedData.equals(KEY_C))
      {
        Serial.println("Close key matched! Setting GPIO4 HIGH.");
        digitalWrite(CONTROL_PIN, HIGH);
      }
      else if (receivedData.equals(KEY_O))
      {
        Serial.println("Open key matched! Setting GPIO4 LOW.");
        digitalWrite(CONTROL_PIN, LOW);
      }
      else{
        Serial.println("Nothing.");
        digitalWrite(8, HIGH); // turn the LED on
        delay(1000); // wait for a second
        digitalWrite(8, LOW); // turn the LED off
        delay(1000); // wait for a second
      }
      receivedData = ""; // Reset buffer
    }
    else
    {
      receivedData += incomingByte;
    }
  }
}