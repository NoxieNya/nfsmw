#include "Speed/Indep/Src/Frontend/HUD/feMinimap.hpp"

#include "Speed/Indep/Libs/Support/Utility/UCOM.h"
#include "Speed/Indep/Src/AI/gps.h"
#include "Speed/Indep/Src/FEng/FEMath.h"
#include "Speed/Indep/Src/Frontend/FEngFrontend.hpp"
#include "Speed/Indep/Src/Frontend/FEngInterfaces/FEngInterfaceFEImages.hpp"
#include "Speed/Indep/Src/Frontend/FEngInterfaces/FEngInterfaceFEObjects.hpp"
#include "Speed/Indep/Src/Frontend/FEngInterfaces/FEngInterfaceFEStrings.hpp"
#include "Speed/Indep/Src/Frontend/HUD/FeMinimapStreamer.hpp"
#include "Speed/Indep/Src/Frontend/Database/FEDatabase.hpp"
#include "Speed/Indep/Src/Misc/attribuserinclude.h"
#include "Speed/Indep/bWare/Inc/bChunk.hpp"
#include "Speed/Indep/Src/Gameplay/GIcon.h"
#include "Speed/Indep/Src/Gameplay/GManager.h"
#include "Speed/Indep/Src/Interfaces/SimEntities/IPlayer.h"
#include "Speed/Indep/Src/Interfaces/Simables/IAI.h"
#include "Speed/Indep/Src/Interfaces/Simables/IVehicle.h"
#include "Speed/Indep/Src/Sim/Simulation.h"
#include "Speed/Indep/Src/World/TrackInfo.hpp"
#include "Speed/Indep/Src/World/OnlineManager.hpp"
#include "Speed/Indep/Src/World/RaceParameters.hpp"
#include "Speed/Indep/Src/AI/AITarget.h"
#include "Speed/Indep/Src/Interfaces/Simables/ICollisionBody.h"
#include "Speed/Indep/Src/Physics/PVehicle.h"
#include "Speed/Indep/bWare/Inc/bMath.hpp"

extern float MinimapPivotX;
extern float MinimapPivotY;
extern float MinimapDispX;
extern float MinimapMaxSpeed;
extern bool MinimapShowNonPursuitCops;
extern bool MinimapShowPursuitCops;
extern RaceParameters TheRaceParameters;

Minimap::GameplayIconInfo
    Minimap::kGameplayIconInfo[GIcon::kType_Count]; // size: 0x0, address: 0x8041BCA0, Decl: speed/indep/src/frontend/hud/FeMinimap.cpp:69

void GetVehicleVectors(bVector2 *pos, bVector2 *dir, ISimable *isimable) {
    UMath::Vector3 position = isimable->GetPosition();
    pos->y = -position.x;
    pos->x = position.z;
    UMath::Vector3 forwardVec;
    ICollisionBody *irigidbody;
    if (isimable->QueryInterface(&irigidbody)) {
        forwardVec = irigidbody->GetForwardVector();
        dir->y = -forwardVec.x;
        dir->x = forwardVec.z;
    }
}

static int LoaderMiniMap(bChunk *chunk) {
    return gChoppedMiniMapManager->Loader(chunk);
}

static int UnloaderMiniMap(bChunk *chunk) {
    return gChoppedMiniMapManager->Unloader(chunk);
}

static bChunkLoader bChunkLoaderMiniMap(0x3A100, LoaderMiniMap, UnloaderMiniMap);

Minimap::Minimap(const char *pkg_name, int player_number) : HudElement(pkg_name, 0x40010000), TrackmapArtUVs() {
    mCopFlashCounter = -1;
    mMapDefaultPos.z = 0.0f;
    mMapDefaultPos.y = 0.0f;
    mMapDefaultPos.x = 0.0f;
    mSpeedZoomScale = 0.0f;
    mPolyRotation = 0.0f;
    MinimapPivotX = 0.0f;
    mTrackTargetNormalized.x = 0.0f;
    mTrackTargetNormalized.y = 0.0f;
    mTrackMapCentre.x = 0.0f;
    mTrackMapCentre.y = 0.0f;

    for (int i = 0; i < 4; i++) {
        TrackmapArt[i] = static_cast<FEMultiImage *>(RegisterMultiImage(FEngHashString("TRACK_MAP%d", i + 1)));
        if (TrackmapArt[i] != nullptr) {
            TrackmapArt[i]->GetUVs(0, TrackmapArtUVs[i][0], TrackmapArtUVs[i][1]);
        }
    }

    TrackmapLayout = RegisterObject(FEngHashString("TRACK_MAP"));
    TrackmapNorth = RegisterImage(FEngHashString("MINIMAP_NORTH_INDICATOR"));
    mPlayerCarIndicator = RegisterImage(FEngHashString("PLAYERCARINDICATOR"));
    mPlayerCarIndicator2 = RegisterImage(FEngHashString("PLAYERCARINDICATOR2"));
    RegisterObject(FEngHashString("TRACKMAPTARGETRING"));
    RegisterObject(FEngHashString("MAP_COLOR_TINT"));

    bMemSet(mGameplayIcons, 0, sizeof(mGameplayIcons));

    mHeliElementArt = RegisterGroup(FEngHashString("HELICOPTER_ICON_GROUP"));
    mHeliLineOfSiteArt = RegisterImage(FEngHashString("HELICOPTER_LINE_OF_SIGHT"));

    for (int i = 0; i < 8u; i++) {
        mCopElementArt[i] = RegisterImage(FEngHashString("MMICON_COPCAR_%d", i));
        mRacerElementArt[i] = RegisterImage(FEngHashString("MMICON_AIRACER_%d", i));
        for (int onType = 0; onType < 17; onType++) {
            if (kGameplayIconInfo[onType].mItemType != 0) {
                if (i == 0 || (bStrStr(kGameplayIconInfo[onType].mElementString, "%d") != nullptr)) {
                    mGameplayIcons[onType][i] = RegisterImage(FEngHashString(kGameplayIconInfo[onType].mElementString, i));
                    if (mGameplayIcons[onType][i] != nullptr) {
                        FEngSetInvisible(mGameplayIcons[onType][i]);
                    }
                } else {
                    mGameplayIcons[onType][i] = nullptr;
                }
            }
        }
    }

    mCheckpointElementArt = RegisterImage(FEngHashString("MMICON_CHECKPOINT"));
    mGPSSelectionElementArt = RegisterImage(0xE8741681);

    if (TrackmapLayout != nullptr) {
        mMapDefaultPos = TrackmapLayout->GetObjData()->Pos;
        mTrackMapCentre.x = FEngGetCenterX(TrackmapLayout);
        mTrackMapCentre.y = FEngGetCenterY(TrackmapLayout);
    }

    InitStaticMiniMapItems();
}

Minimap::~Minimap() {
    gChoppedMiniMapManager->RemoveUncompressedMaps();
}

void Minimap::SetupMinimap(IPlayer *player) {
    const int num_chops = 8;
    i16 chop_nums[4] = {0};
    bVector2 map_pos;
    bVector2 target_pos;
    bVector2 target_dir;

    CurrentTrack = TrackInfo::GetTrackInfo(TheRaceParameters.TrackNumber);

    ISimable *isimable = player->GetSimable();
    GetVehicleVectors(&target_pos, &target_dir, isimable);
    ConvertPos(target_pos, map_pos, CurrentTrack);

    map_pos.x *= num_chops;
    map_pos.y *= num_chops;

    int XSection = static_cast<int>(map_pos.x);
    int YSection = static_cast<int>(map_pos.y);
    float XSection_decimal = map_pos.x - static_cast<float>(XSection);
    float YSection_decimal = map_pos.y - static_cast<float>(YSection);

    if (XSection_decimal < 0.5f) {
        if (YSection_decimal < 0.5f) {
            chop_nums[0] = (YSection - 1) * 8 + XSection - 1;
            chop_nums[1] = (YSection - 1) * 8 + XSection;
            chop_nums[2] = YSection * 8 + XSection - 1;
            chop_nums[3] = YSection * 8 + XSection;
        } else {
            chop_nums[0] = YSection * 8 + XSection - 1;
            chop_nums[1] = YSection * 8 + XSection;
            chop_nums[2] = (YSection + 1) * 8 + XSection - 1;
            chop_nums[3] = (YSection + 1) * 8 + XSection;
            YSection_decimal -= 1.0f;
        }
    } else {
        if (YSection_decimal < 0.5f) {
            chop_nums[0] = (YSection - 1) * 8 + XSection;
            chop_nums[1] = (YSection - 1) * 8 + XSection + 1;
            chop_nums[2] = YSection * 8 + XSection;
            chop_nums[3] = YSection * 8 + XSection + 1;
            XSection_decimal -= 1.0f;
        } else {
            chop_nums[0] = YSection * 8 + XSection;
            chop_nums[1] = YSection * 8 + XSection + 1;
            chop_nums[2] = (YSection + 1) * 8 + XSection;
            chop_nums[3] = (YSection + 1) * 8 + XSection + 1;
            YSection_decimal -= 1.0f;
            XSection_decimal -= 1.0f;
        }
    }

    gChoppedMiniMapManager->UncompressMaps(chop_nums, 4);

    float SectionSize = mSpeedZoomScale;
    float uvScale = SectionSize - 1.0f;

    char texture_name[128];
    for (int i = 0; i < 4; i++) {
        gChoppedMiniMapManager->GetTextureName(texture_name, sizeof(texture_name), chop_nums[i]);
        uint32 texture_hash = FEngHashString(texture_name);
        FEngSetTextureHash(TrackmapArt[i], texture_hash);
    }

    TrackmapArt[0]->SetTopLeft(FEVector2(uvScale, uvScale), false);
    TrackmapArt[0]->SetBottomRight(FEVector2(1.0f, 1.0f), false);

    TrackmapArt[1]->SetTopLeft(FEVector2(0.0f, uvScale), false);
    TrackmapArt[1]->SetBottomRight(FEVector2(1.0f - uvScale, 1.0f), false);

    TrackmapArt[2]->SetTopLeft(FEVector2(uvScale, 0.0f), false);
    TrackmapArt[2]->SetBottomRight(FEVector2(1.0f, 1.0f - uvScale), false);

    TrackmapArt[3]->SetTopLeft(FEVector2(0.0f, 0.0f), false);
    TrackmapArt[3]->SetBottomRight(FEVector2(1.0f - uvScale, 1.0f - uvScale), false);

    float xDisp = -(XSection_decimal * SectionSize);
    float yDisp = -(YSection_decimal * SectionSize);

    TrackmapArt[0]->SetUVs(0, FEVector2(TrackmapArtUVs[0][0].x + xDisp, TrackmapArtUVs[0][0].y + yDisp),
                           FEVector2(TrackmapArtUVs[0][1].x + xDisp, TrackmapArtUVs[0][1].y + yDisp));

    TrackmapArt[1]->SetUVs(0, FEVector2(TrackmapArtUVs[1][0].x + xDisp, TrackmapArtUVs[1][0].y + yDisp),
                           FEVector2(TrackmapArtUVs[1][1].x + xDisp, TrackmapArtUVs[1][1].y + yDisp));

    TrackmapArt[2]->SetUVs(0, FEVector2(TrackmapArtUVs[2][0].x + xDisp, TrackmapArtUVs[2][0].y + yDisp),
                           FEVector2(TrackmapArtUVs[2][1].x + xDisp, TrackmapArtUVs[2][1].y + yDisp));

    TrackmapArt[3]->SetUVs(0, FEVector2(TrackmapArtUVs[3][0].x + xDisp, TrackmapArtUVs[3][0].y + yDisp),
                           FEVector2(TrackmapArtUVs[3][1].x + xDisp, TrackmapArtUVs[3][1].y + yDisp));

    xDisp *= -128.0f;
    yDisp *= -128.0f;
    TrackmapLayout->GetObjData()->Pos = FEVector3(mMapDefaultPos.x - xDisp, mMapDefaultPos.y - yDisp, mMapDefaultPos.z);
    TrackmapLayout->GetObjData()->Pivot = FEVector3(xDisp + MinimapPivotX, yDisp + MinimapPivotY, 0.0f);
}

void Minimap::RefreshMapItems() {
    MiniMapItem *item = StaticMiniMapItems.GetHead();
    while (item != StaticMiniMapItems.EndOfList()) {
        FEngSetInvisible(item->pIcon);
        item = item->GetNext();
    }
    StaticMiniMapItems.DeleteAllElements();
    InitStaticMiniMapItems();
}

void Minimap::ConvertPos(bVector2 &worldPos, bVector2 &minimapPos, TrackInfo *track) {
    minimapPos.x = (worldPos.x - *reinterpret_cast<float *>(reinterpret_cast<char *>(track) + 0xAC)) /
                   *reinterpret_cast<float *>(reinterpret_cast<char *>(track) + 0xB4);
    minimapPos.y = (*reinterpret_cast<float *>(reinterpret_cast<char *>(track) + 0xB0) - worldPos.y) /
                       *reinterpret_cast<float *>(reinterpret_cast<char *>(track) + 0xB4) +
                   1.0f;
}

void Minimap::Update(IPlayer *player) {
    if (!IsElementVisible() || (player == nullptr)) {
        return;
    }

    ISimable *isimable = player->GetSimable();
    if (isimable == nullptr) {
        return;
    }

    MinimapRotateWithPlayer = 1;
    if (Sim::GetUserMode() == Sim::USER_SPLIT_SCREEN) {
        MinimapRotateWithPlayer = 0;
    } else {
        unsigned char rotate_with_player = GRaceStatus::Get().GetRaceParameters() == nullptr ? FEDatabase->GetGameplaySettings()->ExploringMiniMapMode
                                                                                             : FEDatabase->GetGameplaySettings()->RacingMiniMapMode;
        if (!rotate_with_player) {
            MinimapRotateWithPlayer = 0;
        }
    }

    SetupMinimap(player);

    IVehicle *ivehicle = nullptr;
    float speed = 0.0f;
    bVector2 target_pos;
    bVector2 target_dir;
    // bVector2 *target_pos_to_use = &target_pos;
    // bVector2 *target_dir_to_use = &target_dir;
    isimable = player->GetSimable();
    GetVehicleVectors(&target_pos, &target_dir, isimable);

    if (reinterpret_cast<UTL::COM::IUnknown *>(isimable)->QueryInterface(&ivehicle)) {
        speed = bAbs(ivehicle->GetSpeed());
    }

    mPolyRotation = bAngToDeg(bATan(target_dir.y, target_dir.x));
    ConvertPos(target_pos, mTrackTargetNormalized, CurrentTrack);

    if (speed > MinimapMaxSpeed) {
        speed = MinimapMaxSpeed;
    } else if (speed < 0.0f) {
        speed = 0.0f;
    }

    mSpeedZoomScale = 2.0f - speed / MinimapMaxSpeed;
    if (mSpeedZoomScale < 1.0f) {
        mSpeedZoomScale = 1.0f;
    }

    UpdateTrackMapArt();
    if (!MinimapRotateWithPlayer) {
        mPolyRotation = 0.0f;
    }

    UpdateCopElements(ivehicle);
    UpdateAiRacerElements();
    UpdatePlayer2Element();
    UpdateRaceElements();
    UpdateGameplayIcons(player);
}

void Minimap::UpdateTrackMapArt() {
    if (MinimapRotateWithPlayer == 0) {
        FEngSetRotationZ(mPlayerCarIndicator, mPolyRotation);
        FEngSetRotationZ(TrackmapLayout, 0.0f);
        FEngSetRotationZ(TrackmapNorth, 0.0f);
    } else {
        FEngSetRotationZ(mPlayerCarIndicator, 0.0f);
        FEngSetRotationZ(TrackmapLayout, -mPolyRotation);
        FEngSetRotationZ(TrackmapNorth, -mPolyRotation);
    }
}

void Minimap::UpdateElementArt(bVector2 *elementPos, bVector2 *elementDir, FEObject *elementArt, bool pulse) {
    bVector2 mapPos;
    ConvertPos(*elementPos, mapPos, CurrentTrack);

    float epoly_x = (mapPos.x - mTrackTargetNormalized.x) * mSpeedZoomScale;
    float epoly_y = (mapPos.y - mTrackTargetNormalized.y) * mSpeedZoomScale;
    const float sa = bSin(bDegToRad(mPolyRotation));
    const float ca = bCos(bDegToRad(mPolyRotation));
    float rot_epoly_x = epoly_y * ca - epoly_x * sa;
    float rot_epoly_y = epoly_x * ca + epoly_y * sa;
    float distance = bSqrt(rot_epoly_y * rot_epoly_y + rot_epoly_x * rot_epoly_x);
    float alpha = 1.0f;

    if (distance > 0.0f) {
        if (distance > 0.06f) {
            rot_epoly_x *= 0.06f / distance;
            rot_epoly_y *= 0.06f / distance;

            if (distance > 0.125f) {
                alpha = 1.0f - (distance - 0.125f) * 9.523809f;
            }
            if (distance > 0.23f) {
                alpha = 0.0f;
            }
            distance = 0.06f;

            if (pulse) {
                alpha = 1.0f;
            }
        }
    }

    if (distance <= 0.06f) {
        float screen_x = mTrackMapCentre.x + rot_epoly_y * 1024.0f;
        float screen_y = mTrackMapCentre.y + rot_epoly_x * 1024.0f;
        FEngSetCenter(elementArt, screen_x, screen_y);
        FEngSetVisible(elementArt);
        FEngSetRotationZ(elementArt, bAngToDeg(bATan(elementDir->y, elementDir->x)) - mPolyRotation);

        unsigned int color = static_cast<unsigned long>(FEngGetObjectColor(elementArt));
        int alphaInt = static_cast<int>(alpha * 255.0f);
        FEngSetColor(elementArt, color & 0x00FFFFFF | alphaInt << 24);

        if (pulse) {
            FEngSetVisible(mGPSSelectionElementArt);
            FEngSetCenter(mGPSSelectionElementArt, screen_x, screen_y);
        }
    } else {
        FEngSetInvisible(elementArt);
    }
}

void Minimap::UpdateCopElements(IVehicle *ivehicle) {
    unsigned int artIter = 0;
    bool helicopterFound = false;
    eVehicleList list_id = VEHICLE_AICOPS;
    IPursuit *ipursuit = nullptr;

    mCopFlashCounter++;
    if (mCopFlashCounter > 7) {
        mCopFlashCounter = 0;
    }

    IVehicleAI *ivehicleAI = ivehicle->GetAIVehiclePtr();
    ipursuit = ivehicleAI->GetPursuit();

    if (MinimapShowNonPursuitCops || ((ipursuit != nullptr) && !ipursuit->IsPursuitBailed())) {
        const IVehicle::List &vehicles = IVehicle::GetList(list_id);
        for (IVehicle *const *iter = vehicles.begin(); iter != vehicles.end(); ++iter) {
            IVehicle *copVehicle = *iter;
            if (!copVehicle->IsActive()) {
                continue;
            }
            if (artIter > 7) {
                break;
            }

            bVector2 target_pos;
            bVector2 target_dir;
            bVector2 *target_pos_to_use = &target_pos;
            bVector2 *target_dir_to_use = &target_dir;
            ISimable *isimable = copVehicle->GetSimable();
            GetVehicleVectors(target_pos_to_use, target_dir_to_use, isimable);

            IPursuitAI *ipursuitai = nullptr;
            copVehicle->QueryInterface(&ipursuitai);
            FEObject *copArtToUse;

            if (copVehicle->GetVehicleClass() == VehicleClass::CHOPPER) {
                copArtToUse = mHeliElementArt;
                if (MinimapShowNonPursuitCops || ((ipursuitai != nullptr) && ipursuitai->WasWithinEngagementRadius())) {
                    AITarget *target = ipursuitai->GetPursuitTarget();
                    if ((target == nullptr) || target->GetSpeed() > 0.25f) {
                        if (!FEngIsScriptSet(mHeliLineOfSiteArt, FEHashUpper("TRACKING"))) {
                            FEngSetScript(mHeliLineOfSiteArt, FEHashUpper("TRACKING"), true);
                        }
                    } else {
                        if (!FEngIsScriptSet(mHeliLineOfSiteArt, 0x1744B3)) {
                            FEngSetScript(mHeliLineOfSiteArt, 0x1744B3, true);
                        }
                    }
                }
                helicopterFound = true;
                UpdateElementArt(target_pos_to_use, target_dir_to_use, copArtToUse, false);
                UpdateElementArt(target_pos_to_use, target_dir_to_use, mHeliLineOfSiteArt, false);
            } else {
                if (MinimapShowNonPursuitCops || ((ipursuitai != nullptr) && ipursuitai->WasWithinEngagementRadius() && MinimapShowPursuitCops)) {
                    copArtToUse = mCopElementArt[artIter];
                    UpdateElementArt(target_pos_to_use, target_dir_to_use, copArtToUse, false);
                } else {
                    FEngSetInvisible(mCopElementArt[artIter]);
                }
            }

            if (copVehicle->GetVehicleClass() != VehicleClass::CHOPPER) {
                unsigned int copFlasherColour = 0xFFCCCCCC;
                if (ipursuitai && ipursuitai->GetInPursuit()) {
                    if (mCopFlashCounter < 3) {
                        copFlasherColour = 0xFF0000FF;
                    } else if (mCopFlashCounter - 4U < 3) {
                        copFlasherColour = 0xFFA00000;
                    }
                }
                FEngSetColor(mCopElementArt[artIter], copFlasherColour);
                artIter++;
            }
        }
    }

    for (unsigned int i = artIter; i < 8; i++) {
        FEngSetInvisible(mCopElementArt[i]);
    }
    if (!helicopterFound) {
        FEngSetInvisible(mHeliElementArt);
        FEngSetInvisible(mHeliLineOfSiteArt);
    }
}

void Minimap::UpdateAiRacerElements() {
    unsigned int artIter = 0;
    eVehicleList listid = TheOnlineManager.IsOnlineRace() ? VEHICLE_REMOTE : VEHICLE_AIRACERS;
    const IVehicle::List &vehicles = IVehicle::GetList(listid);

    for (IVehicle *const *iter = vehicles.begin(); iter != vehicles.end(); ++iter) {
        IVehicle *ivehicle = *iter;
        if (ivehicle->IsActive()) {
            bVector2 target_pos;
            bVector2 target_dir;
            GetVehicleVectors(&target_pos, &target_dir, ivehicle->GetSimable());
            UpdateElementArt(&target_pos, &target_dir, mRacerElementArt[artIter], false);
            artIter++;
        }
    }

    for (unsigned int i = artIter; i < 8; i++) {
        FEngSetInvisible(mRacerElementArt[i]);
    }
}

void Minimap::UpdatePlayer2Element() {
    if (Sim::GetUserMode() == Sim::USER_SPLIT_SCREEN) {
        IPlayer *player2 = IPlayer::Last(PLAYER_LOCAL);
        ISimable *isimable = player2->GetSimable();
        bVector2 target_pos;
        bVector2 target_dir;
        bVector2 *pPos = &target_pos;
        bVector2 *pDir = &target_dir;
        GetVehicleVectors(pPos, pDir, isimable);
        UpdateElementArt(pPos, pDir, mPlayerCarIndicator2, false);
    }
}

void Minimap::UpdateIconElement(FEImage *image, GIcon *icon) {
    bVector2 pos2D;
    bVector2 dir2D;
    icon->GetPosition2D(pos2D);
    dir2D.x = 1.0f;
    dir2D.y = 0.0f;
    if (icon->GetType() != GIcon::kType_AreaUnlock && !GPS_IsEngaged() && icon->GetIsGPSing()) {
        icon->ClearGPSing();
    }
    bool pulse = icon->GetIsGPSing();
    UpdateElementArt(&pos2D, &dir2D, image, pulse);
    FEngSetRotationZ(image, 0.0f);
}

void Minimap::UpdateRaceElements() {
    UpdateMiniMapItems();
}

void Minimap::AdjustForWidescreen(bool moveOutwards) {
    float offset;
    if (moveOutwards) {
        offset = -120.0f;
        MinimapPivotX = offset;
        MinimapDispX = -0.9375f;
    } else {
        offset = 120.0f;
        MinimapPivotX = 0.0f;
        MinimapDispX = 0.9375f;
    }
    mTrackMapCentre.x += offset;
    for (unsigned int i = 0; i < 4; i++) {
        reinterpret_cast<FEObjData *>(TrackmapArt[i]->pData)->Pos.x += offset;
    }
    reinterpret_cast<FEObjData *>(mPlayerCarIndicator->pData)->Pos.x += offset;
    reinterpret_cast<FEObjData *>(mPlayerCarIndicator->pData)->Pos.y = mTrackMapCentre.y;
}

void Minimap::UpdateMiniMapItems() {
    for (MiniMapItem *item = static_cast<MiniMapItem *>(StaticMiniMapItems.GetHead()); item != StaticMiniMapItems.EndOfList();
         item = static_cast<MiniMapItem *>(item->GetNext())) {
        if (item->bHidden) {
            FEngSetInvisible(item->pIcon);
        } else {
            FEngSetVisible(item->pIcon);

            bVector2 dir(0.0f, 1.0f);
            UpdateElementArt(&item->ItemPosition, &dir, item->pIcon, false);
            FEngSetRotationZ(item->pIcon, 0.0f);
        }
    }
}

void Minimap::InitStaticMiniMapItems() {}

void Minimap::UpdateGameplayIcons(IPlayer *player) {
    int iconsPlaced[GIcon::kType_Count];
    GIcon *sortedIcons[200];

    FEngSetInvisible(mGPSSelectionElementArt);
    bMemSet(iconsPlaced, 0, sizeof(iconsPlaced));

    int numIcons = GManager::Get().GatherVisibleIcons(sortedIcons, player);
    for (int onIcon = 0; onIcon < numIcons; onIcon++) {
        GIcon *icon = sortedIcons[onIcon];
        GIcon::Type iconType = icon->GetType();
        GameplayIconInfo &iconInfo = kGameplayIconInfo[iconType];
        FEImage *image;

        if (iconInfo.mItemType != 0 && static_cast<unsigned int>(iconsPlaced[iconType]) < 8) {
            if (FEDatabase->GetGameplaySettings()->IsMapItemEnabled(static_cast<eWorldMapItemType>(iconInfo.mItemType))) {
                image = mGameplayIcons[iconType][static_cast<unsigned int>(iconsPlaced[iconType])];
                iconsPlaced[iconType]++;
                if (image != nullptr) {
                    UpdateIconElement(image, icon);
                }
            }
        }
    }

    for (int onType = 0; onType < GIcon::kType_Count; onType++) {
        for (int onHideIcon = iconsPlaced[onType]; static_cast<unsigned int>(onHideIcon) < 8; onHideIcon++) {
            if (mGameplayIcons[onType][onHideIcon] != nullptr) {
                FEngSetInvisible(mGameplayIcons[onType][onHideIcon]);
            }
        }
    }
}
