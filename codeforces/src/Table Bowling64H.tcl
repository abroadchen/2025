//
// Created by Psy.C on 2025/10/29.
//
/*
*从标准输入读取第一行到变量t，表示学生人数
循环t次，每次读取一行学生信息（姓名和成绩），追加到列表a中
lappend a [gets stdin]：将每行输入添加到列表a的末尾
 *
*对列表a进行双重排序：
首先按索引0（姓名）进行字典序排序：[lsort -index 0 $a]
然后按索引1（成绩）进行降序整数排序：lsort -decreasing -integer -index 1
这样确保了相同成绩的学生按姓名字母顺序排列，整体按成绩降序排列
 *
 *遍历排序后的列表a，每次迭代将当前元素赋值给变量v
*在列表a中查找所有成绩等于当前学生v的成绩的元素
lindex $v 1：获取当前学生的成绩
lsearch -all：查找所有匹配项，返回匹配元素的索引列表
 *
*计算排名范围：
1 + [lindex $is 0]：第一个匹配位置的排名（+1因为排名从1开始）
[llength $is] > 1 ? 1 + [lindex $is end] : ""：如果是并列成绩，计算最后一个位置的排名
 *
*输出结果：
[join $is -]：将排名范围用连字符连接
[lindex $v 0]：输出学生姓名
 */
for {gets stdin t} {$t > 0} {incr t -1} {
    lappend a [gets stdin]
}

set a [lsort -decreasing -integer -index 1 [lsort -index 0 $a]]

foreach {v} $a {
    set is [lsearch -all $a "* [lindex $v 1]"]
    set is "[expr {1 + [lindex $is 0]}] [expr [llength $is] > 1 ? 1 + [lindex $is end] : \"\"]"
    puts "[join $is -] [lindex $v 0]"
}