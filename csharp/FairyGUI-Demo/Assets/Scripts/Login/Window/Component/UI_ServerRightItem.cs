/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Login
{
    public partial class UI_ServerRightItem : GButton
    {
        public GImage m_imgNew;
        public const string URL = "ui://ffsx6r1gtwkm1i";

        //��ǰ��ť ��������һ�������� ��¼����������
        public ServerInfo nowServerInfo;
        

        public static UI_ServerRightItem CreateInstance()
        {
            return (UI_ServerRightItem)UIPackage.CreateObject("Login", "ServerRightItem");
        }

        public override void ConstructFromXML(XML xml)
        {
            base.ConstructFromXML(xml);

            m_imgNew = (GImage)GetChild("imgNew");

            //�Լ������ʱ ��ʲô
            this.onClick.Add(() =>
            {
                //��¼ѡ��ķ�����ID
                LoginMgr.Instance.loginData.frontServerID = nowServerInfo.id;

                //����ѡ�����
                UIManager.Instance.HideWindow<ServerChooseWindow>();

                //��ʾ���������
                UIManager.Instance.ShowWindow<ServerWindow>();
            });
        }

        /// <summary>
        /// �����ⲿ����ķ��������� ����������
        /// </summary>
        /// <param name="info"></param>
        public void InitInfo(ServerInfo info)
        {
            //��¼������
            this.nowServerInfo = info;

            //���°�ť����ʾ�ķ�������
            this.text = info.id + "��" + info.name;

            //�����Ƿ����·�
            m_imgNew.visible = info.isNew;

            //���� ��ǰ��״̬
            switch (info.state)
            {
                case 0://����
                    this.icon = "ui://Login/ui_DL_liuchang_01";
                    break;
                case 1://��æ
                    this.icon = "ui://Login/ui_DL_fanhua_01";
                    break;
                case 2://��
                    this.icon = "ui://Login/ui_DL_huobao_01";
                    break;
                case 3://ά��
                    this.icon = "ui://Login/ui_DL_weihu_01";
                    break;
            }
        }
    }
}