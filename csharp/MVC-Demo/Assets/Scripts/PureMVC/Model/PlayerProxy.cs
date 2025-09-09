using System.Collections;
using System.Collections.Generic;
using PureMVC.Patterns.Proxy;
using UnityEngine;

public class PlayerProxy : Proxy
{
    
    public new const string NAME = "PlayerProxy";
    public PlayerProxy() : base(PlayerProxy.NAME)
    {
        var data = new PlayerDataObj();

        data.playerName = PlayerPrefs.GetString("PlayerName", "xx");
        data.lev = PlayerPrefs.GetInt("PlayerLev", 1);
        data.money = PlayerPrefs.GetInt("PlayerMoney", 0);
        data.gem = PlayerPrefs.GetInt("PlayerGem", 0);
        data.power = PlayerPrefs.GetInt("PlayerPower", 0);
        data.hp = PlayerPrefs.GetInt("PlayerHp", 100);
        data.atk = PlayerPrefs.GetInt("PlayerAtk", 10);
        data.def = PlayerPrefs.GetInt("PlayerDef", 10);
        data.crit = PlayerPrefs.GetInt("PlayerCrit", 10);
        data.miss = PlayerPrefs.GetInt("PlayerMiss", 10);
        data.luck = PlayerPrefs.GetInt("PlayerLuck", 10);
        
        Data = data;
    }

    public void LevUp()
    {
        var data = Data as PlayerDataObj;
        data.lev += 1;
        data.hp += data.lev;
        data.atk += data.lev;
        data.def += data.lev;
        data.crit += data.lev;
        data.miss += data.lev;
        data.luck += data.lev;
        
        //SaveData();
    }

    public void SaveData()
    {
        var data = Data as PlayerDataObj;
        PlayerPrefs.SetString("PlayerName", data.playerName);
        PlayerPrefs.SetInt("PlayerLev", data.lev);
        PlayerPrefs.SetInt("PlayerMoney", data.money);
        PlayerPrefs.SetInt("PlayerGem", data.gem);
        PlayerPrefs.SetInt("PlayerPower", data.power);
        PlayerPrefs.SetInt("PlayerHp", data.hp);
        PlayerPrefs.SetInt("PlayerAtk", data.atk);
        PlayerPrefs.SetInt("PlayerDef", data.def);
        PlayerPrefs.SetInt("PlayerCrit", data.crit);
        PlayerPrefs.SetInt("PlayerMiss", data.miss);
        PlayerPrefs.SetInt("PlayerLuck", data.luck);
    }
}
