using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainTowerObject : MonoBehaviour
{
    int hp;
    int maxHp;
    bool isDead;
    static MainTowerObject instance;
    public static MainTowerObject Instance => instance;

    void Awake()
    {
        instance = this;
    }



    public void UpdateHp(int hp, int maxHp)
    {
        this.hp = hp;
        this.maxHp = maxHp;
        UIManager.Instance.GetPanel<GamePanel>().UpdateTowerHp(hp, maxHp);
    }

    public void Wound(int damage)
    {
        if (isDead) return;
        hp -= damage;
        if (hp <= 0)
        {
            hp = 0;
            isDead = true;
            GameOverPanel panel = UIManager.Instance.ShowPanel<GameOverPanel>();
            panel.InitInfo((int)(GameLevelMgr.Instance.player.money * 0.5f), false);
        }
        UpdateHp(hp, maxHp);
    }


    void OnDestroy()
    {
        instance = null; 
    }
}
