using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GamePanel : BasePanel<GamePanel>
{

    public CustomGUILabel labScore;
    public CustomGUILabel labTime;
    public CustomGUIButton btnQuit;
    public CustomGUIButton btnSetting;
    public CustomGUITexture texHP;
    [HideInInspector]
    public int nowScore = 0;

    public float hpW = 350;
    [HideInInspector]
    public float nowTime = 0;

    private int time;
    // Start is called before the first frame update
    void Start()
    {
        btnSetting.clickEvent += () =>
        {
            SettingPanel.Instance.ShowMe();
            Time.timeScale = 0;
        };
        btnQuit.clickEvent += () =>
        {
            QuitPanel.Instance.ShowMe();
            Time.timeScale = 0;
        };

        // AddScore(100);
        // UpdateHP(100, 30);
    }

    // Update is called once per frame
    void Update()
    {
        nowTime += Time.deltaTime;

        time = (int)nowTime;
        labTime.content.text = "";
        if (time / 3600 > 0)
        {
            labTime.content.text += time / 3600 + "时";
        }
        if (time % 3600 / 60 > 0 || labTime.content.text != "")
        {
            labTime.content.text += time % 3600 / 60 + "分";
        }
        labTime.content.text += time % 60 + "秒";
    }

    public void AddScore(int score)
    {
        nowScore += score;
        labScore.content.text = nowScore.ToString();
    }

    public void UpdateHP(int maxHP, int HP)
    {
        texHP.guiPos.width = (float)HP / maxHP * hpW;
    }
}
