// BlockInfo.cs
// @author  June
// @date    2025.08.17
// @discription:

using Tetris.Lesson2;

namespace Tetris.Lesson4;

internal class BlockInfo
{
    private List<Position[]> list;

    public BlockInfo(EDrawType type)
    {
        list = new List<Position[]>();

        switch (type)
        {
            case EDrawType.Cube:
                list.Add(new Position[3]
                {
                    new Position(2, 0),
                    new Position(0, 1),
                    new Position(2, 1)
                });
                break;
            case EDrawType.Line:
                list.Add(new Position[3]
                {
                    new Position(0, -1),
                    new Position(0, 1),
                    new Position(0, 2)
                });
                list.Add(new Position[3]
                {
                    new Position(-4, 0),
                    new Position(-2, 0),
                    new Position(2, 0)
                });
                list.Add(new Position[3]
                {
                    new Position(0, -2),
                    new Position(0, -1),
                    new Position(0, 1)
                });
                list.Add(new Position[3]
                {
                    new Position(-2, 0),
                    new Position(2, 0),
                    new Position(4, 0)
                });
                break;
            case EDrawType.Tank:
                list.Add(new Position[3]
                {
                    new Position(-2, 0),
                    new Position(2, 0),
                    new Position(0, 1)
                });
                list.Add(new Position[3]
                {
                    new Position(0, -1),
                    new Position(-2, 0),
                    new Position(0, 1)
                });
                list.Add(new Position[3]
                {
                    new Position(0, -1),
                    new Position(-2, 0),
                    new Position(2, 0)
                });
                list.Add(new Position[3]
                {
                    new Position(0, -1),
                    new Position(2, 0),
                    new Position(0, 1)
                });
                break;
            case EDrawType.LeftLadder:
                list.Add(new Position[3]
                {
                    new Position(0, -1),
                    new Position(2, 0),
                    new Position(2, 1)
                });
                list.Add(new Position[3]
                {
                    new Position(-2, 1),
                    new Position(0, 1),
                    new Position(2, 0)
                });
                list.Add(new Position[3]
                {
                    new Position(-2, -1),
                    new Position(-2, 0),
                    new Position(0, 1)
                });
                list.Add(new Position[3]
                {
                    new Position(-2, 0),
                    new Position(0, -1),
                    new Position(2, -1)
                });
                break;
            case EDrawType.RightLadder:
                list.Add(new Position[3]
                {
                    new Position(0, -1),
                    new Position(-2, 0),
                    new Position(-2, 1)
                });
                list.Add(new Position[3]
                {
                    new Position(-2, -1),
                    new Position(0, -1),
                    new Position(2, 0)
                });
                list.Add(new Position[3]
                {
                    new Position(2, -1),
                    new Position(2, 0),
                    new Position(0, 1)
                });
                list.Add(new Position[3]
                {
                    new Position(-2, 0),
                    new Position(0, 1),
                    new Position(2, 1)
                });
                break;
            case EDrawType.LeftLongLadder:
                list.Add(new Position[3]
                {
                    new Position(-2, -1),
                    new Position(0, -1),
                    new Position(0, 1)
                });
                list.Add(new Position[3]
                {
                    new Position(-2, 0),
                    new Position(2, 0),
                    new Position(2, 1)
                });
                list.Add(new Position[3]
                {
                    new Position(0, -1),
                    new Position(0, 1),
                    new Position(2, 1)
                });
                list.Add(new Position[3]
                {
                    new Position(-2, 1),
                    new Position(-2, 0),
                    new Position(2, 0)
                });
                break;
            case EDrawType.RightLongLadder:
                list.Add(new Position[3]
                {
                    new Position(0, -1),
                    new Position(2, -1),
                    new Position(0, 1)
                });
                list.Add(new Position[3]
                {
                    new Position(-2, 0),
                    new Position(2, 0),
                    new Position(2, 1)
                });
                list.Add(new Position[3]
                {
                    new Position(-2, 1),
                    new Position(0, 1),
                    new Position(0, -1)
                });
                list.Add(new Position[3]
                {
                    new Position(-2, -1),
                    new Position(-2, 0),
                    new Position(2, 0)
                });
                break;
        }
    }

    public Position[] this[int index]
    {
        get
        {
            if (index < 0)
                return list[0];
            else if (index >= list.Count)
                return list[list.Count - 1];
            else
                return list[index];
        }
    }

    public int Count { get => list.Count;}

}