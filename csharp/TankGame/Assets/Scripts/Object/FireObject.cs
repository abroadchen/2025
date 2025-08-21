using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum E_Pos_Type
{
    TopLeft,
    Top,
    TopRight,
    Left,
    Right,
    BottomLeft,
    Bottom,
    BottomRight 
}


public class FireObject : MonoBehaviour
{
    public E_Pos_Type type;
    public Vector3 screenPos;

    private Vector3 initDir;
    FireInfo fireInfo;
    int nowNum;
    float nowCd;
    float nowDelay;
    BulletInfo nowBulletInfo;
    float changeAngle;
    Vector3 nowDir;

    // Update is called once per frame
    void Update()
    {
        UpdatePos();
        ResetFireInfo();
        UpdateFire();
    }

    void UpdatePos()
    {
        screenPos.z = 351;
        switch (type)
        {
            case E_Pos_Type.TopLeft:
                screenPos.x = 0;
                screenPos.y = Screen.height;
                initDir = Vector3.right;
                break;
            case E_Pos_Type.Top:
                screenPos.x = Screen.width / 2;
                screenPos.y = Screen.height;
                initDir = Vector3.right;
                break;
            case E_Pos_Type.TopRight:
                screenPos.x = Screen.width;
                screenPos.y = Screen.height;
                initDir = Vector3.left;
                break;
            case E_Pos_Type.Left:
                screenPos.x = 0;
                screenPos.y = Screen.height / 2;
                initDir = Vector3.right;
                break;
            case E_Pos_Type.Right:
                screenPos.x = Screen.width;
                screenPos.y = Screen.height / 2;
                initDir = Vector3.left;
                break;
            case E_Pos_Type.BottomLeft:
                screenPos.x = 0;
                screenPos.y = 0;
                initDir = Vector3.right;
                break;
            case E_Pos_Type.Bottom:
                screenPos.x = Screen.width / 2;
                screenPos.y = 0;
                initDir = Vector3.right;
                break;
            case E_Pos_Type.BottomRight:
                screenPos.x = Screen.width;
                screenPos.y = 0;
                initDir = Vector3.left;
                break;
        }
        transform.position = Camera.main.ScreenToWorldPoint(screenPos);
    }

    void ResetFireInfo()
    {
        if (nowCd != 0 && nowNum != 0) return;
        if (fireInfo != null)
        {
            nowDelay -= Time.deltaTime;
            if (nowDelay > 0) return;
        }
        List<FireInfo> list = GameDataMgr1.Instance.fireData.fireInfoList;
        fireInfo = list[Random.Range(0, list.Count)];
        nowNum = fireInfo.num;
        nowCd = fireInfo.cd;
        nowDelay = fireInfo.delay;
        string[] strs = fireInfo.ids.Split(',');
        int beginID = int.Parse(strs[0]);
        int endID = int.Parse(strs[1]);
        int randomBulletID = Random.Range(beginID, endID + 1);
        nowBulletInfo = GameDataMgr1.Instance.bulletData.bulletInfoList[randomBulletID - 1];

        if (fireInfo.type == 2)
        {
            switch (type)
            {
                case E_Pos_Type.Top:
                case E_Pos_Type.Bottom:
                case E_Pos_Type.Left:
                case E_Pos_Type.Right:
                    changeAngle = 180f / (nowNum + 1);
                    break;
                case E_Pos_Type.TopLeft:
                case E_Pos_Type.TopRight:
                case E_Pos_Type.BottomLeft:
                case E_Pos_Type.BottomRight:
                    changeAngle = 90f / (nowNum + 1);
                    break;
            }
        }
    }

    void UpdateFire()
    {
        if (nowCd == 0 && nowNum == 0) return;

        nowCd -= Time.deltaTime;
        if (nowCd > 0) return;
        GameObject bullet;
        BulletObject bulletObj;

        switch (fireInfo.type)
        {
            case 1:
                //动态创建子弹对象
                bullet = Instantiate(Resources.Load<GameObject>(nowBulletInfo.resName));
                //动态添加子弹脚本
                bulletObj = bullet.AddComponent<BulletObject>();
                //把当前的子弹数据传入子弹脚本进行初始化
                bulletObj.InitInfo(nowBulletInfo);
                bullet.transform.position = transform.position;
                bullet.transform.rotation = Quaternion.LookRotation(PlayerObject.Instance.transform.position - transform.position);
                --nowNum;
                nowCd = nowNum == 0 ? 0 : fireInfo.cd;
                break;
            case 2:
                if (nowCd == 0)
                {
                    for (var i = 0; i < nowNum; i++)
                    {
                        bullet = Instantiate(Resources.Load<GameObject>(nowBulletInfo.resName));
                        bulletObj = bullet.AddComponent<BulletObject>();
                        bulletObj.InitInfo(nowBulletInfo);
                        bullet.transform.position = transform.position;

                        nowDir = Quaternion.AngleAxis(changeAngle * i, Vector3.up) * initDir;
                        bullet.transform.rotation = Quaternion.LookRotation(nowDir);
                    }
                    nowCd = nowNum = 0;
                }
                else
                {
                    bullet = Instantiate(Resources.Load<GameObject>(nowBulletInfo.resName));
                    bulletObj = bullet.AddComponent<BulletObject>();
                    bulletObj.InitInfo(nowBulletInfo);
                    bullet.transform.position = transform.position;

                    nowDir = Quaternion.AngleAxis(changeAngle * (fireInfo.num - nowNum), Vector3.up) * initDir;
                    bullet.transform.rotation = Quaternion.LookRotation(nowDir);
                    --nowNum;
                    nowCd = nowNum == 0 ? 0 : fireInfo.cd;
                }
                break;
        }
    }
}
