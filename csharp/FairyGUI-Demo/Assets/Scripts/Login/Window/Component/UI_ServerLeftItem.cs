/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Login
{
    public partial class UI_ServerLeftItem : GButton
    {
        public GImage m_imgBK;
        public const string URL = "ui://ffsx6r1gtwkm1h";

        //��ʼ������
        private int beignIndex;
        //����������
        private int endIndex;

        public static UI_ServerLeftItem CreateInstance()
        {
            return (UI_ServerLeftItem)UIPackage.CreateObject("Login", "ServerLeftItem");
        }

        public override void ConstructFromXML(XML xml)
        {
            base.ConstructFromXML(xml);

            m_imgBK = (GImage)GetChild("imgBK");

            this.onClick.Add(()=> {

                //֪ͨѡ����� �ı��Ҳ������������
                var panel = UIManager.Instance.GetWindow<ServerChooseWindow>();
                panel.UpdatePanel(beignIndex, endIndex);
            });
        }

        /// <summary>
        /// �ṩ���ⲿʹ�õĳ�ʼ����ఴť ����ķ���
        /// </summary>
        /// <param name="beginIndex"></param>
        /// <param name="endIndex"></param>
        public void InitInfo(int beginIndex, int endIndex)
        {
            //��¼��Χ
            this.beignIndex = beginIndex;
            this.endIndex = endIndex;

            //�ı䰴ť��ʾ����
            this.text = beginIndex + " - " + endIndex + "��";
        }

    }
}