using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GamePanel1 : BasePanel1<GamePanel1>
{

    public UIButton btnBack;
    public UILabel labTime;

    public List<GameObject> hpObjs;

    public float nowTime = 0;
    public override void Init()
    {
        btnBack.onClick.Add(new EventDelegate(() =>
        {
            QuitPanel1.Instance.ShowMe();
        }));

        Invoke("TestFun", 5);
    }

    void TestFun()
    {
        GameOverPanel.Instance.ShowMe();
    }

    public void ChangeHp(int hp)
    {
        for (int i = 0; i < hpObjs.Count; i++)
        {
            hpObjs[i].SetActive(i < hp);
        }
    }

    void Update()
    {
        nowTime += Time.deltaTime;
        labTime.text = "";
        if ((int)nowTime / 3600 > 0)
        {
            labTime.text += (int)(nowTime / 3600) + "时";
        }
        if ((int)nowTime % 3600 / 60 > 0 || labTime.text != "")
        {
            labTime.text += (int)(nowTime % 3600 / 60) + "分";
        }
        labTime.text += (int)(nowTime % 60) + "秒";

    }

}
