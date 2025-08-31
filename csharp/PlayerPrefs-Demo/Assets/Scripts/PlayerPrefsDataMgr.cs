using System;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;
using UnityEngine;

public class PlayerPrefsDataMgr 
{
    public static PlayerPrefsDataMgr Instance { get; } = new PlayerPrefsDataMgr();

    private PlayerPrefsDataMgr()
    {
        
    }

    public void SaveData(object data, string keyName)
    {
        var dataType = data.GetType();
        var infos = dataType.GetFields();
        var saveKeyName = "";
        FieldInfo info;
        foreach (var t in infos)
        {
            info = t;
            saveKeyName = keyName + "_" + dataType.Name + "_" + info.FieldType.Name + "_" + info.Name;
            SaveValue(info.GetValue(data), saveKeyName);
        }
        PlayerPrefs.Save();
    }

    private void SaveValue(object value, string keyName)
    {
        var fieldType = value.GetType();
        if (fieldType == typeof(int))
        {
            PlayerPrefs.SetInt(keyName, (int)value);
        }
        else if (fieldType == typeof(float))
        {
            PlayerPrefs.SetFloat(keyName, (float)value);
        }
        else if (fieldType == typeof(bool))
        {
            PlayerPrefs.SetInt(keyName, (bool)value ? 1 : 0);
        }
        else if (fieldType == typeof(string))
        {
            PlayerPrefs.SetString(keyName, value.ToString());
        }
        else if (typeof(IList).IsAssignableFrom(fieldType))
        {
            var list = value as IList;
            var index = 0;
            PlayerPrefs.SetInt(keyName, list.Count);
            foreach (var obj in list)
            {
                SaveValue(obj, keyName + index);
                ++index;
            }
        }
        else if (typeof(IDictionary).IsAssignableFrom(fieldType))
        {
            var dic = value as IDictionary;
            PlayerPrefs.SetInt(keyName, dic.Count);
            var index = 0;
            foreach (var key in dic.Keys)
            {
                SaveValue(key, keyName + "_key_" + index);
                SaveValue(dic[key], keyName + "_value_" + index);
                ++index;
            }
        }
        else
        {
            SaveData(value, keyName);
        }
    }

    public object LoadData(Type type, string keyName)
    {
        var data = Activator.CreateInstance(type);
        var infos = type.GetFields();
        var loadKeyName = ""; 
        FieldInfo info;
        for (var i = 0; i < infos.Length; i++)
        {
            info = infos[i];
            loadKeyName = keyName + "_" + type.Name + "_" + info.FieldType.Name + "_" + info.Name;
            info.SetValue(data, LoadValue(info.FieldType, loadKeyName));
        }
        return data;
    }
    
    private object LoadValue(Type fieldType, string keyName)
    {
        if (fieldType == typeof(int))
        {
            return PlayerPrefs.GetInt(keyName, 0);
        }
        else if (fieldType == typeof(float))
        {
            return PlayerPrefs.GetFloat(keyName, 0);
        }
        else if (fieldType == typeof(string))
        {
            return PlayerPrefs.GetString(keyName, "");
        }
        else if (fieldType == typeof(bool))
        {
            return PlayerPrefs.GetInt(keyName, 0) == 1 ? true : false;
        }
        else if (typeof(IList).IsAssignableFrom(fieldType))
        {
            var count = PlayerPrefs.GetInt(keyName, 0);
            var list = Activator.CreateInstance(fieldType) as IList;
            for (var i = 0; i < count; i++)
            {
                list.Add(LoadValue(fieldType.GetGenericArguments()[0], keyName + i));
            }

            return list;
        }
        else if (typeof(IDictionary).IsAssignableFrom(fieldType))
        {
            var count = PlayerPrefs.GetInt(keyName, 0);
            var dic = Activator.CreateInstance(fieldType) as IDictionary;
            var kvType = fieldType.GetGenericArguments();
            for (var i = 0; i < count; i++)
            {
                dic.Add(LoadValue(kvType[0], keyName + "_key_" + i), LoadValue(kvType[1], keyName + "_value_" + i));
            }

            return dic;
        }
        else
        {
            return LoadData(fieldType, keyName);
        }


    }
}
