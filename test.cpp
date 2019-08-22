#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
#include "MQTT_Func.h"
#include "sqlite3.h"

#include "enumeration.h"
#include "Lib/resource.h"
#include "Lib/JSON.h"
#include "MN_AEreg.h"

#if !defined(WIN32)
#include <unistd.h>
#else
#include <windows.h>
#endif

#if defined(_WRS_KERNEL)
#include <OsWrapper.h>
#endif



//////////////////




/////////////////

int main() {
     
    sqlite3 *db;
    int rc;
    char *zErrMsg = 0;
    char *sql;
    const char* data = "Callback function called";
    int ch;
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    
    //Connect to MQTT Server
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    
    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        //exit(EXIT_FAILURE);
    }
    
    //Create MQTT Subscribe Topic for Initial Registration Request
    create_Topic("reg_req", "Sensor011", "CSE_01");
    //create_Topic("reg_req", "+", "CSE_01");
    
    //Subscribe to the Topic
    printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
           "Press Q<Enter> to quit\n\n", TOPIC, CLIENTID, QOS);
    MQTTClient_subscribe(client, TOPIC, QOS);
    
    // Register CSE
    
    //Local AE Registration
    Response Resp;
    Registration(client);
    process_msg(buf);
    if(op == 1&& ty == 2) {
	//Create response code
	Response Resp;
	RES.Resource_Type = ty;
	RES.resourceName = rn;
	//RES.resourceID = ;
	//RES.parentID = ;
	//RES.creationTime = ;          //ct     1
	//RES.lastModifiedTime = ;      //lt     1
	//RES.labels = ;
	RAE.App_ID = api;
	RAE.requestReachability = rr;
	RAE.AE_ID = "SAE01";
	aei = "SAE01";
	RAE.pointOfAccess = poa; 
	
	Resp.responseStatusCode = 2001;
	Resp.Request_Identifier = rqi;
	Resp.To = From;
	Resp.From = CSE_ID;
	lcl = true;
	buf = Create_Resp(Resp);
	process_msg(buf);
    }
    // Create TABLE for Registration
    
    sql = "CREATE TABLE Registration("  \
      "AE_ID TEXT PRIMARY KEY     NOT NULL," \
      "API           TEXT    NOT NULL," \
      "ResourceName            TEXT     NOT NULL," \
      "RequestReachability        TEXT );";
    
    rc = sqlite3_open("Middle Node.db", &db);

    if( rc ) {
	    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	    return(0);
    }	
    else 	fprintf(stderr, "Opened database successfully\n");
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
    } 
    else        fprintf(stdout, "Registration Table created successfully\n");
    char * temp12 = "123";
    //Store in Local DB
    sql = "INSERT INTO Registration (AE_ID,API,ResourceName,RequestReachability)"\
    "VALUES ('temp12','temp12','temp12',' temp12 ');";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ) {
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
    } 
    else       fprintf(stdout, "Operation done successfully\n");
    
    
/*	sql = "CREATE TABLE COMPANY("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "AGE            INT     NOT NULL," \
      "ADDRESS        CHAR(50)," \
      "SALARY         REAL );";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
    } else {
       fprintf(stdout, "Table created successfully\n");
    }     
    
    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
    } else {
       fprintf(stdout, "Table created successfully\n");
    }     
    * 
    
    sql = "SELECT * from COMPANY";

    /* Execute SQL statement 
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   
    if( rc != SQLITE_OK ) {
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
    } else {
       fprintf(stdout, "Operation done successfully\n");
    }
    
    /* Create merged SQL statement 
    sql = "DELETE from COMPANY where ID=2; " \
          "SELECT * from COMPANY";

    /* Execute SQL statement 
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   
    if( rc != SQLITE_OK ) {
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
    } else {
       fprintf(stdout, "Operation done successfully\n");
    }
    * 
    * */
    
    sqlite3_close(db);
    

    
    
    
    pubmsg.payload = PAYLOAD;
    pubmsg.payloadlen = (int)strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n"
            "on topic %s for client with ClientID: %s\n",
            (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);
    

	
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);    
    MbedJSONValue demo;
	
    const  char* json = "{\"my_array\": [\"demo_string\", 10], \"my_boolean\": true}";
    
	       //parse the previous string and fill the object demo
    parse(demo, json);
    
    string my_str;
    int my_int;
    bool my_bool;
    
    my_str = demo["my_array"][0].get<std::string>();
    my_int = demo["my_array"][1].get<int>();
    my_bool = demo["my_boolean"].get<bool>();
    
    printf("my_str: %s\r\n", my_str.c_str());
    printf("my_int: %d\r\n", my_int);
    printf("my_bool: %s\r\n", my_bool ? "true" : "false");

    Request Req;
    //AE_ID[0] = 'S';                    //Initial registration
    //struct Mendatory m1;
    Req.To = CSE_ID;
    Req.From = "S";
    Req.Request_Identifier = "m_createAE22";
    Req.Resource_Type = 2;
    Req.Operation = 1;
    lcl = true;

    //struct CreateAE CAE;
    CAE.resourceName = CSE_ID;
    CAE.requestReachability = true;
    CAE.App_ID = "C01.com.farm.app01";
    const char* buf;
    buf = Create_Req(Req);
    return 0;
	
}
