#include <Arduino.h>

const int pins[] = {13, 14, 15, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33};
const int numPins = 14; // must match exactly how many pins are in the array above

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting pair scan...");
}

void loop()
{
  for (int i = 0; i < numPins; i++)
  {
    for (int j = 0; j < numPins; j++)
    {
      if (i == j)
        continue;

      int pin1 = pins[i];
      int pin2 = pins[j];

      // Safety check
      if (pin1 > 33 || pin2 > 33)
      {
        Serial.println("Skipping invalid pin!");
        continue;
      }

      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);

      Serial.print(">>> GPIO ");
      Serial.print(pin1);
      Serial.print(" HIGH + GPIO ");
      Serial.print(pin2);
      Serial.println(" LOW");

      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      delay(1500);

      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      delay(300);
    }
  }
  Serial.println("Restarting scan...");
}