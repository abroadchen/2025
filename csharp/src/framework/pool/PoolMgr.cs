
public class PoolData
{
    public GameObject fatherObj;
    public List<GameObject> poolList;

    public PoolData(GameObject obj, GameObject poolObj)
    {
        fatherObj = new GameObject(obj.name);
        fatherObj.transform.parent = poolObj.transform;
        poolList = new List<GameObject>() {};
        PushObj(obj);
    }

    public void PushObj(GameObject obj)
    {
        obj.SetActive(false);
        poolList.Add(obj);
        obj.transform.parent = fatherObj.transform;
    }

    public GameObject GetObj()
    {
        GameObject obj = null;
        obj = poolList[0];
        poolList.RemoveAt(0);
        obj.SetActive(true);
        obj.transform.parent = null;
        return obj;
    }
}
public class PoolMgr : BaseManager<PoolMgr>
{
    public Dictionary<string, PoolData> poolDic = new Dictionary<>();
    private GameObject poolObj;

    public void GetObj(string name, UnityAction<GameObject> callback)
    {
        GameObject obj = null;
        if (poolDic.ContainsKey(name) && poolDic[name].poolList.Count > 0)
        {
            //obj = poolDic[name].GetObj();
            callback(poolDic[name].GetObj());
        }
        else
        {
            ResMgr.GetInstance().LoadAsync<GameObject>(name, (o) => 
            {
                o.name = name;
                callback(o);
            });
            //obj = GameObject.Instantiate(Resources.Load<GameObject>(name));
            //obj.name = name;//和pool名字一样
        }

 
        return obj;
    }

    public void PushObj(string name, GameObject obj)
    {
        if (poolObj == null)
            poolObj = new GameObject("Pool");

        if (poolDic.ContainsKey(name))
        {
            poolDic[name].PushObj(obj);
        }
        else
        {
            poolDic.Add(name, new PoolData(obj, poolObj)); 
        }
    }

    public void Clear()
    {
        poolDic.Clear();
        poolObj = null;
    }
}



public class Test : MonoBehaviour
{
    void Start() {}

    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            PoolMgr.GetInstance().GetObj("Test/Cube");
        }

        if (Input.GetMouseButtonDown(1))
        {
            PoolMgr.GetInstance().GetObj("Test/Sphere"); 
        }
    }
}

public class DelayPush : MonoBehaviour
{
    void OnEnable()
    {
        Invoke("Push", 1);
    }

    void Push()
    {
        PoolMgr.GetInstance().PushObj(this.gameObject.name, this.gameObject);
    }
}
