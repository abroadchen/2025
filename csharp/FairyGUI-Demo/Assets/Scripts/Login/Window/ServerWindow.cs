using System.Collections;
using System.Collections.Generic;
using FairyGUI;
using Login;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ServerWindow : Window
{
    protected override void OnInit()
    {
        base.OnInit();
        contentPane = UIPackage.CreateObject("Login", "ServerWindow").asCom;
        contentPane.MakeFullScreen();
        var panel = contentPane as UI_ServerWindow;
        panel.m_btnBegin.onClick.Add(() =>
        {
            LoginMgr.Instance.SaveLoginData();
            UIManager.Instance.ClearWindow(true);
            SceneManager.LoadScene("GameScene");
        });
        panel.m_btnChange.onClick.Add(() =>
        {
            UIManager.Instance.ShowWindow<ServerChooseWindow>();
            UIManager.Instance.HideWindow<ServerWindow>();
        });
        panel.m_btnClose.onClick.Add(() =>
        {
            LoginMgr.Instance.loginData.autoLogin = false;
            UIManager.Instance.ShowWindow<LoginWindow>();
            UIManager.Instance.HideWindow<ServerWindow>();
        });
    }

    protected override void OnShown()
    {
        base.OnShown();
        var id = LoginMgr.Instance.loginData.frontServerID;
        var panel = contentPane as UI_ServerWindow;
        if (id == 0)
        {
            panel.m_txtName.text = "请选择服务器";
        }
        else
        {
            var info = BinaryDataMgr.Instance.GetTable<ServerInfoContainer>().dataDic[id];
            panel.m_txtName.text = info.id + "区  " + info.name;
        }
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
}
