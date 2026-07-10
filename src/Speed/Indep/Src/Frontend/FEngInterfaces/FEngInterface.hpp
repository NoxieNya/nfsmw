#ifndef __FENGINTERFACE_HPP
#define __FENGINTERFACE_HPP

#include "Speed/Indep/Src/FEng/FEPackage.h"
#include "Speed/Indep/Src/FEng/FEngine.h"

// File: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp
// total size: 0x8
// Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:20
class cFEng {
  public:
    static void Init(); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:24

    static void Destroy(); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:25

    static cFEng *Get() { // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:26
        return mInstance;
    }

    void QueuePackagePush(const char *pPackageName, int pArg, u32 ControlMask,
                          bool pSuppressSimPause); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:31

    void QueuePackagePop(int numPackagesToPop); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:32

    void QueuePackageSwitch(const char *pPackageName, int pArg, u32 ControlMask,
                            bool pSuppressSimPause); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:30
    void QueuePopChildPackages(const char *pPackageName);

    void PushNoControlPackage(const char *pPackageName,
                              FE_PACKAGE_PRIORITY pPriority); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:36

    void PopNoControlPackage(const char *pPackageName); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:37

    void PushErrorPackage(const char *pPackageName, int pArg, u32 ControlMask); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:41
    void PopErrorPackage();                                                     // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:42
    bool IsErrorState() {                                                       // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:43
        return mFEng->IsErrorScreenMode();
    }

    void PopErrorPackage(int port); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:42

    FEPackage *FindPackageWithControl(); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:47
    FEPackage *FindPackageAtBase();      // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:48
    FEPackage *FindPackageActive(const char *pPackageName);
    FEPackage *FindPackageIdle(const char *pPackageName);
    FEPackage *FindPackage(const char *pPackageName); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:49

    bool IsPackagePushed(const char *pPackageName); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:50

    bool IsPackageInControl(const char *pPackageName); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:51

    void PrintLoadedPackages(); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:94

    void UnloadPackage(FEPackage *pPackagePtr) { // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:70
        mFEng->UnloadPackage(pPackagePtr);
    }

    void QueuePackageMessage(uint32 pMessage, const char *pPackageName,
                             FEObject *obj); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:60

    void QueueGameMessage(uint32 pMessage, const char *pPackageName,
                          uint32 controlMask); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:61

    void QueueSoundMessage(uint32 pMessage, const char *pPackageName); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:62

    void QueueGameMessagePkg(unsigned int pMessage, FEPackage *topkg);

    void Service();         // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:66
    void ServiceFengOnly(); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:67
    void DrawForeground();  // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:68

    bool RecordPackageMarker(const char *pkg_name);

    int GetNumPackageMarkers();

    const char *RecallPackageMarker();

    const char *PeekPackageMarker();

    void MakeLoadedPackagesDirty(); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:69

    void EnablePackageControl(FEPackage *pkg, bool bProcess);

    int GetNumPackagesPushed() {}
    bool IsErrorMode();

    cFEng();  // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:80
    ~cFEng(); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:81

  private:
    void QueueMessage(uint32 pMessage, const char *pPackageName, FEObject *to,
                      uint32 controlMask); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:84

    void PauseAllSystems();                   // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:98
    void ResumeAllSystems(bool flushActions); // Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:99

  private:
    static cFEng *mInstance; // size: 0x4, address: 0x8041B96C, Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:103
    FEngine *mFEng;          // offset 0x0, size 0x4, Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:104
    bool bWasPaused;         // offset 0x4, size 0x1, Decl: speed/indep/src/frontend/fenginterfaces/FEngInterface.hpp:108

    friend class cFEngGameInterface;
};

// From carbon, might be inaccurate
#define FENG_OBJECT_INVISIBLE (1 << 0)                    // :113
#define FENG_OBJECT_IGNORE_LABELHASH (1 << 1)             // :114
#define FENG_OBJECT_DONT_SHOW_IN_DEMO (1 << 2)            // :115
#define FENG_OBJECT_XENON_INVISIBLE (1 << 2)              // :116
#define FENG_OBJECT_PC_ONLY (1 << 3)                      // :117
#define FENG_OBJECT_CONTEXT_HELP (1 << 4)                 // :118
#define FENG_OBJECT_IGNORE_SPECIAL_CHARACTERS (1 << 5)    // :119
#define FENG_OBJECT_CONSOLE_ONLY (1 << 6)                 // :120
#define FENG_OBJECT_MEMCARD_MESSAGE (1 << 7)              // :121
#define FENG_OBJECT_ZSORT (1 << 8)                        // :122
#define FENG_FONTRENDERWRAPPING_CHARACTER (1 << 9)        // :139
#define FENG_RANDOMIZE_STRING (1 << 10)                   // :140
#define FENG_OBJECT_IGNORE_JOY_EVENT_CHARACTERS (1 << 11) // :141
#define FENG_NEXT_GEN_ONLY (1 << 12)                      // :142

// Range: 0x801325E8 -> 0x80132694
int FEPrintf(struct FEString *text /* r3 */, const char *fmt /* r4 */, ...);

// Range: 0x80132694 -> 0x801327DC
int FEPrintf(const char *pkg_name /* r27 */, int object_hash /* r4 */, const char *fmt /* r28 */, ...);

// Range: 0x801327DC -> 0x80132914
int FEPrintf(const char *pkg_name /* r28 */, struct FEObject *obj /* r31 */, const char *fmt /* r4 */, ...);

#endif
