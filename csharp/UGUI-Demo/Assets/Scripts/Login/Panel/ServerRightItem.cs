using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.U2D;
using UnityEngine.UI;


public class ServerRightItem : MonoBehaviour
{
    public Button btnSelf;
    public Image imgNew;
    public Image imgState;
    public Text txtName;
    public ServerInfo nowServerInfo;
    // Start is called before the first frame update
    void Start()
    {
        btnSelf.onClick.AddListener(() =>
        {
            LoginMgr.Instance.LoginData.frontServerID = nowServerInfo.id;
            UIManager.Instance.HidePanel<ChooseServerPanel>();
            UIManager.Instance.ShowPanel<ServerPanel>();
        }); 
    }

    public void InitInfo(ServerInfo info)
    {
        nowServerInfo = info;
        txtName.text = info.id + "区 " + info.name;
        imgNew.gameObject.SetActive(info.isNew);
        imgState.gameObject.SetActive(true);
        SpriteAtlas atlas = Resources.Load<SpriteAtlas>("Login");
        switch (info.state)
        {
            case 0:
                imgState.gameObject.SetActive(false);
                break;
            case 1:
                imgState.sprite = Resources.Load<Sprite>("ui_DL_liuchang_01");
                break;
            case 2:
                imgState.sprite = Resources.Load<Sprite>("ui_DL_fanhua_01");
                break;
            case 3:
                imgState.sprite = Resources.Load<Sprite>("ui_DL_huobao_01");
                break;
            case 4:
                imgState.sprite = Resources.Load<Sprite>("ui_DL_weihu_01");
                break;

        }
    }
}
