public class InputTest : MonoBehaviour
{
    void Start()
    {
        InputMgr.GetInstance().StartOrEndCheck(true);
        EventCenter.GetInstance().AddEventListener<KeyCode>("某键按下", CheckInputDown);
        EventCenter.GetInstance().AddEventListener<KeyCode>("某键抬起", CheckInputUp);
    }

    private void CheckInputDown(KeyCode key)
    {
        //KeyCode code = (KeyCode)key;
        switch (code)
        {
            case KeyCode.W:
                Debug.Log("前进");
                break;
            case KeyCode.A:
                Debug.Log("左转");
                break;
            case KeyCode.S:
                Debug.Log("后退");
                break;
            case KeyCode.D:
                Debug.Log("右转");
                break;
        }
    }

    private void CheckInputUp(object key)
    {

    }
}
