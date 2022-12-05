import paho.mqtt.client as mqtt
import time
import json
from random import randint

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    #client.subscribe("/SENS01/*")

# The callback for when a PUBLISH message is received from the server.

def on_message(client, userdata, msg):
    print("Message received-> " + msg.topic + " " + str(msg.payload))  # Print a received msg
    
    #dt = {"lux": randint(3,6)}
    #client.publish(topic = "/asdasdas/WRITE_SENSDATA", payload = json.dumps(dt))
    #print("publish")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.username_pw_set("manager", "pwd")
client.connect("192.168.1.23", 1883, 60)

lst = [
    "/SENS/01/READ/ALL",
    "/SENS/01/READ/HUM",
    "/SENS/01/READ/TMP",
    "/SENS/01/READ/LUX"
    #"/SENS/01/SYS/RESTART",
    #"/SENS/01/SYS/DETAIL"

]

while True:
    idx = randint(0, len(lst)-1)
    print("Sending: "+ lst[idx][13:])
#    dt = {"lux": 3}
    client.publish(topic = lst[idx], payload = '')
#    print("publish")
    time.sleep(5)
    


# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
#client.loop_forever()
