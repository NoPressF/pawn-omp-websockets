#pragma once

#include "client.hpp"
#include "indexed-vector.hpp"
#include "constructor.hpp"
#include <memory>

class WebSocketClientManager
{
	typedef std::shared_ptr<WebSocketClient> WebSocketClientPointer;

public:
	DISABLE_CPY_MOV_CTOR(WebSocketClientManager)

	static WebSocketClientManager& getInstance();

	int create(const std::string& connectNameCallback,
		const std::string& failNameCallback,
		const std::string& disconnectNameCallabck,
		const std::string& messageNameCallback);

	bool destroy(int id);
	void destroyAll();

	WebSocketClientPointer getClient(int id);

private:
	IndexedVector<WebSocketClientPointer> m_clients;

	explicit WebSocketClientManager();
};
