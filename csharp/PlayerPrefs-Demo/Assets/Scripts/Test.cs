using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class PlayerInfo
{
    public int age;
    public string name;
    public float height;
    public bool isMale;

    public List<int> list = new List<int>();

    public Dictionary<int, string> dic = new Dictionary<int, string>();


    public ItemInfo itemInfo = new ItemInfo();

    public List<ItemInfo> itemList = new List<ItemInfo>();


    public Dictionary<int, ItemInfo> itemDic = new Dictionary<int, ItemInfo>();

}


public class ItemInfo
{
    public int id;
    public int num;
    
    public ItemInfo() {}
    
    public ItemInfo(int id, int num)
    {
        this.id = id;
        this.num = num;
    }
}





public class Test : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        //var p = new PlayerInfo();
        //PlayerPrefsDataMgr.Instance.SaveData(p, "Player1");
        PlayerPrefs.DeleteAll();
        var p = PlayerPrefsDataMgr.Instance.LoadData(typeof(PlayerInfo), "Player1") as PlayerInfo;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
