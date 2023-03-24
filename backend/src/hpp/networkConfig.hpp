#include <Arduino.h>

class NetworkConfig
{
private:
public:
    const char *ssid;
    const char *password;

    NetworkConfig();

    /*

    ~~INFO~~
    The values for ssid and password need to be assignt in the constructer.
    For example like that.

    NetworkConfig::NetworkConfig(){
    ssid = (const char*) "SSID";
    password = (const char*) "Password";
    }

    */
};
