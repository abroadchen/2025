using System.Collections;
using System.Collections.Generic;
using FairyGUI;
using Login;
using UnityEngine;

public class RegisterWindow : Window
{
    protected override void OnInit()
    {
        base.OnInit();
        contentPane = UIPackage.CreateObject("Login", "RegisterWindow").asCom;
        contentPane.MakeFullScreen();
        var panel = contentPane as UI_RegisterWindow;
        panel.m_btnSure.onClick.Add(() =>
        { 
            if (panel.m_inputAN.text.Length <= 6 || panel.m_inputPW.text.Length <= 3)
            {
                UIManager.Instance.ShowWindow<TipWindow>().ChangeInfo("账户必须大于6位密码必须大于3位");
                panel.m_inputAN.text = "";
                panel.m_inputPW.text = "";
                return;
            }

            if (LoginMgr.Instance.RegisterUser(panel.m_inputAN.text, panel.m_inputPW.text))
            {
                var loginPanel = UIManager.Instance.ShowWindow<LoginWindow>();
                loginPanel.SetInfo(panel.m_inputAN.text, panel.m_inputPW.text);
                UIManager.Instance.HideWindow<RegisterWindow>();
            }
            else
            {
                UIManager.Instance.ShowWindow<TipWindow>().ChangeInfo("用户名已存在");
                panel.m_inputAN.text = "";
                panel.m_inputPW.text = "";
            }
        });
        panel.m_btnClose.onClick.Add((() =>
        {
            UIManager.Instance.ShowWindow<LoginWindow>();
            UIManager.Instance.HideWindow<RegisterWindow>();
        }));
    }
    
    protected override void DoShowAnimation()
    {
        contentPane.GetTransition("show").Play(base.DoShowAnimation);
    }

    protected override void DoHideAnimation()
    {
        contentPane.GetTransition("hide").Play(base.DoHideAnimation);
    }
}
