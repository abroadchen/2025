using System.Collections;
using System.Collections.Generic;
using UnityEditor.SearchService;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameOverPanel : BasePanel
{
    public Text txtWin;
    public Text txtInfo;
    public Text txtMoney;
    public Button btnSure;
    public override void Init()
    {
        btnSure.onClick.AddListener(() =>
        {
            UIManager.Instance.HidePanel<GameOverPanel>();
            UIManager.Instance.HidePanel<GamePanel>();
            GameLevelMgr.Instance.ClearInfo();
            SceneManager.LoadScene("BeginScene");
        });

    }

    public void InitInfo(int money, bool isWin)
    {
        txtWin.text = isWin ? "恭喜你，你赢了" : "你输了";
        txtInfo.text = isWin ? "你获得" + money + "金币" : "你损失" + money + "金币";
        txtMoney.text = "金币：" + money.ToString();

        GameDataMgr.Instance.playerData.haveMoney += money;
        GameDataMgr.Instance.SavePlayerData();
    }
    
    public override void ShowMe()
    {
        base.ShowMe();
        Cursor.lockState = CursorLockMode.None;
    }
}
