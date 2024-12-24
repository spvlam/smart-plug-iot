#include "Payload.h"

// Constructor implementation
Payload::Payload(String action) : _action(action) {}

// Member function implementation
Payload Payload::fromJson(const String &jsonString)
{
    DynamicJsonDocument doc(256); // Adjust the size based on your JSON data size
    deserializeJson(doc, jsonString);

    String action = doc["action"];
    return Payload(action);
}

String Payload::getAction() const
{
    return _action;
}
// Implementation for RemotePayload class

// Default constructor
RemotePayload::RemotePayload() : data_(0)
{
}

// Parameterized constructor
RemotePayload::RemotePayload(String dev, int dat) : device_(dev), data_(dat) {}

// Getter and Setter for Device Name
String RemotePayload::getDeviceName() const
{
    return device_;
}

void RemotePayload::setDeviceName(const String &device)
{
    device_ = device;
}

// Getter and Setter for Data
int RemotePayload::getData() const
{
    return data_;
}

void RemotePayload::setData(int data)
{
    data_ = data;
}
String RemotePayload::toJson() const
{
    StaticJsonDocument<256> doc;
    doc["device"] = device_;
    doc["data"] = data_;

    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}

RemotePayload RemotePayload::fromJson(const String &jsonString)
{
    DynamicJsonDocument doc(256); // Adjust the size based on your JSON data size
    deserializeJson(doc, jsonString);

    String device = doc["device"];
    int data = doc["data"];

    return RemotePayload(device, data);
}

std::vector<RemotePayload> RemotePayload::fromListJson(const String &jsonString)
{
    std::vector<RemotePayload> result;

    DynamicJsonDocument doc(1024); // Adjust the size as needed
    deserializeJson(doc, jsonString);

    if (doc.containsKey("list") && doc["list"].is<JsonArray>())
    {
        JsonArray array = doc["list"].as<JsonArray>();
        for (JsonVariant value : array)
        {
            if (value.is<JsonObject>())
            {
                RemotePayload payload;
                JsonObject obj = value.as<JsonObject>();

                if (obj.containsKey("device") && obj.containsKey("data"))
                {
                    payload.setDeviceName(obj["device"].as<String>());
                    payload.setData(obj["data"].as<int>());
                    result.push_back(payload);
                }
                // You may want to handle other cases or provide error handling here
            }
        }
    }

    return result; // Add this line to ensure a return statement at the end
}
// ---------------------------------------------------------------------------------------------------------------------------------

// Implementation for ScriptPayload class

// Default constructor
ScriptPayload::ScriptPayload() : RemotePayload(), _eqId("") {}

// Parameterized constructor
ScriptPayload::ScriptPayload(String eqId, String dev, int dat) : RemotePayload(dev, dat), _eqId(eqId) {}

// Getter and Setter for Device Name (overriding the base class methods)
String ScriptPayload::getDeviceName() const
{
    return RemotePayload::getDeviceName(); // You can also override the behavior here if needed
}

void ScriptPayload::setDeviceName(const String &device)
{
    RemotePayload::setDeviceName(device); // You can also override the behavior here if needed
}

// Getter and Setter for Data (overriding the base class methods)
int ScriptPayload::getData() const
{
    return RemotePayload::getData(); // You can also override the behavior here if needed
}

void ScriptPayload::setData(int data)
{
    RemotePayload::setData(data); // You can also override the behavior here if needed
}

// Getter and Setter for EQId
String ScriptPayload::getEQId() const
{
    return _eqId;
}

void ScriptPayload::setEQId(const String &eqId)
{
    _eqId = eqId;
}

// Serialization to JSON (overriding the base class method)
String ScriptPayload::toJson() const
{
    StaticJsonDocument<256> doc;
    doc["eqId"] = _eqId;
    doc["device"] = getDeviceName(); // Using overridden method
    doc["data"] = getData();         // Using overridden method

    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}

// Deserialization from JSON
ScriptPayload ScriptPayload::fromJson(const String &jsonString)
{
    DynamicJsonDocument doc(256); // Adjust the size based on your JSON data size
    deserializeJson(doc, jsonString);

    String eqId = doc["eqId"];
    String device = doc["device"];
    int data = doc["data"];

    return ScriptPayload(eqId, device, data);
}

// Deserialization from a JSON array (overriding the base class method)
std::vector<ScriptPayload> ScriptPayload::fromListJson(const String &jsonString)
{
    std::vector<ScriptPayload> result;

    DynamicJsonDocument doc(1024); // Adjust the size as needed
    deserializeJson(doc, jsonString);

    if (doc.containsKey("list") && doc["list"].is<JsonArray>())
    {
        JsonArray array = doc["list"].as<JsonArray>();
        for (JsonVariant value : array)
        {
            if (value.is<JsonObject>())
            {
                JsonObject obj = value.as<JsonObject>();

                if (obj.containsKey("eqId") && obj.containsKey("device") && obj.containsKey("data"))
                {
                    ScriptPayload payload(
                        obj["eqId"].as<String>(),
                        obj["device"].as<String>(),
                        obj["data"].as<int>());
                    result.push_back(payload);
                }
                // You may want to handle other cases or provide error handling here
            }
        }
    }

    return result; // Add this line to ensure a return statement at the end
}
