// #include <WiFi.h>
// #include <ESPAsyncWebServer.h>
// #include <SimpleDHT.h>
// #include <TFT_eSPI.h>

// // Bibliothèque asynchrone pour le web

// #define DHTPIN 4 // Pin du capteur DHT
// #define LEDPIN 5 // Pin de la LED

// SimpleDHT22 dht22(DHTPIN);  // Utilisation de SimpleDHT
// AsyncWebServer server(80);
// TFT_eSPI tft = TFT_eSPI(); // Création de l'objet pour l'écran

// float temperature = 0.0;
// int ledState = LOW;
// int threshold = 25; // Seuil par défaut pour la LED
// unsigned long previousMillis = 0; // Variable pour suivre le temps écoulé
// const long interval = 5000; // Intervalle entre les actualisations de l'écran (5 secondes)
// String ssid = "iPhone di aness"; // Votre SSID

// void setup() {
//     Serial.begin(115200);
//     pinMode(LEDPIN, OUTPUT);

//     // Connexion au WiFi
//     WiFi.begin(ssid.c_str(), "12345678");
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(1000);
//         Serial.println("Connexion au WiFi...");
//     }
//     Serial.println("Connecté au WiFi.");

//     // Initialisation de l'écran
//     tft.init();
//     tft.fillScreen(TFT_BLACK);
//     tft.setTextColor(TFT_WHITE);
//     tft.setTextSize(2);

//     // Affichage du message de connexion centré
//     String message = "Connecté au WiFi de " + ssid;
//     int messageWidth = tft.textWidth(message); // Largeur du texte
//     int centerX = (tft.width() - messageWidth) / 2; // Calculer la position X centrée
//     tft.drawString(message, centerX, 0); // Dessiner le message centré

//     // Initialisation des routes de l'API
//     setupRoutes();
// }

// void setupRoutes() {
//     server.on("/sensors", HTTP_GET, [](AsyncWebServerRequest *request){
//         request->send(200, "application/json", "{\"sensors\":[{\"id\":\"temp\",\"type\":\"temperature\",\"value\":" + String(temperature) + "},{\"id\":\"light\",\"type\":\"light\",\"value\":0}]}");
//     });

//     server.on("/sensors/temp", HTTP_GET, [](AsyncWebServerRequest *request){
//         float humidity = 0; // Variable pour l'humidité, non utilisée ici
//         int err = dht22.read2(&temperature, &humidity, NULL);
//         if (err != SimpleDHTErrSuccess) {
//             Serial.print("Erreur de lecture DHT22, code: "); Serial.println(err);
//             request->send(500, "text/plain", "Erreur de lecture du capteur de température");
//             return;
//         }
//         request->send(200, "application/json", "{\"value\":" + String(temperature) + "}");
//     });

//     server.on("/led", HTTP_POST, [](AsyncWebServerRequest *request){
//         String state = request->getParam("state", true)->value();
//         if (state == "on") {
//             ledState = HIGH;
//         } else {
//             ledState = LOW;
//         }
//         digitalWrite(LEDPIN, ledState);
//         request->send(200, "text/plain", "LED state changed");
//     });

//     server.on("/led/threshold", HTTP_PUT, [](AsyncWebServerRequest *request){
//         String newThreshold = request->getParam("threshold", true)->value();
//         threshold = newThreshold.toInt();
//         request->send(200, "text/plain", "Threshold updated");
//     });

//     server.begin();
// }

// void loop() {
//     float humidity = 0; // Variable pour l'humidité, non utilisée ici
//     unsigned long currentMillis = millis();

//     // Lecture des capteurs toutes les 5 secondes
//     if (currentMillis - previousMillis >= interval) {
//         previousMillis = currentMillis;

//         // Lecture du capteur de température
//         int err = dht22.read2(&temperature, &humidity, NULL);
//         if (err != SimpleDHTErrSuccess) {
//             Serial.print("Erreur de lecture DHT22, code: "); Serial.println(err);
//             return;
//         }

//         // Contrôle de la LED selon le seuil
//         if (temperature > threshold) {
//             digitalWrite(LEDPIN, HIGH);
//             ledState = HIGH;
//         } else {
//             digitalWrite(LEDPIN, LOW);
//             ledState = LOW;
//         }

//         // Effacer l'écran avant d'afficher les nouvelles données
//         tft.fillScreen(TFT_BLACK);

//         // Afficher le message de connexion centré
//         String message = "Connecté au WiFi de " + ssid;
//         int messageWidth = tft.textWidth(message); // Largeur du texte
//         int centerX = (tft.width() - messageWidth) / 2; // Calculer la position X centrée
//         tft.drawString(message, centerX, 0); // Dessiner le message centré
        
//         // Afficher la température et l'état de la LED
//         tft.setCursor(0, 30);  // Changer la position pour ne pas écraser le message WiFi
//         tft.drawString("Temp: " + String(temperature, 1) + " C", 0, 30);  // Affiche la température avec 1 décimale
//         tft.drawString("LED: " + String((ledState == HIGH) ? "ON" : "OFF"), 0, 60);  // Affiche l'état de la LED

//         Serial.println("Écran mis à jour.");
//     }
// }


/*
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SimpleDHT.h>
#include <TFT_eSPI.h>

// Bibliothèque asynchrone pour le web

#define DHTPIN 4 // Pin du capteur DHT
#define LEDPIN 5 // Pin de la LED

SimpleDHT22 dht22(DHTPIN);  // Utilisation de SimpleDHT
AsyncWebServer server(80);
TFT_eSPI tft = TFT_eSPI(); // Création de l'objet pour l'écran

float temperature = 0.0;
int ledState = LOW;
int threshold = 25; // Seuil par défaut pour la LED
unsigned long previousMillis = 0; // Variable pour suivre le temps écoulé
const long interval = 5000; // Intervalle entre les actualisations de l'écran (5 secondes)
String ssid = "iPhone di aness"; // Votre SSID

void displayCenteredMessage(String message, int yOffset = 0) {
    tft.setTextDatum(MC_DATUM); // Positionnement du texte au centre
    tft.setCursor(0, 0); // Réinitialiser le curseur
    int messageWidth = tft.textWidth(message); // Largeur du texte
    int centerX = (tft.width() - messageWidth) / 2; // Calculer la position X centrée
    tft.drawString(message, centerX, (tft.height() / 2) + yOffset); // Dessiner le message centré
}


void setup() {
    Serial.begin(115200);
    pinMode(LEDPIN, OUTPUT);

    // Connexion au WiFi
    WiFi.begin(ssid.c_str(), "12345678");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connexion au WiFi...");
    }
    Serial.println("Connecté au WiFi.");

    // Initialisation de l'écran
    tft.init();
    tft.setRotation(1);      // Rotation de l'affichage si nécessaire
    tft.fillScreen(TFT_BLACK); // Effacer l'écran
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);      // Taille du texte

    // Affichage du message de connexion centré
    displayCenteredMessage("Connecté au WiFi de " + ssid);
    
    // Initialisation des routes de l'API
    setupRoutes();
}

void setupRoutes() {
    server.on("/sensors", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "application/json", "{\"sensors\":[{\"id\":\"temp\",\"type\":\"temperature\",\"value\":" + String(temperature) + "},{\"id\":\"light\",\"type\":\"light\",\"value\":0}]}");
    });

    server.on("/sensors/temp", HTTP_GET, [](AsyncWebServerRequest *request){
        float humidity = 0; // Variable pour l'humidité, non utilisée ici
        int err = dht22.read2(&temperature, &humidity, NULL);
        if (err != SimpleDHTErrSuccess) {
            Serial.print("Erreur de lecture DHT22, code: "); Serial.println(err);
            request->send(500, "text/plain", "Erreur de lecture du capteur de température");
            return;
        }
        request->send(200, "application/json", "{\"value\":" + String(temperature) + "}");
    });

    server.on("/led", HTTP_POST, [](AsyncWebServerRequest *request){
        String state = request->getParam("state", true)->value();
        if (state == "on") {
            ledState = HIGH;
        } else {
            ledState = LOW;
        }
        digitalWrite(LEDPIN, ledState);
        request->send(200, "text/plain", "LED state changed");
    });

    server.on("/led/threshold", HTTP_PUT, [](AsyncWebServerRequest *request){
        String newThreshold = request->getParam("threshold", true)->value();
        threshold = newThreshold.toInt();
        request->send(200, "text/plain", "Threshold updated");
    });

    server.begin();
}

void loop() {
    float humidity = 0; // Variable pour l'humidité, non utilisée ici
    unsigned long currentMillis = millis();

    // Lecture des capteurs toutes les 5 secondes
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        // Lecture du capteur de température
        int err = dht22.read2(&temperature, &humidity, NULL);
        if (err != SimpleDHTErrSuccess) {
            Serial.print("Erreur de lecture DHT22, code: "); Serial.println(err);
            return;
        }

        // Contrôle de la LED selon le seuil
        if (temperature > threshold) {
            digitalWrite(LEDPIN, HIGH);
            ledState = HIGH;
        } else {
            digitalWrite(LEDPIN, LOW);
            ledState = LOW;
        }

        // Effacer l'écran avant d'afficher les nouvelles données
        tft.fillScreen(TFT_BLACK);

        // Afficher le message de connexion centré
        displayCenteredMessage("Connecté au WiFi de " + ssid);

        // Afficher la température et l'état de la LED
        displayCenteredMessage("Temp: " + String(temperature, 1) + " C", 30);  // Affiche la température avec 1 décimale
        displayCenteredMessage("LED: " + String((ledState == HIGH) ? "ON" : "OFF"), 60);  // Affiche l'état de la LED

        Serial.println("Écran mis à jour.");
    }
}
*/

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <TFT_eSPI.h>

// Remplacez par vos identifiants Wi-Fi
const char* ssid = "iPhone di aness";      // Nom du réseau Wi-Fi
const char* password = "12345678";   // Mot de passe du réseau Wi-Fi

TFT_eSPI tft = TFT_eSPI(); // Création de l'objet pour l'écran
AsyncWebServer server(80); // Création du serveur Web

void setup() {
  Serial.begin(115200);

  // Initialisation de l'écran
  tft.init();
  tft.setRotation(1); // Ajustez la rotation si nécessaire
  tft.fillScreen(TFT_BLACK); // Effacer l'écran
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2); // Taille du texte

  // Connexion au Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connexion au WiFi");
  
  // Tentative de connexion au réseau Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnecté au WiFi");
  
  // Récupération et affichage de l'adresse IP
  String ipAddress = WiFi.localIP().toString();
  Serial.print("Adresse IP: ");
  Serial.println(ipAddress);
  
  // Afficher l'adresse IP sur l'écran
  tft.drawString("IP: " + ipAddress, 10, 10);

  // Configuration des routes du serveur Web
  setupRoutes();
}

void setupRoutes() {
  // Route pour afficher un message sur l'écran
  server.on("/message", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("text")) {
      String message = request->getParam("text")->value();
      displayMessage(message); // Affiche le message sur l'écran
      request->send(200, "text/plain", "Message affiché sur l'écran."); // Réponse au client
    } else {
      request->send(400, "text/plain", "Paramètre 'text' manquant."); // Réponse en cas d'erreur
    }
  });

  // Démarrer le serveur
  server.begin();
}

void displayMessage(String message) {
  tft.fillScreen(TFT_BLACK); // Effacer l'écran
  tft.setTextDatum(MC_DATUM); // Positionnement du texte au centre
  tft.drawString(message, tft.width() / 2, tft.height() / 2); // Affichage du message
}

void loop() {
  // La boucle peut rester vide si vous n'avez rien à faire
}

