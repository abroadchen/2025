using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WeaponObj : MonoBehaviour
{
    public GameObject bullet;
    public Transform[] shootPos;

    public TankBaseObj fatherObj;

    public void SetFather(TankBaseObj obj)
    {
        fatherObj = obj;
    }

    public void Fire()
    {
        for (var i = 0; i < shootPos.Length; i++)
        {
            GameObject obj = Instantiate(bullet, shootPos[i].position, shootPos[i].rotation);
            BulletObj bulletObj = obj.GetComponent<BulletObj>();
            bulletObj.SetFather(fatherObj);
        }
    }
}
