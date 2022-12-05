import paho.mqtt.client as mqtt
import time
import json
from random import randint


# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("/SENS/*/WRITE/#")

# The callback for when a PUBLISH message is received from the server.

def on_message(client, userdata, msg):
    #dt = json.loads(msg.payload)
    try:
        print(json.loads(msg.payload))
    except:
        print(msg.payload)
    print("Message received-> " + msg.topic )  # Print a received msg
    print("----------------------------------")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.username_pw_set("consumer", "pwd")
client.connect("192.168.1.23", 1883, 60)




# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()
