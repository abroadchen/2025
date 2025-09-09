using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MP_MainPanel : BasePanel
{
    // Start is called before the first frame update
    void Start()
    {
        UpdateInfo(PlayerModel.Data);
        //PlayerModel.Data.AddEventListener(UpdateInfo);
        
        EventCenter.GetInstance().AddEventListener<PlayerModel>("玩家数据", UpdateInfo);
    }

    // Update is called once per frame
    protected override void OnClick(string btnName)
    {
        base.OnClick(btnName);
        switch (btnName)
        {
            case "btnRole":
                UIManager.GetInstance().ShowPanel<MP_RolePanel>("RolePanel");
                break;
        }
    }

    public void UpdateInfo(PlayerModel data)
    {
        GetControl<Text>("txtName").text = data.PlayerName;
        GetControl<Text>("txtLev").text = "LV." + data.Lev;
        GetControl<Text>("txtMoney").text = data.Money.ToString();
        GetControl<Text>("txtGem").text = data.Gem.ToString();
        GetControl<Text>("txtPower").text = data.Power.ToString();
    }

    private void OnDestroy()
    {
        //PlayerModel.Data.RemoveEventListener(UpdateInfo);
        EventCenter.GetInstance().RemoveEventListener<PlayerModel>("玩家数据", UpdateInfo);
    }
}
