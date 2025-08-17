// Map.cs
// @author  June
// @date    2025.08.17
// @discription:

using GreedySnake.Lesson1;
using GreedySnake.Lesson3;
using GreedySnake.Lesson4;

namespace GreedySnake.Lesson5;

internal class Map : IDraw
{
    public Wall[] walls;

    public Map()
    {
        walls = new Wall[Game.w + (Game.h - 3) * 2];
        var index = 0;
        for (var i = 0; i < Game.w; i+=2)
        {
            walls[index] = new Wall(i, 0);
            ++index;
        }

        for (var i = 0; i < Game.w; i+=2)
        {
            walls[index] = new Wall(i, Game.h - 2);
            ++index;
        }

        for (var i = 1; i < Game.h - 2; i++)
        {
            walls[index] = new Wall(0, i);
            ++index;
        }

        for (var i = 1; i < Game.h - 2; i++)
        {
            walls[index] = new Wall(Game.w - 2, i);
            ++index;
        }
    }

    public void Draw()
    {
        for (var i = 0; i < walls.Length; i++)
        {
            walls[i].Draw();
        }
    }
}