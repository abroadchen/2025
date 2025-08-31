using System.Collections;
using System.Collections.Generic;
using FairyGUI;
using Login;
using UnityEngine;

public class TipWindow : Window
{
    protected override void OnInit()
    {
        base.OnInit();
        //UIPackage package = UIPackage.AddPackage("UI/Login");
        //foreach (var item in package.dependencies)
        //{
        //    UIPackage.AddPackage("UI/" + item["name"]);
        //}
        //contentPane = UIPackage.CreateObject("Login", "TipWindow").asCom;
        contentPane = UIManager.Instance.LoadComponent("Login", "TipWindow");
        contentPane.MakeFullScreen();
        modal = true;
    }

    public void ChangeInfo(string info)
    {
        (contentPane as UI_TipWindow).m_frame.m_txtInfo.text = info;
    }

    protected override void DoShowAnimation()
    {
        contentPane.GetTransition("show").Play(base.DoShowAnimation);
    }

    protected override void DoHideAnimation()
    {
        contentPane.GetTransition("hide").Play(base.DoShowAnimation);
    }
}
