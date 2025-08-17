public class Task : MonoBehaviour
{

    
    void Start()
    {
        EventCenter.GetInstance().AddEventListener("MonsterDead", TaskWaitMonsterDeadDo);
    }

    public void TaskWaitMonsterDeadDo(object info)
    {
        Debug.Log("任务 记录");
    }

    void OnDestroy()
    {
        EventCenter.GetInstance().RemoveEventListener("MonsterDead", TaskWaitMonsterDeadDo);
    }
}
