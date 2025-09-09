using System.Collections;
using System.Collections.Generic;
using PureMVC.Interfaces;
using PureMVC.Patterns.Command;
using PureMVC.Patterns.Mediator;
using UnityEngine;

public class HidePanelCommand : SimpleCommand
{
    public override void Execute(INotification notification)
    {
        base.Execute(notification);

        var m = notification.Body as Mediator;
        if (m != null && m.ViewComponent != null)
        {
            GameObject.Destroy((m.ViewComponent as MonoBehaviour).gameObject);
            m.ViewComponent = null;
        }
    }
}
