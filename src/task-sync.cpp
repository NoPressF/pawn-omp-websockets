#include "task-sync.hpp"

TaskSync& TaskSync::getInstance()
{
	static TaskSync instance;
	return instance;
}

void TaskSync::operator+=(TaskSync::Task task)
{
	std::lock_guard<std::mutex> lg(m_mutex);
	m_queue.push(task);
}

void TaskSync::executeAllAndClear()
{
	std::lock_guard<std::mutex> lg(m_mutex);
	while (!m_queue.empty())
	{
		m_queue.front()();
		m_queue.pop();
	}
}

TaskSync::TaskSync() { }