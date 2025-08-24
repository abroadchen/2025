using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMove : MonoBehaviour
{
    public Transform target;
    public Vector3 offsetPos;

    public float bodyHeight;
    public float moveSpeed;
    public float rotationSpeed;

    Vector3 targetPos;
    Quaternion targetRot;


    // Update is called once per frame
    void Update()
    {
        if (target == null) return;
        targetPos = target.position + target.forward * offsetPos.z;
        targetPos += target.up * offsetPos.y;
        targetPos += target.right * offsetPos.x;
        transform.position = Vector3.Lerp(transform.position, targetPos, moveSpeed * Time.deltaTime);

        targetRot = Quaternion.LookRotation(target.position + Vector3.up * bodyHeight - transform.position);
        transform.rotation = Quaternion.Slerp(transform.rotation, targetRot, rotationSpeed * Time.deltaTime);
    }

    public void SetTarget(Transform target)
    {
        this.target = target;
    }
}
