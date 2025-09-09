using System.Collections;
using System.Collections.Generic;
using PureMVC.Interfaces;
using PureMVC.Patterns.Facade;
using UnityEngine;

public class GameFacade : Facade
{
    public static GameFacade Instance
    {
        get
        {
            if (instance == null)
            {
                instance = new GameFacade();
            }

            return instance as GameFacade;
        }
    }

    protected override void InitializeController()
    {
        base.InitializeController();
        
        RegisterCommand(PureNotification.START_UP, () =>
        {
            return new StartUpCommand();
        });
        
        RegisterCommand(PureNotification.SHOW_PANEL, () =>
        {
            return new ShowPanelCommand();
        });
        
        RegisterCommand(PureNotification.HIDE_PANEL, () =>
        {
            return new HidePanelCommand();
        });
        
        RegisterCommand(PureNotification.LEV_UP, () =>
        {
            return new LevUpCommand();
        });
    }

    public void StartUp()
    {
        SendNotification(PureNotification.START_UP);
        SendNotification(PureNotification.SHOW_PANEL);
    }
}

