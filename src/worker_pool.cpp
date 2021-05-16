#include "worker_pool.h"

WorkerPool::WorkerPool(int numberOfWorkers) {
	this->startWorkers(numberOfWorkers);
}

void WorkerPool::startWorkers(int numberOfWorkers) {
	for (int i = 0; i < numberOfWorkers; ++i) {
		auto work_loop = [this] { this->doWork(); };
		this->workers.push_back(std::async(std::launch::async, work_loop));
	}
}

void WorkerPool::stopWorkers() {
	{
		std::unique_lock<std::mutex> lockGuard(this->taskQueueLock);
		for (auto&& worker : this->workers) {
			this->tasks.push_back({});
		}
	}
	tasksAreAvailableSignal.notify_all();
	this->workers.clear();
}

WorkerPool::~WorkerPool() {
	this->stopWorkers();
}

void WorkerPool::doWork() {
	std::packaged_task<void()> task;
	do {
		std::unique_lock<std::mutex> lockGuard(this->taskQueueLock);
		if (this->tasks.empty()) {
			tasksAreAvailableSignal.wait(lockGuard, [this] {
				return !this->tasks.empty();
			});
		}
		task = std::move(this->tasks.front());
		tasks.pop_front();
		if (task.valid()) {
			task();
		}
	} while (task.valid());
}