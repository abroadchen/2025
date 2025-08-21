using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Main : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        RoleInfo info = GameDataMgr1.Instance.GetNowSelHeroInfo();
        GameObject obj = Instantiate(Resources.Load<GameObject>(info.resName));
        PlayerObject playerObj = obj.GetComponent<PlayerObject>();
        playerObj.speed = info.speed * 20;
        playerObj.maxHp = 10;
        playerObj.nowHp = info.hp;
        playerObj.roundSpeed = 20;
        GamePanel1.Instance.ChangeHp(info.hp);
    }

}
