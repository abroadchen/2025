// Map.cs
// @author  June
// @date    2025.08.17
// @discription:

using Tetris.Lesson1;
using Tetris.Lesson2;

namespace Tetris.Lesson3;

internal class Map : IDraw
{
    private List<DrawObject> walls = new List<DrawObject>();
    public List<DrawObject> dynamicWalls = new List<DrawObject>();


    private GameScene curGameScene;
    private int w;
    public int h;
    private int[] recordInfo;
    public Map(GameScene scene)
    {
        this.curGameScene = scene;
        h = Game.h - 6;
        recordInfo = new int[h];

        w = 0;
        for (var i = 0; i < Game.w; i+=2)
        {
            walls.Add(new DrawObject(EDrawType.Wall, i, h));
            ++w;
        }

        w -= 2;
        for (var i = 0; i < h; i++)
        {
            walls.Add(new DrawObject(EDrawType.Wall, 0, i));
            walls.Add(new DrawObject(EDrawType.Wall, Game.w - 2, i));
        }
    }

    public void Draw()
    {
        foreach (var t in walls)
        {
            t.Draw();
        }

        foreach (var t in dynamicWalls)
        {
            t.Draw();
        }
    }

    private void ClearDraw()
    {
        foreach (var t in dynamicWalls)
        {
            t.ClearDraw();
        }
    }

    /// <summary>
    /// 提供给外部添加动态方块的函数
    /// </summary>
    /// <param name="walls"></param>
    public void AddWalls(List<DrawObject> walls)
    {
        for (var i = 0; i < walls.Count; i++)
        {
            walls[i].ChangeType(EDrawType.Wall);
            dynamicWalls.Add(walls[i]);

            if (walls[i].pos.y <= 0)
            {
                this.curGameScene.StopThread();
                Game.ChangeScene(ESceneType.End);
                return;
            }
            
            
            recordInfo[h - 1 - walls[i].pos.y] += 1;
        }
        ClearDraw();
        CheckClear();
        Draw();
    }

    private void CheckClear()
    {
        var delList = new List<DrawObject>();
        for (var i = 0; i < recordInfo.Length; i++)
        {
            if (recordInfo[i] != w) return;
            
            //for (var j = 0; j < dynamicWalls.Count; j++)
            //{
            //    if (i == h - 1 - dynamicWalls[j].pos.y)
            //        delList.Add(dynamicWalls[j]);
            //    else if (h - 1 - dynamicWalls[j].pos.y > i)
            //    {
            //        ++dynamicWalls[j].pos.y;
            //    }
            //}
            foreach (var wall in dynamicWalls)
            {
                if (i == h - 1 - wall.pos.y)
                    delList.Add(wall);
                else if (h - 1 - wall.pos.y > i)
                {
                    ++wall.pos.y;
                }
            }

            foreach (var wall in delList)
            {
                dynamicWalls.Remove(wall);
            }

            for (var j = i; j < recordInfo.Length - 1; j++)
            {
                recordInfo[j] = recordInfo[j + 1];
            }

            recordInfo[recordInfo.Length - 1] = 0;
            
            CheckClear();
            break;
        }
    }
}