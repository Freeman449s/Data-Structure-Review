//
// Created by Freeman on 2021/6/17.
//

#ifndef DATA_STRUCTURE_REVIEW_CALCULATOR_HPP
#define DATA_STRUCTURE_REVIEW_CALCULATOR_HPP

#include <vector>
#include <stack>
#include "../Exceptions.hpp"

namespace Chapter3 {
    /**
     * 问题：字符向量infix中保存了中缀式形式的算式，现要求编写程序计算此算式。
     * 算式中只包括个位数字，符号只包括+、-、*、/和括号，除法使用整除。
     */
    class Calculator {
    public:
        std::vector<char> infix;
        std::vector<char> postfix;

    public:
        /**
         * 中缀转后缀。
         * 运算方法：遇到数字直接加入后缀表达式；遇到符号则弹出栈中优先级更高或同级的符号，然后将此符号入栈。
         * 特别地，前括号在压栈前具有最高优先级，压栈后具有最低优先级，只有遇到后括号时才能弹出。
         */
        std::vector<char> infixToPostfix() {
            int i = 0;
            std::stack<char> s;
            while (i < infix.size()) {
                char ch = infix[i];
                i++;
                if (isDigit(ch)) {
                    postfix.push_back(ch);
                }
                else { // 运算符
                    if (ch == '(') s.push(ch);
                    else if (ch == '+' || ch == '-') {
                        // +、-、*、/均弹出
                        while (!s.empty() && (s.top() == '+' || s.top() == '-' || s.top() == '*' || s.top() == '/')) {
                            postfix.push_back(s.top());
                            s.pop();
                        }
                        // 遇到括号或栈为空
                        s.push(ch);
                    }
                    else if (ch == '*' || ch == '/') {
                        // 弹出*、/
                        while (!s.empty() && (s.top() == '*' || s.top() == '/')) {
                            postfix.push_back(s.top());
                            s.pop();
                        }
                        s.push(ch);
                    }
                    else if (ch == ')') {
                        while (s.top() != '(') {
                            postfix.push_back(s.top());
                            s.pop();
                        }
                        s.pop(); // 弹出前括号
                    }
                }
            }
            while (!s.empty()) {
                postfix.push_back(s.top()); // 弹出剩余操作符
                s.pop();
            }
            return postfix;
        }

        /**
         * 后缀表达式运算。
         * 运算方法：遇到数字压栈；遇到符号时，弹出栈顶数字作为右操作数，次栈顶数字作为左操作数（左操作数先入栈，后出栈），运算后压栈。
         * 扫描完后缀表达式后，栈中应只剩下一个元素，该元素就是运算结果。
         * @return 运算结果
         */
        double calculate() {
            std::stack<double> s;
            int i = 0;
            while (i < postfix.size()) {
                char ch = postfix[i];
                i++;
                if (isDigit(ch)) s.push(ch - '0');
                else {
                    double b = s.top();
                    s.pop();
                    double a = s.top();
                    s.pop();
                    s.push(op(a, ch, b));
                }
            }
            return s.top();
        }

    private:
        static bool isDigit(char ch) {
            return ch >= '0' && ch <= '9';
        }

        static double op(double a, char op, double b) {
            if (op == '+') return a + b;
            else if (op == '-') return a - b;
            else if (op == '*') return a * b;
            else {
                if (b != 0) return a / b;
                else throw DivisionByZeroException();
            }
        }
    };
}

#endif //DATA_STRUCTURE_REVIEW_CALCULATOR_HPP
