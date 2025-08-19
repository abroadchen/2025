using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RankPanel : BasePanel<RankPanel>
{
    public CustomGUIButton btnClose;

    // private List<CustomGUILabel> labPM = new List<CustomGUILabel>();
    private List<CustomGUILabel> labName = new List<CustomGUILabel>();
    private List<CustomGUILabel> labScore = new List<CustomGUILabel>();
    private List<CustomGUILabel> labTime = new List<CustomGUILabel>();
    // Start is called before the first frame update
    void Start()
    {
        for (int i = 1; i <= 10; i++)
        {
            // labPM.Add(transform.Find("PM/labPM" + i).GetComponent<CustomGUILabel>());
            labName.Add(transform.Find("Name/labName" + i).GetComponent<CustomGUILabel>());
            labScore.Add(transform.Find("Score/labScore" + i).GetComponent<CustomGUILabel>());
            labTime.Add(transform.Find("Time/labTime" + i).GetComponent<CustomGUILabel>());
        }
        btnClose.clickEvent += () =>
        {
            HideMe();
            BeginPanel.Instance.ShowMe();
        };

        // GameDataMgr.Instance.AddRankInfo("测试", 100, 8432);

        HideMe();
    }
    
    public override void ShowMe()
    {
        base.ShowMe();
        UpdatePanelInfo();
    }

    public void UpdatePanelInfo()
    {
        List<RankInfo> list = GameDataMgr.Instance.rankData.list;
        for (var i = 0; i < list.Count; i++)
        {
            labName[i].content.text = list[i].name;
            labScore[i].content.text = list[i].score.ToString();
            int time = (int)list[i].time;
            labTime[i].content.text = "";
            if (time / 3600 > 0)
            {
                labTime[i].content.text += time / 3600 + "时";
            }
            if (time % 3600 / 60 > 0 || labTime[i].content.text != "")
            {
                labTime[i].content.text += time % 3600 / 60 + "分";
            }
            labTime[i].content.text += time % 60 + "秒";
        }
    }
}
