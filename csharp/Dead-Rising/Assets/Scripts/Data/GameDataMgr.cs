using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameDataMgr
{
    static GameDataMgr instance = new GameDataMgr();
    public static GameDataMgr Instance => instance;

    public RoleInfo nowSelRole;
    public MusicData musicData;

    public PlayerData playerData;
    public List<RoleInfo> roleInfoList;
    public List<SceneInfo> sceneInfoList;

    public List<MonsterInfo> monsterInfoList;

    public List<TowerInfo> towerInfoList;
    GameDataMgr()
    {
        musicData = JsonMgr.Instance.LoadData<MusicData>("MusicData");
        playerData = JsonMgr.Instance.LoadData<PlayerData>("PlayerData");
        roleInfoList = JsonMgr.Instance.LoadData<List<RoleInfo>>("RoleInfo");
        sceneInfoList = JsonMgr.Instance.LoadData<List<SceneInfo>>("SceneInfo");
        monsterInfoList = JsonMgr.Instance.LoadData<List<MonsterInfo>>("MonsterInfo");
        towerInfoList = JsonMgr.Instance.LoadData<List<TowerInfo>>("TowerInfo");
    }

    public void SaveMusicData()
    {
        JsonMgr.Instance.SaveData(musicData, "MusicData");
    }

    public void SavePlayerData()
    {
        JsonMgr.Instance.SaveData(playerData, "PlayerData");
    }

    public void PlaySound(string resName)
    {
        GameObject musicObj = new GameObject();
        AudioSource a = musicObj.AddComponent<AudioSource>();
        a.clip = Resources.Load<AudioClip>(resName);
        a.volume = musicData.soundValue;
        a.mute = !musicData.soundOpen;
        a.Play();
        GameObject.Destroy(musicObj, a.clip.length);
    }
}
