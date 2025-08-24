using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterPoint : MonoBehaviour
{
    public int maxWave;
    public int monsterNumOneWave;
    int nowNum;
    public List<int> monsterIDs;
    int nowID;
    public float createOffsetTime;
    public float delayTime;
    public float firstDelayTime;
    // Start is called before the first frame update
    void Start()
    {
        Invoke("CreateWave", firstDelayTime);
        GameLevelMgr.Instance.AddMonsterPoint(this);
        GameLevelMgr.Instance.UpdateMaxNum(maxWave);
    }

    // Update is called once per frame
    void CreateWave()
    {
        nowID = monsterIDs[Random.Range(0, monsterIDs.Count)];
        nowNum = monsterNumOneWave;
        CreateMonster();
        --maxWave;
        GameLevelMgr.Instance.ChangeNowWaveNum(1);
    }

    void CreateMonster()
    {
        MonsterInfo info = GameDataMgr.Instance.monsterInfoList[nowID - 1];
        GameObject obj = Instantiate(Resources.Load<GameObject>(info.res), transform.position, Quaternion.identity);
        MonsterObject monster = obj.GetComponent<MonsterObject>();
        monster.InitInfo(info);
        // GameLevelMgr.Instance.ChangeMonsterNum(1);
        GameLevelMgr.Instance.AddMonster(monster);
        --nowNum;
        if (nowNum == 0)
        {
            if (maxWave > 0)
                Invoke("CreateWave", delayTime);
        }
        else
        {
            Invoke("CreateMonster", createOffsetTime);
        }
    }

    public bool CheckOver()
    {
        return nowNum == 0 && maxWave == 0;
    }
}
