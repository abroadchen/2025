from ncclient import manager
from ncclient.xml_ import to_ele


def netconf():
    return manager.connect(host="192.168.1.1",
                         port=830,
                         username="admin",
                         password="admin",
                         look_for_keys=False,
                         allow_agent=False,
                         device_params={'name': 'default'},
                         hostkey_verify=False)


if __name__ == '__main__':
    CONFIG = """
    
        rpc标签包裹的内容
    """
    try:
        m = netconf()
        content = to_ele(CONFIG)
        res = m.rpc(content)
        # if "<ok/>" in str(res):
        #     print("exec success")
        # else:
        #     print("exec failed")
    except Exception as e:
        print(e)
    finally:
        m.close()