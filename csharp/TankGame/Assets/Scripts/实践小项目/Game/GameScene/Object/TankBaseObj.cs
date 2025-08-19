using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class TankBaseObj : MonoBehaviour
{
    public int atk;
    public int def;
    public int maxHp;
    public int hp;

    public float moveSpeed = 10;
    public float roundSpeed = 100;
    public float headRoundSpeed = 100;

    public GameObject deadEff;

    public Transform tankHead;

    public abstract void Fire();

    public virtual void Wound(TankBaseObj other)
    {
        int dmg = other.atk - def;
        if (dmg <= 0)
            return;
        hp -= dmg;
        if (hp <= 0)
        {
            hp = 0;
            Dead();
        }
    }

    public virtual void Dead()
    {
        Destroy(gameObject);
        if (deadEff != null)
        {
            GameObject effObj = Instantiate(deadEff, transform.position, transform.rotation);
            AudioSource audioSource = effObj.GetComponent<AudioSource>();
            audioSource.volume = GameDataMgr.Instance.musicData.soundValue;
            audioSource.mute = !GameDataMgr.Instance.musicData.isOpenSound;
            audioSource.Play(); 
        }
    }
}
