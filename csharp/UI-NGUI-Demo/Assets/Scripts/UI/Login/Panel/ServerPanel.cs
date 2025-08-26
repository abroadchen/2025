using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ServerPanel : BasePanel<ServerPanel>
{
    public UILabel labInfo;
    public UIButton btnChange;
    public UIButton btnBegin;

    public UIButton btnBack;
    public override void Init()
    {
        btnChange.onClick.Add(new EventDelegate(() =>
        {
            ChooseServerPanel.Instance.ShowMe();
            HideMe();
        }));
        btnBegin.onClick.Add(new EventDelegate(() =>
        {
            LoginMgr.Instance.SaveLoginData();
            SceneManager.LoadScene("GameScene");
        }));
        btnBack.onClick.Add(new EventDelegate(() =>
        {
            LoginPanel.Instance.ShowMe();
            HideMe();
        }));
        HideMe();
    }

    public override void ShowMe()
    {
        base.ShowMe();
        int id = LoginMgr.Instance.LoginData.frontServerID;
        Server info = LoginMgr.Instance.ServerInfo.serverDic[id];
        labInfo.text = info.name;
    }
}
