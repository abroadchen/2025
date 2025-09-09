using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RolePresenter : MonoBehaviour
{
    private MVP_RoleView roleView;

    private static RolePresenter presenter = null;

    public static RolePresenter Presenter
    {
        get
        {
            return presenter;
        }
        private set
        {
            presenter = value;
        }
    }

    public static void ShowMe()
    {
        if (Presenter is null)
        {
            var res = Resources.Load<GameObject>("UI/RolePanel");
            var obj = Instantiate(res, GameObject.Find("Canvas").transform, false);
            Presenter = obj.GetComponent<RolePresenter>();
        }
        Presenter.gameObject.SetActive(true);
    }
    
    public static void HideMe()
    {
        Presenter?.gameObject.SetActive(false);
    }
    // Start is called before the first frame update
    void Start()
    {
        roleView = this.GetComponent<MVP_RoleView>();
        UpdateInfo(PlayerModel.Data);
        roleView.btnClose.onClick.AddListener(ClickCloseBtn);
        roleView.btnLevUp.onClick.AddListener(ClickLevUpBtn);
        PlayerModel.Data.AddEventListener(UpdateInfo);
    }

    private void ClickCloseBtn()
    {
        HideMe();
    }

    private void ClickLevUpBtn()
    {
        PlayerModel.Data.LevUp();
    }

    // Update is called once per frame
    private void UpdateInfo(PlayerModel data)
    {
        if (roleView == null) return;
        roleView.txtLev.text = "LV." + data.Lev;
        roleView.txtHp.text = data.Hp.ToString();
        roleView.txtAtk.text = data.Atk.ToString();
        roleView.txtDef.text = data.Def.ToString();
        roleView.txtCrit.text = data.Crit.ToString();
        roleView.txtMiss.text = data.Miss.ToString();
        roleView.txtLuck.text = data.Luck.ToString();
    }

    private void OnDestroy()
    {
        PlayerModel.Data.RemoveEventListener(UpdateInfo);
    }
}
