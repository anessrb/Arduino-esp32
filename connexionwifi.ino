#include <WiFi.h>

// Remplacez ces valeurs par les identifiants de votre réseau WiFi
const char* ssid = "VotreSSID";
const char* password = "VotreMotDePasse";

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connexion au WiFi
  WiFi.begin(ssid, password);
  Serial.print("Tentative de connexion au réseau: ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connecté!");
  Serial.print("Connecté au réseau: ");
  Serial.println(ssid);
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Rien à faire ici pour l'instant
}