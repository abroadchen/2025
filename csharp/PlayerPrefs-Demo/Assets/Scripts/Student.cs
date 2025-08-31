using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using UnityEngine;

public class Student
{
    public int age;
    public string name;
    public int number;
    public bool sex;

    public void Save(string fileName)
    {
        if (!Directory.Exists(Application.persistentDataPath + "/Student"))
            Directory.CreateDirectory(Application.persistentDataPath + "/Student");
        using var fs = new FileStream(Application.persistentDataPath + "/Student/" + fileName + ".json", FileMode.OpenOrCreate, FileAccess.Write);
        var bytes = BitConverter.GetBytes(age);
        fs.Write(bytes, 0, bytes.Length);
        bytes = Encoding.UTF8.GetBytes(name);
        fs.Write(BitConverter.GetBytes(bytes.Length), 0, 4);
        fs.Write(bytes, 0, bytes.Length);
        bytes = BitConverter.GetBytes(number);
        fs.Write(bytes, 0, bytes.Length);
        bytes = BitConverter.GetBytes(sex);
        fs.Write(bytes, 0, bytes.Length);
        fs.Flush();
        //fs.Dispose();
        fs.Close();
    }

    public static Student Load(string fileName)
    {
        if (!File.Exists(Application.persistentDataPath + "/Student/" + fileName + ".json")) return null;
        var s = new Student();
        using var fs = File.Open(Application.persistentDataPath + "/Student/" + fileName + ".json", FileMode.Open, FileAccess.Read);
        var bytes = new byte[fs.Length];
        fs.Read(bytes, 0, bytes.Length);
        fs.Close();
        var index = 0;
        s.age = BitConverter.ToInt32(bytes, index);
        index += 4;
        var length = BitConverter.ToInt32(bytes, index);
        index += 4;
        s.name = Encoding.UTF8.GetString(bytes, index, length);
        index += length;
        s.number = BitConverter.ToInt32(bytes, index);
        index += 4;
        s.sex = BitConverter.ToBoolean(bytes, index);
        return s;
    }
}
