using System.Collections;
using System.Collections.Generic;
using System.Text;
using UnityEngine;

public class PlayerData : BaseData
{
    public string name;
    public int atk;
    public int lev;
    public override int GetBytesNum()
    {
        return 4 + 4 + 4 + Encoding.UTF8.GetBytes(name).Length;
    }

    public override byte[] Writing()
    {
        var index = 0;
        var bytes = new byte[GetBytesNum()];
        WriteString(bytes, name, ref index);
        WriteInt(bytes, atk, ref index);
        WriteInt(bytes, lev, ref index);
        return bytes;
    }

    public override int Reading(byte[] bytes, int beginIndex = 0)
    {
        var index = beginIndex;
        name = ReadString(bytes, ref index);
        atk = ReadInt(bytes, ref index);
        lev = ReadInt(bytes, ref index);
        return index - beginIndex;
    }
}
