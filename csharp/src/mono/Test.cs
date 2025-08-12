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
