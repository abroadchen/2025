using System.Collections;
using System.Collections.Generic;
using PureMVC.Interfaces;
using PureMVC.Patterns.Command;
using UnityEngine;

public class ShowPanelCommand : SimpleCommand
{
    public override void Execute(INotification notification)
    {
        base.Execute(notification);

        var panelName = notification.Body.ToString();
        switch (panelName)
        {
            case "MainPanel":
                if (!Facade.HasMediator(NewMainViewMediator.NAME))
                    Facade.RegisterMediator(new NewMainViewMediator());

                var mm = Facade.RetrieveMediator(NewMainViewMediator.NAME) as NewMainViewMediator;
                if (mm != null && mm.ViewComponent == null)
                {
                    var res = Resources.Load<GameObject>("UI/MainPanel");
                    var obj = Object.Instantiate(res, GameObject.Find("Canvas").transform, false);
                    mm.SetView(obj.GetComponent<NewMainView>()); 
                }
                SendNotification(PureNotification.UPDATE_PLAYER_INFO, Facade.RetrieveProxy(PlayerProxy.NAME).Data);
                break;
            case "RolePanel":
                if (!Facade.HasMediator(NewRoleViewMediator.NAME))
                    Facade.RegisterMediator(new NewRoleViewMediator());

                if (Facade.RetrieveMediator(NewRoleViewMediator.NAME) is NewRoleViewMediator rm && rm.ViewComponent == null)
                {
                    var res = Resources.Load<GameObject>("UI/RolePanel");
                    var obj = Object.Instantiate(res, GameObject.Find("Canvas").transform, false);
                    rm.SetView(obj.GetComponent<NewRoleView>()); 
                }
                SendNotification(PureNotification.UPDATE_PLAYER_INFO, Facade.RetrieveProxy(PlayerProxy.NAME).Data);
                break;
        }
    }
}
