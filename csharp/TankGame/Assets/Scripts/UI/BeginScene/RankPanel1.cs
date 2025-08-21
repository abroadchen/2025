using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RankPanel1 : BasePanel1<RankPanel1> 
{
    
    public UIButton btnClose;
    public UIScrollView svList;

    private List<RankItem> itemList = new List<RankItem>();
    public override void Init()
    {
        btnClose.onClick.Add(new EventDelegate(() =>
        {
            HideMe();
        }));
        HideMe();

        //create test data
        // for (var i = 0; i < 10; i++)
        // {
        //     GameDataMgr1.Instance.AddRankData("name" + i, Random.Range(1, 100));
        // }
    }

    public override void ShowMe()
    {
        base.ShowMe();
        List<RankInfo1> list = GameDataMgr1.Instance.rankData.rankList;
        for (var i = 0; i < list.Count; i++)
        {
            if (i < itemList.Count)
            {
                itemList[i].InitInfo(i + 1, list[i].name, list[i].time);
            }
            else
            {
                GameObject obj = Instantiate(Resources.Load<GameObject>("UI/RankItem"));
                obj.transform.SetParent(svList.transform, false);
                obj.transform.localPosition = new Vector3(0, 115 - i * 45, 0);
                RankItem item = obj.GetComponent<RankItem>();
                item.InitInfo(i + 1, list[i].name, list[i].time);
                itemList.Add(item);
            }
        }
    }
}
