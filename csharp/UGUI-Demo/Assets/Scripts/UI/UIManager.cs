using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIManager
{
    static UIManager instance = new UIManager();
    public static UIManager Instance => instance;

    Dictionary<string, BasePanel> panelDic = new Dictionary<string, BasePanel>();

    Transform canvasTrans;
    UIManager()
    {
        canvasTrans = GameObject.Find("Canvas").transform;
        GameObject.DontDestroyOnLoad(canvasTrans.gameObject);
    }

    public T ShowPanel<T>() where T : BasePanel
    {
        string panelName = typeof(T).Name;

        if (panelDic.ContainsKey(panelName))
            return panelDic[panelName] as T;     


        GameObject panelObj = GameObject.Instantiate(Resources.Load<GameObject>("UI/" + panelName));
        panelObj.transform.SetParent(canvasTrans, false);
        T panel = panelObj.GetComponent<T>();
        panelDic.Add(panelName, panel);
        panel.ShowMe();
        return panel;
    }

    public void HidePanel<T>(bool isFade = true) where T : BasePanel
    {
        string panelName = typeof(T).Name;

          
        if (panelDic.ContainsKey(panelName))
            {
                if (isFade)
                {
                    panelDic[panelName].HideMe(() =>
                    {
                        panelDic.Remove(panelName);
                        GameObject.Destroy(panelDic[panelName].gameObject);
                    });
                }
                else
                {
                    panelDic.Remove(panelName);
                    GameObject.Destroy(panelDic[panelName].gameObject);
                }
            }
    }
    
    public T GetPanel<T>() where T : BasePanel
    {
        string panelName = typeof(T).Name;
        if (panelDic.ContainsKey(panelName))
        {
            return panelDic[panelName] as T;
        }
        return null;
    }
}
