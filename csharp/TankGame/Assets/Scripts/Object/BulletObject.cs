using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletObject : MonoBehaviour
{
    private BulletInfo info;
    
    private float time;
    public void InitInfo(BulletInfo info)
    {
        this.info = info;
        Invoke("DealyDestroy", info.lifeTime);
    }

    void DealyDestroy()
    {
        // Destroy(gameObject);
        Dead();
    }

    public void Dead()
    {
        GameObject effObj = Instantiate(Resources.Load<GameObject>(info.deadEffRes));
        effObj.transform.position = transform.position;
        Destroy(effObj, 1);
        Destroy(gameObject);
    }


    private void OggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("Player"))
        {
            PlayerObject obj = other.GetComponent<PlayerObject>();
            obj.Wound();
            Dead(); 
        }
    }
    // Update is called once per frame
    void Update()
    {
        transform.Translate(Vector3.forward * Time.deltaTime * info.forwardSpeed);
        switch (info.type)
        {
            case 2:
                time += Time.deltaTime;
                transform.Translate(Vector3.right * Time.deltaTime * Mathf.Sin(time * info.roundSpeed) * info.rightSpeed);
                break;
            case 3:
                transform.rotation *= Quaternion.AngleAxis(Time.deltaTime * info.roundSpeed, Vector3.up);
                break;
            case 4:
                transform.rotation *= Quaternion.AngleAxis(Time.deltaTime * -info.roundSpeed, Vector3.up);
                break;
            case 5:
                transform.rotation = Quaternion.Slerp(transform.rotation, Quaternion.LookRotation(PlayerObject.Instance.transform.position - transform.position), Time.deltaTime * info.roundSpeed);
                break;
        }
    }
}
