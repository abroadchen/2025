// BlockWorker.cs
// @author  June
// @date    2025.08.17
// @discription:

using Tetris.Lesson1;
using Tetris.Lesson2;
using Tetris.Lesson3;
using Tetris.Lesson4;

namespace Tetris.Lesson5;

internal enum EChangeType
{
    Left,
    right
}



internal class BlockWorker : IDraw
{
    private List<DrawObject> blocks;
    private Dictionary<EDrawType, BlockInfo> blockInfoDic;
    private BlockInfo curBlockInfo;
    private int curInfoIndex;

    public BlockWorker()
    {
        blockInfoDic = new Dictionary<EDrawType, BlockInfo>()
        {
            { EDrawType.Cube, new BlockInfo(EDrawType.Cube) },
            { EDrawType.Line, new BlockInfo(EDrawType.Line) },
            { EDrawType.Tank, new BlockInfo(EDrawType.Tank) },
            { EDrawType.LeftLadder, new BlockInfo(EDrawType.LeftLadder) },
            { EDrawType.RightLadder, new BlockInfo(EDrawType.RightLadder) },
            { EDrawType.LeftLongLadder, new BlockInfo(EDrawType.LeftLongLadder) },
            { EDrawType.RightLongLadder, new BlockInfo(EDrawType.RightLongLadder) }
        };
        
        RandomCreateBlock();
    }

    public void RandomCreateBlock()
    {
        var r = new Random();
        var type = (EDrawType)r.Next(1, 8);
        blocks = new List<DrawObject>()
        {
            new DrawObject(type),
            new DrawObject(type),
            new DrawObject(type),
            new DrawObject(type)
        };

        blocks[0].pos = new Position(24, -5);
        curBlockInfo = blockInfoDic[type];
        curInfoIndex = r.Next(0, curBlockInfo.Count);
        var pos = curBlockInfo[curInfoIndex];
        for (var i = 0; i < pos.Length; i++)
        {
            blocks[i + 1].pos = blocks[0].pos + pos[i];
        }
    }

    public void Draw()
    {
        for (var i = 0; i < blocks.Count; i++)
        {
            blocks[i].Draw();
        }
    }

    public void ClearDraw()
    {
        for (var i = 0; i < blocks.Count; i++)
        {
            blocks[i].ClearDraw();
        }
    }

    public void Change(EChangeType type)
    {
        ClearDraw();
        switch (type)
        {
            case EChangeType.Left:
                --curInfoIndex;
                if (curInfoIndex < 0)
                    curInfoIndex = curBlockInfo.Count - 1;
                break;
            case EChangeType.right:
                ++curInfoIndex;
                if (curInfoIndex >= curBlockInfo.Count)
                    curInfoIndex = 0;
                break;
        }

        var pos = curBlockInfo[curInfoIndex]; 
        for (var i = 0; i < pos.Length; i++)
        {
            blocks[i + 1].pos = blocks[0].pos + pos[i];
        }
        Draw();
    }

    public bool CanChange(EChangeType type, Map map)
    {
        var curIndex = curInfoIndex;
        switch (type)
        {
            case EChangeType.Left:
                --curIndex;
                if (curIndex < 0)
                    curIndex = curBlockInfo.Count - 1;
                break;
            case EChangeType.right:
                ++curIndex;
                if (curIndex >= curBlockInfo.Count)
                    curIndex = 0;
                break;
        }

        var curPos = curBlockInfo[curIndex];
        Position tempPos;
        for (var i = 0; i < curPos.Length; ++i)
        {
            tempPos = blocks[0].pos + curPos[i];
            if (tempPos.x < 2 ||
                tempPos.x >= Game.w - 2 ||
                tempPos.y >= map.h)
                return false;
        }
        for (var i = 0; i < curPos.Length; ++i)
        {
            tempPos = blocks[0].pos + curPos[i];
            for (var j = 0; j < map.dynamicWalls.Count; ++j)
            {
                if (tempPos == map.dynamicWalls[j].pos)
                    return false;
            }
        }
        return true;
    }

    public void MoveRL(EChangeType type)
    {
        ClearDraw();
        var movePos = new Position(type == EChangeType.Left ? -2 : 2, 0);
        for (var i = 0; i < blocks.Count; ++i)
        {
            blocks[i].pos += movePos;
        }
        Draw();
    }

    public bool CanMoveRL(EChangeType type, Map map)
    {
        var movePos = new Position(type == EChangeType.Left ? -2 : 2, 0);
        Position pos;
        for (var i = 0; i < blocks.Count; ++i)
        {
            pos = blocks[i].pos + movePos;
            if (pos.x < 2 || pos.x >= Game.w - 2)
                return false;
        }

        for (var i = 0; i < blocks.Count; ++i)
        {
            pos = blocks[i].pos + movePos;
            for (var j = 0; j < map.dynamicWalls.Count; ++j)
            {
                if (pos == map.dynamicWalls[j].pos)
                    return false;
            }
        }
        return true;
    }


    public void AutoMove()
    {
        ClearDraw();
        //var downMove = new Position(0, 1);
        for (var i = 0; i < blocks.Count; ++i)
        {
            blocks[i].pos.y += 1;
        }
        Draw();
    }

    public bool CanMove(Map map)
    {
        var movePos = new Position(0, 1);
        Position pos;
        for (var i = 0; i < blocks.Count; ++i)
        {
            pos = blocks[i].pos + movePos;
            if (pos.y >= map.h)
            {
                map.AddWalls(blocks);
                RandomCreateBlock();
                return false;
            }
        }

        for (var i = 0; i < blocks.Count; ++i)
        {
            pos = blocks[i].pos + movePos;
            for (var j = 0; j < map.dynamicWalls.Count; ++j)
            {
                if (pos == map.dynamicWalls[i].pos)
                {
                    map.AddWalls(blocks);
                    RandomCreateBlock();
                    return false;
                }
            }
        }
        return true;
    }
}