using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cam : MonoBehaviour
{
    public Transform targetPlayer;
    public float H = 10;
    private Vector3 pos;

    // Update is called once per frame
    void LateUpdate()
    {
        if (targetPlayer == null) return;
        pos.x = targetPlayer.position.x;
        pos.z = targetPlayer.position.z;
        pos.y = H;
        transform.position = pos;
    }
}
