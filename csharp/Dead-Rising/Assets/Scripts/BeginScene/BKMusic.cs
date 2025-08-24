using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BKMusic : MonoBehaviour
{
    static BKMusic instance;
    public static BKMusic Instance => instance;

    AudioSource bkSource;

    void Awake()
    {
        instance = this;
        bkSource = GetComponent<AudioSource>();

        MusicData data = GameDataMgr.Instance.musicData;
        SetIsOpen(data.musicOpen);
        ChangeValue(data.musicValue);
    }

    public void SetIsOpen(bool isOpen)
    {
        bkSource.mute = !isOpen;
    }

    public void ChangeValue(float value)
    {
        bkSource.volume = value;
    }
}
