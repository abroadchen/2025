// BeginScene.cs
// @author  June
// @date    2025.08.17
// @discription:
using GreedySnake.Lesson1;
namespace GreedySnake.Lesson2;

internal class BeginScene : BeginOrEndBaseScene
{
    public BeginScene()
    {
        strTitle = "贪吃蛇";
        strOne = "开始游戏";
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