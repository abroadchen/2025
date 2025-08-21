using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameDataMgr1
{
    private static GameDataMgr1 instance = new GameDataMgr1();
    public static GameDataMgr1 Instance => instance;

    public MusicData1 musicData;

    public RankData1 rankData;

    public RoleData roleData;

    public BulletData bulletData;

    public FireData fireData;

    public int nowSelHeroIndex = 0;

    private GameDataMgr1()
    {
        musicData = XmlDataMgr.Instance.LoadData(typeof(MusicData1), "MusicData") as MusicData1;
        rankData = XmlDataMgr.Instance.LoadData(typeof(RankData1), "RankData") as RankData1;
        roleData = XmlDataMgr.Instance.LoadData(typeof(RoleData), "RoleData") as RoleData;
        bulletData = XmlDataMgr.Instance.LoadData(typeof(BulletData), "BulletData") as BulletData;
        fireData = XmlDataMgr.Instance.LoadData(typeof(FireData), "FireData") as FireData;
    }

    public void SaveMusicData()
    {
        XmlDataMgr.Instance.SaveData(musicData, "MusicData");
    }

    public void SetMusicIsOpen(bool isOpen)
    {
        musicData.musicIsOpen = isOpen;
        BKMusic1.Instance.SetBKMusicIsOpen(isOpen);
    }

    public void SetSoundIsOpen(bool isOpen)
    {
        musicData.soundIsOpen = isOpen;
    }

    public void SetMusicValue(float value)
    {
        musicData.musicValue = value;
        BKMusic1.Instance.SetBKMusicValue(value);
    }

    public void SetSoundValue(float value)
    {
        musicData.soundValue = value;

    }


    #region 排行榜相关
    public void AddRankData(string name, int time)
    {
        RankInfo1 rankInfo = new RankInfo1();
        rankInfo.name = name;
        rankInfo.time = time;
        rankData.rankList.Add(rankInfo);
        rankData.rankList.Sort((a, b) => a.time > b.time ? -1 : 1);
        if (rankData.rankList.Count > 20)
            rankData.rankList.RemoveAt(20);
        XmlDataMgr.Instance.SaveData(rankData, "RankData");
    }
    #endregion


    #region 玩家数据相关
    public RoleInfo GetNowSelHeroInfo()
    {
        return roleData.roleList[nowSelHeroIndex];
    }
    #endregion
}
