using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CubeObj : MonoBehaviour
{
    public GameObject[] rewardObjects;
    public GameObject deadEff;
    private void OnTriggerEnter(Collider other)
    {
        int rangeInt = Random.Range(0, 100);
        if (rangeInt < 50)
        {
            rangeInt = Random.Range(0, rewardObjects.Length);
            Instantiate(rewardObjects[rangeInt], transform.position, transform.rotation);
        }

        GameObject effObj = Instantiate(deadEff, transform.position, transform.rotation);
        AudioSource audioS = effObj.GetComponent<AudioSource>();
        audioS.volume = GameDataMgr.Instance.musicData.soundValue;
        audioS.mute = !GameDataMgr.Instance.musicData.isOpenSound;

        Destroy(gameObject);
    }
}
