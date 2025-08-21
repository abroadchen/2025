using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class QuitPanel1 : BasePanel1<QuitPanel1>
{
    public UIButton btnSure;
    public UIButton btnClose;
    public override void Init()
    {
        btnSure.onClick.Add(new EventDelegate(() =>
        {
            SceneManager.LoadScene("BeginScene");
        }));
        btnClose.onClick.Add(new EventDelegate(() =>
        {
            HideMe();
        }));
        HideMe(); 
    }
}
