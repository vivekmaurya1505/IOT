#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"   //Header FIle
#define ADDRESS     "tcp://localhost:1883" //Broker address
#define CLIENTID    "ExampleClientPub" //Client ID (Optional)
#define TOPIC       "MQTT Examples" // Topic Name
#define PAYLOAD     "Hello World!" //Msg or Paload
#define QOS         1				//Quality of Service
#define TIMEOUT     10000L			//Maximum time
volatile MQTTClient_deliveryToken deliveredtoken; //Instance of Delivary token
void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)

{
    int i;
    char* payloadptr;
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");
    payloadptr = message->payload;
    for(i=0; i<message->payloadlen; i++)
    {
        putchar(*payloadptr++);
    }
    putchar('\n');
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}
void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}

// Main function
int main(int argc, char* argv[])
{
    MQTTClient client; //client instance
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg =  MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;
// Creating a MQTT Client
    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
//Decalring Keep alive interval    
conn_opts.keepAliveInterval = 20;
// Clean session - True or False    
conn_opts.cleansession = 1;

//Async -  setting call back
    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);
//return code
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
//If connection sucessful

    pubmsg.payload = PAYLOAD; //define payload
    pubmsg.payloadlen = strlen(PAYLOAD); //lenght of payload
//Qulity of service    
pubmsg.qos = QOS;
//Retain flag    
pubmsg.retained = 0;
//Delivered token    
deliveredtoken = 0;
//Publish a message    
MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);


    printf("Waiting for publication of %s\n"
            "on topic %s for client with ClientID: %s\n",
            PAYLOAD, TOPIC, CLIENTID);
//Match the delivary token   
 while(deliveredtoken != token);
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    
return rc;
}
