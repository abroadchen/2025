package primary.class2;

/**
 * Created by June on 2026/4/1 ...
 */
public class Code2_RandToRand {

    ///生成 1 到 5 的均匀随机整数（包含1和5）
    ///每个数字出现概率都是 1/5
    public static int f() {
        return (int)(Math.random()*5)+1;
    }
    ///如果结果是 1 或 2，返回 0 P(返回0) = P(得到1或2) = 1/4 + 1/4 = 1/2
    ///如果结果是 4 或 5，返回 1 P(返回1) = P(得到4或5) = 1/4 + 1/4 = 1/2
    public static int a() {
        int ans = 0;
        do {
            ans = f();
        } while (ans == 3);
        return ans < 3 ? 0 : 1;
    }
    ///用三个等概率的0或1位组合成一个0-7的数，然后排除7
    ///a()<<2：将 a() 结果左移2位（相当于乘以4）
    ///a()<<1：将 a() 结果左移1位（相当于乘以2）
    ///保持原值
    public static int b() {
        int ans = 0;
        do {
            ans = (a()<<2) + (a()<<1) + a();
        } while (ans == 7);
        return ans;
    }
    public static int c() {
        return b()+1;
    }

    public static class RandomBox {
        private final int mn, mx;
        public RandomBox(int mn, int mx) {
            this.mn = mn;
            this.mx = mx;
        }
        public int random() {
            return mn + (int)(Math.random()*(mx - mn + 1));
        }
        public int mn() { return mn; }
        public int mx() { return mx; }
    }
    ///将任意范围的随机数转换为等概率的0或1
    ///如果范围大小是奇数，排除中间值以保证0和1的概率相等
    ///如果结果小于中点，返回0；否则返回1
    public static int rd01(RandomBox randomBox) {
        int mn = randomBox.mn(), mx = randomBox.mx(), sz = mx - mn + 1;
        boolean od = (sz&1) != 0;
        int mid = sz/2, ans = 0;
        do {
            ans = randomBox.random()-mn;
        } while (od && ans == mid);
        return ans < mid ? 0 : 1;
    }

    /**
     计算需要的二进制位数（num）
     生成 num 个随机的 0 或 1 位
     组合成一个整数
     如果超出范围则重新生成
     加上偏移量 fr 得到最终结果
     */
    public static int random(RandomBox randomBox, int fr, int to) {
        if (fr == to) return fr;
        int range = to - fr, num = 1;
        while ((1<<num)-1 < range) num++;
        int ans = 0;
        do {
            ans = 0;
            for (int i = 0; i < num; ++i)
                ans |= rd01(randomBox)<<i;
        } while (ans > range);
        return ans + fr;
    }

    public static void main(String[] args) {

    }
}
