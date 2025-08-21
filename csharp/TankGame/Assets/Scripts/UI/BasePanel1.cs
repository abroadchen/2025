using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class BasePanel1<T> : MonoBehaviour where T : class
{
    private static T instance;
    public static T Instance => instance;

    protected virtual void Awake()
    {
        instance = this as T;
    }
    // Start is called before the first frame update
    void Start()
    {
        Init();
    }


    public abstract void Init();

    public virtual void ShowMe()
    {
        gameObject.SetActive(true);
    }

    public virtual void HideMe()
    {
        gameObject.SetActive(false);
    }

}
