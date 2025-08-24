using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class GameLevelMgr
{
    static GameLevelMgr instance = new GameLevelMgr();
    public static GameLevelMgr Instance => instance;

    public PlayerObject player;

    List<MonsterPoint> monsterPointList = new List<MonsterPoint>();
    int nowWaveNum = 0;
    int maxWaveNum = 0;
    // int nowMonsterNum = 0;

    List<MonsterObject> monsterList = new List<MonsterObject>();

    GameLevelMgr()
    {

    }

    public void InitInfo(SceneInfo info)
    {
        UIManager.Instance.ShowPanel<GamePanel>();
        RoleInfo roleInfo = GameDataMgr.Instance.nowSelRole;
        Transform heroPos = GameObject.Find("HeroBornPos").transform;
        GameObject heroObj = GameObject.Instantiate(Resources.Load<GameObject>(roleInfo.res), heroPos.position, heroPos.rotation);
        player = heroObj.GetComponent<PlayerObject>();
        player.InitPlayerInfo(roleInfo.atk, info.money);


        Camera.main.GetComponent<CameraMove>().SetTarget(heroObj.transform);

        MainTowerObject.Instance.UpdateHp(info.towerHp, info.towerHp);
    }

    public void AddMonsterPoint(MonsterPoint point)
    {
        monsterPointList.Add(point);
    }

    public bool CheckOver()
    {
        for (var i = 0; i < monsterPointList.Count; i++)
        {
            if (!monsterPointList[i].CheckOver())
            {
                return false;
            }
        }
        if (monsterList.Count > 0) return false;
        return true;
    }


    public void UpdateMaxNum(int num)
    {
        maxWaveNum += num;
        nowWaveNum = maxWaveNum;
        UIManager.Instance.GetPanel<GamePanel>().UpdateWaveNum(nowWaveNum, maxWaveNum);
    }

    public void ChangeNowWaveNum(int num)
    {
        nowWaveNum -= num;
        UIManager.Instance.GetPanel<GamePanel>().UpdateWaveNum(nowWaveNum, maxWaveNum);
    }

    // public void ChangeMonsterNum(int num)
    // {
    //     nowMonsterNum += num;
    // }

    public void ClearInfo()
    {
        monsterPointList.Clear();
        monsterList.Clear();
        nowWaveNum = maxWaveNum = 0;
        player = null;
    }

    public void AddMonster(MonsterObject monster)
    {
        monsterList.Add(monster);
    }

    public void RemoveMonster(MonsterObject monster)
    {
        monsterList.Remove(monster);
    }

    public MonsterObject FindMonster(Vector3 pos, int range)
    {
        for (var i = 0; i < monsterList.Count; i++)
        {
            if (!monsterList[i].isDead && Vector3.Distance(pos, monsterList[i].transform.position) <= range)
            {
                return monsterList[i];
            }
        }
        return null;
    }

    public List<MonsterObject> FindMonsters(Vector3 pos, int range)
    {
        List<MonsterObject> list = new List<MonsterObject>();
        for (var i = 0; i < monsterList.Count; i++)
        {
            if (!monsterList[i].isDead && Vector3.Distance(pos, monsterList[i].transform.position) <= range)
            {
                list.Add(monsterList[i]);
            }
        }

        return list;
    }
}
