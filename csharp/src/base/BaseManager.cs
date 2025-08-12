using UnityEngine;
public class BaseManager<T> where T : new()
{
    private static T instance;

    public static T GetInstance()
    {
        if (instance == null)
            instance = new T();
        return instance;
    }
}

public class GameManager : BaseManager<GameManager>
{

}

public class Test
{
    void Main()
    {
        GameManager.GetInstance();
    }
}