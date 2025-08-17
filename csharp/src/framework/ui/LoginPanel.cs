namespace DefaultNamespace;

public class LoginPanel : BasePanel
{
    protected override void Awake()
    {
        base.Awake();
    }
    void Start()
    {
        //GetControl<Button>("btnStart").onClick.AddListener(ClickStart);
        //GetControl<Button>("btnQuit").onClick.AddListener(ClickQuit);

        //EventTrigger trigger = GetControl<Button>("btnStart").gameObject.AddComponent<>();
        //EventTrigger.Entry entry = new EventTrigger.Entry();
        //entry.eventID = EventTriggerType.Drag;
        //entry.callback.AddListener(Drag);
        //trigger.triggers.Add(entry);
        UIManager.AddCustomEventListener(GetControl<Button>("btnStart"), EventTriggerType.PointerEnter, (data) =>
        {
            
        });
    }

    private void Drag(BaseEventData data)
    {
        
    }
    
    void Update() {}

    public override void ShowMe()
    {
        base.ShowMe();
    }

    protected override void OnClick(string btnName)
    {
        switch (btnName)
        {
            case "btnStart":
                Debug.Log("btnStart");
                break;
            case "btnQuit":
                Debug.Log("btnQuit");
                break;
        }
    }

    protected override void OnValueChanged(string toggleName, bool value)
    {
    }
    
    public void InitInfo() {}
}