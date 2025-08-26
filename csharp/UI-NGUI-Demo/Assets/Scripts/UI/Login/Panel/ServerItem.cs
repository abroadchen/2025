using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ServerItem : MonoBehaviour
{
    public UIButton btn;
    public UILabel labInfo;
    int beginIndex;
    int endIndex;
    // Start is called before the first frame update
    void Start()
    {
        btn.onClick.Add(new EventDelegate(() =>
        { 
            ChooseServerPanel.Instance.UpdatePanel(beginIndex, endIndex);
        }));
    }

    public void InitInfo(int beginIndex, int endIndex)
    {
        this.beginIndex = beginIndex;
        this.endIndex = endIndex;
        labInfo.text = beginIndex + " - " + endIndex + "区";
    }
}
