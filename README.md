# ESP32 NimBLE Keyboard library

Changed the original [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) to support NimBLE.

This library allows you to make the ESP32 act as a Bluetooth Keyboard and control what it does.  
You might also be interested in:
- [ESP32-NimBLE-Mouse](https://github.com/wakwak-koba/ESP32-NimBLE-Mouse)
- [ESP32-NimBLE-Gamepad](https://github.com/lemmingDev/ESP32-BLE-Gamepad)

## About this fork

This repository is a fork of [wakwak-koba/ESP32-NimBLE-Keyboard](https://github.com/wakwak-koba/ESP32-NimBLE-Keyboard), which itself ports the original [T-vK/ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) to NimBLE.

Changes made in this fork:
- Modified `src/BleKeyboard.h` to add an `#include <functional>` and a `std::function`-based `Callback` type, enabling callback support (e.g. for connection/disconnection events).
- Added a new example, [`examples/esp32_ir-ble_kbd`](examples/esp32_ir-ble_kbd), which demonstrates using an IR receiver on the ESP32 to send BLE keyboard shortcuts (e.g. to control the ChatGPT Desktop App) via an infrared remote.
