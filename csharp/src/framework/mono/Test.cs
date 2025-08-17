public class TestTest
{

    public TestTest()
    {
        MonoMgr.GetInstance().StartCoroutine(Test123());
    }

    IEnumerator Test123()
    {
        yield return new waitForSeconds(1f);
        Debug.Log("-----------")
    }

    public void Update()
    {
        Debug.Log("TestTest");
    }
}

public class Test : MonoBehaviour
{
    void Start()
    {
        TestTest t = new TestTest();
        MonoMgr.GetInstance().AddUpdateListener(t.Update);

        UIManager.GetInstance().ShowPanel<LoginPanel>("LoginPanel", E_UI_Layer.Mid, ShowPanelOver);
        
        //LoginPanel p = this.gameObject.GetComponet<LoginPanel>();
        //p.InitInfo();
    }

    private void ShowPanelOver(LoginPanel panel)
    {
        panel.InitInfo();
        Invoke("DelayHide", 1);
    }

    private void DelayHide()
    {
        UIManager.GetInstance().HidePanel("LoginPanel");
    }

    public void InitInfo()
    {
        Debug.Log("初始化数据");
    }


	public override void ShowMe()
	{
		base.ShowMe();
        Debug.Log("ShowMe");
	}

    public void ClickStart()
    {
        //UIManager.GetInstance().ShowPanel<>("LoginPanel");
    }

    public void ClickQuit()
    {
        
    }
    
    
    
    
    void Update() 
    {
        if (Input.GetMouseButtonDown(0))
        {
            GameObject obj = ResMgr.GetInstance().Load<GameObject>("Test/Cube");
            obj.transform.localScale = Vector3.one * 2;
        }

        if (Input.GetMouseButtonDown(1))
        {
            //ResMgr.GetInstance().LoadAsync<GameObject>("Test/Cube", DoSomething);
            
            ResMgr.GetInstance().LoadAsync<GameObject>("Test/Cube", (obj) => {
                obj.transform.localScale = Vector3.one * 2;
            });
        }
    }

    private void DoSomething(GameObject obj)
    {
        obj.transform.localScale = Vector3.one * 2;
    }
}
