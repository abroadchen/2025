using System.Collections;
using System.Collections.Generic;
using PureMVC.Interfaces;
using PureMVC.Patterns.Mediator;
using UnityEngine;

public class NewRoleViewMediator : Mediator
{
    public new static string NAME = "NewRoleViewMediator";

    public NewRoleViewMediator() : base(NAME)
    {
    }

    public void SetView(NewRoleView view)
    {
        ViewComponent = view;
        view.btnClose.onClick.AddListener(() =>
        {
            SendNotification(PureNotification.HIDE_PANEL, this);
        });
        view.btnLevUp.onClick.AddListener(() =>
        {
            SendNotification(PureNotification.LEV_UP);
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
                (ViewComponent as NewRoleView)?.UpdateInfo(notification.Body as PlayerDataObj);
                break;
        }
    }
}
