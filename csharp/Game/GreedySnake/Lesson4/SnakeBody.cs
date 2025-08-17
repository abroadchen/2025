// SnakeBody.cs
// @author  June
// @date    2025.08.17
// @discription:

using GreedySnake.Lesson3;

namespace GreedySnake.Lesson4;

internal enum ESnakeBodyType
{
    Head,
    Body
}


internal class SnakeBody : GameObject
{
    private ESnakeBodyType type;
    
    public SnakeBody(int x, int y, ESnakeBodyType type)
    {
        pos = new Position(x, y);
        this.type = type;
    }
    
    public override void Draw()
    {
        Console.SetCursorPosition(pos.x, pos.y);
        Console.ForegroundColor = type == ESnakeBodyType.Head ? ConsoleColor.Yellow : ConsoleColor.Green;
        Console.Write(type == ESnakeBodyType.Head ? "●" : "◎");
    }
}