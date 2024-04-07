#include <iostream>
#include <variant>
#include <cassert>

int main() {
    // 定义一个能够存储 int、float、std::string 类型的 variant 对象
    std::variant<int, float, std::string> v;

    // 使用构造函数初始化 variant 对象
    std::variant<int, float, std::string> w(3.14f);

    // 赋值 variant 对象
    v = 42;
    assert(std::get<int>(v) == 42); // 检查是否正确赋值

    // 获取 variant 所保有可选项的下标
    std::cout << "Index of v: " << v.index() << std::endl;

    // 使用 valueless_by_exception 检查 variant 是否在非法状态
    std::cout << "Is v valueless by exception? " << std::boolalpha << v.valueless_by_exception() << std::endl;

    // 使用 std::get 读取 variant 的值
    try {
        int i = std::get<int>(v);
        std::cout << "Value of v: " << i << std::endl;
    } catch (const std::bad_variant_access& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    // 使用 std::visit 以 variant 所保有的参数调用提供的函数对象
    std::visit([](auto&& arg) {
        std::cout << "Visited: " << arg << std::endl;
    }, v);

    return 0;
}

