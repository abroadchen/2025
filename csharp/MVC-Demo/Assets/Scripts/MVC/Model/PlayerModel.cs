using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class PlayerModel
{
    public string PlayerName { get; private set; }

    public int Lev { get; private set; }

    public int Money { get; private set; }

    public int Gem { get; private set; }

    public int Power { get; private set; }

    public int Hp { get; private set; }

    public int Atk { get; private set; }

    public int Def { get; private set; }

    public int Crit { get; private set; }

    public int Miss { get; private set; }

    public int Luck { get; private set; }

    //private event UnityAction<PlayerModel> updateEvent;

    private static PlayerModel data = null;

    public static PlayerModel Data
    {
        get
        {
            if (data != null) return data;
            data = new PlayerModel();
            data.Init();

            return data;
        }
    }

    public void Init()
    {
        PlayerName = PlayerPrefs.GetString("PlayerName", "xx");
        Lev = PlayerPrefs.GetInt("PlayerLev", 1);
        Money = PlayerPrefs.GetInt("PlayerMoney", 0);
        Gem = PlayerPrefs.GetInt("PlayerGem", 0);
        Power = PlayerPrefs.GetInt("PlayerPower", 0);
        Hp = PlayerPrefs.GetInt("PlayerHp", 100);
        Atk = PlayerPrefs.GetInt("PlayerAtk", 10);
        Def = PlayerPrefs.GetInt("PlayerDef", 10);
        Crit = PlayerPrefs.GetInt("PlayerCrit", 10);
        Miss = PlayerPrefs.GetInt("PlayerMiss", 10);
        Luck = PlayerPrefs.GetInt("PlayerLuck", 10);
    }

    public void LevUp()
    {
        Lev += 1;
        Hp += Lev;
        Atk += Lev;
        Def += Lev;
        Crit += Lev;
        Miss += Lev;
        Luck += Lev;
        
        SaveData();
    }

    public void SaveData()
    {
        PlayerPrefs.SetString("PlayerName", PlayerName);
        PlayerPrefs.SetInt("PlayerLev", Lev);
        PlayerPrefs.SetInt("PlayerMoney", Money);
        PlayerPrefs.SetInt("PlayerGem", Gem);
        PlayerPrefs.SetInt("PlayerPower", Power);
        PlayerPrefs.SetInt("PlayerHp", Hp);
        PlayerPrefs.SetInt("PlayerAtk", Atk);
        PlayerPrefs.SetInt("PlayerDef", Def);
        PlayerPrefs.SetInt("PlayerCrit", Crit);
        PlayerPrefs.SetInt("PlayerMiss", Miss);
        PlayerPrefs.SetInt("PlayerLuck", Luck);
        
        UpdateInfo();
    }

    public void AddEventListener(UnityAction<PlayerModel> function)
    {
        //updateEvent += function;
    }
    
    public void RemoveEventListener(UnityAction<PlayerModel> function)
    {
        //updateEvent -= function;
    }

    private void UpdateInfo()
    {
        //updateEvent?.Invoke(this);
        EventCenter.GetInstance().EventTrigger<PlayerModel>("玩家数据", this);
    }
}
