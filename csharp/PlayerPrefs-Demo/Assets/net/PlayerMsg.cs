using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMsg : BaseMsg
{
    public int playerID;
    public PlayerData playerData;
    public override int GetBytesNum()
    {
        return 4 + 4 + 4 + playerData.GetBytesNum();
    }

    public override byte[] Writing()
    {
        var index = 0;
        var bytesNum = GetBytesNum();
        var bytes = new byte[bytesNum];
        WriteInt(bytes, GetID(), ref index);
        WriteInt(bytes, bytesNum - 8, ref index);
        WriteInt(bytes, playerID, ref index);
        WriteData(bytes, playerData, ref index);
        return bytes;
    }

    public override int Reading(byte[] bytes, int beginIndex = 0)
    {
        var index = beginIndex;
        playerID = ReadInt(bytes, ref index);
        playerData = ReadData<PlayerData>(bytes, ref index);
        return index - beginIndex;
    }

    public override int GetID()
    {
        return 1001;
    }
}
