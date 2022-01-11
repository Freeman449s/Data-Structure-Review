//
// Created by Freeman on 2021/8/28.
//

#ifndef DATA_STRUCTURE_REVIEW_DEL_CHAR_HPP
#define DATA_STRUCTURE_REVIEW_DEL_CHAR_HPP

namespace Chapter4 {
    /**
     * 问题：设计一个算法，从字符数组中删除给定的字符。
     * 方法：将相邻两个匹配字符间的字符向前移动i位，其中i是目前已发现的匹配字符数。
     * 该方法的时间复杂度为O(N).
     * 函数已经过测试。
     */
    class DelChar {
    public:
        static void solve(char str[], char ch) {
            int chCount = 0, i, j;
            for (i = 0; str[i] != '\0';) { // str[i] == '\0'对应不存在ch的情况
                if (str[i] == ch) {
                    chCount += 1;
                    for (j = i + 1 - chCount; str[j + chCount] != '\0'; j++) { // 字符前移
                        if (str[j + chCount] == ch) { // 到达下一个ch
                            i = j + chCount; // i直接跳转至下一个ch处
                            break;
                        }
                        str[j] = str[j + chCount];
                    }
                    if (str[j + chCount] == '\0') { // 到达字符串末尾，函数退出
                        str[j] = '\0';
                        break;
                    }
                }
                else i += 1; // str[i] == ch情况下，i的更新由内层循环完成
            }
        }
    };
}

#endif //DATA_STRUCTURE_REVIEW_DEL_CHAR_HPP
