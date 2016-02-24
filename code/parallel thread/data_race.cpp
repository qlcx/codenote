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
