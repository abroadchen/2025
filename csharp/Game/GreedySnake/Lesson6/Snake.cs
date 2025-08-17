// Snake.cs
// @author  June
// @date    2025.08.17
// @discription:


using GreedySnake.Lesson3;
using GreedySnake.Lesson4;
using GreedySnake.Lesson5;

namespace GreedySnake.Lesson6;

internal enum EMoveDir
{
    Up,
    Down,
    Left,
    Right
}

internal class Snake : IDraw
{
    private SnakeBody[] bodies;
    private int nowNum;
    private EMoveDir dir;

    public Snake(int x, int y)
    {
        bodies = new SnakeBody[200];
        bodies[0] = new SnakeBody(x, y, ESnakeBodyType.Head);
        nowNum = 1;
        dir = EMoveDir.Right;
    }

    public void Draw()
    {
        for (var i = 0; i < nowNum; i++)
        {
            bodies[i].Draw();
        }
    }

    #region 蛇的移动

    public void Move()
    {

        var lastBody = bodies[nowNum - 1];
        Console.SetCursorPosition(lastBody.pos.x, lastBody.pos.y);
        Console.Write("  ");

        for (var i= nowNum - 1; i > 0; i--)
        {
            bodies[i].pos = bodies[i - 1].pos;
        }
        
        
        switch (dir)
        {
            case EMoveDir.Up:
                --bodies[0].pos.y;
                break;
            case EMoveDir.Down:
                ++bodies[0].pos.y;
                break;
            case EMoveDir.Left:
                bodies[0].pos.x -= 2;
                break;
            case EMoveDir.Right:
                bodies[0].pos.x += 2;
                break;
        }
    }

    #endregion

    #region 改变方向

    public void ChangeDir(EMoveDir dir)
    {
        if (dir == this.dir ||
            nowNum > 1 && 
            (this.dir == EMoveDir.Left && dir == EMoveDir.Right ||
             this.dir == EMoveDir.Right && dir == EMoveDir.Left ||
             this.dir == EMoveDir.Up && dir == EMoveDir.Down ||
             this.dir == EMoveDir.Down && dir == EMoveDir.Up))
            return;
        this.dir = dir;
    }

    #endregion
    
    #region 撞墙撞身体检测

    public bool CheckEnd(Map map)
    {
        for (var i = 0; i < map.walls.Length; i++)
        {
            if (bodies[0].pos == map.walls[i].pos)
                return true;
        }

        for (var i = 1; i < nowNum; i++)
        {
            if (bodies[0].pos == bodies[i].pos)
                return true;
        }

        return false;
    }
    
    #endregion
    
    #region 蛇吃食物

    public bool CheckSamePos(Position p)
    {
        for (var i = 0; i < nowNum; i++)
        {
            if (bodies[i].pos == p)
                return true;
        }

        return false;
    }

    public void CheckEatFood(Food food)
    {
        if (bodies[0].pos == food.pos)
        {
            food.RandomPos(this);
            AddBody();
        }
    }

    #endregion

    #region 长身体

    private void AddBody()
    {
        SnakeBody frontBody = bodies[nowNum - 1];
        bodies[nowNum] = new SnakeBody(frontBody.pos.x, frontBody.pos.y, ESnakeBodyType.Body);
        ++nowNum;
    }

    #endregion
}