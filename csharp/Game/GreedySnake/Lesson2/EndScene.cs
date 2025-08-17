// EndScene.cs
// @author  June
// @date    2025.08.17
// @discription:
using GreedySnake.Lesson1;
namespace GreedySnake.Lesson2;

internal class EndScene : BeginOrEndBaseScene
{
    public EndScene()
    {
        strTitle = "结束游戏";
        strOne = "回到开始界面";
    }
    public override void EnterJDoSomthing()
    {
        if (nowSelIndex == 0)
        {
            Game.ChangeScene(ESceneType.Begin);
        }
        else
        {
            Environment.Exit(0);
        }
    }
}