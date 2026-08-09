# ESP32 BLE Keyboard + Wi-Fi SoftAP + OTA Example

This example demonstrates how to run a NimBLE-based BLE keyboard and a Wi-Fi SoftAP at the same time on an ESP32, and to provide web-based firmware updates via the [ESP32FwUploader](https://github.com/tomorrow56/ESP32FwUploader) library.

## Features

- BLE HID keyboard using ESP32-NimBLE-Keyboard
- Wi-Fi SoftAP for wireless access without an existing router
- Web-based OTA firmware update (`http://192.168.4.1/update`)
- Status LED on GPIO27 using a WS2812B NeoPixel

## Requirements

- **ESP32 development board** (ESP32-DevKitC or similar)
- **WS2812B / NeoPixel LED** connected to **GPIO27** (optional but expected by default)
- A **PC or smartphone** to connect to the ESP32's SoftAP and use the OTA page

## Required libraries

Install the following libraries in the Arduino IDE:

1. **ESP32-NimBLE-Keyboard** (this library)
2. **ESP32FwUploader** by tomorrow56
3. **FastLED**

## Default configuration

| Setting | Value | Notes |
| :--- | :--- | :--- |
| SoftAP SSID | `ESP32-BLE-KBD` | Connect your PC/phone to this network |
| SoftAP password | `12345678` | Change for production use |
| SoftAP IP | `192.168.4.1` | Default AP address |
| OTA URL | `http://192.168.4.1/update` | Open this in a browser after connecting |
| BLE device name | `ESP32_KBD` | Keep it short to fit the 31-byte advertising packet |
| LED pin | `GPIO27` | WS2812B status LED |

## Usage

1. Build and upload the sketch to your ESP32.
2. Open the Serial Monitor at **115200 bps**.
3. The ESP32 starts the BLE keyboard and creates the Wi-Fi SoftAP.
4. Connect your PC or smartphone to the `ESP32-BLE-KBD` Wi-Fi network.
5. Open `http://192.168.4.1/update` in a browser.
6. Select a compiled `.bin` file and start the OTA update.
7. When the BLE keyboard is connected to a host, it sends `Ctrl+Shift+A` every 5 seconds as a demo.

## Customizing keyboard actions

Edit `loop()` to replace the demo shortcut with the keys you need:

```cpp
bleKeyboard.press(KEY_LEFT_CTRL);
bleKeyboard.press(KEY_LEFT_SHIFT);
bleKeyboard.press('a');
delay(100);
bleKeyboard.releaseAll();
```

## Notes

- NimBLE is used instead of the classic BLE stack to reduce RAM/CPU usage so Wi-Fi and BLE can coexist more comfortably.
- Keep the BLE device name short (18 characters or fewer recommended) so it fits in the legacy BLE advertising packet.
