using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class CameraAnimator : MonoBehaviour
{
    Animator animator;
    UnityAction overAction;
    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
    }


    public void TurnLeft(UnityAction action)
    {
        animator.SetTrigger("Left");
        overAction = action;
    }

    public void TurnRight(UnityAction action)
    {
        animator.SetTrigger("Right");
        overAction = action;
    }

    public void PlayerOver()
    {
        overAction?.Invoke();
        overAction = null;
    }
}
