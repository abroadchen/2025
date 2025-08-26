using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RegisterPanel : BasePanel<RegisterPanel>
{
    public UIInput inputUserName;
    public UIInput inputPassword;
    public UIButton btnSure;
    public UIButton btnClose;
    public override void Init()
    {
        btnClose.onClick.Add(new EventDelegate(() =>
        {
            HideMe();
            LoginPanel.Instance.ShowMe();
        }));
        btnSure.onClick.Add(new EventDelegate(() =>
        {
            if (inputUserName.value.Length <= 6 ||
            inputPassword.value.Length <= 6)
            {
                TipPanel.Instance.ShowMe();
                TipPanel.Instance.ChangeInfo("用户名或密码长度不能小于6位");
                return;
            }

            if (LoginMgr.Instance.RegisterUser(inputUserName.value, inputPassword.value))
            {
                LoginPanel.Instance.SetInfo(inputUserName.value, inputPassword.value);
                HideMe();
                LoginPanel.Instance.ShowMe();
                LoginMgr.Instance.ClearLoginData();
            }
            else
            {
                TipPanel.Instance.ShowMe();
                TipPanel.Instance.ChangeInfo("用户名已存在");
            }
        }));
        HideMe();
    }
    
    public override void ShowMe()
    {
        base.ShowMe();
        inputUserName.value = "";
        inputPassword.value = "";
    }
}
