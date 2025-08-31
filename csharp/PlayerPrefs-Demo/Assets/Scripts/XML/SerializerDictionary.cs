using System.Collections;
using System.Collections.Generic;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;
using UnityEngine;

public class SerilizerDictionary<TKey, TValue> : Dictionary<TKey, TValue>, IXmlSerializable
{
    public XmlSchema GetSchema()
    {
        return null;
    }

    public void ReadXml(XmlReader reader)
    {
        var keySer = new XmlSerializer(typeof(TKey));
        var valueSer = new XmlSerializer(typeof(TValue));
        reader.Read();
        while (reader.NodeType != XmlNodeType.EndElement)
        {
            var key = (TKey)keySer.Deserialize(reader);
            var value = (TValue)valueSer.Deserialize(reader);
            this.Add(key, value);
        }
    }

    public void WriteXml(XmlWriter writer)
    {
        var keySer = new XmlSerializer(typeof(TKey));
        var valueSer = new XmlSerializer(typeof(TValue));
        foreach (var kv in this)
        {
            keySer.Serialize(writer, kv.Key);
            valueSer.Serialize(writer, kv.Value);
        }
    }
}
