public class InputMgr : BaseManager<InputMgr>
{
    private bool isStart = false;

    public InputMgr()
    {
        MonoMgr.GetInstance().AddUpdateListener(MyUpdate);
    }


    public void StartOrEndCheck(bool isOpen)
    {
        isStart = isOpen;
    }

    private void CheckKeyCode(KeyCode key)
    {
        if (Input.GetKeyDown(key))
            EventCenter.GetInstance().EventTrigger("某键按下", key);
        if (Input.GetKeyUp(key))
            EventCenter.GetInstance().EventTrigger("某键抬起", key);
    }


    private void MyUpdate()
    {
        if (!isStart)
            return;
        CheckKeyCode(KeyCode.W);
        CheckKeyCode(KeyCode.A);
        CheckKeyCode(KeyCode.S);
        CheckKeyCode(KeyCode.D);
    }
}
