// InputThread.cs
// @author  June
// @date    2025.08.17
// @discription:

namespace Tetris.Lesson13;

internal class InputThread
{
    private Thread inputThread;

    public event Action inputEvent;
    
    private static InputThread instance = new InputThread();

    public static InputThread Instance
    {
        get
        {
            return instance;
        }
    }
    
    private InputThread()
    {
        inputThread = new Thread(InputCheck);
        inputThread.IsBackground = true;
        inputThread.Start();
    }

    private void InputCheck()
    {
        while (true)
        {
            inputEvent?.Invoke();
        }
    }
}