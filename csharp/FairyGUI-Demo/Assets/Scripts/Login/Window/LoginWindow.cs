using System.Collections;
using System.Collections.Generic;
using FairyGUI;
using Login;
using UnityEngine;

public class LoginWindow : Window
{
    protected override void OnInit()
    {
        base.OnInit();
        contentPane = UIPackage.CreateObject("Login", "LoginWindow").asCom;
        contentPane.MakeFullScreen();
        var panel = contentPane as UI_LoginWindow;
        panel.m_btnSure.onClick.Add(() =>
        {
            if (panel.m_inputAN.text.Length <= 6 || panel.m_inputPW.text.Length <= 3)
            {
                UIManager.Instance.ShowWindow<TipWindow>().ChangeInfo("账户必须大于6位密码必须大于3位");
                return;
            }

            if (LoginMgr.Instance.CheckInfo(panel.m_inputAN.text, panel.m_inputPW.text))
            {
                LoginMgr.Instance.loginData.userName = panel.m_inputAN.text;
                LoginMgr.Instance.loginData.passWord = panel.m_inputPW.text;
                LoginMgr.Instance.loginData.rememberPw = panel.m_cbPW.selected;
                LoginMgr.Instance.loginData.autoLogin = panel.m_cbAuto.selected;
                LoginMgr.Instance.SaveLoginData();
                if (LoginMgr.Instance.loginData.frontServerID == 0)
                {
                    UIManager.Instance.ShowWindow<ServerChooseWindow>();
                }
                else
                {
                    UIManager.Instance.ShowWindow<ServerWindow>();
                }
                UIManager.Instance.HideWindow<LoginWindow>();
            }
            else
            {
                UIManager.Instance.ShowWindow<TipWindow>().ChangeInfo("账户或密码错误");
            }
        });
        panel.m_btnRe.onClick.Add(() =>
        {
            UIManager.Instance.ShowWindow<RegisterWindow>();
            UIManager.Instance.HideWindow<LoginWindow>();
        });
        panel.m_cbPW.onChanged.Add(() =>
        {
            if (!panel.m_cbPW.selected)
                panel.m_cbAuto.selected = false;
        });
        panel.m_cbAuto.onChanged.Add(() =>
        {
            if (panel.m_cbAuto.selected)
                panel.m_cbPW.selected = true;
        });
    }

    protected override void DoShowAnimation()
    {
        base.DoShowAnimation();
        contentPane.GetTransition("show").Play();
    }

    protected override void DoHideAnimation()
    {
        contentPane.GetTransition("hide").Play(base.DoHideAnimation);
    }

    protected override void OnShown()
    {
        base.OnShown();
        var data = LoginMgr.Instance.loginData;
        var panel = contentPane as UI_LoginWindow;
        panel.m_cbPW.selected = data.rememberPw;
        panel.m_cbAuto.selected = data.autoLogin;
        panel.m_inputAN.text = data.userName;
        panel.m_inputPW.text = data.passWord;
        if (data.autoLogin)
        {
            if (LoginMgr.Instance.CheckInfo(panel.m_inputAN.text, panel.m_inputPW.text))
            {

                if (LoginMgr.Instance.loginData.frontServerID == 0)
                {
                    UIManager.Instance.ShowWindow<ServerChooseWindow>();
                }
                else
                {
                    UIManager.Instance.ShowWindow<ServerWindow>();
                }
                UIManager.Instance.HideWindow<LoginWindow>();
            }
            else
            {
                UIManager.Instance.ShowWindow<TipWindow>().ChangeInfo("账户或密码错误");
            } 
        }
    }

    public void SetInfo(string userName, string passWord)
    {
        var panel = contentPane as UI_LoginWindow;
        panel.m_inputAN.text = userName;
        panel.m_inputPW.text = passWord;
    }
}
