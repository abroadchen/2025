using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BKMusic : MonoBehaviour
{
    private static BKMusic instance;
    public static BKMusic Instance => instance;

    private AudioSource audioSource;
    // Start is called before the first frame update
    void Awake()
    {
        instance = this;
        audioSource = GetComponent<AudioSource>();

        ChangeOpen(GameDataMgr.Instance.musicData.isOpenBK);
        ChangeValue(GameDataMgr.Instance.musicData.bkValue);
    }

    public void ChangeValue(float value)
    {
        audioSource.volume = value;
    }

    public void ChangeOpen(bool isOpen)
    {
        audioSource.mute = !isOpen;
    }
}
