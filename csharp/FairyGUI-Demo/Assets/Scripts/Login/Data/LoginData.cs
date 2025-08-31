using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class LoginData
{
    public string userName;
    public string passWord;
    public bool rememberPw;
    public bool autoLogin;
    public int frontServerID = 0;
}
