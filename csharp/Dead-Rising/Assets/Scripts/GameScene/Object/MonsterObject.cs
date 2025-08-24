using System.Collections;
using System.Collections.Generic;
using TMPro.Examples;
using UnityEngine;
using UnityEngine.AI;

public class MonsterObject : MonoBehaviour
{
    Animator animator;
    NavMeshAgent agent;
    MonsterInfo monsterInfo;
    int hp;
    public bool isDead = false;

    float frontTime = 0;

    void Awake()
    {
        agent = GetComponent<NavMeshAgent>();
        animator = GetComponent<Animator>();
    }

    public void InitInfo(MonsterInfo info)
    {
        monsterInfo = info;
        animator.runtimeAnimatorController = Resources.Load<RuntimeAnimatorController>(info.animator);
        hp = info.hp;
        agent.speed = agent.acceleration = info.moveSpeed;
        agent.angularSpeed = info.roundSpeed;
    }

    public void Wound(int damage)
    {
        if (isDead) return;
        hp -= damage;
        animator.SetTrigger("Wound");
        if (hp <= 0)
        {
            Dead();
        }
        else
        {
            GameDataMgr.Instance.PlaySound("Music/Wound");
        }
    }

    public void Dead()
    {
        isDead = true;
        // agent.isStopped = true;
        agent.enabled = false;
        animator.SetBool("Dead", true);
        GameDataMgr.Instance.PlaySound("Music/dead");
        GameLevelMgr.Instance.player.AddMoney(10);
    }

    public void DeadEvent()
    {
        // GameLevelMgr.Instance.ChangeMonsterNum(-1);
        GameLevelMgr.Instance.RemoveMonster(this);
        Destroy(gameObject);

        if (GameLevelMgr.Instance.CheckOver())
        {
            GameOverPanel panel = UIManager.Instance.ShowPanel<GameOverPanel>();
            panel.InitInfo(GameLevelMgr.Instance.player.money, true);
        }
    }

    public void BornOver()
    {
        agent.SetDestination(MainTowerObject.Instance.transform.position);
        animator.SetBool("Run", true);
    }

    // Update is called once per frame
    void Update()
    {
        if (isDead) return;
        animator.SetBool("Run", agent.velocity != Vector3.zero);
        if (Vector3.Distance(transform.position, MainTowerObject.Instance.transform.position) < 5 && Time.deltaTime - frontTime >= monsterInfo.atkOffset)
        {
            frontTime = Time.time;
            animator.SetTrigger("Atk");
        }
    }

    public void AtkEvent()
    {
        Collider[] colliders = Physics.OverlapSphere(transform.position + transform.forward + transform.up, 1, 1 << LayerMask.NameToLayer("MainTower"));

        GameDataMgr.Instance.PlaySound("Music/Eat");

        for (var i = 0; i < colliders.Length; i++)
        {
            if (MainTowerObject.Instance.gameObject == colliders[i].gameObject)
            {
                MainTowerObject.Instance.Wound(monsterInfo.atk);
            }
        }
    }
}
