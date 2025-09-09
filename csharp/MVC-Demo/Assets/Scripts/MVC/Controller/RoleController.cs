using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoleController : MonoBehaviour
{
    private RoleView roleView;

    private static RoleController controller = null;

    public static RoleController Controller
    {
        get
        {
            return controller;
        }
        private set
        {
            controller = value;
        }
    }

    public static void ShowMe()
    {
        if (Controller is null)
        {
            var res = Resources.Load<GameObject>("UI/RolePanel");
            var obj = Instantiate(res, GameObject.Find("Canvas").transform, false);
            Controller = obj.GetComponent<RoleController>();
        }
        Controller.gameObject.SetActive(true);
    }
    
    public static void HideMe()
    {
        Controller?.gameObject.SetActive(false);
    }
    // Start is called before the first frame update
    void Start()
    {
        roleView = this.GetComponent<RoleView>();
        roleView.UpdateInfo(PlayerModel.Data);
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
        if (roleView != null)
        {
            roleView.UpdateInfo(data);
        }
    }
    
    private void OnDestroy()
    {
        PlayerModel.Data.RemoveEventListener(UpdateInfo);
    }
}
