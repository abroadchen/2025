/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Login
{
    public partial class UI_WindowTip : GComponent
    {
        public GRichTextField m_txtInfo;
        public GButton m_closeButton;
        public GGraph m_dragArea;
        public GGraph m_contentArea;
        public const string URL = "ui://ffsx6r1gea6c3";

        public static UI_WindowTip CreateInstance()
        {
            return (UI_WindowTip)UIPackage.CreateObject("Login", "WindowTip");
        }

        public override void ConstructFromXML(XML xml)
        {
            base.ConstructFromXML(xml);

            m_txtInfo = (GRichTextField)GetChild("txtInfo");
            m_closeButton = (GButton)GetChild("closeButton");
            m_dragArea = (GGraph)GetChild("dragArea");
            m_contentArea = (GGraph)GetChild("contentArea");
        }
    }
}