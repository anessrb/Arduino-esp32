# main.py
from microWebSrv import MicroWebSrv
import machine
import time

# Simulons des lectures de capteurs
def get_temperature():
    return 25.5  # Remplacez ceci par une vraie lecture de capteur

def get_light():
    return 500  # Remplacez ceci par une vraie lecture de capteur

# Configurons la LED
led = machine.Pin(2, machine.Pin.OUT)  # Supposons que la LED est sur la broche 2

# Handlers pour l'API
def handle_sensors(httpClient, httpResponse):
    sensors = {
        "temperature": get_temperature(),
        "light": get_light()
    }
    httpResponse.WriteResponseJSONOk(sensors)

def handle_led(httpClient, httpResponse):
    data = httpClient.ReadRequestContentAsJSON()
    if 'state' in data:
        if data['state']:
            led.on()
        else:
            led.off()
        httpResponse.WriteResponseOk()
    else:
        httpResponse.WriteResponseBadRequest()

# Configuration des routes
routeHandlers = [
    ('/sensors', 'GET', handle_sensors),
    ('/led', 'POST', handle_led)
]

# Création et démarrage du serveur
srv = MicroWebSrv(routeHandlers=routeHandlers)
srv.Start(threaded=True)

# Boucle principale
while True:
    # Ici, vous pouvez ajouter du code pour mettre à jour l'affichage, 
    # vérifier les boutons, etc.
    time.sleep(1)