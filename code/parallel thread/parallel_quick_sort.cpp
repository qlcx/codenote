//functional programming����ʽ���
//future���п�������
template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
	if(input.empty())
	{
		return input;
	}
	std::list<T> result;
	result.splice(result.begin(), input, input.begin());
	T const& pivot = *result.begin();
	//partition(beg, end, unarypred)ʹ��unarypred�������У�����ķ������п�ʼ��������ķ�������β��
	//����һ��ָ�������  ָ�����һ������unarypredԪ��֮���λ��
	auto divide_point = std::partition(input.begin(), input.end(),
										[&](T const& t){return t < pivot;});
	std::list<T> lower_part;
	lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
	std::future<std::list<T> > new_lower(
		spawn_task(&parallel_quick_sort<T>, std::move(lower_part)));
	auto new_higher(parallel_quick_sort(std::move(input)));
	result.splice(result.end(), new_higher);
	result.splice(result.begin(), new_lower.get());
	return result;
}

//template <class Fn, class... ArgTypes> struct result_of<Fn(ArgTypes...)>;
//�õ���ArgΪ�����б��Fn�ɵ��ú����ķ�������
template<typename F, typename A>
std::future<std::result_of<F(A&&)>::type>
	spawn_task(F&& f, A&& a)
{
	typedef std::result_of<F(A&&)>::type result_type;
	//std::packaged_task<>��һ��future�󶨵�һ��������ɵ��ö���
	//��std::packaged_task<>���󱻵���ʱ�����͵�����صĺ�����ɵ��ö���(ʹ��get_future��Ա����)
	std::packaged_task<result_type(A&&)> task(std::move(f));
	std::future<result_type> res(task.get_future());
	std::thread t(std::move(task), std::move(a));
	t.detach();
	return res;
}