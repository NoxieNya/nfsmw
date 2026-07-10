#ifndef UIWORLDMAP_HPP
#define UIWORLDMAP_HPP

#include <types.h>

#include "Speed/Indep/Src/Frontend/Database/FEDatabase.hpp"
#include "Speed/Indep/Src/Frontend/MenuScreens/Common/feUIWidgetMenu.hpp"
#include "Speed/Indep/Src/Frontend/MenuScreens/Common/feWidget.hpp"
#include "Speed/Indep/Src/Gameplay/GIcon.h"
#include "Speed/Indep/Src/Misc/Timer.hpp"
#include "Speed/Indep/bWare/Inc/bList.hpp"
#include "Speed/Indep/bWare/Inc/bMath.hpp"
#include "Speed/Indep/Src/Frontend/MenuScreens/Safehouse/quickrace/uiTrackMapStreamer.hpp"
#include "Speed/Indep/Src/Input/ActionQueue.h"
#include "Speed/Indep/Src/World/TrackInfo.hpp"

enum eMiniMapModes {
    MMM_STATIC = 0,
    MMM_ROTATE = 1,
    MMM_OFF = 2,
    MMM_MIN = 0,
    MMM_MAX = 2,
};

// File: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp
// total size: 0x38
// Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:37
class MapItem : public bTNode<MapItem> {
  public:
    // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:40
    MapItem(eWorldMapItemType type, FEObject *iconObj, bVector2 &map_pos, bVector2 &world_pos, float rot, GIcon *icon)
        : pIcon(iconObj), InitialPos(map_pos), WorldPos(world_pos), Rot(rot), TheType(type), TheIcon(icon), bHidden(false) {
        if (!FEDatabase->GetGameplaySettings()->IsMapItemEnabled(type)) {
            bHidden = true;
            Hide();
        } else {
            bHidden = false;
            Show();
        }
        FEngGetSize(pIcon, InitialSize.x, InitialSize.y);
        FEngSetCenter(pIcon, InitialPos.x, InitialPos.y);
        FEngSetRotationZ(pIcon, Rot);
    };

    virtual ~MapItem() {} // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:61

    void GetInitialPos(bVector2 &pos) { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:63
        pos = InitialPos;
    }

    void GetWorldPos(bVector2 &pos) {
        pos = WorldPos;
    }

    void GetCurrentPos(bVector2 &pos) { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:64
        FEngGetCenter(pIcon, pos.x, pos.y);
    }

    virtual void UpdatePos(bVector2 &pos) { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:65
        FEngSetCenter(pIcon, pos.x, pos.y);
    }

    virtual void UpdateScale(float scale) { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:66
        FEngSetSize(pIcon, InitialSize.x * scale, InitialSize.y * scale);
    }

    virtual void Draw() {} // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:68

    virtual void Show() { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:70
        FEngSetVisible(pIcon);
    }

    virtual void Hide() { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:71
        FEngSetInvisible(pIcon);
    }

    virtual void ResetSize() { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:73
        FEngSetSize(pIcon, InitialSize.x, InitialSize.y);
    }

    GIcon *GetIcon() { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:75
        return TheIcon;
    }

    void SetHidden(bool b) { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:78
        bHidden = b;
        if (!b) {
            Show();
        } else {
            Hide();
        }
    }

    bool IsHidden() { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:79
        return bHidden;
    }

    eWorldMapItemType GetType() { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:81
        return TheType;
    }

  protected:
    FEObject *pIcon;           // offset 0x8, size 0x4, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:91
    bVector2 InitialPos;       // offset 0xC, size 0x8, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:93
    bVector2 InitialSize;      // offset 0x14, size 0x8, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:94
    bVector2 WorldPos;         // offset 0x1C, size 0x8
    float Rot;                 // offset 0x24, size 0x4
    eWorldMapItemType TheType; // offset 0x28, size 0x4, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:96
    GIcon *TheIcon;            // offset 0x2C, size 0x4, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:97
    bool bHidden;              // offset 0x30, size 0x1
};

// total size: 0x3C
// Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:155
class CopItem : public MapItem {
  public:
    CopItem(FEObject *icon, bVector2 &pos, bVector2 &world_pos, float rot, eWorldMapItemType type)
        : MapItem(type, icon, pos, world_pos, rot, nullptr), FlashTimer(-1) { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:158
    }

    ~CopItem() override {} // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:161

    void Draw() override;

  protected:
    int FlashTimer; // offset 0x38, size 0x4, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:166
};

// total size: 0x40
// Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:172
class HeliItem : public CopItem {
  public:
    HeliItem(FEImage *view, FEObject *icon, bVector2 &pos, bVector2 &world_pos, float rot)
        : CopItem(icon, pos, world_pos, rot, WMIT_COP_HELI), pViewCone(view) { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:175
        InitialSize.x = FEngGetScaleX(pIcon);
        InitialSize.y = FEngGetScaleY(pIcon);
        FEngSetCenter(pViewCone, pos.x, pos.y);
        FEngSetRotationZ(pViewCone, rot);
    }

    ~HeliItem() override {} // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:184

    void Draw() override;

    void UpdatePos(bVector2 &pos) override { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:188
        FEngSetCenter(pIcon, pos.x, pos.y);
        FEngSetCenter(pViewCone, pos.x, pos.y);
    }
    void UpdateScale(float scale) override { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:189
        FEngSetScaleX(pIcon, InitialSize.x * scale);
        FEngSetScaleY(pIcon, InitialSize.y * scale);
    }
    void Show() override { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:191
        MapItem::Show();
        FEngSetVisible(pViewCone);
    }
    void Hide() override { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:192
        MapItem::Hide();
        FEngSetInvisible(pViewCone);
    }

    void ResetSize() override { // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:194
        FEngSetScaleX(pIcon, InitialSize.x);
        FEngSetScaleY(pIcon, InitialSize.y);
    }

  protected:
    FEImage *pViewCone; // offset 0x3C, size 0x4, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:198
};

class ItemTypeToggle : public FEButtonWidget {
  public:
    ItemTypeToggle(uint32 name_hash, eWorldMapItemType type, bool vis) : FEButtonWidget(true) {
        ItemType = type;
        NameHash = name_hash;
        pIcon = nullptr;
        bVisibility = vis;
        bExiting = false;
    };
    ~ItemTypeToggle() override {}
    void Act(const char *parent_pkg, uint32 data) override;
    void CheckMouse(const char *parent_pkg, const float mouse_x, const float mouse_y) override;
    void Draw() override;
    void Position() override;
    void UnsetFocus() override;
    void SetIcon(FEImage *icon, uint32 texHash, uint32 texColour);
    void SetIconGroup(FEObject *obj) {
        pIconGroup = obj;
    }
    eWorldMapItemType GetType() {
        return ItemType;
    }
    bool GetVisibility() {
        return bVisibility;
    }
    void Show() override;
    void Hide() override;
    void StartExit() {
        bExiting = true;
    }

  protected:
    eWorldMapItemType ItemType; // offset 0x40, size 0x4
    uint32 NameHash;            // offset 0x44, size 0x4
    FEImage *pIcon;             // offset 0x48, size 0x4
    FEObject *pIconGroup;       // offset 0x4C, size 0x4
    bool bVisibility;           // offset 0x50, size 0x4
    bool bExiting;              // offset 0x54, size 0x4
};

// total size: 0x19C
// Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:213
class WorldMap : public UIWidgetMenu {
  public:
    WorldMap(ScreenConstructorData *sd);
    ~WorldMap() override;

    void NotificationMessage(u32 msg, FEObject *obj, u32 param1, u32 param2) override;

    static GIcon *GetGPSingIcon() {} // Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:272
    static void SetGPSing(GIcon *icon);
    static void ClearGPSing();

  private:
    void ScrollZoom(eScrollDir dir);
    float GetZoomFactor(eWorldMapZoomLevels level);
    void UpdateIconVisibility(eWorldMapItemType type, bool vis);
    void ClearItems();
    bool ClampToMapBounds(float &x, float &y);
    void UpdateCursor(bool zoom_thing);
    void UpdateAnalogInput();
    void MoveCursor(float x, float y);
    bool SnapCursor();
    void PanToCursor(float to_zoom);
    void PanToPlayer();
    void Setup() override;
    void AddMapItemOption(uint32 name_hash, eWorldMapItemType type);
    void AddPlayerCar();
    void AddCops();
    void AddRoadBlocks();
    void AddIcon(eWorldMapItemType type, uint32 icon_hash, GIcon *icon);
    void AddIcons(GIcon::Type desiredIconType);
    void SetupNavigation();
    void SetupEvent();
    void SetupPursuit();
    void ConvertPos(bVector2 &pos);
    float ConvertRot(bVector2 &dir);
    void DrawItemType();
    void DrawItemStats();
    void RefreshHeader();

    FEObject *Cursor;                // offset 0x138, size 0x4, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:337
    ActionQueue *mActionQ;           // offset 0x13C, size 0x4, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:338
    bVector2 CurrentVelocity;        // offset 0x140, size 0x8, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:339
    Timer TimeSinceLastMove;         // offset 0x148, size 0x4
    bVector2 CursorMoveFrom;         // offset 0x14C, size 0x8, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:340
    TrackInfo *pCurrentTrack;        // offset 0x154, size 0x4
    FEMultiImage *TrackMap;          // offset 0x158, size 0x4, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:343
    bVector2 MapTopLeft;             // offset 0x15C, size 0x8, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:344
    bVector2 MapSize;                // offset 0x164, size 0x8, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:345
    bTList<MapItem> TheMapItems;     // offset 0x16C, size 0x8, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:350
    MapItem *SelectedItem;           // offset 0x174, size 0x4, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:351
    UITrackMapStreamer *MapStreamer; // offset 0x178, size 0x4, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:353
    uint32 CurrentView;              // offset 0x17C, size 0x4
    int CurrentZoom;                 // offset 0x180, size 0x4, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:358
    int CurrentRaceType;             // offset 0x184, size 0x4
    bool bInToggleMode;              // offset 0x188, size 0x1
    bool bCursorOn;                  // offset 0x18C, size 0x1, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:360
    bool bCursorMoving;              // offset 0x190, size 0x1, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:361
    bool bLeftHeldOnMap;             // offset 0x194, size 0x1, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.hpp:362
    float fSnapDist;                 // offset 0x198, size 0x4
    static GIcon *mGPSingIcon;       // size: 0x4, address: 0x8041B640, Decl: speed/indep/src/frontend/menuscreens/ingame/uiWorldMap.cpp:191
};

#endif
