public class Monster : MonoBehaviour
{
    public int type = 1;
    public string name = "123123";

    void Start()
    {
        Dead();
    }
    
    void Update() {}

    void Dead()
    {
        Debug.Log("怪物死亡");
        //GameObject.Find("Player").GetComponent<Player>().MonsterDeadDo();
        //GameObject.Find("Task").GetComponent<Task>().TaskWaitMonsterDeadDo();
        //GameObject.Find("Other").GetComponent<Other>().OtherWaitMonsterDeadDo();
    
        EventCenter.GetInstance().EventTrigger("MonsterDead", this);
    }
}
