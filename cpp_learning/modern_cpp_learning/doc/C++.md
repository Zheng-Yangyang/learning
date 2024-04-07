#### 1.被弃用的特性

**不再允许字符串字面值常量赋值给一个 `char *`。如果需要用字符串字面值常量赋值和初始化一个 `char *`，应该使用 `const char *` 或者 `auto`。**

```cpp
#include<iostream>
int main()
{
    char *str = "hello world";
    std::cout << str << std::endl;
}
```

会报下面的`warning`

```shell
1.cpp:4:17: warning: ISO C++11 does not allow conversion from string literal to 'char *' [-Wwritable-strings]
    char *str = "hello world";
                ^
1 warning generated.
```

