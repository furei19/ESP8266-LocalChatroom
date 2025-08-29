# 💬 ESP8266 Local Chatroom

**“A fun project ⚡ that transforms an ESP8266 board into a standalone Wi-Fi hotspot 📶 and local chat server 💬, enabling real-time communication 🔄 between connected devices.

Users can connect with their phones 📱 or laptops 💻, open a webpage 🌐, and chat with everyone else on the same hotspot — no mobile data 🚫📶 or internet required!”** 

## Status: Unfinished 🚧

---

## 🛠️ Materials Needed
- **ESP8266 NodeMCU (ESP-12E/ESP-12F)**  
- **I2C LCD 16x2 display** (with backpack, address `0x27` or `0x3F`)  
- **Passive buzzer** (for notifications)  
- **Jumper wires**  
- **Breadboard** (optional, for prototyping)  
- **Micro USB cable** (to flash ESP8266)

---

## ⚡ Wiring Guide

| Component      | ESP8266 Pin | Notes |
|----------------|-------------|-------|
| **LCD SDA**    | `D2` (GPIO4) | I2C Data line |
| **LCD SCL**    | `D1` (GPIO5) | I2C Clock line |
| **Buzzer +**   | `D5` (GPIO14) | Controlled via `tone()` |
| **Buzzer –**   | `GND` | Ground |
| **LCD VCC**    | `3.3V` | Power |
| **LCD GND**    | `G` | Ground |

---

## 📡 How It Works
1. The ESP8266 starts in **Access Point (AP) mode** with:  
   - SSID: `ESP8266_Chat`  
   - Password: `chat1234`  
2. Connect your phone/laptop to this Wi-Fi.  
3. Open a browser and go to:  http://192.168.4.1
4. Pick a nickname and join the chat.  
5. Messages are sent via **WebSockets** and broadcast to all connected users.  
6. The LCD shows network info, and the buzzer makes sounds on new messages/joins.  

---

## 💻 Setup & Upload
1. Install [Arduino IDE](https://www.arduino.cc/en/software).  
2. Add ESP8266 board support:  
- Go to `File > Preferences` → paste this in *Additional Board Manager URLs*:  
  ```
  http://arduino.esp8266.com/stable/package_esp8266com_index.json
  ```
- Then go to `Tools > Board > Board Manager` → search **esp8266** → install.  
3. Install the following libraries via **Library Manager**:  
- `ESPAsyncWebServer` (by me-no-dev)  
- `ESPAsyncTCP` (by me-no-dev)  
- `LiquidCrystal_I2C` (by Frank de Brabander)  
4. Connect your ESP8266 via USB.  
5. Select board: `NodeMCU 1.0 (ESP-12E Module)` (or equivalent).  
6. Upload the `main.ino` file from this repo.  

---

## 🚀 Run Demo
- After flashing, the LCD will show the Wi-Fi SSID and password.  
- Connect your phone/laptop to the ESP’s Wi-Fi.  
- Visit `http://192.168.4.1` → open the chat page.  
- Start chatting locally — no internet needed!  

---

## 🔮 Future Ideas (Under Construction 🚧)
This project is just the start — here are some possible upgrades:
- ⚡ **Upgrade to ESP32** more RAM, faster CPU, dual-core for better performance.
- 📂 **File sharing** between clients (send text/images via base64).  
- 📊 **Chat logging** on SD card.  
- 🔔 **User-specific buzzer tones**.  
- 📱 **Mobile-friendly UI redesign**.  
- 🌍 **Port forwarding / mesh networking** for extended range.  
- 🔒 **Nicknames & password-protected rooms**.  

*(Contributions welcome — feel free to fork & PR!)*

---

## 🐙 How to Clone
To get the code locally:
```bash
git clone https://github.com/<your-username>/ESP8266-LocalChatroom.git
cd ESP8266-LocalChatroom
