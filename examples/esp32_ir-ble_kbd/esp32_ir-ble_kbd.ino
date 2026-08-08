/*
 * ESP32 IR to Bluetooth HID Controller
 * 
 * Dependencies:
 * - ESP32-BLE-Keyboard: https://github.com/tomorrow56/ESP32-NimBLE-Keyboard（Fork)
 * - IRremoteESP8266: https://github.com/crankyoldgit/IRremoteESP8266
 */

#include <Arduino.h>
#include <BleKeyboard.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// --- Configuration ---
const uint8_t kRecvPin = 22; // IR Receiver Pin
const uint8_t kTransPin = 21; // IR Transmitter Pin
BleKeyboard bleKeyboard("IR-BLE_KBD");
IRrecv irrecv(kRecvPin);
decode_results results;

// --- IR Code Mapping (Example - Change to your remote codes) ---
// Note: You need to run a simple IR receiver sketch first to find your remote's HEX codes.
#define IR_CODE_APPROVE  0x807FC03F
#define IR_CODE_DECLINE  0x807FF00F
#define IR_CODE_SEND     0x807F50AF
#define IR_CODE_NEW_CHAT 0x807F00FF
#define IR_CODE_FAST_MODE 0x807F708F
#define IR_CODE_VOICE    0x807F38C7

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE Keyboard...");
  bleKeyboard.begin();
  
  Serial.println("Starting IR Receiver...");
  irrecv.enableIRIn(); // Start the receiver
}

void sendShortcut(uint8_t modifier, uint8_t key) {
  if (bleKeyboard.isConnected()) {
    Serial.println("Sending shortcut...");
    bleKeyboard.press(modifier);
    bleKeyboard.press(key);
    delay(100);
    bleKeyboard.releaseAll();
  } else {
    Serial.println("BLE not connected");
  }
}

void loop() {
  if (irrecv.decode(&results)) {
    // Print the received code to Serial for debugging/mapping
    Serial.print("Received IR Code: 0x");
    Serial.println(results.value, HEX);
    
    if (bleKeyboard.isConnected()) {
      switch (results.value) {
        case IR_CODE_APPROVE:
          Serial.println("Action: Approve");
          // Example: Custom shortcut for Approve (e.g., Ctrl+Shift+A)
          bleKeyboard.press(KEY_LEFT_CTRL);
          bleKeyboard.press(KEY_LEFT_SHIFT);
          bleKeyboard.press('a');
          delay(100);
          bleKeyboard.releaseAll();
          break;

        case IR_CODE_DECLINE:
          Serial.println("Action: Decline");
          // Example: Custom shortcut for Decline (e.g., Ctrl+Shift+X)
          bleKeyboard.press(KEY_LEFT_CTRL);
          bleKeyboard.press(KEY_LEFT_SHIFT);
          bleKeyboard.press('x');
          delay(100);
          bleKeyboard.releaseAll();
          break;

        case IR_CODE_SEND:
          Serial.println("Action: Send");
          bleKeyboard.write(KEY_RETURN); // Usually Enter
          break;

        case IR_CODE_NEW_CHAT:
          Serial.println("Action: New Chat");
          // Ctrl + N (Windows) or Cmd + N (Mac)
          bleKeyboard.press(KEY_LEFT_CTRL); 
          bleKeyboard.press('n');
          delay(100);
          bleKeyboard.releaseAll();
          break;

        case IR_CODE_VOICE:
          Serial.println("Action: Voice Dictation");
          // Ctrl + Shift + D (ChatGPT Dictation)
          bleKeyboard.press(KEY_LEFT_CTRL);
          bleKeyboard.press(KEY_LEFT_SHIFT);
          bleKeyboard.press('d');
          delay(100);
          bleKeyboard.releaseAll();
          break;

        default:
          Serial.println("Unknown IR Code. Map it in the code!");
          break;
      }
    }
    
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
