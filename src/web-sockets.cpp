#include <Server/Components/Pawn/Impl/pawn_natives.hpp>
#include <Server/Components/Pawn/Impl/pawn_impl.hpp>
#include "task-sync.hpp"
#include "web-sockets.hpp"

StringView WebSocketsComponent::componentName() const	
{
	return "WebSockets";
}

SemanticVersion WebSocketsComponent::componentVersion() const
{
	return SemanticVersion(1, 0, 0, 0);
}

void WebSocketsComponent::onLoad(ICore* c)
{
	core_ = c;
	core_->getEventDispatcher().addEventHandler(this);
	setAmxLookups(core_);
}

void WebSocketsComponent::onInit(IComponentList* components)
{
	pawn_ = components->queryComponent<IPawnComponent>();

	if (pawn_)
	{
		setAmxFunctions(pawn_->getAmxFunctions());
		setAmxLookups(components);
		pawn_->getEventDispatcher().addEventHandler(this);
	}
}

void WebSocketsComponent::onReady()
{
	
}

void WebSocketsComponent::onFree(IComponent* component)
{
	if (component == pawn_)
	{
		pawn_ = nullptr;
		setAmxFunctions();
		setAmxLookups();
	}
}

void WebSocketsComponent::free()
{
	delete this;
}

void WebSocketsComponent::reset()
{
	
}

void WebSocketsComponent::onAmxLoad(IPawnScript& script)
{
	script_ = &script;
	pawn_natives::AmxLoad(script.GetAMX());
}

void WebSocketsComponent::onAmxUnload(IPawnScript& script)
{
	WebSocketClientManager::getInstance().destroyAll();
}

void WebSocketsComponent::onTick(Microseconds elapsed, TimePoint now)
{
	TaskSync::getInstance().executeAllAndClear();
}

WebSocketsComponent* WebSocketsComponent::getInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new WebSocketsComponent();
	}
	return instance_;
}

IPawnScript* WebSocketsComponent::getScript() const
{
	return script_;
}

ICore* WebSocketsComponent::getCore() const
{
	return core_;
}

WebSocketsComponent::~WebSocketsComponent()
{
	if (pawn_)
	{
		pawn_->getEventDispatcher().removeEventHandler(this);
	}
}