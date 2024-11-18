#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// Definição dos pinos para NodeMCU 0.9
const int BUZ_PIN = D6;   // GPIO12
const int FIRE_PIN = D7;  // GPIO13
const int GAS_PIN = D5;   // GPIO14

// Configurações do WiFi
const char* ssid = "Lucas";
const char* password = "12345678";

// Configurações do CallMeBot
const String phoneNumber = "5511975911432";  // Formato: 5511999999999
const String apiKey = "1561950";

unsigned long previousMillis = 0;
const long interval = 500;  // Intervalo de verificação (500ms)
bool is_buz_on = false;
bool buzzer_enabled = false;
bool alreadyNotified = false;

void setup() {
  Serial.begin(115200);
  
  // Configura os pinos
  pinMode(BUZ_PIN, OUTPUT);
  pinMode(FIRE_PIN, INPUT);
  pinMode(GAS_PIN, INPUT);
  
  // Desliga o buzzer inicialmente
  digitalWrite(BUZ_PIN, HIGH);
  
  // Conecta ao WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado ao WiFi");
  Serial.println("IP: " + WiFi.localIP().toString());
  
  // Envia mensagem inicial
  sendWhatsAppMessage("Sistema de detecção de fogo e gás iniciado!");
}

void sendWhatsAppMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    
    message.replace(" ", "%20");
    String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + message;
    
    http.begin(client, url);
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      Serial.printf("Mensagem WhatsApp enviada, código HTTP: %d\n", httpResponseCode);
    } else {
      Serial.printf("Erro ao enviar mensagem WhatsApp: %s\n", http.errorToString(httpResponseCode).c_str());
    }
    
    http.end();
  }
}

void buz_on() {
  buzzer_enabled = true;
}

void buz_off() {
  buzzer_enabled = false;
  digitalWrite(BUZ_PIN, HIGH);
}

bool is_buz_enable() {
  return buzzer_enabled;
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    bool danger_detected = false;
    
    // Verifica se detectou chamas (LOW significa detecção)
    if (digitalRead(FIRE_PIN) == LOW) {
      danger_detected = true;
      Serial.println("Fogo detectado!");
    }
    
    // Verifica se detectou gás (LOW significa detecção)
    if (digitalRead(GAS_PIN) == LOW) {
      danger_detected = true;
      Serial.println("Gás detectado!");
    }
    
    if (danger_detected) {
      if (!is_buz_enable()) {
        buz_on();
        if (!alreadyNotified) {
          sendWhatsAppMessage("Alerta! Fogo ou gás detectado. Verifique imediatamente!");
          alreadyNotified = true;
        }
      }
    } else {
      buz_off();
      alreadyNotified = false;
    }
  }
  
  // Controle do buzzer
  if (buzzer_enabled) {
    is_buz_on = !is_buz_on;
    digitalWrite(BUZ_PIN, is_buz_on ? LOW : HIGH);
  }
}
