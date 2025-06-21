/*
 * @Author: Psy.C abroadchen@163.com
 * @Date: 2024-10-27 20:56:26
 * @LastEditors: Psy.C abroadchen@163.com
 * @LastEditTime: 2024-10-27 21:07:58
 * @FilePath: /undefined/Users/chen/Documents/NameMatcher.java
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
public class NameMatcher {

    public static boolean containsName(String[] names, String targetName) {
        return Arrays.stream(names).anyMatch(name -> name.equals(targetName));
    }   
}