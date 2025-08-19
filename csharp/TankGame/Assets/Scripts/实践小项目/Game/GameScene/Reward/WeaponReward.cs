using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WeaponReward : MonoBehaviour
{
    
    public GameObject[] weaponObj;
    public GameObject getEff;
    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            int index = Random.Range(0, weaponObj.Length);
            PlayerObj player = other.GetComponent<PlayerObj>();
            player.ChangeWeapon(weaponObj[index]);

            GameObject eff = Instantiate(getEff, transform.position, transform.rotation);
            AudioSource audioS = eff.GetComponent<AudioSource>();
            audioS.volume = GameDataMgr.Instance.musicData.soundValue;
            audioS.mute = !GameDataMgr.Instance.musicData.isOpenSound;

            Destroy(gameObject);
        }
    }
}
