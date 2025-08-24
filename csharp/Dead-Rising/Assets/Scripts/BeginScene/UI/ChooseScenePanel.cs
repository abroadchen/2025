using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class ChooseScenePanel : BasePanel
{
    public Button btnLeft;
    public Button btnRight;
    public Button btnStart;
    public Button btnBack;

    public Text txtInfo;
    public Image imgScene;

    int nowIndex;
    SceneInfo nowSceneInfo;
    public override void Init()
    {
        btnLeft.onClick.AddListener(() =>
        {
            --nowIndex;
            if (nowIndex < 0)
            {
                nowIndex = GameDataMgr.Instance.sceneInfoList.Count - 1;
            }
            ChangeScene();
        });
        btnRight.onClick.AddListener(() =>
        {
            ++nowIndex;
            if (nowIndex >= GameDataMgr.Instance.sceneInfoList.Count)
            {
                nowIndex = 0;
            }
            ChangeScene();
        });
        btnStart.onClick.AddListener(() =>
        {
            UIManager.Instance.HidePanel<ChooseScenePanel>();
            AsyncOperation ao = SceneManager.LoadSceneAsync(nowSceneInfo.sceneName);
            ao.completed += (obj) =>
            {
                GameLevelMgr.Instance.InitInfo(nowSceneInfo);
            };
            
        });
        btnBack.onClick.AddListener(() =>
        {
            UIManager.Instance.HidePanel<ChooseScenePanel>();
            UIManager.Instance.ShowPanel<ChooseHeroPanel>();
        });
        ChangeScene();
    }

    void ChangeScene()
    {
        nowSceneInfo = GameDataMgr.Instance.sceneInfoList[nowIndex];
        imgScene.sprite = Resources.Load<Sprite>(nowSceneInfo.imgRes);

        txtInfo.text = "名称:\n" + nowSceneInfo.name + "\n" + "描述:\n" + nowSceneInfo.tips;
    }
}
