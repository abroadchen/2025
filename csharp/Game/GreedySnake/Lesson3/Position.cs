// Position.cs
// @author  June
// @date    2025.08.17
// @discription:

namespace GreedySnake.Lesson3;

struct Position
{
    public int x;
    public int y;
    
    public Position(int x, int y)
    {
        this.x = x;
        this.y = y;
    }
    
    public static bool operator ==(Position a, Position b)
    {
        return a.x == b.x && a.y == b.y;
    }
    
    public static bool operator !=(Position a, Position b)
    {
        return !(a == b);
    }
}