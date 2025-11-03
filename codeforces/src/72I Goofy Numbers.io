//
// Created by Psy.C on 2025/11/3.
//
/*

初始化变量all为1，用于标记是否所有数字位都能整除原数（1表示true，0表示false）
初始化变量one为0，用于标记是否至少有一个数字位能整除原数（1表示true，0表示false）
将原始数字a保存到变量was中，因为在循环中a会被修改

计算a除以10的余数，即获取a的最后一位数字，赋值给last
将a除以10，然后取floor（向下取整）
这样就去掉了a的最后一位数字
检查原始数字was是否能被当前数字位last整除
如果能整除：设置one为1（表示至少有一个数字位能整除）
如果不能整除：设置all为0（表示不是所有数字位都能整除）
如果a变为0，说明已经处理完所有数字位，跳出循环

根据条件输出相应结果：
如果all为1（所有数字位都能整除原数），输出"happier"
否则检查one：
如果one为1（至少有一个数字位能整除），输出"happy"
否则输出"upset"

*/
a := File standardInput readLine asNumber
all := 1
one := 0
was := a

for(cur, 1, 111, (
  last := a % 10
  a := a / 10
  a := a floor
  if(was % last == 0, one := 1, all := 0)
  if(a == 0, break)
))
if(all == 1, "happier" println, 
  (if(one == 1, "happy" println, "upset" println)))
