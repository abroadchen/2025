using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BKMusic1 : MonoBehaviour
{
    private static BKMusic1 instance;
    public static BKMusic1 Instance => instance;

    private AudioSource bkAudio;

    void Awake()
    {
        instance = this;
        bkAudio = GetComponent<AudioSource>();

        SetBKMusicIsOpen(GameDataMgr1.Instance.musicData.musicIsOpen);
        SetBKMusicValue(GameDataMgr1.Instance.musicData.musicValue);
    }

    public void SetBKMusicIsOpen(bool isOpen)
    {
        bkAudio.mute = !isOpen;
    }
    
    public void SetBKMusicValue(float value)
    {
        bkAudio.volume = value;
    }
}
