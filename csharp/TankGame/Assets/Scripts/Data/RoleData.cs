using System.Collections;
using System.Collections.Generic;
using System.Xml.Serialization;
using UnityEngine;

public class RoleData 
{
    public List<RoleInfo> roleList = new List<RoleInfo>();
}

public class RoleInfo
{
    [XmlAttribute]
    public int hp;
    [XmlAttribute]
    public int speed;
    [XmlAttribute]
    public int volume;
    [XmlAttribute]
    public string resName;
    [XmlAttribute]
    public float scale;
}