# ESP32-NimBLE-Keyboard ライブラリ修正内容

## 概要
ESP32-NimBLE-KeyboardライブラリをNimBLE-Arduino v2.3.4に対応させるための修正を実施。

## 修正対象ファイル

### 1. BleKeyboard.cpp
**ファイルパス**: `ESP32-NimBLE-Keyboard/BleKeyboard.cpp`

#### 修正内容:
- **API名変更対応**:
  - `inputReport()` → `getInputReport()`
  - `outputReport()` → `getOutputReport()`
  - `manufacturer()->setValue()` → `setManufacturer()`
  - `setPnpId()` → `setPnp()`
  - `hidInfo()` → `setHidInfo()`
  - `reportMap()` → `setReportMap()`
  - `hidService()` → `getHidService()`

- **セキュリティ設定の変更**:
  - `BLESecurity()` → `NimBLEDevice::setSecurityAuth()`
  - `NimBLESecurity` インスタンス生成を廃止
  - `NimBLEDevice::setSecurityPasskey()` を使用

- **定数名変更**:
  - `ESP_LE_AUTH_BOND` → `ESP_LE_AUTH_REQ_BOND`

- **接続状態検出の改善**:
  - `isConnected()` メソッドで `getConnectedCount()` を追加使用
  - NimBLE-Arduino v2.3.4の新しいAPI対応

#### 修正箇所 (行番号):
- 108-116行: `isConnected()` メソッドの改善
- 125-150行: `taskServer()` 内のAPI呼び出し修正

### 2. BleConnectionStatus.cpp
**ファイルパス**: `ESP32-NimBLE-Keyboard/BleConnectionStatus.cpp`

#### 修正内容:
- **デバッグ情報追加**:
  - `onConnect()` に接続ログ出力を追加
  - `onDisconnect()` に切断ログ出力を追加

#### 修正箇所 (行番号):
- 6-10行: `onConnect()` メソッドにデバッグ出力追加
- 12-16行: `onDisconnect()` メソッドにデバッグ出力追加

## 依存関係・環境

- **NimBLE-Arduino ライブラリ**: v2.3.4 (最新)

---
**修正日**: 2025-08-16