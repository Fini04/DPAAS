#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

class Websocket
{
private:
    // void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
    // void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
public:
    // Websocket();
    String getAction();
    void setAction(String pAction);
    void notifyClients();
    void socketSetup();
    void socketLoop();
    void getStepperPositions(uint x, uint y);
};