using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainController : MonoBehaviour
{
    private MainView mainView;

    public static MainController Controller { get; private set; } = null;

    // ReSharper disable Unity.PerformanceAnalysis
    public static void ShowMe()
    {
        if (Controller is null)
        {
            var res = Resources.Load<GameObject>("UI/MainPanel");
            var obj = Instantiate(res, GameObject.Find("Canvas").transform, false);
            Controller = obj.GetComponent<MainController>();
        }
        Controller.gameObject.SetActive(false);
    }

    public static void HideMe()
    {
        Controller?.gameObject.SetActive(false);
    }

    private void Start()
    {
        mainView = this.GetComponent<MainView>();
        mainView.UpdateInfo(PlayerModel.Data);
        mainView.btnRole.onClick.AddListener(ClickRoleBtn);
        
        PlayerModel.Data.AddEventListener(UpdateInfo);
    }

    private void ClickRoleBtn()
    {
        RoleController.ShowMe();
    }

    private void UpdateInfo(PlayerModel data)
    {
        if (mainView != null)
        {
            mainView.UpdateInfo(data);
        }
    }

    private void OnDestroy()
    {
        PlayerModel.Data.RemoveEventListener(UpdateInfo);
    }
}
