public class Other : MonoBehaviour
{
    void Start()
    {
        EventCenter.GetInstance().AddEventListener<Monster>("MonsterDead", OtherWaitMonsterDeadDo);
    }
    public void OtherWaitMonsterDeadDo(Monster info)
    {
        Debug.Log("其他 各个对象要做的事");
    }


    void OnDestroy()
    {
        EventCenter.GetInstance().RemoveEventListener<Monster>("MonsterDead", OtherWaitMonsterDeadDo);
    }
}
