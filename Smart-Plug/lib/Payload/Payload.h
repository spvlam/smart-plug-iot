#ifndef Payload_h
#define Payload_h
#include <Arduino.h>
#include <ArduinoJson.h>
class Payload
{
public:
    // Constructor
    Payload(String action);
    static Payload fromJson(const String &jsonString);
    String getAction() const;
    // Member function

private:
    String _action;
};

class RemotePayload
{
private:
    String device_;
    int data_;

public:
    RemotePayload();
    RemotePayload(String dev, int dat);
    // Getter and Setter for Device Name
    String getDeviceName() const;
    void setDeviceName(const String &device);
    // Getter and Setter for Data
    int getData() const;
    void setData(int data);
    String toJson() const;
    static RemotePayload fromJson(const String &jsonString);
    static std::vector<RemotePayload> fromListJson(const String &jsonString);
};

class ScriptPayload : public RemotePayload {
    private:
        String _eqId;
    public:
    ScriptPayload();
    ScriptPayload( String eqId, String dev, int dat);
    String getDeviceName() const;
    void setDeviceName(const String &device);
    // Getter and Setter for Data
    int getData() const;
    void setData(int data);
    String getEQId() const;
    void setEQId(const String &eqId);
    String toJson() const;
    static ScriptPayload fromJson(const String &jsonString);
    static std::vector<ScriptPayload> fromListJson(const String &jsonString);
};
#endif
