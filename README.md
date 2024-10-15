# Projet ESP32 avec capteur DHT22, LED, écran TFT et API RESTful

Ce projet utilise un microcontrôleur ESP32 pour afficher des données de capteur (température), contrôler une LED en fonction de la température et fournir une API RESTful pour interagir avec ces composants. L'écran TFT intégré permet d'afficher les informations de connexion et l'état des capteurs en temps réel.

## Matériel requis

- ESP32 avec écran TFT intégré (ex. TTGO T-Display)
- Capteur de température et d'humidité DHT22
- LED et résistance (optionnelle)
- Connexion WiFi
- Bibliothèques Arduino requises (voir la section Installation)

## Fonctionnalités

- **Affichage de la température sur un écran TFT** : La température est mesurée toutes les 5 secondes via le capteur DHT22 et affichée sur l'écran.
- **Contrôle de la LED** : La LED est allumée lorsque la température dépasse un seuil défini (par défaut : 25°C). Ce seuil peut être modifié via une requête API.
- **API RESTful** :
  - `/sensors` : Retourne les données des capteurs (température).
  - `/sensors/temp` : Retourne uniquement la température.
  - `/led` : Permet d'allumer ou d'éteindre la LED.
  - `/led/threshold` : Permet de modifier le seuil de température pour allumer la LED.

## Schéma de câblage

1. **Capteur DHT22** :
   - VCC → 3.3V
   - GND → GND
   - DATA → Pin GPIO 4 (DHTPIN)
   
2. **LED** :
   - Anode (patte longue) → Résistance (330Ω ou 220Ω) → Pin GPIO 5 (LEDPIN)
   - Cathode → GND

## Installation

1. **Installer les bibliothèques Arduino nécessaires** :
   - [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
   - [SimpleDHT](https://github.com/winlinvip/SimpleDHT)
   - [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)

2. **Configuration de l'écran TFT** :
   - Modifier le fichier `User_Setup_Select.h` dans la bibliothèque TFT_eSPI pour choisir les bons réglages pour votre écran.

3. **Connexion au WiFi** :
   - Modifiez les variables `ssid` et `password` dans le code pour vous connecter à votre réseau WiFi.

4. **Téléverser le code sur l'ESP32** :
   - Utilisez l'IDE Arduino pour téléverser le code.

## API Endpoints

### 1. Récupérer les données des capteurs

- **Méthode** : `GET`
- **Endpoint** : `/sensors`
- **Réponse** :
  ```json
  {
    "sensors": [
      {"id": "temp", "type": "temperature", "value": 22.5},
      {"id": "light", "type": "light", "value": 0}
    ]
  }
