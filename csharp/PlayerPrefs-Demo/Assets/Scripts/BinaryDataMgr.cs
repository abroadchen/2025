using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using UnityEngine;

public class BinaryDataMgr
{
    private static string SAVE_PATH = Application.persistentDataPath + "/Data/";
    public static string DATA_BINARY_PATH = Application.streamingAssetsPath + "/Binary/";
    
    private Dictionary<string, object> tableDic = new Dictionary<string, object>(); 
    public static BinaryDataMgr Instance { get; } = new BinaryDataMgr(); 
    private BinaryDataMgr() {}
    
    public void InitData() {}
    
    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="T">容器类名</typeparam>
    /// <typeparam name="K">数据结构体类名</typeparam>
    public void LoadTable<T, K>()
    {
        using (var fs = File.Open(DATA_BINARY_PATH + typeof(K).Name + ".tang", FileMode.Open, FileAccess.Read))
        {
            var bytes = new byte[fs.Length];
            fs.Read(bytes, 0, bytes.Length);
            fs.Close();
            var index = 0;
            var count = BitConverter.ToInt32(bytes, index);
            index += 4;
            var keyNameLength = BitConverter.ToInt32(bytes, index);
            index += 4;
            var keyName = Encoding.UTF8.GetString(bytes, index, keyNameLength);
            index += keyNameLength;
            var containerType = typeof(T);
            var containerObj = Activator.CreateInstance(containerType);
            var classType = typeof(K);
            var infos = classType.GetFields();
            for (var i = 0; i < count; i++)
            {
                var dataObj = Activator.CreateInstance(classType);
                foreach (var info in infos)
                {
                    if (info.FieldType == typeof(int))
                    {
                        info.SetValue(dataObj, BitConverter.ToInt32(bytes, index));
                        index += 4;
                    }
                    else if (info.FieldType == typeof(float))
                    {
                        info.SetValue(dataObj, BitConverter.ToSingle(bytes, index));
                        index += 4;
                    }
                    else if (info.FieldType == typeof(bool))
                    {
                        info.SetValue(dataObj, BitConverter.ToBoolean(bytes, index));
                        index += 1;
                    }
                    else if (info.FieldType == typeof(string))
                    {
                        var length = BitConverter.ToInt32(bytes, index);
                        index += 4;
                        info.SetValue(dataObj, Encoding.UTF8.GetString(bytes, index, length));
                        index  += length;
                    }
                }
    
                var dicObject = containerType.GetField("dataDic").GetValue(containerObj);
                var mInfo = dicObject.GetType().GetMethod("Add");
                var keyValue = classType.GetField(keyName).GetValue(dataObj);
                mInfo.Invoke(dicObject, new object[] { keyValue, dataObj });
            }
            tableDic.Add(typeof(T).Name, containerObj);
            fs.Close();
        }
    }

    public T GetTable<T>() where T : class
    {
        var tableName = typeof(T).Name;
        if (tableDic.ContainsKey(tableName))
            return tableDic[tableName] as T;
        return null;
    }
    
    

    public void Save(object obj, string fileName)
    {
        if (!Directory.Exists(SAVE_PATH)) Directory.CreateDirectory(SAVE_PATH);
        using var fs = new FileStream(SAVE_PATH + fileName + ".json", FileMode.OpenOrCreate, FileAccess.Write);
        var bf = new BinaryFormatter();
        bf.Serialize(fs, obj);
        fs.Close();
    }

    public T Load<T>(string fileName) where T : class
    {
        if (!File.Exists(SAVE_PATH + fileName + ".json")) return default(T);
        T obj;
        using var fs = File.Open(SAVE_PATH + fileName + ".json", FileMode.Open, FileAccess.Read);
        var bf = new BinaryFormatter();
        obj = bf.Deserialize(fs) as T;
        fs.Close();
        return obj;
    }
}
