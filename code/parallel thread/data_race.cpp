//在初始化的时候保护共享数据

//二次检查锁定(两次if(!resource_ptr))  容易产生恶性竞争条件
/*
//double_cheched_locking
std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;
void undefined_behaviour_with_double_checked_locking()
{
	if(!resource_ptr)
	{
		std::lock_guard<std::mutex> lk(resource_mutex);
		if(!resource_ptr)
		{
			resource_ptr.reset(new some_resource);
		}
	}
	resource_ptr->do_something();
}
*/

//使用std::once_flag和std::call_once可以避免这些问题

//使用call_once的延迟初始化(保护仅用于初始化)
//call_once:保证多个线程对该函数只调用一次
std::thread_ptr<some_resource> resource_ptr;
std::once_flag resource_flag;
void init_resource()
{
	resource_ptr.reset(new some_resource);
}
void foo()
{
	std::call_once(resource_flag, init_resource);
	resource_ptr->do_something();
}