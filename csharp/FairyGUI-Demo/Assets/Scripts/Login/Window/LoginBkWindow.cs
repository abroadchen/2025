using System.Collections;
using System.Collections.Generic;
using FairyGUI;
using UnityEngine;

public class LoginBkWindow : Window
{
    protected override void OnInit()
    {
        base.OnInit();
        contentPane = UIPackage.CreateObject("Login", "LoginBKWindow").asCom;
        contentPane.MakeFullScreen();
    }
}
