### 对象使用过程中背后调用了哪些方法

```cpp
class Test
{
public:
    Test(int a = 10) : ma(a)
    {
        std::cout << "Test(int)" << std::endl;
    }
    ~Test()
    {
        std::cout << "~Test" << std::endl;
    }
    Test(const Test& t) :ma(t.ma)
    {
        std::cout << "const Test&" << std::endl;
    }
    Test& operator=(const Test& t)
    {
        std::cout << "operator=" << std::endl;
        ma = t.ma;
        return *this;
    }
    
private:
    int ma;
};
int main() {
    Test t1;
    Test t2(t1);
    Test t3 = t1;
    Test t4 = Test(20); //=> Test t4(20);存在对临时对象的优化
    //Test(20) 显示生成临时对象，是没有名字的，所以其生存周期：所在的语句
	//语句结束，临时对象就析构了 
	/*
	C++编译器对于对象构造的优化：用临时对象生成新对象的时候，临时对象
	就不产生了，直接构造新对象就可以了
	*/
    std::cout << std::endl;
    const Test& ref = Test(40);
    return 0;
}
```

接下来看

```cpp
int main()
{
	Test t1;//调用构造函数 
	Test t2(t1);//调用拷贝构造函数 
	Test t3 = t1;//调用拷贝构造函数，因为t3还没有生成 

	Test t4 = Test(20);//和Test t4(20);没有区别的！
	cout << "--------------" << endl;

	//t4.operator=(t2)
	t4 = t2;//调用赋值函数，因为t4原本已存在 


	//Test(30)显式生成临时对象
	//t4原本已存在，所以不是构造，这个临时对象肯定要构造生成的 
	//临时对象生成后，给t4赋值 
	//出语句后，临时对象析构 
	//t4.operator=(const Test &t)
	t4 = Test(30);
	cout << "--------------" << endl;
	return 0;
}
```

```cpp
int main()
{
	Test t1;
	Test t2(t1);
	Test t3 = t1;
	Test t4 = Test(20);
	cout << "--------------" << endl;
	t4 = t2;	
	t4 = Test(30);
	t4 = (Test)30;
	t4 = 30
	cout << "--------------" << endl;

	Test *p = &Test(40);//指针指向临时对象，这个临时对象肯定是要生成的
	//然后p指向这个临时对象的地址
	//出语句后，临时对象析构 
	//此时p指向的是一个已经析构的临时对象，p相当于野指针了 
	
	const Test &ref = Test(50);//引用一个临时对象，这个临时对象也是要生成的
    //出语句后，临时对象不析构，因为引用相当于是别名，临时对象出语句析构是因为没有名字 
	//用引用变量引用临时对象是安全的，临时对象就是有名字了，临时对象的生存周期就变成引用变量的
	//生存周期了。引用变量是这个函数的局部变量，return完，这个临时对象才析构 
	cout << "--------------" << endl;
	return 0;
}
```

```cpp
#include <iostream>
using namespace std;
class Test
{
public:
	//有默认值，可以有2种构造方式：Test()  Test(20)
	Test(int data = 10) :ma(data)
	{
		cout << "Test(int)" << endl;
	}
	~Test()
	{
		cout << "~Test()" << endl;
	}
	Test(const Test& t) :ma(t.ma)
	{
		cout << "Test(const Test&)" << endl;
	}
	void operator=(const Test& t)
	{
		cout << "operator=" << endl;
		ma = t.ma;
	}
	int getData()const { return ma; }
private:
	int ma;
};
Test GetObject(Test t)
{
	int val = t.getData();
	Test tmp(val);
	return tmp;
}
int main()
{
	Test t1;//1、调用带整型参数的构造函数 
	Test t2;//2、调用带整型参数的构造函数
	t2 = GetObject(t1);//函数调用，实参传递给形参，是初始化还是赋值？
	//当然是初始化，对象初始化是调用构造函数，赋值是两个对象都存在 调用左边对象的=重载
	//t1是已经构造好的Test对象，而形参是t是正在定义的Test对象 
	//3、调用Test(const Test&) 拿t1拷贝构造形参t
	//4、调用Test(int)的构造，构造tmp对象 然后return tmp;tmp是不能直接给t2赋值的
	//因为tmp和t2是两个不同函数栈帧上的对象，是不能直接进行赋值的 GetObject函数完成调用时
	//tmp对象作为局部对象就析构了 ，为了把返回值带出来， 在return tmp;这里，首先要在main函数栈帧
	//上构建一个临时对象，目的就是把tmp对象带出来， 
	//5、调用 Test(const Test&)，tmp拷贝构造main函数栈帧上的临时对象
	//6、出 GetObject作用域，tmp析构
	//7、形参t对象析构
	//8、operator =，把main函数刚才构建的临时对象赋值给t2，临时对象没名字，出了语句就要析构 
	//9、把main函数刚才构建的临时对象析构 
	//10、main函数结束，t2析构
	//11、t1析构 

	return 0;
}

```

