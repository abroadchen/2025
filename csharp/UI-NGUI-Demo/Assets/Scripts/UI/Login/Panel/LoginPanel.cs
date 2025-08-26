using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LoginPanel : BasePanel<LoginPanel>
{
    public UIInput inputUserName;
    public UIInput inputPassword;
    public UIButton btnRegister;
    public UIButton btnLogin;
    public UIToggle togRemember;
    public UIToggle togAutoLogin;
    public override void Init()
    {
        btnRegister.onClick.Add(new EventDelegate(() =>
        {
            HideMe();
            RegisterPanel.Instance.ShowMe();
        }));
        btnLogin.onClick.Add(new EventDelegate(() =>
        {
            if (LoginMgr.Instance.CheckInfo(inputUserName.value, inputPassword.value))
            {
                LoginMgr.Instance.LoginData.userName = inputUserName.value;
                LoginMgr.Instance.LoginData.password = inputPassword.value;
                LoginMgr.Instance.LoginData.rememberPW = togRemember.value;
                LoginMgr.Instance.LoginData.autoLogin = togAutoLogin.value;

                if (LoginMgr.Instance.LoginData.frontServerID == 0)
                {
                    ChooseServerPanel.Instance.ShowMe();
                }
                else
                {
                    ServerPanel.Instance.ShowMe();
                }
                
                HideMe();
            }
            else
            {
                TipPanel.Instance.ChangeInfo("用户名或密码错误");
                TipPanel.Instance.ShowMe();
            }




            LoginMgr.Instance.SaveLoginData();
        }));
        togRemember.onChange.Add(new EventDelegate(() =>
        {
            if (!togRemember.value)
            {
                togAutoLogin.value = false;
            }
        }));
        togAutoLogin.onChange.Add(new EventDelegate(() =>
        {
            if (togAutoLogin.value)
            {
                togRemember.value = true;
            }
        }));


        LoginData data = LoginMgr.Instance.LoginData;
        togRemember.value = data.rememberPW;
        togAutoLogin.value = data.autoLogin;
        if (data.userName != "")
            inputUserName.value = data.userName;
        if (data.rememberPW)
            inputPassword.value = data.password;
        if (data.autoLogin)
        { 
            if (LoginMgr.Instance.CheckInfo(inputUserName.value, inputPassword.value))
            {

                if (LoginMgr.Instance.LoginData.frontServerID == 0)
                {
                    ChooseServerPanel.Instance.ShowMe();
                }
                else
                {
                    ServerPanel.Instance.ShowMe();
                }
                
                HideMe();
            }
            else
            {
                TipPanel.Instance.ChangeInfo("用户名或密码错误");
                TipPanel.Instance.ShowMe();
            }
        }
    }

    public void SetInfo(string userName, string password)
    {
        inputUserName.value = userName;
        inputPassword.value = password;
    }
}
