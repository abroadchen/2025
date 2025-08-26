using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class BasePanel<T> : MonoBehaviour where T : class
{
    static T instance;
    public static T Instance => instance;

    protected virtual void Awake()
    {
        instance = this as T;
    }
    // Start is called before the first frame update
    protected virtual void Start()
    {
        Init();
    }

    public abstract void Init();
    // Update is called once per frame
    public virtual void ShowMe()
    {
        gameObject.SetActive(true);
    }
    
    public virtual void HideMe()
    {
        gameObject.SetActive(false);
    }
}
