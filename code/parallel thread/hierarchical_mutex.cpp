class hierarchical_mutex
{
	std::mutex internal_mutex;
	unsigned long const hierarchy_value;
	unsigned long const previous_hierarchy_value;
	//thread_local关键字，表明它是线程局部的，在线程结束的时候也会被销毁
	static thread_local unsigned long this_thread_hierarchy_value;
	
	//检查线程是否符合层次
	void check_for_hierarchy_violation()
	{
		if(this_thread_hierarchy_value <= hierarchy_value)
		{
			throw std::logic_error("mutex hierarchy violated");
		}
	}
	//更新线程层次
	void update_hierarchy_value()
	{
		previous_hierarchy_value = this_thread_hierarchy_value;
		this_thread_hierarchy_value = hierarchy_value;
	}
public:
	explicit hierarchical_mutex(unsigned long value) : hierarchy_value(value), previous_hierarchy_value(0) { }
	
	void lock()
	{
		check_for_hierarchy_violation();
		internal_mutex.lock();
		update_hierarchy_value();
	}
	void unlock()
	{
		this_thread_hierarchy_value = previous_hierarchy_value;
		internal_mutex.unlock();
	}
	//判断互斥锁是否已经被其他线程持有
	bool try_lock()
	{
		check_for_hierarchy_violation();
		if(!internal_mutex.try_lock())
			return false;
		update_hierarchy_value();
		return true;
	}
};
//初始化为最大值，使之在开始时任意互斥元都能被锁定
thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value(MAX_VALUE);	
