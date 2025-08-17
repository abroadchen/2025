//需要自己保证它的位移性
public class SingletonMono<T> : MonoBehaviour where T : MonoBehaviour
{
    private static T instance;

    public static T GetInstance()
    {
        //不能直接new
        //拖动到对象上 或 加脚本
        return instance;
    }

    protected virtual void Awake()
    {
        instance = this as T;
        //this.gameObject.AddComponent
    }
}


public class NewBehaviourScript : SingletonMono<NewBehaviourScript>
{
    void Start()
    {
        Debug.Log(NewBehaviourScript.GetInstance().name);
    }

    protected override void Awake()
    {
        base.Awake();
    }
}