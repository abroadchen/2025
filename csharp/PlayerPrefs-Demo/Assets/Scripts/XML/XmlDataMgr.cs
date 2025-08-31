using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Xml.Serialization;
using UnityEngine;

public class XmlDataMgr
{
    public static XmlDataMgr Instance { get; } = new XmlDataMgr();

    private XmlDataMgr()
    {
        
    }

    public void SaveData(object data, string fileName)
    {
        var path = Application.persistentDataPath + "/" + fileName + ".xml";
        using var writer = new StreamWriter(path);
        var s = new XmlSerializer(data.GetType());
        s.Serialize(writer, data);
    }

    public object LoadData(Type type, string fileName)
    {
        var path = Application.persistentDataPath + "/" + fileName + ".xml";
        if (!File.Exists(path))
        {
            path = Application.streamingAssetsPath + "/" + fileName + ".xml";
            if (!File.Exists(path))
            {
                return Activator.CreateInstance(type);
            }
        }
        using var reader = new StreamReader(path);
        var s = new XmlSerializer(type);
        return s.Deserialize(reader);
    }
}
