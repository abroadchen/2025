package class1;

/// num & (1 << i)：按位AND运算，检查num的第i位是否为1
/// 将整数以二进制形式输出
public class Code1_PrintBinary {
    public static void print(int num) {
        //从最高位(第31位)到最低位(第0位)遍历每一位
        for (int i = 31; i >= 0; --i) {
            //将num与只有第i位为1的掩码进行AND运算
            //如果结果为0，说明第i位是0；否则第i位是1
            System.out.print((num&(1<<i)) == 0 ? '0' : '1');
        }
        System.out.println();
    }
}
