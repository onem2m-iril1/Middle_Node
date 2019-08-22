#define ADDRESS     "tcp://192.168.0.113:1883"
#define CLIENTID    "MiddleNode"
#define QOS         1
#define TIMEOUT     10000L

char* PAYLOAD  =	"Hello |";
const char* buf;

char TOPIC[40] = "TEST";
volatile MQTTClient_deliveryToken deliveredtoken;


void create_Topic(char* tpc_ty, char* orignator, char* receiver)
{
    sprintf(TOPIC,"/oneM2M/%s/%s/%s",tpc_ty,orignator,receiver);
    printf("Topic is %s", TOPIC);
}


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}


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
    printf("   message: %s",message->payload);

    /*payloadptr = message->payload;
    for(i=0; i<message->payloadlen; i++)
    {
        putchar(*payloadptr++);
    }*/
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
