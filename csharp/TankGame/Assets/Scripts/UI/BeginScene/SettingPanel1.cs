using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SettingPanel1 : BasePanel1<SettingPanel1>
{
    public UIButton btnClose;
    public UISlider sliderMusic;
    public UISlider sliderSound;
    public UIToggle togMusic;
    public UIToggle togSound;

    public override void Init()
    {
        btnClose.onClick.Add(new EventDelegate(() =>
        {
            HideMe();
        }));
        sliderMusic.onChange.Add(new EventDelegate(() =>
        {
            GameDataMgr1.Instance.SetMusicValue(sliderMusic.value);
        }));
        sliderSound.onChange.Add(new EventDelegate(() =>
        {
            GameDataMgr1.Instance.SetSoundValue(sliderSound.value);
        }));
        togMusic.onChange.Add(new EventDelegate(() =>
        {
            GameDataMgr1.Instance.SetMusicIsOpen(togMusic.value);
        }));
        togSound.onChange.Add(new EventDelegate(() =>
        {
            GameDataMgr1.Instance.SetSoundIsOpen(togSound.value);
        }));
        HideMe();
    }

    public override void ShowMe()
    {
        base.ShowMe();
        MusicData1 musicData = GameDataMgr1.Instance.musicData;
        togMusic.value = musicData.musicIsOpen;
        togSound.value = musicData.soundIsOpen;
        sliderMusic.value = musicData.musicValue;
        sliderSound.value = musicData.soundValue;
    }
    public override void HideMe()
    {
        base.HideMe();
        GameDataMgr1.Instance.SaveMusicData();
    }
}
