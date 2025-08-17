// GameScene.cs
// @author  June
// @date    2025.08.17
// @discription:
using GreedySnake.Lesson1;
using GreedySnake.Lesson4;
using GreedySnake.Lesson5;
using GreedySnake.Lesson6;

namespace GreedySnake.Lesson2;

internal class GameScene : ISceneUpdate
{
    private Map map;
    private Snake snake;
    private Food food;
    private int updateIndex = 0;
    public GameScene()
    {
        map = new Map();
        snake = new Snake(40, 10);
        food = new Food(snake);
    }

    public void Update()
    {
        if (updateIndex % 5000 == 0)
        {
            map.Draw();
            food.Draw();
            snake.Move();
            snake.Draw();
            if (snake.CheckEnd(map))
            {
                Game.ChangeScene(ESceneType.End);
            }
            snake.CheckEatFood(food);
            updateIndex = 0;
        }
        ++updateIndex;

        if (Console.KeyAvailable)
        {
            switch (Console.ReadKey(true).Key)
            {
                case ConsoleKey.W:
                    snake.ChangeDir(EMoveDir.Up);
                    break;
                case ConsoleKey.S:
                    snake.ChangeDir(EMoveDir.Down);
                    break;
                case ConsoleKey.A:
                    snake.ChangeDir(EMoveDir.Left);
                    break;
                case ConsoleKey.D:
                    snake.ChangeDir(EMoveDir.Right);
                    break;
            }
        }
    }
}