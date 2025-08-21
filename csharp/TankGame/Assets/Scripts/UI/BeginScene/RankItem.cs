using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RankItem : MonoBehaviour
{
    public UILabel labRank;
    public UILabel labName;
    public UILabel labTime;

    public void InitInfo(int rank, string name, int time)
    {
        labRank.text = rank.ToString();
        labName.text = name;
        string str = "";
        if (time / 3600 > 0)
        {
            str += time / 3600 + "时";
        }
        if (time % 3600 / 60 > 0 || str != "")
        {
            str += time % 3600 / 60 + "分";
        }
        str += time % 60 + "秒";
        labTime.text = str;

    }

}
