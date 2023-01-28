#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

////////////////////////
///// config  //////////

const int dead_zone = 1;

/// config end ////
///////////////////


Adafruit_MPU6050 mpu;
int calc_var, i = 0;
int current_position;  //0= undef, 1=x_pos, 2=y_pos, 3=x_nex, 4=y_neg
int y_pos_count = 0, x_pos_count = 0, y_neg_count = 0, x_neg_count = 0;
#define LINE_START "Rotate Monitor <"
#define LINE_END ">"




void setup(void) {
  Serial.begin(9600);
  while (!Serial)
    delay(10);  // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }

  Serial.println("");
  delay(100);

  //get current orientation
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  if ((abs(a.acceleration.x)) - (abs(a.acceleration.y)) > 0) {  //pos=x, neg=y
    if (a.acceleration.x > 0) {
      ///////////x_pos
      current_position = 1;
      sendOrientation("X_POS");
    } else {
      ///////////x_neg
      current_position = 3;
      sendOrientation("X_NEG");
    }
  } else {
    if (a.acceleration.y > 0) {
      ///////////y_pos
      current_position = 2;
      sendOrientation("Y_POS");
    } else {
      ///////////Y_neg
      current_position = 4;
      sendOrientation("Y_NEG");
    }
  }
  delay(200);
}


void loop() {
  // put your main code here, to run repeatedly:
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  //which axis is up?
  //that one is now measuring 1g, not 0g
  switch (current_position) {  //0= undef, 1=x_pos, 2=y_pos, 3=x_nex, 4=y_neg
    case (1):
    case (3):
      if (dead_zone + (abs(a.acceleration.x)) - (abs(a.acceleration.y)) < 0) {
        if (a.acceleration.y > 0) {
          if (y_pos_count = 2) {
            current_position = 2;
            sendOrientation("Y_POS");
            y_pos_count = 0;
            x_pos_count = 0;
            y_neg_count = 0;
            x_neg_count = 0;
          } else {
            y_pos_count++;
            x_pos_count = 0;
            y_neg_count = 0;
            x_neg_count = 0;
          }
        } else {
          if (y_neg_count = 2) {
            current_position = 4;
            sendOrientation("Y_NEG");
            y_pos_count = 0;
            x_pos_count = 0;
            y_neg_count = 0;
            x_neg_count = 0;
          } else {
            y_pos_count = 0;
            x_pos_count = 0;
            y_neg_count++;
            x_neg_count = 0;
          }
        }
      }

      break;
    case (2):
    case (4):
      if (dead_zone + (abs(a.acceleration.y)) - (abs(a.acceleration.x)) < 0) {
        if (a.acceleration.x > 0) {
          if (x_pos_count = 2) {
            current_position = 1;
            sendOrientation("X_POS");
            y_pos_count = 0;
            x_pos_count = 0;
            y_neg_count = 0;
            x_neg_count = 0;
          } else {
            y_pos_count = 0;
            x_pos_count++ ;
            y_neg_count = 0;
            x_neg_count = 0;
          }
        } else {
          if (x_pos_count = 2) {
            current_position = 3;
            sendOrientation("X_NEG");
            y_pos_count = 0;
            x_pos_count = 0;
            y_neg_count = 0;
            x_neg_count = 0;          
          } else {
            y_pos_count = 0;
            x_pos_count = 0;
            y_neg_count = 0;
            x_neg_count++ ;            
          }
        }
      }
      break;
    case (0):
    default:  //Z_POS or NOT_SURE
              // for NOT_SURE, assume Z_POS
      break;
  }
  delay(200);
}

void sendOrientation(String text1) {

  Serial.println("change detected");

  Serial.print(LINE_START);
  Serial.print(text1);
  Serial.println(LINE_END);
}
