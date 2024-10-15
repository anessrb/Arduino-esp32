#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

const char* ssid = "iPhone di Aness";
const char* password = "12345678";

AsyncWebServer server(80);

// Broche de la LED
const int ledPin = 2;

// Fonction simulée pour la température
float getTemperature() {
  return 25.5; // Valeur simulée
}

// Fonction simulée pour la lumière
int getLightIntensity() {
  return 500; // Valeur simulée
}

void setup() {
  Serial.begin(115200);
  
  // Configuration de la LED
  pinMode(ledPin, OUTPUT);

  // Connexion WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi...");
  }
  Serial.println("Connecté au WiFi");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());

  // Route pour les capteurs
  server.on("/sensors", HTTP_GET, [](AsyncWebServerRequest *request){
    StaticJsonDocument<200> doc;
    doc["temperature"] = getTemperature();
    doc["light"] = getLightIntensity();
    
    String response;
    serializeJson(doc, response);
    request->send(200, "application/json", response);
  });

  // Route pour la LED
  server.on("/led", HTTP_POST, [](AsyncWebServerRequest *request){
    if (request->hasParam("state", true)) {
      AsyncWebParameter* p = request->getParam("state", true);
      String state = p->value();
      
      if (state == "on") {
        digitalWrite(ledPin, HIGH);
        request->send(200, "text/plain", "LED allumée");
      } else if (state == "off") {
        digitalWrite(ledPin, LOW);
        request->send(200, "text/plain", "LED éteinte");
      } else {
        request->send(400, "text/plain", "État invalide");
      }
    } else {
      request->send(400, "text/plain", "Paramètre 'state' manquant");
    }
  });

  // Démarrage du serveur
  server.begin();
}

void loop() {
  // Le serveur web asynchrone gère les requêtes automatiquement
  // Vous pouvez ajouter ici d'autres tâches si nécessaire
  delay(10);
}