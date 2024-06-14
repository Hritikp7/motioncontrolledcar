#include <SoftwareSerial.h>

// Bluetooth serial pins
SoftwareSerial myBluetooth(2, 3);  // RX, TX


// Pins for the Hall sensors and ADXL axes
const int hallSensor01 = 4;
const int hallSensor02 = 5;
const int adxl_X = A0;  // ADXL X-axis
const int adxl_Y = A1;  // ADXL Y-axis

// Variables to store sensor states
int hallSensor01State = 0;
int hallSensor02State = 0;
int adxl_X_Reading = 0;
int adxl_Y_Reading = 0;

void setup() {
  // Initialize pin modes
  pinMode(adxl_X, INPUT);
  pinMode(adxl_Y, INPUT);
  pinMode(hallSensor01, INPUT);
  pinMode(hallSensor02, INPUT);

  // Initialize serial communication
  myBluetooth.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // Read the ADXL sensor values
  adxl_X_Reading = analogRead(adxl_X);
  adxl_Y_Reading = analogRead(adxl_Y);

  // Read the Hall sensor states
  hallSensor01State = digitalRead(hallSensor01);
  hallSensor02State = digitalRead(hallSensor02);

  // Debugging output to the serial monitor
  Serial.print("X: ");
  Serial.println(adxl_X_Reading);
  delay(500);
  Serial.print("Y: ");
  Serial.println(adxl_Y_Reading);
  delay(500);

  // Control logic based on sensor states and ADXL readings
  if (hallSensor01State == LOW) {
    if (adxl_Y_Reading >= 375) {
      myBluetooth.write("U"); 
      Serial.println("SERVO2 ROTATE UP"); 
    } else if (adxl_Y_Reading <= 320) {
      myBluetooth.write("D");
      Serial.println("SERVO2 ROTATE DOWN");
    } else if (adxl_X_Reading >= 375) {
      myBluetooth.write("r");
      Serial.println("SERVO0 ROTATE LEFT");
    } else if (adxl_X_Reading <= 315) {
      myBluetooth.write("l");
      Serial.println("SERVO0 ROTATE RIGHT");
    }
  } else if (hallSensor02State == LOW) {
    if (adxl_X_Reading <= 300) {
      myBluetooth.write("O");  // Open command
      Serial.println("SERVO3 OPEN CLIPPER");
    } else if (adxl_X_Reading >= 370) {
      myBluetooth.write("C");  // Close command
      Serial.println("SERVO3 CLOSE CLIPPER");
    }
  } else {
    if (adxl_Y_Reading >= 375) {
      myBluetooth.write("F");  // Forward command
      Serial.println("FORWARD");
    } else if (adxl_Y_Reading <= 320) {
      myBluetooth.write("B");  // Backward command
      Serial.println("BACKWARD");
    } else if (adxl_X_Reading >= 375) {
      myBluetooth.write("R");  // Right command
      Serial.println("RIGHT");
    } else if (adxl_X_Reading <= 315) {
      myBluetooth.write("L");  // Left command
      Serial.println("LEFT");
    }else{
      myBluetooth.write("N");  // Left command
      Serial.println("NEUTRAL");
    }
    delay(1000);
  }
}
