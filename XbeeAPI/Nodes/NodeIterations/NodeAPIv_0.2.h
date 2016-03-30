/*
  XbeeAPI
*/
#ifndef XbeeAPI_h
#define XbeeAPI_h

#include <Arduino.h>
#include <HardwareSerial.h>

class XbeeAPI
{
  public:
    // public methods
    XbeeAPI(HardwareSerial * serialPort, int pin, const char* name);
    uint8_t sendMessage(unsigned char* message);
    bool responseReady();
    unsigned char* getResponse();
  private:
    // Private methods
    int produceFrame(unsigned char* escapedFrame, unsigned char* frame, unsigned char* message, int len, int id);
    void poll();
    bool validatePacket(unsigned char* packet);
    unsigned char escape(unsigned char* packet, unsigned char* output);
    void unescape(unsigned char* packet, unsigned char* output);

    // Fields
    public:
    class TxStatus
    {
    public:
      TxStatus(unsigned char* packet);
      bool wasSuccessful();
      uint8_t  getDeliveryStatus();
    private:
      uint8_t delivery;
    };

    public:
    class RxMessage
    {
    public:
      RxMessage();
      bool hasTerminated();
      unsigned char appendPayload(unsigned char* packet);
      unsigned char* getPayload();
    private:
      uint8_t frameID;
      bool terminated;
      unsigned char *payload; 
    };

  private:
    RxMessage *message;
    TxStatus *txstatus;
    HardwareSerial *serial;
    const char* name;
    
};

#endif