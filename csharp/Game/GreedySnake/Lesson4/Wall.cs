// Wall.cs
// @author  June
// @date    2025.08.17
// @discription:

using GreedySnake.Lesson3;

namespace GreedySnake.Lesson4;

internal class Wall : GameObject
{
    public Wall(int x, int y)
    {
        pos = new Position(x, y);
    }
    
    public override void Draw()
    {
        Console.SetCursorPosition(pos.x, pos.y);
        Console.ForegroundColor = ConsoleColor.Red;
        Console.Write("■");
    }
}