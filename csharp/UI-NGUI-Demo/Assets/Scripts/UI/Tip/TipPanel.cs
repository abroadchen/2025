using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TipPanel : BasePanel<TipPanel>
{
    public UIButton btnSure;
    public UILabel labInfo;
    public override void Init()
    {
        btnSure.onClick.Add(new EventDelegate(() =>
        {
            HideMe();
        }));
        HideMe();
    }

    public void ChangeInfo(string info)
    {
        labInfo.text = info;
    }
}
