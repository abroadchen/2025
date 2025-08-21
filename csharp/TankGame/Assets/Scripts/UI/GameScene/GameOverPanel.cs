using System.Collections;
using System.Collections.Generic;
using UnityEditor.SearchService;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameOverPanel : BasePanel1<GameOverPanel>
{
    public UILabel labTime;
    public UIInput inputName;

    public UIButton btnSure;

    private int endTime;
    public override void Init()
    {
        btnSure.onClick.Add(new EventDelegate(() =>
        {
            GameDataMgr1.Instance.AddRankData(inputName.value, endTime);
            SceneManager.LoadScene("BeginScene");

        }));
        HideMe();
    }

    public override void ShowMe()
    {

        base.ShowMe();
        endTime = (int)GamePanel1.Instance.nowTime;
        labTime.text = GamePanel1.Instance.labTime.text;
    }
}
