using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletObj : MonoBehaviour
{
    public float moveSpeed = 50;
    public TankBaseObj fatherObj;
    public GameObject effObj;


    // Update is called once per frame
    void Update()
    {
        transform.Translate(Vector3.forward * Time.deltaTime * moveSpeed);
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Cube") ||
            other.CompareTag("Player") && fatherObj.CompareTag("Monster") ||
            other.CompareTag("Monster") && fatherObj.CompareTag("Player"))
        {
            TankBaseObj obj = other.GetComponent<TankBaseObj>();
            if (obj != null)
            {
                obj.Wound(fatherObj);
            }


            if (effObj != null)
                {
                    GameObject eff = Instantiate(effObj, transform.position, transform.rotation);
                    AudioSource audioS = eff.GetComponent<AudioSource>();
                    audioS.volume = GameDataMgr.Instance.musicData.soundValue;
                    audioS.mute = !GameDataMgr.Instance.musicData.isOpenSound;
                }
            Destroy(gameObject);
        }
    }
    
    public void SetFather(TankBaseObj obj)
    {
        fatherObj = obj;
    }
}
