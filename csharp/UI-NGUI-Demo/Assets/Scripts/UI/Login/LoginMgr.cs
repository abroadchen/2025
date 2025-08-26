using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LoginMgr
{
    static LoginMgr instance = new LoginMgr();
    public static LoginMgr Instance => instance;

    LoginMgr()
    {
        loginData = XmlDataMgr.Instance.LoadData(typeof(LoginData), "LoginData") as LoginData;
        registerData = XmlDataMgr.Instance.LoadData(typeof(RegisterData), "RegisterData") as RegisterData;
        serverInfo = XmlDataMgr.Instance.LoadData(typeof(ServerInfo), "ServerInfo") as ServerInfo;
    }

    LoginData loginData;
    RegisterData registerData;
    public RegisterData RegisterData => registerData;

    public LoginData LoginData => loginData;//只能得不能改

    ServerInfo serverInfo;
    public ServerInfo ServerInfo => serverInfo;

    public void SaveLoginData()
    {
        XmlDataMgr.Instance.SaveData(loginData, "LoginData");
    }

    public void SaveRegisterData()
    {
        XmlDataMgr.Instance.SaveData(registerData, "RegisterData");
    }

    public bool RegisterUser(string userName, string password)
    {
        if (registerData.registerInfo.ContainsKey(userName)) return false;
        registerData.registerInfo.Add(userName, password);
        SaveRegisterData();
        return true;
    }

    public bool CheckInfo(string userName, string password)
    {
        if (!registerData.registerInfo.ContainsKey(userName)) return false;
        return registerData.registerInfo[userName] == password;
    }

    public void ClearLoginData()
    {
        loginData.frontServerID = 0; 
    } 
}
