#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__

#include <iostream>
#include <string>
#include <utility>

/**
 * 自定义异常基类
 */
class MyException : public std::exception {
protected:
    std::string message;

public:
    explicit MyException(std::string message) { // explicit关键字防止隐式转换
        this->message = std::move(message);
    }

    MyException() {
        this->message = "";
    }
};

/**
 * 非法参数异常
 */
class IllegalArgumentException : public MyException {
public:
    explicit IllegalArgumentException(std::string message) : MyException(std::move(message)) {
    }

    IllegalArgumentException() : MyException() {
    }
};

/**
 * 索引越界异常
 */
class IndexOutOfRangeException : public MyException {
public:
    explicit IndexOutOfRangeException(std::string message) : MyException(std::move(message)) {

    }

    IndexOutOfRangeException() : MyException() {

    }
};

/**
 * 内存耗尽错误
 */
class OutOfMemoryError : public MyException {
public:
    explicit OutOfMemoryError(std::string message) : MyException(std::move(message)) {

    }

    OutOfMemoryError() : MyException() {

    }
};

/**
 * 除零异常
 */
class DivisionByZeroException : public MyException {
public:
    explicit DivisionByZeroException(std::string message) : MyException(std::move(message)) {

    }

    DivisionByZeroException() : MyException() {

    }
};

/**
 * 空栈异常（栈为空时试图弹出栈顶元素）
 */
class EmptyStackException : public MyException {
public:
    explicit EmptyStackException(std::string message) : MyException(std::move(message)) {

    }

    EmptyStackException() : MyException() {

    }
};

/**
 * 非法状态异常，可能在以下情况抛出：
 * 试图向已满队列插入元素
 */
class IllegalStateException : public MyException {
public:
    explicit IllegalStateException(std::string message) : MyException(std::move(message)) {

    }

    IllegalStateException() : MyException() {

    }
};

/**
 * 空队列异常（队列为空时试图取出队头元素）
 */
class EmptyQueueException : public MyException {
public:
    explicit EmptyQueueException(std::string message) : MyException(std::move(message)) {

    }

    EmptyQueueException() : MyException() {

    }
};

/**
 * 非法操作异常
 */
class IllegalOperationException : public MyException {
public:
    explicit IllegalOperationException(std::string message) : MyException(std::move(message)) {

    }

    IllegalOperationException() : MyException() {

    }
};

#endif // !__EXCEPTIONS_HPP__