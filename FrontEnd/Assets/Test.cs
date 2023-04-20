using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Deep;
using Deep.Net;

class Test : MonoBehaviour 
{
    Channel test = new Channel(1024);
    
    private void Start()
    {
        test.Open();
        test.Bind(new System.Net.IPEndPoint(System.Net.IPAddress.Any, 1000));
    }

    private void OnApplicationQuit()
    {
        test.Dispose();
    }
}
