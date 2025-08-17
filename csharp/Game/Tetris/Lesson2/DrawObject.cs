// DrawObject.cs
// @author  June
// @date    2025.08.17
// @discription:

namespace Tetris.Lesson2;

internal enum EDrawType
{
    Wall,
    Cube,
    Line,
    Tank,
    LeftLadder,
    RightLadder,
    LeftLongLadder,
    RightLongLadder
}



internal class DrawObject : IDraw
{

    public Position pos;
    public EDrawType type;

    public DrawObject(EDrawType type)
    {
        this.type = type;
    }

    public DrawObject(EDrawType type, int x, int y): this(type)
    {
        this.pos = new Position(x, y);
    }

    public void ClearDraw()
    {
        if (pos.y < 0) return;
        Console.SetCursorPosition(pos.x, pos.y);
        Console.Write("  ");
    }
    public void Draw()
    { 
        if (pos.y < 0) return;
        Console.SetCursorPosition(pos.x, pos.y);
        Console.ForegroundColor = type switch
        {
            EDrawType.Wall => ConsoleColor.Red,
            EDrawType.Cube => ConsoleColor.Blue,
            EDrawType.Line => ConsoleColor.Green,
            EDrawType.Tank => ConsoleColor.Cyan,
            EDrawType.LeftLadder or EDrawType.RightLadder => ConsoleColor.Magenta,
            EDrawType.LeftLongLadder or EDrawType.RightLongLadder => ConsoleColor.Yellow,
            _ => Console.ForegroundColor
        };
        Console.Write("■");
    }

    public void ChangeType(EDrawType type)
    {
        this.type = type;
    }
}