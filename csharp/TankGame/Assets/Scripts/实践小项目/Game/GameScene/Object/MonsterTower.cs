using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class MonsterTower : TankBaseObj
{
    public float fireOffsetTime = 1;
    private float nowTime = 0;
    public Transform[] shootPos;

    public GameObject bulletObj;
    public override void Fire()
    {
        for (var i = 0; i < shootPos.Length; i++)
        {
            GameObject obj = Instantiate(bulletObj, shootPos[i].position, shootPos[i].rotation);
            BulletObj bullet = obj.GetComponent<BulletObj>();
            bullet.SetFather(this);
        }
    }

    // Update is called once per frame
    void Update()
    {
        nowTime += Time.deltaTime;
        if (nowTime >= fireOffsetTime)
        {
            Fire();
            nowTime = 0;
        }
    }
    
    public override void Wound(TankBaseObj other)
    {

    }
}
