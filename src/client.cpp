#include <sdk.hpp>
#include "task-sync.hpp"
#include "web-socket.hpp"
#include "web-sockets.hpp"
#include "client.hpp"

WebSocketClient::WebSocketClient(
	const std::string& connectName, 
	const std::string& failName, 
	const std::string& disconnectName, 
	const std::string& messageName) 
	: m_functionConnectName(connectName),
	m_functionFailName(failName),
	m_functionDisconnectName(disconnectName),
	m_functionMessageName(messageName)
{
	m_client.set_access_channels(websocketpp::log::alevel::none);
	m_client.set_error_channels(websocketpp::log::alevel::none);

	m_client.set_open_handler([&](WebsocketConnection)
		{
			m_connected = true;

			int idx = getID();
			std::string func = m_functionConnectName;
			TaskSync::getInstance() += [idx, func]()
			{
				int funcIDX = 0;
				IPawnScript* script = WebSocketsComponent::getInstance()->getScript();
				
				if (!script->FindPublic(func.c_str(), &funcIDX))
				{
					script->Push(idx);
					script->Exec(NULL, funcIDX);
				}
			};
		});

	m_client.set_fail_handler([&](WebsocketConnection)
		{
			m_connected = false;

			int idx = getID();
			std::string func = m_functionFailName;
			TaskSync::getInstance() += [idx, func]()
			{
				int funcIDX = 0;
				IPawnScript* script = WebSocketsComponent::getInstance()->getScript();
				if (!script->FindPublic(func.c_str(), &funcIDX))
				{
					script->Push(idx);
					script->Exec(NULL, funcIDX);
				}
			};
		});

	m_client.set_close_handler([&](WebsocketConnection)
		{
			m_connected = false;

			int idx = getID();
			std::string func = m_functionDisconnectName;
			TaskSync::getInstance() += [idx, func]()
			{
				int funcIDX = 0;
				IPawnScript* script = WebSocketsComponent::getInstance()->getScript();
				if (!script->FindPublic(func.c_str(), &funcIDX))
				{
					script->Push(idx);
					script->Exec(NULL, funcIDX);
				}
			};
		});

	m_client.set_message_handler([&](WebsocketConnection, WebsocketMessage msg)
		{
			try
			{
				std::string data = msg->get_payload();

				int idx = getID();
				std::string func = m_functionMessageName;
				TaskSync::getInstance() += [idx, func, data]()
				{
					int funcIDX = 0;
					IPawnScript* script = WebSocketsComponent::getInstance()->getScript();
					if (!script->FindPublic(func.c_str(), &funcIDX))
					{
						cell addr = 0;

						script->PushString(&addr, NULL, data.c_str(), false, false);
						script->Push(idx);
						script->Exec(NULL, funcIDX);
						script->Release(addr);
					}
				};
			}
			catch (...)
			{
			}
		});

	m_client.init_asio();
}

WebSocketClient::~WebSocketClient()
{
	disconnect();
}

bool WebSocketClient::connect(const std::string& ip)
{
	if (isConnected())
		return false;

	try
	{
		websocketpp::lib::error_code ec;
		auto ptr = m_client.get_connection(ip, ec);
		if (ec) return false;

		m_connectionPtr = ptr->get_handle();
		m_client.connect(ptr);

		m_asioThread = boost::thread(boost::bind(&WebsocketClient::run, &m_client));
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool WebSocketClient::disconnect()
{
	if (!isConnected())
		return false;

	try
	{
		m_client.close(m_connectionPtr, websocketpp::close::status::normal, "");
		if (m_asioThread.joinable())
			m_asioThread.join();

		m_connected = false;
		return m_client.stopped();
	}
	catch (...)
	{
		return false;
	}
}

bool WebSocketClient::isConnected() const
{
	return m_connected;
}

bool WebSocketClient::send(const std::string& message)
{
	if (!isConnected())
		return false;

	try
	{
		if (m_client.get_con_from_hdl(m_connectionPtr)->send(message, websocketpp::frame::opcode::text))
			return false;

		return true;
	}
	catch (...)
	{
		return false;
	}
}

int WebSocketClient::getID() const
{
	return m_id;
}

void WebSocketClient::setID(int index)
{
	m_id = index;
}