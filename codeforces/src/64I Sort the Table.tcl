//
// Created by Psy.C on 2025/10/29.
//

/*
*从标准输入读取第一行，按空格分割成列表，存储到变量l中
这是表的列标题列表
 *
*从标准输入读取第二行，按逗号分割成列表，存储到变量r中
这是排序规则列表
初始化空列表a用于存储表格数据
 *
*无限循环读取输入数据：
读取一行到变量b
如果读取到空行则跳出循环
否则将该行按空格分割后添加到列表a中
这部分读取表格的具体数据行
 *
*将排序规则列表r进行反向排序
因为后面要从后往前应用排序规则（稳定排序的特性）
 *
 *遍历排序规则列表中的每一项
*查找当前排序列在标题列表中的索引位置
[lindex $x 0]：获取排序规则中的列名
[lsearch $l ...]：在标题列表中查找该列名的索引
 *
*根据排序规则进行排序：
如果是"ASC"（升序），则按该列升序排序
否则是降序，按该列降序排序
lsort -index $j：按指定索引列进行排序
 *
 *
 *遍历排序后的数据列表，逐行输出
 *
 */

set l [split [gets stdin]]
set r [split [gets stdin] ,]
set a {}

while {1} {
    gets stdin b
    if {$b == ""} {break}
    lappend a [split $b]
}

set r [lreverse $r]

foreach {x} $r {
    set j [lsearch $l [lindex $x 0]]
    if {[lindex $x 1] == "ASC"} {
        set a [lsort -index $j $a]
    } else {
        set a [lsort -decreasing -index $j $a]
    }
}

foreach {y} $a {puts $y}