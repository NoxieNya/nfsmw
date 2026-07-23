#ifndef FEOBJECTSORTER_H_
#define FEOBJECTSORTER_H_

#include <types.h>
#include "FEObject.h"
#include "FEngStandard.h"

// File: speed/indep/src/feng/FEObjectSorter.h
// total size: 0x8
// Decl: speed/indep/src/feng/FEObjectSorter.h:24
struct SFERadixKey {
    FEObject *pobObject; // offset 0x0, size 0x4, Decl: speed/indep/src/feng/FEObjectSorter.h:25
    u32 ulKey;           // offset 0x4, size 0x4, Decl: speed/indep/src/feng/FEObjectSorter.h:26
};

// total size: 0x4004
// Decl: speed/indep/src/feng/FEObjectSorter.h:34
template <int N> class FEObjectSorter {
  private:
    u32 mulNumObjects;              // offset 0x0, size 0x4, Decl: speed/indep/src/feng/FEObjectSorter.h:36
    SFERadixKey mastFinalList[N];   // offset 0x4, size 0x2000, Decl: speed/indep/src/feng/FEObjectSorter.h:37
    SFERadixKey mastScratchList[N]; // offset 0x2004, size 0x2000, Decl: speed/indep/src/feng/FEObjectSorter.h:38

  public:
    FEObjectSorter() { // Decl: speed/indep/src/feng/FEObjectSorter.h:41
        Zero();
    }

    void Zero() { // Decl: speed/indep/src/feng/FEObjectSorter.h:46
        mulNumObjects = 0;
    }

    void AddObject(FEObject *pobObject, float fZValue) { // Decl: speed/indep/src/feng/FEObjectSorter.h:51
        mastFinalList[mulNumObjects].pobObject = pobObject;
        mastFinalList[mulNumObjects].ulKey = *reinterpret_cast<u32 *>(&fZValue);
        mulNumObjects++;
    }

    u32 GetNumObjects() { // Decl: speed/indep/src/feng/FEObjectSorter.h:59
        return mulNumObjects;
    }

    SFERadixKey *GetListPtr() { // Decl: speed/indep/src/feng/FEObjectSorter.h:70
        return mastFinalList;
    }

    void SortObjects();
};

// UNSOLVED
template <int N> void FEObjectSorter<N>::SortObjects() { // Decl: speed/indep/src/feng/FEObjectSorter.h:81
    SFERadixKey *pstDestList = mastScratchList;
    SFERadixKey *pstSrcList = mastFinalList;
    i32 alElemCount[256];
    i32 alElemIndex[256];
    i32 lNumBytes = mulNumObjects << 3;
    i32 i = 0;

    for (int32 b = 3; b >= 0; b--) {
        FEngMemSet(alElemCount, 0, sizeof(alElemCount));
        u8 *pucByte = reinterpret_cast<u8 *>(pstSrcList) + b + 4;
        for (i = 0; i < lNumBytes; i += 8) {
            alElemIndex[pucByte[i]]++;
        }
        alElemIndex[0] = 0;
        for (i = 0; i < 255; i++) {
            alElemIndex[i + 1] = alElemIndex[i] + alElemCount[i];
        }
        for (i = 0; i < static_cast<i32>(mulNumObjects); i++) {
            u8 ucIndex = pucByte[i * 8];
            SFERadixKey *pstTemp = pstDestList + alElemIndex[ucIndex];
            pstTemp->pobObject = pstSrcList[i].pobObject;
            pstTemp->ulKey = pstSrcList[i].ulKey;
            alElemIndex[ucIndex]++;
        }
        SFERadixKey *pstTemp = pstSrcList;
        pstSrcList = pstDestList;
        pstDestList = pstTemp;
    }
};

#endif
