#pragma once
#include <inttypes.h>

// Chose between a table based CRC (flash expensive, fast)
// or a computed CRC (smaller, slow)
#define ONEWIRE_CRC8_TABLE 1

#define DS2482_COMMAND_RESET 0xF0 // Device reset

#define DS2482_COMMAND_SRP 0xE1 // Set read pointer
#define DS2482_POINTER_STATUS 0xF0
#define DS2482_STATUS_BUSY (1 << 0)
#define DS2482_STATUS_PPD (1 << 1)
#define DS2482_STATUS_SD (1 << 2)
#define DS2482_STATUS_LL (1 << 3)
#define DS2482_STATUS_RST (1 << 4)
#define DS2482_STATUS_SBR (1 << 5)
#define DS2482_STATUS_TSB (1 << 6)
#define DS2482_STATUS_DIR (1 << 7)
#define DS2482_POINTER_DATA 0xE1
#define DS2482_POINTER_CONFIG 0xC3
#define DS2482_CONFIG_APU (1 << 0)
#define DS2482_CONFIG_SPU (1 << 2)
#define DS2482_CONFIG_1WS (1 << 3)

#define DS2482_COMMAND_WRITECONFIG 0xD2
#define DS2482_COMMAND_RESETWIRE 0xB4
#define DS2482_COMMAND_WRITEBYTE 0xA5
#define DS2482_COMMAND_READBYTE 0x96
#define DS2482_COMMAND_SINGLEBIT 0x87
#define DS2482_COMMAND_TRIPLET 0x78

#define WIRE_COMMAND_SKIP 0xCC
#define WIRE_COMMAND_SELECT 0x55
#define WIRE_COMMAND_SEARCH 0xF0

#define DS2482_ERROR_TIMEOUT (1 << 0)
#define DS2482_ERROR_SHORT (1 << 1)
#define DS2482_ERROR_CONFIG (1 << 2)


class OneWireDS2482
{
  public:
    OneWireDS2482();
    OneWireDS2482(uint8_t address);

    void setup();
    void loop();

    uint8_t getAddress();
    uint8_t getError();
    uint8_t checkPresence();

    //DS2482-800 only
    bool selectChannel(uint8_t channel);

    void deviceReset();
    void setReadPointer(uint8_t readPointer);
    uint8_t readStatus();
    bool readStatusShortDet();
    uint8_t readData();
    uint8_t waitOnBusy();
    uint8_t readConfig();
    void writeConfig(uint8_t config);
    uint8_t crc8(const uint8_t *addr, uint8_t len);
    void setStrongPullup();
    void clearStrongPullup();
    void setActivePullup();
    void clearActivePullup();
    uint8_t wireReset();
    void wireWriteByte(uint8_t data, uint8_t power = 0);
    uint8_t wireReadByte();
    void wireWriteBit(uint8_t data, uint8_t power = 0);
    uint8_t wireReadBit();
    void wireSkip();
    void wireSelect(const uint8_t rom[8]);
    void wireResetSearch();
    uint8_t wireSearch(uint8_t *address);

  private:
    void begin();
    uint8_t end();
    void writeByte(uint8_t);
    uint8_t readByte();

    uint8_t mAddress;
    uint8_t mError;

    uint8_t searchAddress[8];
    uint8_t searchLastDiscrepancy;
    uint8_t searchLastDeviceFlag;
};
