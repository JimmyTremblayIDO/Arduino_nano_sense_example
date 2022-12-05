#include <Arduino.h>
#include <Arduino_LSM9DS1.h> //IMU-acc-mag-gyro
#include <Arduino_APDS9960.h> //prox-light-color-gesture
#include <Arduino_HTS221.h> //temp-humidity
#include <Arduino_LPS22HB.h> //pressure
#include <PDM.h> //microphone

float x, y, z, averageVal; //float values for IMU

//microphone variables
short sampleBuffer[256]; // buffer to read samples into, each sample is 16-bits
volatile int samplesRead; // number of samples read

//PDM-CALLBACK-FUNCTION
void onPDMdata() {
  // query the number of bytes available
  int bytesAvailable = PDM.available();

  // read into the sample buffer
  PDM.read(sampleBuffer, bytesAvailable);

  // 16-bit, 2 bytes per sample
  samplesRead = bytesAvailable / 2;
}

void setup() {
  Serial.begin(115200);

  //IMU-acc-mag-gryo
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  //prox-light-color-gesture
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
  }

  //temp-humidity
  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
  }

  //baro-pressure
  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
  }

  //microphone

  PDM.onReceive(onPDMdata); // configure the data receive callback
  // PDM.setGain(30); // optionally set the gain, defaults to 20
  if (!PDM.begin(1, 16000)) {// initialize PDM with: - one channel (mono mode) - a 16 kHz sample rate
    Serial.println("Failed to start PDM!");
    while (1);
  }

}

void loop() {

  //MICROPHONE##################################################################################################
  if (samplesRead) {
    // print samples to the serial monitor or plotter
    for (int i = 0; i < samplesRead; i++) {
      Serial.println(sampleBuffer[i]);
    }
    samplesRead = 0; // clear the read count
  }

  //BARO_PRESSURE###############################################################################################
  /*Serial.print("Barometric pressure= ");
  Serial.println(BARO.readPressure());*/

  //TEMP_HUMIDITY###############################################################################################
  /*Serial.print("Temperature= ");
  Serial.print(HTS.readTemperature());
  Serial.print(" Humidity= ");
  Serial.println(HTS.readHumidity());*/

  //PROXIMITY###################################################################################################
  /*if (APDS.proximityAvailable()) {
    Serial.println(APDS.readProximity());
  }*/

  //ACCELEROMETER###############################################################################################
  /*if(IMU.accelerationAvailable()){
    IMU.readAcceleration(x, y, z);
  }
  averageVal=((fabs(x)+fabs(y)+fabs(z))/3);
  Serial.print("x= ");
  Serial.print(x);
  Serial.print(", y= ");
  Serial.print(y);
  Serial.print(", z= ");
  Serial.println(z);
  //Serial.print(", average= ");
  //Serial.println(averageVal);
  delay(10);*/

  //GYROSCOPE##################################################################################################
  /*if(IMU.gyroscopeAvailable()){
    IMU.readGyroscope(x, y, z);
  }
  averageVal=((fabs(x)+fabs(y)+fabs(z))/3);
  Serial.print("x= ");
  Serial.print(x);
  Serial.print(", y= ");
  Serial.print(y);
  Serial.print(", z= ");
  Serial.println(z);
  //Serial.print(", average= ");
  //Serial.println(averageVal);
  delay(10);*/

  //MAGNETOMETER###############################################################################################
  /*IMU.readMagneticField(x, y, z);
  averageVal=((fabs(x)+fabs(y)+fabs(z))/3);
  Serial.print("x= ");
  Serial.print(x);
  Serial.print(", y= ");
  Serial.print(y);
  Serial.print(", z= ");
  Serial.println(z);
  Serial.print(", average= ");
  Serial.println(averageVal);
  delay(10);*/

  //R-G-B_LEDS#################################################################################################
  //also supports analogWrite(0-255)###########################################################################
  /*digitalWrite(LEDR, LOW);
  delay(1000);
  digitalWrite(LEDR, HIGH);
  delay(1000);
  digitalWrite(LEDG, LOW);
  delay(1000);
  digitalWrite(LEDG, HIGH);
  delay(1000);
  digitalWrite(LEDB, LOW);
  delay(1000);
  digitalWrite(LEDB, HIGH);
  delay(1000);*/
}