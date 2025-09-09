using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainPresenter : MonoBehaviour
{
    private MVP_MainView mainView;

    private static MainPresenter Presenter { get; set; } = null;

    // ReSharper disable Unity.PerformanceAnalysis
    public static void ShowMe()
    {
        if (Presenter is null)
        {
            var res = Resources.Load<GameObject>("UI/MainPanel");
            var obj = Instantiate(res, GameObject.Find("Canvas").transform, false);
            Presenter = obj.GetComponent<MainPresenter>();
        }
        Presenter.gameObject.SetActive(false);
    }

    public static void HideMe()
    {
        Presenter?.gameObject.SetActive(false);
    }

    private void Start()
    {
        mainView = this.GetComponent<MVP_MainView>();
        UpdateInfo(PlayerModel.Data);
        mainView.btnRole.onClick.AddListener(ClickRoleBtn);
        
        PlayerModel.Data.AddEventListener(UpdateInfo);
    }

    private void ClickRoleBtn()
    {
        //RoleController.ShowMe();
        RolePresenter.ShowMe();
    }

    private void UpdateInfo(PlayerModel data)
    {
        if (mainView == null) return;
        mainView.txtName.text = data.PlayerName;
        mainView.txtLev.text = "LV." + data.Lev.ToString();
        mainView.txtMoney.text = data.Money.ToString();
        mainView.txtGem.text = data.Gem.ToString();
        mainView.txtPower.text = data.Power.ToString();
    }

    private void OnDestroy()
    {
        PlayerModel.Data.RemoveEventListener(UpdateInfo);
    }
}
