using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameDataMgr
{
    private static GameDataMgr instance = new GameDataMgr();
    public static GameDataMgr Instance { get => instance; }
    public MusicData musicData;
    public RankList rankData;

    private GameDataMgr()
    {
        musicData = PlayerPrefsDataMgr.Instance.LoadData(typeof(MusicData), "Music") as MusicData;
        if (!musicData.notFirst)
        {
            musicData.notFirst = true;
            musicData.isOpenBK = true;
            musicData.isOpenSound = true;
            musicData.bkValue = 1;
            musicData.soundValue = 1;
            PlayerPrefsDataMgr.Instance.SaveData(musicData, "Music");
        }
        rankData = PlayerPrefsDataMgr.Instance.LoadData(typeof(RankList), "Rank") as RankList;
    }

    public void AddRankInfo(string name, int score, float time)
    {
        rankData.list.Add(new RankInfo(name, score, time));
        rankData.list.Sort((a, b) => a.time < b.time ? -1 : 1);
        for (var i = rankData.list.Count - 1; i >= 10; i--)
        {
            rankData.list.RemoveAt(i);
        }
        PlayerPrefsDataMgr.Instance.SaveData(rankData, "Rank");
    }

    public void OpenOrCloseMusic(bool isOpen)
    {
        musicData.isOpenBK = isOpen;
        BKMusic.Instance.ChangeOpen(isOpen);
        PlayerPrefsDataMgr.Instance.SaveData(musicData, "Music");
    }

    public void OpenOrCloseSound(bool isOpen)
    {
        musicData.isOpenSound = isOpen;
        PlayerPrefsDataMgr.Instance.SaveData(musicData, "Music");
    }

    public void ChangeBKValue(float value)
    {
        musicData.bkValue = value;
        BKMusic.Instance.ChangeValue(value);
        PlayerPrefsDataMgr.Instance.SaveData(musicData, "Music");
    }

    public void ChangeSoundValue(float value)
    {
        musicData.soundValue = value;
        PlayerPrefsDataMgr.Instance.SaveData(musicData, "Music");
    }
}
