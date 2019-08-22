
void Registration(MQTTClient client)
{
    //Create AE
    //Mendatory resources: Operation, To, From, Request Identifier ,Resource Type, Content 
    //Resource Specific Attributes [M]: App-ID, requestReachability, supportedReleaseVersions
    //                              [0]: PointofAccess, ResourceName
    Request Req;
    AE_ID = "S";                    //Initial registration
    //struct Mendatory m1;
    Req.To = CSE_ID; 
    Req.From = AE_ID;
    Req.Request_Identifier = "m_createAE22";
    Req.Resource_Type = 2;
    Req.Operation = 1;
    lcl = true;
    
    //struct CreateAE CAE;
    CAE.resourceName = CLIENTID;
    CAE.requestReachability = true;
    CAE.App_ID = "C01.com.farm.app01";
    buf = Create_Req(Req);
}
