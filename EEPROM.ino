#include <Wire.h>

#define MPU_ADDR 0x68

// Simple moving average filter
const int FILTER_SIZE = 5;
int16_t ax_buffer[FILTER_SIZE], ay_buffer[FILTER_SIZE], az_buffer[FILTER_SIZE];
int16_t gx_buffer[FILTER_SIZE], gy_buffer[FILTER_SIZE], gz_buffer[FILTER_SIZE];
int buffer_index = 0;

void setup() {
  Serial.begin(115200);
  
  // Initialize I2C with lower speed for reliability
  Wire.begin();
  Wire.setClock(100000); // 100kHz - slower but more reliable
  
  Serial.println("MPU6050 Slow & Steady Test");
  
  // Initialize buffers
  for(int i=0; i<FILTER_SIZE; i++) {
    ax_buffer[i] = ay_buffer[i] = az_buffer[i] = 0;
    gx_buffer[i] = gy_buffer[i] = gz_buffer[i] = 0;
  }
  
  // Reset MPU6050
  resetMPU();
  
  delay(1000);
  
  Serial.println("\nReading raw values (no calibration):");
  Serial.println("AX\tAY\tAZ\tGX\tGY\tGZ");
}

void resetMPU() {
  // Send reset command
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1
  Wire.write(0x80); // Device reset
  Wire.endTransmission();
  delay(100);
  
  // Wake up
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00); // Wake up
  Wire.endTransmission();
  delay(100);
  
  // Configure
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x1A); // CONFIG
  Wire.write(0x03); // DLPF = 3 (44Hz bandwidth)
  Wire.endTransmission();
}

bool readMPU(int16_t* ax, int16_t* ay, int16_t* az, 
             int16_t* gx, int16_t* gy, int16_t* gz) {
  static uint8_t buffer[14];
  
  // Request data
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  if (Wire.endTransmission(false) != 0) return false;
  
  // Request 14 bytes
  uint8_t bytesRead = Wire.requestFrom(MPU_ADDR, 14);
  if (bytesRead != 14) return false;
  
  // Read all bytes
  for (uint8_t i = 0; i < 14; i++) {
    buffer[i] = Wire.read();
  }
  
  // Combine bytes
  *ax = (buffer[0] << 8) | buffer[1];
  *ay = (buffer[2] << 8) | buffer[3];
  *az = (buffer[4] << 8) | buffer[5];
  *gx = (buffer[8] << 8) | buffer[9];
  *gy = (buffer[10] << 8) | buffer[11];
  *gz = (buffer[12] << 8) | buffer[12];
  
  return true;
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  
  if (readMPU(&ax, &ay, &az, &gx, &gy, &gz)) {
    // Store in buffer for filtering
    ax_buffer[buffer_index] = ax;
    ay_buffer[buffer_index] = ay;
    az_buffer[buffer_index] = az;
    gx_buffer[buffer_index] = gx;
    gy_buffer[buffer_index] = gy;
    gz_buffer[buffer_index] = gz;
    
    buffer_index = (buffer_index + 1) % FILTER_SIZE;
    
    // Calculate moving average
    int32_t ax_avg = 0, ay_avg = 0, az_avg = 0;
    int32_t gx_avg = 0, gy_avg = 0, gz_avg = 0;
    
    for(int i=0; i<FILTER_SIZE; i++) {
      ax_avg += ax_buffer[i];
      ay_avg += ay_buffer[i];
      az_avg += az_buffer[i];
      gx_avg += gx_buffer[i];
      gy_avg += gy_buffer[i];
      gz_avg += gz_buffer[i];
    }
    
    ax_avg /= FILTER_SIZE;
    ay_avg /= FILTER_SIZE;
    az_avg /= FILTER_SIZE;
    gx_avg /= FILTER_SIZE;
    gy_avg /= FILTER_SIZE;
    gz_avg /= FILTER_SIZE;
    
    // Display
    Serial.print(ax_avg); Serial.print("\t");
    Serial.print(ay_avg); Serial.print("\t");
    Serial.print(az_avg); Serial.print("\t");
    Serial.print(gx_avg); Serial.print("\t");
    Serial.print(gy_avg); Serial.print("\t");
    Serial.println(gz_avg);
  } else {
    Serial.println("Read failed - retrying...");
    delay(100);
  }
  
  delay(50);
}