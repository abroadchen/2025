using System.Collections;
using System.Collections.Generic;
using System.Xml.Serialization;
using UnityEngine;

public class RankData1
{
    public List<RankInfo1> rankList = new List<RankInfo1>();
}

public class RankInfo1
{
    [XmlAttribute]
    public string name;
    [XmlAttribute]
    public int time;
}