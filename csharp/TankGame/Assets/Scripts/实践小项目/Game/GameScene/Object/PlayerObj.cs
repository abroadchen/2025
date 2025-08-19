using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerObj : TankBaseObj
{
    public WeaponObj nowWeapon;
    public Transform weaponPos;
    public override void Fire()
    {
        if (nowWeapon != null)
            nowWeapon.Fire();
    }

    // Update is called once per frame
    void Update()
    {
        transform.Translate(Input.GetAxis("Vertical") * Vector3.forward * Time.deltaTime * moveSpeed);
        transform.Rotate(Input.GetAxis("Horizontal") * Vector3.up * Time.deltaTime * roundSpeed);
        tankHead.Rotate(Input.GetAxis("Mouse X") * Vector3.up * Time.deltaTime * headRoundSpeed);
        if (Input.GetMouseButtonDown(0))
        {
            Fire();
        }
    }

    public override void Dead()
    {
        // base.Dead();
        Time.timeScale = 0;
        LossPanel.Instance.ShowMe();
    }

    public override void Wound(TankBaseObj other)
    {
        base.Wound(other);
        GamePanel.Instance.UpdateHP(maxHp, hp);
    }

    public void ChangeWeapon(GameObject weapon)
    {
        if (nowWeapon != null)
        {
            Destroy(nowWeapon.gameObject);
            nowWeapon = null;
        }

        GameObject weaponObj = Instantiate(weapon, weaponPos, false);
        nowWeapon = weaponObj.GetComponent<WeaponObj>();
        nowWeapon.SetFather(this);
    }
}
