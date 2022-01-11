//
// Created by Freeman on 2021/8/20.
//

#ifndef DATA_STRUCTURE_REVIEW_KMP_HPP
#define DATA_STRUCTURE_REVIEW_KMP_HPP

#include <string>
#include <vector>

namespace Chapter4 {
    /**
     * Knuth-Morris-Pratt模式匹配算法。
     * 算法引入了最长匹配前后缀的概念，即一个字符串各相等前后缀中最长的一对。
     * 若主串和模式的某个字符失配，此时模式的一部分已经与主串的一部分匹配，将模式向后移动，直到模式中已匹配部分的最长匹配前缀，与主串中相应的最长匹配后缀重合。
     * 此时主串中的指针不必回溯，保证了只需遍历主串一遍算法即可终止。
     * 时间复杂度：O(M+N)。求nextval：O(M)；模式匹配：O(N)。
     * 代码已通过测试。
     */
    class KMP {
    public:
        /**
         * 查找主串str中，第一个与模式pattern匹配的子串的位置。
         * @param str 主串
         * @param pattern 模式
         * @return 主串str中，第一个与模式pattern匹配的子串的位置。不存在匹配子串时返回-1。
         */
        static int find(const std::string &str, const std::string &pattern) {
            int i = 0, j = 0;
            std::vector<int> next = getNext(pattern);
            std::vector<int> nextval = getNextval(pattern, next);
            while (i < str.size() && j + 1 < pattern.size() + 1) { // string.size()为无符号类型；j可能取-1，将j加1保证运算结果正确
                if (j == -1 || str.at(i) == pattern.at(j)) { // str[i]==pattern[j]，继续向下匹配；或为特殊情况：j==-1，i和j都需后移
                    i += 1;
                    j += 1;
                }
                else { // 发生不匹配，j回溯
                    j = nextval[j + 1] - 1; // nextval从1开始保存数据，取nextval值需要经过两次变换
                }
            }
            if (j >= pattern.size()) return i - pattern.size();
            else return -1;
        }

    private:
        static std::vector<int> getNext(const std::string &pattern) {
            std::vector<int> next(pattern.size() + 1);
            int j = 1, t = 0; // 为方便实现，next从1开始存储数据
            next[1] = 0; // next[1]始终为0
            while (j < pattern.size()) {
                /**
                 *  比较p[j]与p[t]是否相等；或为特殊情况：t已回溯到0. 任何一种情况下，都令p[j+1]=t+1.
                 *  t的初值为next[j]，可能随着迭代回溯到next[next[j]]，next[next[next[j]]]等，直到0.
                 */
                if (t == 0 || pattern.at(j - 1) == pattern.at(t - 1)) { // pattern从0开始存储，需要减1完成对齐
                    j += 1;
                    t += 1;
                    next[j] = t;
                }
                else {
                    t = next[t];
                }
            }
            return next;
        }

        static std::vector<int> getNextval(const std::string &pattern, const std::vector<int> &next) {
            std::vector<int> nextval(next.size());
            nextval[1] = 0;
            for (int i = 2; i <= pattern.size(); i++) { // nextval.size() == pattern.size() + 1
                if (pattern.at(i - 1) != pattern.at(next[i] - 1)) nextval[i] = next[i];
                else nextval[i] = nextval[next[i]];
            }
            return nextval;
        }
    };
}

#endif //DATA_STRUCTURE_REVIEW_KMP_HPP
