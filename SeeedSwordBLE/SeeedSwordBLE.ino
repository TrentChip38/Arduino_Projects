//Board: Seeed XIAO nRF52840 Sense
//Board manager: Seeed nRF52 Boards
//Libraries: Seeed_Arduino_LSM6DS3 and Seeeduino or nrf52
//Maybe these? ArduinoBLE or NimBLE-Arduino and maybe FastIMU
#include <bluefruit.h>
#include <LSM6DS3.h>
#include <Wire.h>

//Instantiate bluetooth
BLEUart bleuart;
//Instantiate the IMU
LSM6DS3 imu(I2C_MODE, 0x6A);

const int sampleRateHz = 50;
const int delayMs = 1000 / sampleRateHz;  // ~20ms for 50Hz

// Connection tracking
bool isConnected = false;
// Status printing
unsigned long lastStatusMillis = 0;
const unsigned long statusIntervalMs = 2000;

void setup() {
  Serial.begin(115200);
  delay(500);  // Give Serial time to start
  
  Serial.println("\n\n=== SeeedSword BLE Game Controller ===");
  Serial.println("Initializing IMU...");
  
  if (imu.begin() != 0) {
    Serial.println("ERROR: IMU failed to initialize!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("IMU initialized successfully");

  // Set up BLE
  Serial.println("Initializing Bluetooth...");
  if (!Bluefruit.begin()) {
    Serial.println("ERROR: Bluefruit.begin() failed!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("Bluefruit.begin() OK");

  Bluefruit.setName("SeeedSword");
  Bluefruit.setTxPower(4); // increase transmit power for reliability
  // Configure security to prefer Just Works pairing (no MITM), easing PC pairing
  Bluefruit.Security.setIOCaps(false, false, false);
  Bluefruit.Security.setMITM(false);
  Bluefruit.Security.setSecuredCallback(connection_secured_cb);
  
  // Register connection callbacks early (before advertising)
  Bluefruit.Periph.setConnectCallback(onConnect);
  Bluefruit.Periph.setDisconnectCallback(onDisconnect);

  // Set up UART service (allow open access)
  bleuart.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  bleuart.begin();

  // Configure advertising
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);  // 20ms fast, 152.5ms slow
  Bluefruit.Advertising.setFastTimeout(30);

  Bluefruit.Advertising.start(0);  // Advertise forever
  Serial.print("Advertising running: ");
  Serial.println(Bluefruit.Advertising.isRunning() ? "yes" : "no");
  
  Serial.println("BLE Advertising started!");
  Serial.println("Looking for connection...");
  Serial.println("Device name: SeeedSword");
  Serial.println("");
  
  // Set up connection callbacks (Periph API matches library examples)
  Bluefruit.Periph.setConnectCallback(onConnect);
  Bluefruit.Periph.setDisconnectCallback(onDisconnect);
  // Also log advertising state changes
  Bluefruit.Advertising.setSlowCallback(adv_slow_cb);
  Bluefruit.Advertising.setStopCallback(adv_stop_cb);
}

// BLE Connection callback
void onConnect(uint16_t conn_handle) {
  isConnected = true;
  char central_name[32] = {0};
  BLEConnection *conn = Bluefruit.Connection(conn_handle);
  if (conn) {
    conn->getPeerName(central_name, sizeof(central_name));
  } else {
    Serial.print("Warning: Connection object not found for handle="); Serial.println(conn_handle);
  }
  Serial.print("Connected to: ");
  Serial.println(central_name[0] ? central_name : "central");
}

// BLE Disconnection callback
void onDisconnect(uint16_t conn_handle, uint8_t reason) {
  isConnected = false;
  Serial.print("Disconnected (handle="); Serial.print(conn_handle);
  Serial.print(") reason=0x"); Serial.println(reason, HEX);
  Serial.println("Waiting for new connection...");
}

// Generic Bluefruit event callback to catch connect/disconnect for different API versions
// (Removed generic event callback; using Periph callbacks instead)

// Advertising callbacks
void adv_slow_cb(void) {
  Serial.println("Advertising switched to slow interval");
}

void adv_stop_cb(void) {
  Serial.println("Advertising stopped");
}

// Called when a connection becomes secured (encrypted)
void connection_secured_cb(uint16_t conn_handle) {
  Serial.print("Connection secured (handle="); Serial.print(conn_handle); Serial.println(")");
}

void loop() {
  unsigned long now = millis();
  if (now - lastStatusMillis >= statusIntervalMs) {
    lastStatusMillis = now;
    Serial.print("Status: connected_count=");
    Serial.print(Bluefruit.connected());
    Serial.print("  AdvRunning=");
    Serial.println(Bluefruit.Advertising.isRunning() ? "yes" : "no");
    if (!isConnected) {
      Serial.print("BLEUart available bytes=");
      Serial.println(bleuart.available());
    }
  }
  if (isConnected) {
    // Read IMU data
    float ax = imu.readFloatAccelX();
    float ay = imu.readFloatAccelY();
    float az = imu.readFloatAccelZ();
    
    float gx = imu.readFloatGyroX();
    float gy = imu.readFloatGyroY();
    float gz = imu.readFloatGyroZ();
    
    // Create formatted message
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "ACC:%.2f,%.2f,%.2f|GYR:%.2f,%.2f,%.2f",
             ax, ay, az, gx, gy, gz);
    
    // Send via BLE
    bleuart.println(buffer);
    
    // Also print to Serial for debugging
    Serial.println(buffer);
  }
  
  delay(delayMs);
}