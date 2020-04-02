#pragma once
#include <inttypes.h>
#include <Arduino.h>
#include "OneWire.h"
// #include <OneWireDS2482.h>

// #define DebugInfoSearch

// forward declaration
class OneWireDS2482;

// base class for different search implementations
class OneWireSearch
{
  public:
    enum SearchState
    {
        SearchNew,
        SearchNext,
        SearchStart,
        SearchStep,
        SearchEnd,
        SearchError,
        SearchFinished
    };
    enum SearchMode
    {
        All,
        Family,
        NoFamily,
        Id
    };

    OneWireSearch(OneWireDS2482 *iBM);

    SearchState loop();
    void newSearchAll();
    void newSearchFamily(uint8_t iFamily);
    void newSearchNoFamily(uint8_t iNoFamily);
    void newSearchForId(tIdRef iId);
    void manageSearchCounter(SearchState iState);
    SearchState state();

  protected:
    OneWireDS2482 *mBM = NULL;
    uint32_t mDelay = 0;

#ifdef DebugInfoSearch
    uint32_t mDuration = 0;
    uint32_t mDurationOld = 0;
    uint32_t mCurrDelay = 0;
    uint32_t mMaxDelay = 0;
#endif

    SearchState mSearchState = SearchNew;
    SearchMode mSearchMode = All;
    
    // search buffer has to be 8 Byte, 
    // part of search result is crc byte
    uint8_t mSearchResultId[8]; 
    int8_t mSearchLastDiscrepancy = -1;
    uint8_t mSearchLastFamilyDiscrepancy;
    uint8_t mSearchLastDeviceFlag;
    int8_t mSearchLastZero = -1;
    uint8_t mSearchStep = 0;
    uint8_t mSearchFamily = 0;

    bool MatchSearchMode(uint8_t iFamily);
    virtual void wireSearchNew() = 0;
    virtual void wireSearchNext() = 0;
    virtual bool wireSearchStart(uint8_t iStatus) = 0;
    virtual bool wireSearchStep(uint8_t iStep) = 0;
    virtual bool wireSearchEnd() = 0;
    virtual bool wireSearchFinished(bool iIsError) = 0;
    virtual uint8_t wireSearchBlocking(tIdRef eAddress) = 0;
};