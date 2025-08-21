using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class BeginPanel1 : BasePanel1<BeginPanel1>
{
    public UIButton btnBegin;
    public UIButton btnRank;
    public UIButton btnSetting;
    public UIButton btnQuit;
    public override void Init()
    {
        btnBegin.onClick.Add(new EventDelegate(() =>
        {
            ChoosePanel.Instance.ShowMe();
            HideMe();
        }));
        btnRank.onClick.Add(new EventDelegate(() =>
        {
            RankPanel1.Instance.ShowMe();
        }));
        btnSetting.onClick.Add(new EventDelegate(() =>
        {
            SettingPanel1.Instance.ShowMe();
        }));
        btnQuit.onClick.Add(new EventDelegate(() =>
        {
            Application.Quit();
        }));
        
    }

}
