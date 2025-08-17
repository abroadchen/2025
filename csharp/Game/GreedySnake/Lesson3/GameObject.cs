// GameObject.cs
// @author  June
// @date    2025.08.17
// @discription:

namespace GreedySnake.Lesson3;

internal abstract class GameObject : IDraw
{
    public Position pos;
    public abstract void Draw();
}