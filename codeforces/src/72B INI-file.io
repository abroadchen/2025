//
// Created by Psy.C on 2025/11/3.
//
/*
创建一个新的Map对象并赋值给变量MP，用于存储配置文件的节和键值对
在MP中创建一个空字符串键，对应一个空的Map，用于存储全局节（没有节名的键值对）
从标准输入读取一行并转换为数字，赋值给变量N（表示总行数）
初始化section变量为空字符串，用于跟踪当前所在的节
从1到N循环处理每一行输入
读取一行输入并去除首尾空白字符
如果行首字符是分号";"（注释行），则跳过此行
如果行首字符是左方括号"["，表示这是一个节标题行
去掉第一个字符"["，获取剩下的字符串
获取字符串长度
去掉最后一个字符"]"，提取节名称
去除节名称前后的空白字符
如果该节在MP中不存在，则创建一个新的Map来存储该节的键值对
继续处理下一行
找到等号"="的位置，p记录等号的索引
提取等号左边的部分作为键L，并去除空白字符
提取等号右边的部分作为值R，并去除空白字符
将键值对存储到当前节对应的Map中
获取MP中所有的键（节名），并按字母顺序排序
遍历排序后的所有节名
获取当前节对应的Map
如果节名长度大于等于1（不是全局节），则输出节标题格式"[节名]"
获取当前节中所有键并排序
遍历每个键，获取对应的值
按"键=值"格式输出每一行
输出格式化的键值对
*/
MP := Map clone
MP atPut ("", Map clone)
N := File standardInput readLine asNumber
section := ""

for(i, 1, N,
  Line := File standardInput readLine
  Line = Line strip
  if((Line at(0)) == (";" at(0)), continue)
  if((Line at(0)) == ("[" at(0)),
    Line = Line slice(1)
    len := Line size
    Line = Line slice(0, len - 1)
    section = Line strip
    if (MP at(section) == nil,
      MP atPut(section, Map clone)
    )
    continue
  )
  p := 0
  while((Line at(p)) != ("=" at(0)), p = p + 1)
  L := Line slice(0, p) strip
  R := Line slice(p + 1) strip
  MP at(section) atPut(L, R)
)

keys := MP keys sort
keys foreach(key,
  mp := MP at(key)
  if((key size) >= 1,
    sec := "[" .. key .. "]"
    sec println
  )
  mp keys sort foreach(L,
    R := mp at(L)
    out := L .. "=" .. R
    out println
  )
)
