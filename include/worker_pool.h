#pragma once

#include <future>
#include <deque>

class WorkerPool {
public:

	WorkerPool(int numberOfWorkers);
	WorkerPool(const WorkerPool& w) = delete;
	~WorkerPool();

	template<class F, class R = std::result_of_t<F&()>>
	std::future<R> addTask(F&& func) {
		std::packaged_task<void(void)> task(std::forward<F>(func));
		auto result = task.get_future();
		{
			std::unique_lock<std::mutex> lockGuard(this->taskQueueLock);
			this->tasks.emplace_back(std::move(task));
		}
		this->tasksAreAvailableSignal.notify_one();
		return result;
	}

	void startWorkers(int numberOfWorkers);
	void stopWorkers();

private:

	std::mutex taskQueueLock;
	std::condition_variable tasksAreAvailableSignal;
	std::deque<std::packaged_task<void()>> tasks;
	std::vector<std::future<void>> workers;

	void doWork();
};