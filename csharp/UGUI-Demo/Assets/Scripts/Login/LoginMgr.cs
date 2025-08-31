using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LoginMgr
{
    static LoginMgr instance = new LoginMgr();
    public static LoginMgr Instance => instance;

    LoginData loginData;
    public LoginData LoginData => loginData;
    RegisterData registerData;
    public RegisterData RegisterData => registerData;

    List<ServerInfo> serverData;
    public List<ServerInfo> ServerData => serverData;
    LoginMgr()
    {
        loginData = JsonMgr.Instance.LoadData<LoginData>("LoginData");
        registerData = JsonMgr.Instance.LoadData<RegisterData>("RegisterData");
        serverData = JsonMgr.Instance.LoadData<List<ServerInfo>>("ServerData");
    }

    public void SaveLoginData()
    {
        JsonMgr.Instance.SaveData(loginData, "LoginData");
    }

    public void SaveRegisterData()
    {
        JsonMgr.Instance.SaveData(registerData, "RegisterData");
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
        if (registerData.registerInfo[userName] != password) return false;
        return true;
    }

    public void ClearLoginData()
    {
        loginData.userName = "";
        loginData.password = "";
        loginData.isAutoLogin = false;
        loginData.isRemember = false;
        loginData.frontServerID = 0;
        SaveLoginData();
    }
}
