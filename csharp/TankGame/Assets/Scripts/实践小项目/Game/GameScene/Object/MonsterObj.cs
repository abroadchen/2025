using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterObj : TankBaseObj
{
    private Transform targetPos;
    public Transform[] randomPos;
    public Transform lookAtTarget;
    public float fireDis = 5;
    public float fireOffsetTime = 1;
    private float nowTime = 0;


    public Transform[] shootPos;
    public GameObject bulletObj;


    public Texture maxHpBK;
    public Texture hpBK;
    private Rect maxHpRect;
    private Rect hpRect;
    private float showTime = 0;

    public override void Fire()
    {
        for (var i = 0; i < shootPos.Length; i++)
        {
            GameObject obj = Instantiate(bulletObj, shootPos[i].position, shootPos[i].rotation);
            BulletObj bullet = obj.GetComponent<BulletObj>();
            bullet.SetFather(this);
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        RandomPos();
    }

    // Update is called once per frame
    void Update()
    {
        transform.LookAt(targetPos);
        transform.Translate(Vector3.forward * Time.deltaTime * moveSpeed);
        if (Vector3.Distance(transform.position, targetPos.position) < 0.05f)
        {
            RandomPos();
        }


        if (lookAtTarget != null)
        {
            tankHead.LookAt(lookAtTarget);

            if (Vector3.Distance(transform.position, lookAtTarget.position) <= fireDis)
            {
                nowTime += Time.deltaTime;
                if (nowTime >= fireOffsetTime)
                {
                    Fire();
                    nowTime = 0;
                }
            }
        }
    }

    private void RandomPos()
    {
        if (randomPos.Length == 0) return;
        targetPos = randomPos[Random.Range(0, randomPos.Length)];
    }

    public override void Dead()
    {
        base.Dead();
        GamePanel.Instance.AddScore(10);
    }

    private void OnGUI()
    {
        if (showTime > 0)
        {
            showTime -= Time.deltaTime;
            Vector3 screenPos = Camera.main.WorldToScreenPoint(transform.position);
            screenPos.y = Screen.height - screenPos.y;


            maxHpRect.x = screenPos.x - 50;
            maxHpRect.y = screenPos.y - 50;
            maxHpRect.width = 100;
            maxHpRect.height = 15;
            GUI.DrawTexture(maxHpRect, maxHpBK);

            hpRect.x = screenPos.x - 50;
            hpRect.y = screenPos.y - 50;
            hpRect.width = (float)hp / maxHp * 100f;
            hpRect.height = 15;
            GUI.DrawTexture(hpRect, hpBK);
        }
    }

    public override void Wound(TankBaseObj other)
    {
        base.Wound(other);
        showTime = 3;
    }
}
