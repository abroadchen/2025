using System.Collections;
using System.Collections.Generic;
using PureMVC.Interfaces;
using PureMVC.Patterns.Mediator;
using UnityEngine;

public class NewMainViewMediator : Mediator
{
    public new static string NAME = "NewMainViewMediator";
    
    public NewMainViewMediator() : base(NAME)
    {
    }

    public void SetView(NewMainView view)
    {
        ViewComponent = view;
        view.btnRole.onClick.AddListener(() =>
        {
            SendNotification(PureNotification.SHOW_PANEL, "RolePanel");
        });
    }

    public override string[] ListNotificationInterests()
    {
        return new string[]
        {
            PureNotification.UPDATE_PLAYER_INFO,
 
        };
    }

    public override void HandleNotification(INotification notification)
    {
        switch (notification.Name)
        {
            case PureNotification.UPDATE_PLAYER_INFO:
                (ViewComponent as NewMainView)?.UpdateInfo(notification.Body as PlayerDataObj);
                break;
        }
    }

    public override void OnRegister()
    {
        base.OnRegister();
    }
}
