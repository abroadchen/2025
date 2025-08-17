namespace DefaultNamespace;

public class BasePanel : MonoBehaviour
{
    private Dictionary<string, List<UIBehaviour>> controlDic = new Dictionary<>();

    protected virtual void Awake()
    {
        FindChildrenControl<Button>();
        FindChildrenControl<Image>();
        FindChildrenControl<Text>();
        FindChildrenControl<Toggle>();
        FindChildrenControl<Slider>();
        FindChildrenControl<ScrollRect>();
        FindChildrenControl<InputField>();
    }

    public virtual void ShowMe()
    {
        
    }

    public virtual void HideMe()
    {
        
    }

	protected virtual void OnClick(string controlName)
    {
        
    }

	protected virtual void OnValueChanged(string toggleName, bool value)
    {
 d
    }

    
    protected T GetControl<T>(string controlName) where T : UIBehaviour
    {
        if (controlDic.ContainsKey(controlName))
        {
            return controlDic[controlName][0] as T;
        }
        return null;
    }

	private void FindChildrenControl<T>() where T : UIBehaviour
    {
        var childs = GetComponentsInChildren<T>();
        foreach (var child in childs)
        {
            if (!controlDic.ContainsKey(child.name))
            {
                controlDic.Add(child.name, new List<UIBehaviour>());
            }
            controlDic[child.name].Add(child);

            if (child is Button)
            {
                child.onClick.AddListener(() =>
                {
                    UIManager.GetInstance().HidePanel();
                    OnClick(child.name);
                });
            }
			else if (child is Toggle)
            {
                child.onValueChanged.AddListener((value) =>
                {
                    OnValueChanged(child.name, value);
                });
            }
        }
    }
}