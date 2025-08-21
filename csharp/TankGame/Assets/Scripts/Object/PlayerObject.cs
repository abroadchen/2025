using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerObject : MonoBehaviour
{

    private static PlayerObject instance;
    public static PlayerObject Instance => instance;
    public int nowHp;
    public int maxHp;
    public int speed;
    public int roundSpeed;
    public bool isDead;

    private Quaternion targetQ;


    private Vector3 nowPos;
    private Vector3 frontPos;

    void Awake()
    {
        instance = this;
    }

    public void Dead()
    {
        isDead = true;
        GameOverPanel.Instance.ShowMe();
    }


    
    public void Wound()
    {
        if (isDead) return;
        nowHp--;
        GamePanel1.Instance.ChangeHp(nowHp);
        if (nowHp <= 0) Dead();
    }

    private float hValue;
    private float vValue;
    // Update is called once per frame
    void Update()
    {
        if (isDead) return;
        hValue = Input.GetAxisRaw("Horizontal");
        vValue = Input.GetAxisRaw("Vertical");
        if (hValue == 0) targetQ = Quaternion.identity;
        else targetQ = hValue < 0 ? Quaternion.AngleAxis(20, Vector3.forward) : Quaternion.AngleAxis(-20, Vector3.forward);
        transform.rotation = Quaternion.Slerp(transform.rotation, targetQ, Time.deltaTime * roundSpeed);

        frontPos = transform.position;
        transform.Translate(Vector3.forward * Time.deltaTime * speed * vValue);
        transform.Translate(Vector3.right * Time.deltaTime * speed * hValue, Space.World);

        nowPos = Camera.main.WorldToScreenPoint(transform.position);
        if (nowPos.x <= 0 || nowPos.x >= Screen.width)
        {
            transform.position = new Vector3(frontPos.x, transform.position.y, transform.position.z);
        }
        if (nowPos.y <= 0 || nowPos.y >= Screen.height)
        {
            transform.position = new Vector3(transform.position.x, transform.position.y, frontPos.z);
        }

        if (Input.GetMouseButtonDown(0))
        {
            RaycastHit hitInfo;
            if (Physics.Raycast(Camera.main.ScreenPointToRay(Input.mousePosition), out hitInfo, 1000,
                1 << LayerMask.NameToLayer("Bullet")))
            {
                BulletObject bulletObj = hitInfo.transform.GetComponent<BulletObject>();
                bulletObj.Dead(); 
            }
        }
    }
}
