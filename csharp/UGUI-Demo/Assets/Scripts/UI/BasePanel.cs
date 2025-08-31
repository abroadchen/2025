using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public abstract class BasePanel : MonoBehaviour
{
    CanvasGroup canvasGroup;
    float alphaSpeed = 10;
    bool isShow;
    UnityAction hideCallback;
    protected virtual void Awake()
    {
        canvasGroup = GetComponent<CanvasGroup>();
        if (canvasGroup == null)
        {
            canvasGroup = gameObject.AddComponent<CanvasGroup>();
        }
    }
    // Start is called before the first frame update
    protected virtual void Start()
    {
        Init(); 
    }

    public abstract void Init();

    public virtual void ShowMe()
    {
        isShow = true;
        canvasGroup.alpha = 0;
    }
    public virtual void HideMe(UnityAction callback)
    {
        isShow = false;
        canvasGroup.alpha = 1;
        hideCallback = callback;
    }
    // Update is called once per frame
    void Update()
    {
        if (isShow && canvasGroup.alpha != 1)
        {
            canvasGroup.alpha += alphaSpeed * Time.deltaTime;
            if (canvasGroup.alpha >= 1)
            {
                canvasGroup.alpha = 1;

            }
            else if (!isShow)
            {
                canvasGroup.alpha -= alphaSpeed * Time.deltaTime;
                if (canvasGroup.alpha <= 0)
                {
                    canvasGroup.alpha = 0;
                    hideCallback?.Invoke();
                }
            }
        }     
    }
}
