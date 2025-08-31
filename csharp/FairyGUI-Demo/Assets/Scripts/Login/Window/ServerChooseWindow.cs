using System.Collections;
using System.Collections.Generic;
using FairyGUI;
using Login;
using UnityEngine;

public class ServerChooseWindow : Window
{
    protected override void OnInit()
    {
        base.OnInit();
        contentPane = UIPackage.CreateObject("Login", "ServerChooseWindow").asCom;
        contentPane.MakeFullScreen();
        var panel = contentPane as UI_ServerChooseWindow;

        var serverNum = BinaryDataMgr.Instance.GetTable<ServerInfoContainer>().dataDic.Count;
        var num = serverNum / 5 + 1;
        for (var i = 0; i < num; i++)
        {
            var item = panel.m_listLeft.AddItemFromPool() as UI_ServerLeftItem;
            var beginIndex = i * 5 + 1;
            var endIndex = 5 * (i + 1);
            if (endIndex > serverNum) endIndex = serverNum;
            item.InitInfo(beginIndex, endIndex);
        }
    }

    protected override void OnShown()
    {
        base.OnShown();
        var panel = contentPane as UI_ServerChooseWindow;
        var id = LoginMgr.Instance.loginData.frontServerID;
        if (id == 0)
        {
            panel.m_txtName.text = "请选择服务器";
            panel.m_imgState.visible = false;
        }
        else
        {
            var info = BinaryDataMgr.Instance.GetTable<ServerInfoContainer>().dataDic[id];
            panel.m_txtName.text = info.id + "区  " + info.name;
            panel.m_imgState.visible = true;
            switch (info.state)
            {
                case 0://����
                    panel.m_imgState.url = "ui://Login/ui_DL_liuchang_01";
                    break;
                case 1://��æ
                    panel.m_imgState.url = "ui://Login/ui_DL_fanhua_01";
                    break;
                case 2://��
                    panel.m_imgState.url = "ui://Login/ui_DL_huobao_01";
                    break;
                case 3://ά��
                    panel.m_imgState.url = "ui://Login/ui_DL_weihu_01";
                    break;
            }
        }

        var serverNum = BinaryDataMgr.Instance.GetTable<ServerInfoContainer>().dataDic.Count;
        UpdatePanel(1, 5 > serverNum ? serverNum : 5);
    }

    public void UpdatePanel(int beginIndex, int endIndex)
    {
        var panel = contentPane as UI_ServerChooseWindow;
        panel.m_txtRange.SetVar("string", "服务器" + beginIndex + " - " + endIndex);
        panel.m_txtRange.FlushVars();
        panel.m_listRight.RemoveChildrenToPool();

        var serverInfoContainer = BinaryDataMgr.Instance.GetTable<ServerInfoContainer>();
        for (var i = beginIndex; i <= endIndex; i++)
        {
            var nowInfo = serverInfoContainer.dataDic[i];
            var item = panel.m_listRight.AddItemFromPool() as UI_ServerRightItem;
            item.InitInfo(nowInfo);
        }
    }


    protected override void DoShowAnimation()
    {
        base.DoShowAnimation();
        contentPane.GetTransition("show").Play();
    }

    protected override void DoHideAnimation()
    {
        contentPane.GetTransition("hide").Play(base.DoHideAnimation);
    } 
}
