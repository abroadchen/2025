public class SingletonAutoMono<T> : MonoBehaviour where T : MonoBehaviour
{
    private static T instance;

    public static T GetInstance()
    {
        if (instance == null)
        {
            GameObject obj = new GameObject();
            obj.name = typeof(T).ToString();
            DontDestroyOnLoad(obj);
            instance = obj.AddComponent<T>();
        }
        return instance;
    }

}


public class NewBehaviourScript : SingletonAutoMono<NewBehaviourScript>
{
    public void Test()
    {
        Debug.Log(NewBehaviourScript.GetInstance().name);
    }
}

public class Test : MonoBehaviour
{
    void Start()
    {
        NewBehaviourScript.GetInstance().Test();
    }
    
    void Update() {}
} 

