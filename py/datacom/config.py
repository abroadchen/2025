"""
@author June
@time 2025/7/28
@description:
"""
netconf_info = {"ip": "192.168.100.1", "port": 830, "username": "root", "password": "123456"}
switch_info = {"ip": "192.168.100.1", "port": 22, "username": "root", "password": "123456", "sysname": "X_T1_ACC"}
parameter_command = {
    "ospf_state": {"command": "dis ospf peer b\n", "re": "Down|Init|2-Way|Exstart|Exchange|Loading|Full"},
    "fan_state": {"command": "display fan\n", "re": "Normal"},
}
host_log = """
"""