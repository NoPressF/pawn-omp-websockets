#pragma once

#include "constructor.hpp"
#include <queue>
#include <mutex>
#include <functional>

class TaskSync
{
	typedef std::function<void()> Task;
	typedef std::queue<Task> TaskQueue;

public:
	DISABLE_CPY_MOV_CTOR(TaskSync)

	static TaskSync& getInstance();

	void operator+=(Task task);
	void executeAllAndClear();

private:
	TaskQueue m_queue;
	std::mutex m_mutex;

	explicit TaskSync();
};