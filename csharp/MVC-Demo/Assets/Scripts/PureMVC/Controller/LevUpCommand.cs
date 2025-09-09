using System.Collections;
using System.Collections.Generic;
using PureMVC.Interfaces;
using PureMVC.Patterns.Command;
using UnityEngine;

public class LevUpCommand : SimpleCommand
{
    public override void Execute(INotification notification)
    {
        base.Execute(notification);
        
        var playerProxy = Facade.RetrieveProxy(PlayerProxy.NAME) as PlayerProxy;
        if (playerProxy == null) return;
        playerProxy.LevUp();
        playerProxy.SaveData();
        SendNotification(PureNotification.UPDATE_PLAYER_INFO, playerProxy.Data);
    }
}
