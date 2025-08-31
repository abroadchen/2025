using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LoginPanel : BasePanel
{
    public Button btnRegister;
    public Button btnSure;
    public InputField intputUN;
    public InputField intputPW;
    public Toggle togPW;
    public Toggle togAuto;
    public override void Init()
    {
        btnRegister.onClick.AddListener(() =>
        {
            UIManager.Instance.ShowPanel<RegisterPanel>();
            UIManager.Instance.HidePanel<LoginPanel>();
        });
        btnSure.onClick.AddListener(() =>
        {
            if (intputPW.text.Length <= 6 || intputUN.text.Length <= 6)
            {
                TipPanel panel = UIManager.Instance.ShowPanel<TipPanel>();
                panel.ChangeInfo("用户名或密码长度不能小于6位");
                return;
            }
            if (LoginMgr.Instance.CheckInfo(intputUN.text, intputPW.text))
            {
                LoginMgr.Instance.LoginData.userName = intputUN.text;
                LoginMgr.Instance.LoginData.password = intputPW.text;
                LoginMgr.Instance.LoginData.isRemember = togPW.isOn;
                LoginMgr.Instance.LoginData.isAutoLogin = togAuto.isOn;
                LoginMgr.Instance.SaveLoginData();

                if (LoginMgr.Instance.LoginData.frontServerID <= 0)
                {
                    UIManager.Instance.ShowPanel<ChooseServerPanel>();
                }
                else
                {
                    UIManager.Instance.ShowPanel<ServerPanel>();
                } 

                UIManager.Instance.HidePanel<LoginPanel>();
            }
            else
            {
                UIManager.Instance.ShowPanel<TipPanel>().ChangeInfo("用户名或密码错误");
            }
        });
        togPW.onValueChanged.AddListener((isOn) =>
        {
            if (!isOn) togAuto.isOn = false;
        });
        togAuto.onValueChanged.AddListener((isOn) =>
        {
            if (isOn) togPW.isOn = true;
        });
    }

    public override void ShowMe()
    {
        base.ShowMe();
        LoginData loginData = LoginMgr.Instance.LoginData;
        togPW.isOn = loginData.isRemember;
        togAuto.isOn = loginData.isAutoLogin;
        intputUN.text = loginData.userName;
        if (togPW.isOn) intputPW.text = loginData.password;
        if (togAuto.isOn)
        {
            if (LoginMgr.Instance.CheckInfo(intputUN.text, intputPW.text))
            {
                if (LoginMgr.Instance.LoginData.frontServerID <= 0)
                {
                    UIManager.Instance.ShowPanel<ChooseServerPanel>();
                }
                else
                {
                    UIManager.Instance.ShowPanel<ServerPanel>();
                }

                UIManager.Instance.HidePanel<LoginPanel>(false);
            }
            else
            {
                TipPanel panel = UIManager.Instance.ShowPanel<TipPanel>();
                panel.ChangeInfo("用户名或密码错误");
            }
        }
    }

    public void SetInfo(string userName, string password)
    {
        intputUN.text = userName;
        intputPW.text = password;
    }
}
