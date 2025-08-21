using System.Collections;
using System.Collections.Generic;
using UnityEditor.SearchService;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ChoosePanel : BasePanel1<ChoosePanel>
{
    public UIButton btnClose;
    public UIButton btnLeft;
    public UIButton btnRight;
    public UIButton btnStart;

    public Transform heroPos;

    public List<GameObject> hpObjs;
    public List<GameObject> speedObjs;
    public List<GameObject> volumeObjs;

    private GameObject airPlaneObj;

    public Camera uiCamera;
    public override void Init()
    {
        btnStart.onClick.Add(new EventDelegate(() =>
        {
            SceneManager.LoadScene("GameScene");
        }));
        btnLeft.onClick.Add(new EventDelegate(() =>
        {
            --GameDataMgr1.Instance.nowSelHeroIndex;
            if (GameDataMgr1.Instance.nowSelHeroIndex < 0)
            {
                GameDataMgr1.Instance.nowSelHeroIndex = GameDataMgr1.Instance.roleData.roleList.Count - 1;
            }
            ChangeNowHero();
        }));
        btnRight.onClick.Add(new EventDelegate(() =>
        {
            ++GameDataMgr1.Instance.nowSelHeroIndex;
            if (GameDataMgr1.Instance.nowSelHeroIndex >= GameDataMgr1.Instance.roleData.roleList.Count)
            {
                GameDataMgr1.Instance.nowSelHeroIndex = 0;
            }
            ChangeNowHero();
        }));
        btnClose.onClick.Add(new EventDelegate(() =>
        {
            HideMe();
            BeginPanel1.Instance.ShowMe();
        }));
        HideMe();
    }

    public override void ShowMe()
    {
        base.ShowMe();
        GameDataMgr1.Instance.nowSelHeroIndex = 0;
        ChangeNowHero();
    }

    public override void HideMe()
    {
        base.HideMe();
        DestroyObj();
    }

    private void ChangeNowHero()
    {
        RoleInfo roleInfo = GameDataMgr1.Instance.GetNowSelHeroInfo();
        DestroyObj();
        airPlaneObj = Instantiate(Resources.Load<GameObject>(roleInfo.resName));
        airPlaneObj.transform.SetParent(heroPos, false);
        airPlaneObj.transform.localPosition = Vector3.zero;
        airPlaneObj.transform.localRotation = Quaternion.identity;
        airPlaneObj.transform.localScale = Vector3.one * roleInfo.scale;
        airPlaneObj.layer = LayerMask.NameToLayer("UI");



        for (var i = 0; i < 10; i++)
        {
            hpObjs[i].SetActive(i < roleInfo.hp);
            speedObjs[i].SetActive(i < roleInfo.speed);
            volumeObjs[i].SetActive(i < roleInfo.volume);
        }
    }


    private void DestroyObj()
    {
        if (airPlaneObj != null)
        {
            Destroy(airPlaneObj);
            airPlaneObj = null;
        } 
    }

    private float time;
    private bool isSel;
    void Update()
    {
        time += Time.deltaTime;
        heroPos.Translate(Vector3.up * Mathf.Sin(time) * 0.0001f, Space.World);

        if (Input.GetMouseButtonDown(0))
        {
            if (Physics.Raycast(uiCamera.ScreenPointToRay(Input.mousePosition), 1000,
                1 << LayerMask.NameToLayer("UI")))
            {
                isSel = true;
            }

        }

        if (Input.GetMouseButtonUp(0))
        {
            isSel = false;
        }

        if (Input.GetMouseButton(0) && isSel)
        {
            heroPos.rotation *= Quaternion.AngleAxis(Input.GetAxis("Mouse X") * 20, Vector3.up);
        }

    }
}
