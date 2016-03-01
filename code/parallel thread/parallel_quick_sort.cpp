//functional programming函数式编程
//future并行快速排序
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
	//partition(beg, end, unarypred)使用unarypred划分序列，满足的放在序列开始，不满足的放在序列尾部
	//返回一个指向迭代器  指向最后一个满足unarypred元素之后的位置
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
//得到以Arg为参数列表的Fn可调用函数的返回类型
template<typename F, typename A>
std::future<std::result_of<F(A&&)>::type>
	spawn_task(F&& f, A&& a)
{
	typedef std::result_of<F(A&&)>::type result_type;
	//std::packaged_task<>将一个future绑定到一个函数或可调用对象
	//当std::packaged_task<>对象被调用时，它就调用相关的函数或可调用对象(使用get_future成员函数)
	std::packaged_task<result_type(A&&)> task(std::move(f));
	std::future<result_type> res(task.get_future());
	std::thread t(std::move(task), std::move(a));
	t.detach();
	return res;
}