#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LiquidCrystal_I2C.h>

// ===== Wi-Fi credentials =====
const char* ssid = "ESP8266_Chat";
const char* password = "chat1234";

// ===== Web server + websocket =====
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// ===== LCD setup =====
LiquidCrystal_I2C lcd(0x27, 16, 2); // adjust address/size if needed

// ===== Buzzer setup =====
#define BUZZER_PIN D5  // Passive buzzer connected to D5 (GPIO14)

// ===== Chatroom HTML =====
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>ESP8266 Chatroom</title>
  <style>
    body { font-family: sans-serif; margin: 20px; }
    #chat { border: 1px solid #ccc; height: 200px; overflow-y: scroll; padding: 5px; }
    #nickSection { margin-bottom: 10px; }
  </style>
</head>
<body>
  <h2>ESP8266 Chatroom</h2>
  
  <div id="nickSection">
    <input id="nick" type="text" placeholder="Enter nickname">
    <button onclick="setNick()">Join</button>
  </div>

  <div id="chat"></div>
  
  <div id="msgSection" style="display:none;">
    <input id="msg" type="text" placeholder="Type a message">
    <button onclick="sendMsg()">Send</button>
  </div>

  <script>
    var ws, nickname;
    function setNick() {
      nickname = document.getElementById('nick').value;
      if (!nickname) return;
      ws = new WebSocket('ws://' + location.host + '/ws');
      ws.onmessage = function(event) {
        var chat = document.getElementById('chat');
        chat.innerHTML += event.data + '<br>';
        chat.scrollTop = chat.scrollHeight;
      };
      document.getElementById('nickSection').style.display = 'none';
      document.getElementById('msgSection').style.display = 'block';
    }

    function sendMsg() {
      var input = document.getElementById('msg');
      ws.send(nickname + ": " + input.value);
      input.value = '';
    }
  </script>
</body>
</html>
)rawliteral";

// ===== Handle incoming WebSocket messages =====
void onWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if(info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    String msg = String((char*)data);

    // Beep when a new message arrives
    tone(BUZZER_PIN, 1000, 150);

    // Broadcast the message to all clients
    ws.textAll(msg);
  }
}

void setup() {
  Serial.begin(115200);

  // ===== LCD init =====
  lcd.init();
  lcd.backlight();

  // ===== Wi-Fi AP =====
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Show SSID and password first
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SSID: ESP8266_Chat");
  lcd.setCursor(0, 1);
  lcd.print("PASS: chat1234");
  delay(4000);

  // ===== WebSocket setup =====
  ws.onEvent([](AsyncWebSocket *server, AsyncWebSocketClient *client,
                AwsEventType type, void *arg, uint8_t *data, size_t len){
    if(type == WS_EVT_CONNECT){
      Serial.printf("Client connected: %u\n", client->id());
      tone(BUZZER_PIN, 2000, 200); // higher pitch beep on connect
      ws.textAll("📢 A new user joined the chat!");
    }
    else if(type == WS_EVT_DATA){
      onWebSocketMessage(arg, data, len);
    }
  });
  server.addHandler(&ws);

  // ===== Serve the chat page =====
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.begin();
}

void loop() {
  // Async server handles everything
}
