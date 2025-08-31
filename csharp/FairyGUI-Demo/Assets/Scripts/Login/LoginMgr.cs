using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LoginMgr
{
    private static LoginMgr instance = new LoginMgr();
    public static LoginMgr Instance => instance;

    public LoginData loginData;

    private RegisterData registerData;
    LoginMgr()
    {
        loginData = BinaryDataMgr.Instance.Load<LoginData>("LoginData") ?? new LoginData();
        registerData = BinaryDataMgr.Instance.Load<RegisterData>("RegisterData") ?? new RegisterData();
    }
    
    public void SaveLoginData()
    {
        BinaryDataMgr.Instance.Save(loginData, "LoginData");
    }
    
    public void SaveRegisterData()
    {
        BinaryDataMgr.Instance.Save(registerData, "RegisterData");
    }

    public bool RegisterUser(string userName, string passWord)
    {
        if (registerData.registerDic.ContainsKey(userName)) return false;
        registerData.registerDic.Add(userName, passWord);
        SaveRegisterData();
        ClearLoginData();
        return true;
    }

    public bool CheckInfo(string userName, string passWord)
    {
        if (!registerData.registerDic.ContainsKey(userName)) return false;
        return registerData.registerDic[userName] == passWord;
    }

    public void ClearLoginData()
    {
        loginData.frontServerID = 0;
        loginData.autoLogin = false;
        loginData.rememberPw = false;
    }
}
