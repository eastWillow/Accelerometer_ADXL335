const int xInput = A0;
const int yInput = A1;
const int zInput = A2;
const int buttonPin = 2;

// Raw Ranges:
// initialize to mid-range and allow calibration to
// find the minimum and maximum for each axis
int xRawMin = 512;
int xRawMax = 0;

int yRawMin = 512;
int yRawMax = 0;

int zRawMin = 512;
int zRawMax = 0;

// Take multiple samples to reduce noise
const int sampleSize = 100;

volatile int xRaw = 0;
volatile int yRaw = 0;
volatile int zRaw = 0;
void setup()
{
  pinMode(buttonPin, INPUT);
  analogReference(EXTERNAL);
  Serial.begin(115200);
}

void loop()
{
  while (!Serial);
  displayInfo();
  Serial.println("The calibration starts: ");
  Serial.println("1, make sure that X-axis direction is straight up");
  Serial.println("please type any charactor if you are ready");
  while (Serial.available() == 0) {
    xRaw = ReadAxis(xInput);
    yRaw = ReadAxis(yInput);
    zRaw = ReadAxis(zInput);
    delay(100);
  }
  while (Serial.available() > 0)Serial.read();
  AutoCalibrate(xRaw, yRaw, zRaw);
  displayInfo();
  Serial.println("2, make sure that Y-axis direction is straight up");
  Serial.println("please type any charactor if you are ready");
  while (Serial.available() == 0) {
    xRaw = ReadAxis(xInput);
    yRaw = ReadAxis(yInput);
    zRaw = ReadAxis(zInput);
    delay(100);
  }
  while (Serial.available() > 0)Serial.read();
  AutoCalibrate(xRaw, yRaw, zRaw);
  displayInfo();
  Serial.println("The calibration starts: ");
  Serial.println("3, make sure that Z-axis direction is straight up");
  Serial.println("please type any charactor if you are ready");
  while (Serial.available() == 0) {
    xRaw = ReadAxis(xInput);
    yRaw = ReadAxis(yInput);
    zRaw = ReadAxis(zInput);
    delay(100);
  }
  while (Serial.available() > 0)Serial.read();
  AutoCalibrate(xRaw, yRaw, zRaw);
  displayInfo();
  Serial.println("The calibration starts: ");
  Serial.println("4, make sure that X-axis direction is straight down");
  Serial.println("please type any charactor if you are ready");
  while (Serial.available() == 0) {
    xRaw = ReadAxis(xInput);
    yRaw = ReadAxis(yInput);
    zRaw = ReadAxis(zInput);
    delay(100);
  }
  while (Serial.available() > 0)Serial.read();
  AutoCalibrate(xRaw, yRaw, zRaw);
  displayInfo();
  Serial.println("The calibration starts: ");
  Serial.println("5, make sure that Y-axis direction is straight down");
  Serial.println("please type any charactor if you are ready");
  while (Serial.available() == 0) {
    xRaw = ReadAxis(xInput);
    yRaw = ReadAxis(yInput);
    zRaw = ReadAxis(zInput);
    delay(100);
  }
  while (Serial.available() > 0)Serial.read();
  AutoCalibrate(xRaw, yRaw, zRaw);
  displayInfo();
  Serial.println("The calibration starts: ");
  Serial.println("6, make sure that Z-axis direction is straight down");
  Serial.println("please type any charactor if you are ready");
  while (Serial.available() == 0) {
    xRaw = ReadAxis(xInput);
    yRaw = ReadAxis(yInput);
    zRaw = ReadAxis(zInput);
    delay(100);
  }
  while (Serial.available() > 0)Serial.read();
  AutoCalibrate(xRaw, yRaw, zRaw);
  while (1) {
    xRaw = ReadAxis(xInput);
    yRaw = ReadAxis(yInput);
    zRaw = ReadAxis(zInput);
    displayInfo();
    while (Serial.available() > 0) {
      Serial.read();
      if (Serial.available() == 0)
        break;
    }
  }
}
//
// Read "sampleSize" samples and report the average
//
int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i = 0; i < sampleSize; i++)
  {
    reading += analogRead(axisPin);
  }
  return reading / sampleSize;
}

//
// Find the extreme raw readings from each axis
//
void AutoCalibrate(int xRaw, int yRaw, int zRaw)
{
  Serial.println("Calibrate");
  if (xRaw < xRawMin)
  {
    xRawMin = xRaw;
  }
  if (xRaw > xRawMax)
  {
    xRawMax = xRaw;
  }

  if (yRaw < yRawMin)
  {
    yRawMin = yRaw;
  }
  if (yRaw > yRawMax)
  {
    yRawMax = yRaw;
  }

  if (zRaw < zRawMin)
  {
    zRawMin = zRaw;
  }
  if (zRaw > zRawMax)
  {
    zRawMax = zRaw;
  }
}
void displayInfo() {
  Serial.print("Raw Ranges: X: ");
  Serial.print(xRawMin);
  Serial.print("-");
  Serial.print(xRawMax);

  Serial.print(", Y: ");
  Serial.print(yRawMin);
  Serial.print("-");
  Serial.print(yRawMax);

  Serial.print(", Z: ");
  Serial.print(zRawMin);
  Serial.print("-");
  Serial.print(zRawMax);
  Serial.println();
  Serial.print(xRaw);
  Serial.print(", ");
  Serial.print(yRaw);
  Serial.print(", ");
  Serial.print(zRaw);

  // Convert raw values to 'milli-Gs"
  long xScaled = map(xRaw, xRawMin, xRawMax, -1000, 1000);
  long yScaled = map(yRaw, yRawMin, yRawMax, -1000, 1000);
  long zScaled = map(zRaw, zRawMin, zRawMax, -1000, 1000);

  // re-scale to fractional Gs
  float xAccel = xScaled / 1000.0;
  float yAccel = yScaled / 1000.0;
  float zAccel = zScaled / 1000.0;

  Serial.print(" :: ");
  Serial.print(xAccel);
  Serial.print("G, ");
  Serial.print(yAccel);
  Serial.print("G, ");
  Serial.print(zAccel);
  Serial.println("G");
}

