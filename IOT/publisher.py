#install phao-mqtt module
#pip install paho-mqtt
import paho.mqtt.client as mqtt

client = mqtt.Client()
client1 = mqtt.Client()
client.connect("localhost",1883,60)
client1.connect("localhost",1883,60)
#constructor
while True:
        
#connect to Broker
#brokeraddress,portnumber,keepaliveinterval
	    
#payload = raw_input("Enter the payload : ")
#payload1 = raw_input("Enter the new Pyaload : ")
#payload = "Hello"
    topic_name = "cdac/acts/acpm"
    topic_name1 = "cdac/acts/pune" 
    payload = input("Enter the payload : ")
    client.publish(topic_name,payload)   
    payload1 = input("Enter the new Pyaload : ")   
    client1.publish(topic_name1,payload1)
#client.disconnect()
