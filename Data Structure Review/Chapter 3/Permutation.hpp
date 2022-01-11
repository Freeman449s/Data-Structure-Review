//
// Created by Freeman on 2021/8/17.
//

#ifndef DATA_STRUCTURE_REVIEW_PERMUTATION_HPP
#define DATA_STRUCTURE_REVIEW_PERMUTATION_HPP

#include <set>
#include <string>

namespace Chapter3 {
    /**
     * 问题：使用递归算法求n个不同字符的所有全排序列
     */
    class Permutation {
    public:
        /**
         * 算法1：使用partialSequence表示由部分已参与排序的字符形成的序列，charset存储尚未参与排序的字符。
         * 每次从charset中取出一个字符，拼接到partialSequence之后，然后递归地调用recurPermutation1函数。
         * 慎用STL：使用STL，可能导致时间和空间上的效率降低，并且可能因为记错API导致错误。
         * 函数的正确性已经得到验证。
         */
        static void algorithm1(char chars[], int n) {
            std::set<char> charset;
            for (int i = 0; i <= n - 1; i++) {
                charset.insert(chars[i]);
            }
            recurPermutation1(charset, "");
        }

    private:
        static void recurPermutation1(std::set<char> charset, std::string partialSequence) {
            auto ite = charset.begin();
            if (charset.size() == 1) { // 递归出口
                partialSequence += *ite;
                std::cout << partialSequence << std::endl;
                return;
            }

            for (; ite != charset.end(); ite++) {
                std::set<char> charsetCopy = charset;
                charsetCopy.erase(*ite);
                recurPermutation1(charsetCopy, partialSequence + *ite);
            }
        }

    public:
        /**
         * 算法2：定义recurPermutation2(chars,k,n)函数，可以枚举出chars[0~k]的全部排序序列。
         * 将chars[0~k]范围内的字符逐个与chars[k]交换，此时chars[k]有k种可能性；但在任一分支中，chars[k]都已被确定。
         * 递归地调用recurPermutation2(chars,k-1,n)，得到chars[0~k-1]的全部排序序列。
         * 函数的正确性已经得到验证。
         */
        static void algorithm2(char chars[], int n) {
            recurPermutation2(chars, n - 1, n);
        }

    private:
        static void recurPermutation2(char str[], int k, int n) {
            if (k == 0) { // 递归出口：只需枚举str[0~0]的排序序列
                for (int i = 0; i <= n - 1; i++) {
                    std::cout << str[i];
                }
                std::cout << std::endl;
            }

            for (int i = 0; i <= k; i++) {
                // str[i]与str[k]交换
                char tmp = str[i];
                str[i] = str[k];
                str[k] = tmp;

                recurPermutation2(str, k - 1, n);

                // 恢复原始次序
                tmp = str[i];
                str[i] = str[k];
                str[k] = tmp;
            }
        }
    };
}

#endif //DATA_STRUCTURE_REVIEW_PERMUTATION_HPP
