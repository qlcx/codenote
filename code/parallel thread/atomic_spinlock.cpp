//原子操作(不可以拷贝构造和赋值)--自旋锁的实现
//std::atomic_flag(布尔标志两种状态1.设置; 2.清除)对象类型必须且只能用ATOMIC_FLAG_INIT(清除状态)
//成员函数：1、析构：销毁
//			2、clear：清除(存储操作)
//			3、test_and_set：设置(读-修改-写操作)
//std：：memory_order_acquire、std::memory_order_release等为内存操作顺序参数
class spinlock_mutex
{
	std::atomic_flag flag;
public:
	spinlock_mutex():flag(ATOMIC_FLAG_INIT) {}
	void lock()
	{
		
		while(flag.test_and_set(std::memory_order_acquire));
	}
	void unlock()
	{
		flag.clear(std::memory_order_release);
	}
};