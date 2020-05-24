import paho.mqtt.client as mqtt

mqtt.Client(client_id="1", clean_session=False, userdata=None, transport="tcp")






def on_connect(client,userdata,flags,rc):
    print("connected withresult ",str(rc))
    topic="sha"
    topic1="xolo"
    client.subscribe(topic)
    client.subscribe(topic1)



def on_message(client,userdata,msg):
    if msg.payload.decode()=="hello":
        print("Recieved %s"%(msg.payload.decode()))
    else:
        
        print("Recieved is not hello %s"%(msg.payload.decode()))


def newmsg(client,userdata,msg):
    print("recieved msg %s"%(msg.payload.decode()))


client=mqtt.Client()
port=1883
keepAlive= 60
host="localhost"


client.connect(host,port,keepAlive)
client.on_connect=on_connect
client.on_message=on_message


#client.message(topic,port,keepAlive)
client.loop_forever()
