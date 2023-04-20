using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Deep;
using Deep.Sock;

class Test : MonoBehaviour 
{
    UDPSocket test = new UDPSocket(1024);
    
    private void Start()
    {
        test.Open();
        test.Bind(new System.Net.IPEndPoint(System.Net.IPAddress.Any, 1000));
    }
}
