/*
Package src

	@author: June
	@since: 2026/8/26
	@desc:

- bufio ：带缓冲的IO，用于高效读取输入。
- fmt ：格式化输入输出，用于 Fscan 读入和 Print 输出。
- os ：操作系统接口，用于访问标准输入 os.Stdin 。
- sort ：排序库，用于对切片进行升序排序
- k ：字符串组的数量（每组包含 k 个字符串）。
- n ：每个字符串的长度（所有字符串等长）。
- v ：当前字符串的价值。
- mx ：回文串配对后剩余的最大单串价值（用于最后补充）。
- ans ：累计的最大价值总和

- o: ：定义一个标签 o （original），用于 continue o 跳转到外层循环（Go特有的带标签循环跳转）。
- for fmt.Fscan(in, &k, &n); k > 0; k-- ：
- 读取每组的 k （字符串数量）和 n （字符串长度）。
- 循环条件： k > 0 （还有字符串未处理）。
- 每次迭代 k-- （处理一个字符串后减少计数）

- 遍历字符串的前半部分与后半部分对应位置比较。
- 若 任何一对字符不相等 （非回文）：
- 将字符串加入 np （非回文集合）， 价值取负 （用于后续配对时计算差值）。
- continue o ：跳转到外层循环的下一个字符串。
- 若 所有对应位置都相等 （回文）：
- 循环结束后执行 p[s] = append(p[s], v) ，将字符串加入 p （回文集合），价值为原值

遍历每个非回文串
- for s, a := range np ：遍历 np 中的每个键值对， s 为原字符串， a 为其价值列表（已取负）。 生成反转字符串
- t := []byte(s) ：将字符串 s 转换为字节切片，便于修改。
- 反转循环 ：
- - 交换字节切片的前后对应位置，实现字符串反转。
- rev := string(t) ：将反转后的字节切片转换回字符串。
- b := np[rev] ：获取反转字符串 rev 的价值列表（已取负）
- sort.Ints(a) ：对原字符串的价值列表 a 升序排序。
- sort.Ints(b) ：对反转字符串的价值列表 b 升序排序
配对循环
- - 遍历两个列表，每次取一对价值（第 i 小的原串和第 i 小的反转串）。
- 条件： a[i] + b[i] < 0 （配对后的总价值为负，因为两者都取了负，所以负负得正，实际是正价值）。
- ans -= a[i] + b[i] ：由于 a 和 b 的元素都是负数，减去它们的和等于加上它们绝对值的和。
- delete(np, rev) ：删除已处理的反转字符串，避免重复处理
遍历每个回文串
- for _, a := range p ：遍历 p 中的每个价值列表（键为字符串， _ 省略）。 排序与配对
- sort.Ints(a) ：对价值列表 a 升序排序。
- i := len(a) - 1 ：从列表末尾（最大值）开始遍历。
- 配对循环 ：
- - 条件： i > 0 （还有配对的可能）且 a[i] + a[i-1] > 0 （当前两配对价值为正）。
  - ans += a[i] + a[i-1] ：将配对的正价值加入总和。
  - if -a[i-1] > mx ：记录配对中较小价值的负数（用于最后若剩余一个时补充）。
  - i -= 2 ：跳过已配对的两个元素。 处理剩余单个元素

- if i >= 0 && a[i] > mx ：若最后剩余一个元素（配对循环终止后 i >= 0 ），且其价值大于当前 mx ，则更新 mx 。
  - mx 存储所有回文串中，剩余单个元素的最大价值（或配对中较小价值的负数）

- ans + mx ：最终答案 = 已配对的价值总和 + 最大的剩余单个元素价值。
- 为什么加 mx ？因为回文串中可能有无法配对的单个元素，需补充其最大价值。
- fmt.Print ：输出结果，不带换行
*/
package src

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func main() {
	//创建带缓冲的读取器，从标准输入读取数据
	in := bufio.NewReader(os.Stdin)
	var k, n, v, mx, ans int
	//存储当前读取的字符串
	var s string
	//非回文串集合 ，键为原字符串，值为该字符串的所有价值列表
	np := map[string][]int{}
	//回文串集合 ，键为字符串，值为该字符串的所有价值列表
	p := map[string][]int{}
o:
	for fmt.Fscan(in, &k, &n); k > 0; k-- {
		//读取当前字符串 s 及其价值 v
		fmt.Fscan(in, &s, &v)
		for i := 0; i < n/2; i++ {
			if s[i] != s[n-1-i] {
				np[s] = append(np[s], -v)
				continue o
			}
		}
		p[s] = append(p[s], v)
	}
	for s, a := range np {
		t := []byte(s)
		for i := 0; i < n/2; i++ {
			t[i], t[n-1-i] = t[n-1-i], t[i]
		}
		rev := string(t)
		b := np[rev]
		sort.Ints(a)
		sort.Ints(b)
		for i := 0; i < len(a) && i < len(b) && a[i]+b[i] < 0; i++ {
			ans -= a[i] + b[i]
		}
		delete(np, rev)
	}
	for _, a := range p {
		sort.Ints(a)
		i := len(a) - 1
		for ; i > 0 && a[i]+a[i-1] > 0; i -= 2 {
			ans += a[i] + a[i-1]
			if -a[i-1] > mx {
				mx = -a[i-1]
			}
		}
		if i >= 0 && a[i] > mx {
			mx = a[i]
		}
	}
	fmt.Print(ans + mx)
}
