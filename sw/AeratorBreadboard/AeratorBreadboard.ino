// *****  Test Script for Faucet Aerator *****
#define aref_voltage 3.3
#define in_pin A0
#define red 9
#define green 5
#define blue 6

int rawTemp = 0;
float filteredTempDegC = 0;

void setup() {

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  Serial.begin(9600);
  analogReference(EXTERNAL);
}

void loop() {
  // rawTemp = analogRead(in_pin);
  // Serial.print("rawTemp:");
  // Serial.print(rawTemp);
  // Serial.print(",");

  // float voltage = rawTemp * aref_voltage;
  // voltage /= 1024.0;
  // Serial.print("Voltage:");
  // Serial.print(voltage);
  // Serial.print(",");

  // float rawTempDegC = (voltage - 0.5) * 100;
  // Serial.print("Temp(C):");
  // Serial.print(rawTempDegC);
  // Serial.print(",");

  // filteredTempDegC = (rawTempDegC * (1-alpha)) + (filteredTempDegC * alpha);
  float Temperture = ReadTemp(in_pin);
  Serial.print("TempFiltered(C):");
  Serial.println(Temperture);
  // Serial.print(",");
  if (Temperture >= 40) {
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    blink(red);
  }
  else if (Temperture >= 20) {
    analogWrite(red, int((255/20)*(Temperture-20)));
    analogWrite(green, int((255/20)*(20-(Temperture-20))));
    digitalWrite(blue, LOW);
  }
  else if (Temperture > 5) {
    analogWrite(green, int((255/15)*(Temperture-5)));
    analogWrite(blue, int((255/15)*(15-(Temperture-5))));
    digitalWrite(red, LOW);
  }
  else {
    digitalWrite(blue, HIGH);
  }

  // Beep every 30 seconds while on
  if (millis()>2000 && millis()%30000<=10) {
    tone(3,600,1000);
  }

  delay(10);
}

// Function to get temperture with 3.3v reference
float ReadTemp(int pin) {
  float alpha = 0.25;

  rawTemp = analogRead(pin);
  float voltage = rawTemp * aref_voltage;
  voltage /= 1024.0;
  float rawTempDegC = (voltage - 0.5) * 100;
  filteredTempDegC = (rawTempDegC * (1-alpha)) + (filteredTempDegC * alpha);
  return filteredTempDegC;
}

void blink(int pin) {
  if (int(millis()/620)%2 == 0) {
    digitalWrite(pin, HIGH);
  }
  else {
    digitalWrite(pin, LOW);
  }
}