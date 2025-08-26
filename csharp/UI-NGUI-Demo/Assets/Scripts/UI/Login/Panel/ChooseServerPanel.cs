using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class ChooseServerPanel : BasePanel<ChooseServerPanel>
{
    public Transform svLeft;
    public Transform svRight;
    public UILabel labName;
    public UISprite sprState;

    public UILabel labNowServer;
    List<GameObject> itemList = new List<GameObject>();
    public override void Init()
    {
        ServerInfo info = LoginMgr.Instance.ServerInfo;
        int num = info.serverDic.Count / 5 + 1;
        for (var i = 0; i < num; i++)
        {
            GameObject item = Instantiate(Resources.Load<GameObject>("UI/btnServer"));
            item.transform.SetParent(svLeft, false);
            item.transform.localPosition = new Vector3(-79, 58, 0) + new Vector3(0, -65 * i, 0);
            ServerItem serverItem = item.GetComponent<ServerItem>();
            int beginIndex = i * 5 + 1;
            int endIndex = (i + 1) * 5;
            if (endIndex > info.serverDic.Count)
                endIndex = info.serverDic.Count;
            serverItem.InitInfo(beginIndex, endIndex);
        }
        HideMe();
    }

    public void UpdatePanel(int beginIndex, int endIndex)
    {
        labNowServer.text = "当前服务器：" + beginIndex + " - " + endIndex + "区";
        for (var i = 0; i < itemList.Count; i++)
        {
            Destroy(itemList[i].gameObject);
        }
        itemList.Clear();
        Server nowInfo;
        for (var i = beginIndex; i <= endIndex; i++)
        {
            nowInfo = LoginMgr.Instance.ServerInfo.serverDic[i];
            GameObject serverItem = Instantiate(Resources.Load<GameObject>("UI/btnChooseServer"));
            serverItem.transform.SetParent(svRight, false);
            serverItem.transform.localPosition = new Vector3(-8, 61, 0) + new Vector3((i - 1) % 5 % 2 * 300, (i - 1) % 5 / 2 * -80, 0);

            ServerChooseItem item = serverItem.GetComponent<ServerChooseItem>();
            item.InitInfo(nowInfo);


            itemList.Add(serverItem);
        }
    }

    public override void ShowMe()
    {
        base.ShowMe();

        if (LoginMgr.Instance.LoginData.frontServerID == 0)
        {
            labName.text = "请选择服务器";
            sprState.gameObject.SetActive(false);
        }
        else
        {
            Server info = LoginMgr.Instance.ServerInfo.serverDic[LoginMgr.Instance.LoginData.frontServerID];
            labName.text = info.id + "区" + info.name;
            sprState.gameObject.SetActive(true);
            switch (info.state)
            {
                case 0:
                    sprState.gameObject.SetActive(false);
                    break;
                case 1:
                    sprState.spriteName = "ui_DL_liuchang_01";
                    break;
                case 2:
                    sprState.spriteName = "ui_DL_fanhua_01";
                    break;
                case 3:
                    sprState.spriteName = "ui_DL_huobao_01";
                    break;
                case 4:
                    sprState.spriteName = "ui_DL_weihu_01";
                    break;
            }
        }

        UpdatePanel(1, 5 > LoginMgr.Instance.ServerInfo.serverDic.Count ? LoginMgr.Instance.ServerInfo.serverDic.Count : 5);

    }
}
