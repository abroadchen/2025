using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SettingPanel : BasePanel
{
    public Button btnClose;
    public Toggle togMusic;
    public Toggle togSound;
    public Slider sliderMusic;
    public Slider sliderSound;
    public override void Init()
    {
        MusicData data = GameDataMgr.Instance.musicData;
        togMusic.isOn = data.musicOpen;
        togSound.isOn = data.soundOpen;
        sliderMusic.value = data.musicValue;
        sliderSound.value = data.soundValue;

        btnClose.onClick.AddListener(() =>
        {
            GameDataMgr.Instance.SaveMusicData();
            UIManager.Instance.HidePanel<SettingPanel>();
        });
        togMusic.onValueChanged.AddListener((value) =>
        {
            BKMusic.Instance.SetIsOpen(value);
            GameDataMgr.Instance.musicData.musicOpen = value;
        });
        togSound.onValueChanged.AddListener((value) =>
        {
            GameDataMgr.Instance.musicData.soundOpen = value;
        });
        sliderMusic.onValueChanged.AddListener((value) =>
        {
            BKMusic.Instance.ChangeValue(value);
            GameDataMgr.Instance.musicData.musicValue = value;
        });
        sliderSound.onValueChanged.AddListener((value) =>
        {
            GameDataMgr.Instance.musicData.soundValue = value;
        });
    }
}
