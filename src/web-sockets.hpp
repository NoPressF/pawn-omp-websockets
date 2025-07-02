#pragma once

#include <sdk.hpp>
#include "interface.hpp"
#include "client-manager.hpp"
#include <Server/Components/Pawn/pawn.hpp>

using namespace Impl;

class WebSocketsComponent final : public IWebSocketComponent, public PawnEventHandler, public CoreEventHandler
{
private:
	ICore* core_ = nullptr;
	IPawnComponent* pawn_;
	IPawnScript* script_ = nullptr;
	inline static WebSocketsComponent* instance_ = nullptr;

public:
	StringView componentName() const override;
	SemanticVersion componentVersion() const override;
	void onLoad(ICore* c) override;
	void onInit(IComponentList* components) override;
	void onReady() override;
	void onFree(IComponent* component) override;
	void free() override;
	void reset() override;
	void onAmxLoad(IPawnScript& script) override;
	void onAmxUnload(IPawnScript& script) override;
	void onTick(Microseconds elapsed, TimePoint now) override;

	IPawnScript* getScript() const;
	
	static WebSocketsComponent* getInstance();
	~WebSocketsComponent();
};
