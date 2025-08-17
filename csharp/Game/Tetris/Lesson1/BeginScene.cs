// BeginScene.cs
// @author  June
// @date    2025.08.17
// @discription:

namespace Tetris.Lesson1;

internal class BeginScene : BeginOrEndBaseScene
{
    public BeginScene()
    {
        strTitle = "俄罗斯方块";
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