using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TowerObject : MonoBehaviour
{
    public Transform head;
    public Transform gunPoint;

    float roundSpeed = 20;
    TowerInfo info;
    MonsterObject targetObj;
    float nowTime;
    Vector3 monsterPos;
    List<MonsterObject> targetObjs;

    public void InitInfo(TowerInfo info)
    {
        this.info = info;
    }
    // Update is called once per frame
    void Update()
    {
        if (info.atkType == 1)
        {
            if (targetObj == null ||
                targetObj.isDead ||
                Vector3.Distance(transform.position, targetObj.transform.position) > info.atkRange)
            {
                targetObj = GameLevelMgr.Instance.FindMonster(transform.position, info.atkRange);
            }
            if (targetObj == null) return;
            monsterPos = targetObj.transform.position;
            monsterPos.y = head.position.y;
            head.rotation = Quaternion.Slerp(head.rotation, Quaternion.LookRotation(monsterPos - head.position), roundSpeed * Time.deltaTime);
            if (Vector3.Angle(head.forward, monsterPos - head.position) < 5 && Time.time - nowTime >= info.offsetTime)
            {
                targetObj.Wound(info.atk);
                GameDataMgr.Instance.PlaySound("Music/Tower");
                GameObject effObj = Instantiate(Resources.Load<GameObject>(info.eff), gunPoint.position, gunPoint.rotation);
                Destroy(effObj, 0.2f);
                nowTime = Time.time;
            }
        }
        else
        {
            targetObjs = GameLevelMgr.Instance.FindMonsters(transform.position, info.atkRange);
            if (targetObjs.Count > 0 &&
                Time.time - nowTime > info.offsetTime)
            {
                GameObject effObj = Instantiate(Resources.Load<GameObject>(info.eff), gunPoint.position, gunPoint.rotation);
                Destroy(effObj, 0.2f);

                for (var i = 0; i < targetObjs.Count; i++)
                {
                    targetObjs[i].Wound(info.atk);
                } 
            }
        }
    }
}
