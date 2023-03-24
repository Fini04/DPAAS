#include "./hpp/Websocket.hpp"
#include "./hpp/networkConfig.hpp"

String action = "stop";

NetworkConfig nc;
const char *ssid = nc.ssid;
const char *password = nc.password;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

String Websocket::getAction()
{
  return action;
}
void Websocket::setAction(String pAction)
{
  action = pAction;
}

uint xPos, yPos;
void Websocket::getStepperPositions(uint x, uint y)
{
  xPos = x;
  yPos = y;
}

void Websocket::notifyClients()
{
  ws.textAll(String(yPos) + ", " + String(xPos));
  Serial.println(yPos);
  // ws.textAll(String(ledState));
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
  {
    data[len] = 0;
    if (strcmp((char *)data, "start") == 0)
    {
      action = "start";
    }
    if (strcmp((char *)data, "yVor") == 0)
    {
      action = "yVor";
    }
    if (strcmp((char *)data, "yZuruck") == 0)
    {
      action = "yZuruck";
    }
    if (strcmp((char *)data, "xVor") == 0)
    {
      action = "xVor";
    }
    if (strcmp((char *)data, "xZuruck") == 0)
    {
      action = "xZuruck";
    }
    if (strcmp((char *)data, "stop") == 0)
    {
      action = "stop";
    }
    if (strcmp((char *)data, "callibrate") == 0)
    {
      action = "callibrate";
    }
    if (strcmp((char *)data, "motorAus") == 0)
    {
      action = "motorAus";
    }
    if (strcmp((char *)data, "motorAn") == 0)
    {
      action = "motorAn";
    }
    if (strcmp((char *)data, "grab") == 0)
    {
      action = "grab";
    }
    if (strcmp((char *)data, "release") == 0)
    {
      action = "release";
    }
    if (strcmp((char *)data, "getStepPos") == 0)
    {
      action = "getStepPos";
    }
    if (strcmp((char *)data, "magVor") == 0)
    {
      action = "magVor";
    }
    if (strcmp((char *)data, "magZuruck") == 0)
    {
      action = "magZuruck";
    }
    if (strcmp((char *)data, "armVor") == 0)
    {
      action = "armVor";
    }
    if (strcmp((char *)data, "armZuruck") == 0)
    {
      action = "armZuruck";
    }
    if (strcmp((char *)data, "armGrab") == 0)
    {
      action = "armGrab";
    }
    if (strcmp((char *)data, "armRelease") == 0)
    {
      action = "armRelease";
    }
    if (strcmp((char *)data, "armReinSchieben") == 0)
    {
      action = "armReinSchieben";
    }
    if (strcmp((char *)data, "armRausZiehen") == 0)
    {
      action = "armRausZiehen";
    }
    if (strcmp((char *)data, "akkuLeer") == 0)
    {
      action = "akkuLeer";
    }
    if (strcmp((char *)data, "akkuVoll") == 0)
    {
      action = "akkuVoll";
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
  switch (type)
  {
  case WS_EVT_CONNECT:
    Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
    break;
  case WS_EVT_DISCONNECT:
    Serial.printf("WebSocket client #%u disconnected\n", client->id());
    break;
  case WS_EVT_DATA:
    handleWebSocketMessage(arg, data, len);
    break;
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  }
}

void Websocket::socketSetup()
{

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
    Serial.println(ssid);
    Serial.println(password);
  }

  Serial.println(WiFi.localIP());

  ws.onEvent(onEvent);
  server.addHandler(&ws);

  server.begin();
}