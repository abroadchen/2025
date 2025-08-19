using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum E_PropType
{
    Atk,
    Def,
    MaxHp,
    Hp 
}


public class PropReward : MonoBehaviour
{
    public E_PropType type = E_PropType.Atk;
    public int changeValue = 2;
    public GameObject getEff;

    private void OggerEnter(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            PlayerObj player = other.GetComponent<PlayerObj>();
            switch (type)
            {
                case E_PropType.Atk:
                    player.atk += changeValue;
                    break;
                case E_PropType.Def:
                    player.def += changeValue;
                    break;
                case E_PropType.MaxHp:
                    player.maxHp += changeValue;
                    GamePanel.Instance.UpdateHP(player.maxHp, player.hp);
                    break;
                case E_PropType.Hp:
                    player.hp += changeValue;
                    if (player.hp > player.maxHp)
                    {
                        player.hp = player.maxHp;
                    }
                    GamePanel.Instance.UpdateHP(player.maxHp, player.hp);
                    break;
            }

            GameObject eff = Instantiate(getEff, transform.position, transform.rotation);
            AudioSource audioS = eff.GetComponent<AudioSource>();
            audioS.volume = GameDataMgr.Instance.musicData.soundValue;
            audioS.mute = !GameDataMgr.Instance.musicData.isOpenSound;


            Destroy(gameObject);
        }
    }
}
