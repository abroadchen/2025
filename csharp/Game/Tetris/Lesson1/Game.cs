// Game.cs
// @author  June
// @date    2025.08.16
// @discription:

namespace Tetris.Lesson1;



internal enum ESceneType
{
    Begin,
    Game,
    End
}

internal class Game
{
    public const int w = 50;
    public const int h = 35;

    public static ISceneUpdate nowScene;
    
    public Game()
    {
        Console.CursorVisible = false;
        Console.SetWindowSize(w, h);
        Console.SetBufferSize(w, h);
        ChangeScene(ESceneType.Begin);
        
    }

    public void Start()
    {
        while (true)
        {
            if (nowScene != null)
                nowScene.Update();
        }
    }

    public static void ChangeScene(ESceneType type)//静态方法中不能使用成员变量
    {
        Console.Clear();
        nowScene = type switch
        {
            ESceneType.Begin => new BeginScene(),
            ESceneType.Game => new GameScene(),
            ESceneType.End => new EndScene()
        };
    }
}