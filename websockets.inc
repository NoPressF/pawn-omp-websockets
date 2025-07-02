#if defined _INC_websockets
	#endinput
#endif

native WSClient:CreateWSClient(const connectName[], const failName[], const disconnectName[], const messageName[]);
native bool:DestroyWSClient(const WSClient:wsClient);
native bool:WSClientConnect(const WSClient:wsClient, const ip[]);
native bool:WSClientDisconnect(const WSClient:wsClient);
native bool:WSClientIsConnected(const WSClient:wsClient);
native WSClientSend(const WSClient:wsClient, const message[]);