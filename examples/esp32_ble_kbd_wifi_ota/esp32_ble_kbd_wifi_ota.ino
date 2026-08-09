/*
 * ESP32 BLE Keyboard + Wi-Fi SoftAP + ESP32FwUploader OTA
 *
 * Description:
 *   BLE HID Keyboard (NimBLE) と Wi-Fi SoftAP を同時に動作させ、
 *   ESP32FwUploader ライブラリで Web 経由 OTA を提供する
 *   最小構成のサンプルです。
 *
 * Required libraries:
 *   - ESP32-NimBLE-Keyboard
 *     https://github.com/tomorrow56/ESP32-NimBLE-Keyboard
 *   - ESP32FwUploader
 *     https://github.com/tomorrow56/ESP32FwUploader
 *   - FastLED
 *     https://github.com/FastLED/FastLED
 *
 * Notes:
 *   - NimBLE ベースの BLE ライブラリを使うことで、Wi-Fi/BLE の
 *     共存に必要な RAM/CPU リソースを抑えています。
 *   - BLE デバイス名はレガシーアドバタイジングパケットの
 *     31 バイト制限に注意してください（本スケッチでは 9 文字）。
 */

#include <Arduino.h>
#include <BleKeyboard.h>
#include <ESP32FwUploader.h>
#include <FastLED.h>
#include <WebServer.h>
#include <WiFi.h>

// --- Configuration --------------------------------------------------------

// Wi-Fi SoftAP configuration
constexpr char AP_SSID[] = "ESP32-BLE-KBD";
constexpr char AP_PASSWORD[] = "12345678";
const IPAddress AP_IP(192, 168, 4, 1);
const IPAddress AP_GATEWAY(192, 168, 4, 1);
const IPAddress AP_SUBNET(255, 255, 255, 0);

// BLE device name (keep <= 18 characters to fit legacy advertising packet)
constexpr char BLE_DEVICE_NAME[] = "ESP32_KBD";

// HTTP server / OTA port
constexpr uint16_t HTTP_PORT = 80;

// WS2812B LED configuration (GPIO27)
constexpr uint8_t LED_PIN = 27;
constexpr uint8_t NUM_LEDS = 1;
constexpr uint8_t LED_BRIGHTNESS = 25; // 10 % of 255

// --- Globals --------------------------------------------------------------

BleKeyboard bleKeyboard(BLE_DEVICE_NAME);
WebServer webServer(HTTP_PORT);
CRGB leds[NUM_LEDS];

// --- Helpers --------------------------------------------------------------

void startSoftAP(void) {
  Serial.println("Starting Wi-Fi SoftAP...");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(AP_IP, AP_GATEWAY, AP_SUBNET);
  WiFi.softAP(AP_SSID, AP_PASSWORD);

  Serial.print("SoftAP SSID: ");
  Serial.println(AP_SSID);
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
}

// --- Arduino entry points -------------------------------------------------

void setup() {
  // Initialize WS2812B on GPIO27: blue at 10 % brightness
  FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(LED_BRIGHTNESS);
  leds[0] = CRGB::Blue;
  FastLED.show();

  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 BLE Keyboard + Wi-Fi SoftAP + ESP32FwUploader");

  // 1. Start BLE keyboard (NimBLE)
  Serial.println("Starting BLE keyboard...");
  bleKeyboard.begin();
  Serial.println("BLE keyboard started");

  // 2. Start Wi-Fi SoftAP
  startSoftAP();

  // 3. Start ESP32FwUploader on the web server
  ESP32FwUploader.setDebug(true);
  ESP32FwUploader.setDarkMode(false);
  ESP32FwUploader.setAutoReboot(true);
  ESP32FwUploader.begin(&webServer);

  webServer.begin();

  Serial.print("Open http://");
  Serial.print(WiFi.softAPIP());
  Serial.println("/update for OTA");
}

void loop() {
  // Handle web server and OTA state machine
  webServer.handleClient();
  ESP32FwUploader.loop();

  // BLE keyboard example: send Ctrl+Shift+A every 5 seconds when connected
  static uint32_t lastSendMs = 0U;
  if (bleKeyboard.isConnected()) {
    const uint32_t now = millis();
    if ((now - lastSendMs) >= 5000U) {
      lastSendMs = now;
      Serial.println("Sending Ctrl+Shift+A");
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_SHIFT);
      bleKeyboard.press('a');
      delay(100);
      bleKeyboard.releaseAll();
    }
  }

  delay(1);
}
