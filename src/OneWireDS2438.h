#pragma once

#include <inttypes.h>
#include "OneWire.h"
#include "OneWireDS2482.h"

#define WRITESCRATCH 0x4E
#define COPYSCRATCH 0x48
#define READSCRATCH 0xBE
#define RECALLSCRATCH 0xB8
#define CONVERTT 0x44
#define CONVERTV 0xB4

// ADC configurations
#define CONFIG_VDD 0x09
#define CONFIG_VAD 0x01

// Scratchpad locations
#define STATUS 0
#define TEMP_LSB 1
#define TEMP_MSB 2
#define VOLT_LSB 3
#define VOLT_MSB 4
#define CURR_LSB 5
#define CURR_MSB 6
#define THRESH 7

class OneWireDS2438 : public OneWire
{
  public:
    OneWireDS2438(tIdRef iId);

    void loop() override;
    bool getValue(float &eValue, uint8_t iModelFunction) override;

  private:
    enum StateSensorADC
    {
        Startup,
        StartMeasureTemp,
        GetMeasureTemp,
        SetConfigVDD,
        StartMeasureVDD,
        GetMeasureVDD,
        SetConfigVAD,
        StartMeasureVAD,
        GetMeasureVAD,
        Idle,
        Error
    };

    ScratchPad mScratchPad;

    StateSensorADC mState = Startup;

    bool mParasite;
    
    float mTemp = NAN;
    float mVDD = NAN;
    float mVAD = NAN;
    float mVSens = NAN;

    float mTmpTemp = NAN;
    float mTmpVDD = NAN;
    float mTmpVAD = NAN;
    float mTmpVSens = NAN;

    void init();
    void readScratchPad();
    bool writeConfig(uint8_t config);
    uint8_t readConfig();
    bool startConversionTemp();
    bool updateTemp();
    bool startConversionVolt();
    bool updateVDD();
    bool updateVAD();
};