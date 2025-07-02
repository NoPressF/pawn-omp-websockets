#include <sdk.hpp>
#include <Server/Components/Pawn/pawn.hpp>
#include <Server/Components/Pawn/Impl/pawn_natives.hpp>
#include "client-manager.hpp"
#include "web-sockets.hpp"

SCRIPT_API(CreateWSClient, int(const std::string& connectName, const std::string& failName, const std::string& disconnectName, const std::string& messageName))
{
	try
	{
		auto& manager = WebSocketClientManager::getInstance();
		int id = manager.create(connectName, failName, disconnectName, messageName);

		if (id != -1)
			manager.getClient(id)->setID(id);

		return id;
	}
	catch (...)
	{
		return 0;
	}
}

SCRIPT_API(DestroyWSClient, int(int id))
{
	try
	{
		return WebSocketClientManager::getInstance().destroy(id);
	}
	catch (...)
	{
		return 0;
	}
}

SCRIPT_API(WSClientConnect, int(int id, const std::string& ip))
{
	try
	{
		return WebSocketClientManager::getInstance().getClient(id)->connect(ip);
	}
	catch (...)
	{
		return 0;
	}
}

SCRIPT_API(WSClientDisconnect, int(int id))
{
	try
	{
		return WebSocketClientManager::getInstance().getClient(id)->disconnect();
	}
	catch (...)
	{
		return 0;
	}
}

SCRIPT_API(WSClientIsConnected, int(int id))
{
	try
	{
		return WebSocketClientManager::getInstance().getClient(id)->isConnected();
	}
	catch (...)
	{
		return 0;
	}
}

SCRIPT_API(WSClientSend, int(int id, const std::string& text))
{
	try
	{
		WebSocketClientManager::getInstance().getClient(id)->send(text);
		return 1;
	}
	catch (...)
	{
		return 0;
	}
}