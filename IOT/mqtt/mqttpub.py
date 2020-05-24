import paho.mqtt.client as mqtt


mqtt.Client(client_id="1", clean_session=False, userdata=None, transport="tcp")

client=mqtt.Client()

client.connect("127.0.0.1",1883,60)


client.loop_start()


while True:
    payload=input("hello")
    client.publish("sha",payload,qos=0,retain=False)
    #client.publish("sha",payload)
    
client.loop_forever()
