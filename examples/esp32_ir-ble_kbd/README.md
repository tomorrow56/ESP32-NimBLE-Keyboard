# ESP32 IR to BLE Gateway Example セットアップガイド

このガイドでは、赤外線リモコンを使用してESP32経由でChatGPT Desktop Appを操作するためのセットアップ手順を説明します。

## 1. 必要なもの
- **ESP32 開発ボード** (ESP32-DevKitC など)
- **赤外線受信モジュール** (例: TSOP38238, TL1838)
- **赤外線リモコン** (家庭にあるテレビのリモコン等でOK)
- **PC** (Arduino IDE インストール済み)

## 2. 回路図 (配線)
赤外線受信モジュールをESP32に以下のように接続します。

| 赤外線受信モジュール | ESP32 ピン | 備考 |
| :--- | :--- | :--- |
| **OUT (Signal)** | **GPIO 22** | プログラム内で変更可能 |
| **GND** | **GND** | |
| **VCC** | **3.3V** | (モジュールによっては5V) |

## 3. ソフトウェアの準備
Arduino IDE で以下のライブラリをインストールしてください。
1. **ESP32-NimBLE-Keyboard** modified by tomorrow56 (GitHubからZIPでインストール)
2. **IRremoteESP8266** by crankyoldgit

## 4. 設定手順
1. ESP32にスケッチ `esp32_ir-ble_kbd.ino` を書き込みます。
2. シリアルモニタ（115200bps）を開きます。
3. 使用したいリモコンのボタンを押し、表示される `Received IR Code: 0xXXXXXX` をメモします。
4. コード内の `#define IR_CODE_...` の値を、メモした自分のリモコンのコードに書き換えます。
5. PCのBluetooth設定から「IR-BLE_KBD」を探してペアリングします。

## 5. キーバインドのカスタマイズ
ChatGPT Desktop App の **Settings > Keyboard Shortcuts** を開き、各アクション（Approve, Decline等）に割り当てられているショートカットを確認してください。
ESP32のコード内の `bleKeyboard.press(...)` 部分を、アプリの設定に合わせて調整することで、あらゆる操作をリモコンに割り当てられます。
