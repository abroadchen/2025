using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class RegisterPanel : BasePanel
{
    public Button btnSure;
    public Button btnCancel;
    public InputField intputUN;
    public InputField intputPW;
    public override void Init()
    {
        btnCancel.onClick.AddListener(() =>
        {
            UIManager.Instance.HidePanel<RegisterPanel>();
            UIManager.Instance.ShowPanel<LoginPanel>();
        });
        btnSure.onClick.AddListener(() =>
        {
            if (intputPW.text.Length <= 6 || intputUN.text.Length <= 6)
            {
                TipPanel panel = UIManager.Instance.ShowPanel<TipPanel>();
                panel.ChangeInfo("用户名或密码长度不能小于6位");
                return;
            }
            if (LoginMgr.Instance.RegisterUser(intputUN.text, intputPW.text))
            {
                LoginMgr.Instance.ClearLoginData();
                LoginPanel loginPanel = UIManager.Instance.ShowPanel<LoginPanel>();
                loginPanel.SetInfo(intputUN.text, intputPW.text);
                
                UIManager.Instance.HidePanel<RegisterPanel>();
            }
            else
            {
                TipPanel panel = UIManager.Instance.ShowPanel<TipPanel>();
                panel.ChangeInfo("用户已存在");

                intputUN.text = "";
                intputPW.text = "";
            }
        });
    }
}
