//
// Created by Psy.C on 2025/11/3.
//
/*
定义一个名为concat的方法，接受两个参数a和b
使用..操作符连接两个字符串并返回结果
定义一个名为reverse的方法，接受参数x
将x转换为可变字符串，然后反转并返回
定义一个名为substr的方法，接受参数x(字符串)、a(起始位置)、b(结束位置)、c(步长)
如果c为空(nil)，则设置默认步长为1
创建一个空的可变字符串r，用于存储结果
从索引a-1到b-1，以步长c遍历字符串x
将每个位置的字符追加到结果字符串r中
注意：这里使用a-1和b-1是因为Io语言中字符串索引从0开始，而输入参数从1开始
返回提取的子字符串

创建一个空列表r，用于存储处理后的字符串片段
读取一行输入，在前后各添加一个空格
按双引号"分割字符串，得到多个片段
遍历每个片段，i是索引，v是片段内容
如果索引i是偶数（0,2,4...），说明这是引号外的文本，转换为小写后添加到列表r
如果索引i是奇数（1,3,5...），说明这是引号内的文本，保持原样并在前后加上双引号，然后添加到列表r

将列表r中的所有元素连接成一个字符串
使用doString执行连接后的字符串（可能是为了处理转义字符）
在结果前后加上双引号并输出

*/
concat := method(a, b, a .. b)
reverse := method(x, x asMutable reverse)
substr := method(x, a, b, c, if(c isNil, c = 1)
  r := "" asMutable
  for(i, a - 1, b - 1, c, r append(x at(i)))
  return r
)
r := list()
(" " .. File standardInput readLine .. " ") split("\"") foreach(i, v,
  r append(if(i % 2 == 0, v asLowercase, "\"" .. v .. "\""))
)
writeln("\"", doString(r join("")), "\"")
