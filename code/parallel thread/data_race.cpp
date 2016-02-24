//�ڳ�ʼ����ʱ�򱣻���������

//���μ������(����if(!resource_ptr))  ���ײ������Ծ�������
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

//ʹ��std::once_flag��std::call_once���Ա�����Щ����

//ʹ��call_once���ӳٳ�ʼ��(���������ڳ�ʼ��)
//call_once:��֤����̶߳Ըú���ֻ����һ��
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