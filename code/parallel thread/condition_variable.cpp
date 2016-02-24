#include <queue>
#include <mutex>
#include <condition_variable>

/*
std::condtion_variable::notify_one
std::condtion_variable::wait(unique_lock<std::mutex>, 谓语(lambda));	
*/
//wait => 等待notify_one通知激活，根据lambda返回值判断，不满足则解锁互斥元，并阻塞或等待线程再次通知

template<typename T>
class threadsafe_queue
{
private:
	std::mutex mut;
	std::queue<T> data_queue;
	std::condtion_variable data_cond;
public:
	void push(T new_value)
	{
		std::lock_guard<std::mutex> lk(mut);
		data_queue.push(new_value);
		data_cond.notify_one();
	}
	
	void wait_and_pop(T& value)
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this]{return !data_queue.empty();});
		value = data_queue.front();
		data_queue.pop();
	}
};

threadsafe_queue<data_chunk> data_queue;

void data_preparation_thread()
{
	while(more_data_to_prepare())
	{
		data_chunk const data = prepare_data();
		data_queue.push(data);
	}
}

void data_processing_thread()
{
	while(true)
	{
		data_chunk data;
		data_queue.wait_and_pop(data);
		process(data);
		if(is_last_chunk(data))
			break;
	}
}