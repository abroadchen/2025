using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerObject : MonoBehaviour
{
    int atk;
    public int money;
    float roundSpeed = 50;
    public Transform gunPoint;
    // public string effStr; 
    Animator animator;
    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
    }

    public void InitPlayerInfo(int atk, int money)
    {
        this.atk = atk;
        this.money = money;
        // this.effStr = effStr;
        UpdateMoney();
    }

    // Update is called once per frame
    void Update()
    {
        animator.SetFloat("VSpeed", Input.GetAxis("Vertical"));
        animator.SetFloat("HSpeed", Input.GetAxis("Horizontal"));
        transform.Rotate(Vector3.up, Input.GetAxis("Mouse X") * roundSpeed * Time.deltaTime);


        if (Input.GetKeyDown(KeyCode.LeftShift))
        {
            animator.SetLayerWeight(1, 1);
        }
        else if (Input.GetKeyUp(KeyCode.LeftShift))
        {
            animator.SetLayerWeight(1, 0);
        }

        if (Input.GetKeyDown(KeyCode.R))
        {
            animator.SetTrigger("Roll");
        }

        if (Input.GetMouseButtonDown(0))
        {
            animator.SetTrigger("Fire");
        }
    }


    public void KnifeEvent()
    {
        Collider[] colliders = Physics.OverlapSphere(transform.position + transform.forward + transform.up, 1, 1 << LayerMask.NameToLayer("Monster"));

        GameDataMgr.Instance.PlaySound("Music/Knife");

        for (var i = 0; i < colliders.Length; i++)
        {
            MonsterObject monster = colliders[i].GetComponent<MonsterObject>();
            if (monster != null && !monster.isDead)
            {
                monster.Wound(atk);
                break;
            }
        }

    }

    public void ShootEvent()
    {
        RaycastHit[] hits = Physics.RaycastAll(new Ray(gunPoint.position, transform.forward), 1000, 1 << LayerMask.NameToLayer("Monster"));

        GameDataMgr.Instance.PlaySound("Music/Gun");

        for (var i = 0; i < hits.Length; i++)
        {
            MonsterObject monster = hits[i].collider.GetComponent<MonsterObject>();
            if (monster != null && !monster.isDead)
            {
                GameObject effObj = Instantiate(Resources.Load<GameObject>(GameDataMgr.Instance.nowSelRole.hitEff));
                effObj.transform.position = hits[i].point;
                effObj.transform.rotation = Quaternion.LookRotation(hits[i].normal);
                Destroy(effObj, 1);
                monster.Wound(atk);
                break;
            }
        }
    }

    public void UpdateMoney()
    {
        UIManager.Instance.GetPanel<GamePanel>().UpdateMoney(money);
    }
    
    public void AddMoney(int money)
    {
        this.money += money;
        UpdateMoney();
    }
}
