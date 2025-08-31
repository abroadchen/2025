using System.Collections;
using System.Collections.Generic;
using UnityEditor.SearchService;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class ServerPanel : BasePanel
{
    public Button btnStart;
    public Button btnChange;
    public Button btnBack;
    public Text txtName;
    public override void Init()
    {
        btnBack.onClick.AddListener(() =>
        {
            if (LoginMgr.Instance.LoginData.isAutoLogin)
            {
                LoginMgr.Instance.LoginData.isAutoLogin = false;
            }
            UIManager.Instance.HidePanel<ServerPanel>();
            UIManager.Instance.ShowPanel<LoginPanel>();
        });
        btnStart.onClick.AddListener(() =>
        {
            UIManager.Instance.HidePanel<ServerPanel>();
            UIManager.Instance.HidePanel<LoginBKPanel>();
            LoginMgr.Instance.SaveLoginData();
            SceneManager.LoadScene("GameScene");
        });
        btnChange.onClick.AddListener(() =>
        {
            UIManager.Instance.ShowPanel<ChooseServerPanel>();
            UIManager.Instance.HidePanel<ServerPanel>();
        });
    }

    public override void ShowMe()
    {
        base.ShowMe();
        int id = LoginMgr.Instance.LoginData.frontServerID;
        if (id <= 0)
        {
            txtName.text = "请选择服务器";
        }
        else
        {
            ServerInfo info = LoginMgr.Instance.ServerData[id - 1];
            txtName.text = info.id + "区 " + info.name;
        }
    }
}
