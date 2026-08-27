#include "Speed/Indep/Src/Frontend/MenuScreens/Safehouse/customize/CarCustomize.hpp"
#include "Speed/Indep/Src/EAXSound/EAXSOund.hpp"
#include "Speed/Indep/Src/Frontend/FECarViewer.hpp"
#include "Speed/Indep/Src/Frontend/FEManager.hpp"
#include "Speed/Indep/Src/Frontend/FEngFrontend.hpp"
#include "Speed/Indep/Src/Frontend/FEngHashes/FEHash_FeBonusCards.hpp"
#include "Speed/Indep/Src/Frontend/FEngHashes/ScriptHashes.hpp"
#include "Speed/Indep/Src/Frontend/FEngInterfaces/FEngInterfaceFEImages.hpp"
#include "Speed/Indep/Src/Frontend/FEngInterfaces/FEngInterfaceFEObjects.hpp"
#include "Speed/Indep/Src/Frontend/Localization/Localize.hpp"
#include "Speed/Indep/Src/Frontend/MemoryCard/MemoryCard.hpp"
#include "Speed/Indep/Src/Frontend/MenuScreens/Common/feDialogBox.hpp"
#include "Speed/Indep/Src/Frontend/MenuScreens/Safehouse/FEPkg_GarageMain.hpp"
#include "Speed/Indep/Src/Frontend/MenuScreens/Safehouse/customize/CustomizeManager.hpp"
#include "Speed/Indep/Src/Frontend/Careers/UnlockSystem.hpp"
#include "Speed/Indep/Src/Frontend/Database/FEDatabase.hpp"
#include "Speed/Indep/Src/Frontend/FEngInterfaces/FEngInterface.hpp"
#include "Speed/Indep/Src/FEng/FEString.h"
#include "Speed/Indep/Src/Frontend/MenuScreens/Safehouse/customize/FECustomize.hpp"
#include "Speed/Indep/Src/Frontend/MenuScreens/Safehouse/quickrace/uiShowcase.hpp"
#include "Speed/Indep/Src/Frontend/RaceStarter.hpp"
#include "Speed/Indep/Src/Generated/AttribSys/Classes/frontend.h"
#include "Speed/Indep/Src/Generated/LanguageHashes.hpp"
#include "Speed/Indep/Src/Physics/PhysicsUpgrades.hpp"
#include "Speed/Indep/Src/World/CarInfo.hpp"
#include "Speed/Indep/bWare/Inc/Strings.hpp"
#include "Speed/Indep/bWare/Inc/bPrintf.hpp"
#include "types.h"

extern const float gTradeInFactor = 0.25f; // size: 0x4

uint32 TranslateCustomizeCatToMarker(eCustomizeCategory cat) {
    switch (cat) {
        case CC_BODY_KIT:
            return FEMarkerManager::MARKER_BODY;
        case CC_SPOILERS:
            return FEMarkerManager::MARKER_SPOILER;
        case CC_HOODS:
            return FEMarkerManager::MARKER_HOOD;
        case CC_ROOF_SCOOPS:
            return FEMarkerManager::MARKER_ROOF_SCOOP;
        case CC_CUSTOM_HUD:
            return FEMarkerManager::MARKER_CUSTOM_HUD;
        case CC_ENGINE:
            return FEMarkerManager::MARKER_ENGINE;
        case CC_TRANSMISSION:
            return FEMarkerManager::MARKER_TRANSMISSION;
        case CC_SUSPENSION:
            return FEMarkerManager::MARKER_CHASSIS;
        case CC_NITROUS:
            return FEMarkerManager::MARKER_NOS;
        case CC_TIRES:
            return FEMarkerManager::MARKER_TIRES;
        case CC_BRAKES:
            return FEMarkerManager::MARKER_BRAKES;
        case CC_FORCED_INDUCTION:
            return FEMarkerManager::MARKER_INDUCTION;
        case CC_PAINT:
        case CC_RIM_PAINT:
            return FEMarkerManager::MARKER_PAINT;
        case CC_VINYL_TYPES:
        case CC_VINYL_GROUP_FLAME:
        case CC_VINYL_GROUP_TRIBAL:
        case CC_VINYL_GROUP_STRIPE:
        case CC_VINYL_GROUP_RACING_FLAG:
        case CC_VINYL_GROUP_NATIONAL_FLAG:
        case CC_VINYL_GROUP_BODY:
        case CC_VINYL_GROUP_UNIQUE:
        case CC_VINYL_GROUP_CONTEST:
            return FEMarkerManager::MARKER_VINYL;
        case CC_RIM_BRANDS:
        case CC_RIM_BRAND_5_ZIGEN:
        case CC_RIM_BRAND_ADR:
        case CC_RIM_BRAND_BBS:
        case CC_RIM_BRAND_ENKEI:
        case CC_RIM_BRAND_KONIG:
        case CC_RIM_BRAND_LOWENHART:
        case CC_RIM_BRAND_RACING_HART:
        case CC_RIM_BRAND_OZ:
        case CC_RIM_BRAND_VOLK:
        case CC_RIM_BRAND_ROJA:
            return FEMarkerManager::MARKER_RIMS;
        case CC_DECAL_LOCATION:
        case CC_DECAL_WINDSHIELD:
        case CC_DECAL_REAR_WINDOW:
        case CC_DECAL_LEFT_DOOR:
        case CC_DECAL_RIGHT_DOOR:
        case CC_DECAL_LEFT_QP:
        case CC_DECAL_RIGHT_QP:
        case CC_DECAL_SLOT_1:
        case CC_DECAL_SLOT_2:
        case CC_DECAL_SLOT_3:
        case CC_DECAL_SLOT_4:
        case CC_DECAL_SLOT_5:
        case CC_DECAL_SLOT_6:
            return FEMarkerManager::MARKER_DECAL;
        default:
            return 0;
    }
}

uint32 GetMarkerNameFromCategory(eCustomizeCategory cat) {
    switch (cat) {
        case CC_PARTS:
            return 0xd3a2fbe1;
        case CC_PERFORMANCE:
            return 0x3c27a989;
        case CC_VISUAL:
            return 0x5692be6b;
        case CC_BODY_KIT:
            return 0x7c50498c;
        case CC_SPOILERS:
            return 0x52012995;
        case CC_RIM_BRANDS:
        case CC_RIM_BRAND_5_ZIGEN:
        case CC_RIM_BRAND_ADR:
        case CC_RIM_BRAND_BBS:
        case CC_RIM_BRAND_ENKEI:
        case CC_RIM_BRAND_KONIG:
        case CC_RIM_BRAND_LOWENHART:
        case CC_RIM_BRAND_RACING_HART:
        case CC_RIM_BRAND_OZ:
        case CC_RIM_BRAND_VOLK:
        case CC_RIM_BRAND_ROJA:
            return 0x8a4bfbf2;
        case CC_HOODS:
            return 0x8a4699e1;
        case CC_ROOF_SCOOPS:
            return 0x830100f0;
        case CC_CUSTOM_HUD:
            return 0xc253ec92;
        case CC_ENGINE:
            return 0x2f3ec04d;
        case CC_TRANSMISSION:
            return 0xd1e77ca1;
        case CC_SUSPENSION:
            return 0xb7cbfcce;
        case CC_NITROUS:
            return 0xc129562b;
        case CC_TIRES:
            return 0xd3efbefe;
        case CC_BRAKES:
            return 0x2884658f;
        case CC_FORCED_INDUCTION:
            if (gCarCustomizeManager.IsTurbo()) {
                return 0xd3f65323;
            }
            return 0x63a51aa2;
        case CC_PAINT:
            return 0xd3a2d4d3;
        case CC_VINYL_TYPES:
        case CC_VINYL_GROUP_FLAME:
        case CC_VINYL_GROUP_TRIBAL:
        case CC_VINYL_GROUP_STRIPE:
        case CC_VINYL_GROUP_RACING_FLAG:
        case CC_VINYL_GROUP_NATIONAL_FLAG:
        case CC_VINYL_GROUP_BODY:
        case CC_VINYL_GROUP_UNIQUE:
        case CC_VINYL_GROUP_CONTEST:
            return 0xd413e189;
        case CC_DECAL_LOCATION:
        case CC_DECAL_WINDSHIELD:
        case CC_DECAL_REAR_WINDOW:
        case CC_DECAL_LEFT_DOOR:
        case CC_DECAL_RIGHT_DOOR:
        case CC_DECAL_LEFT_QP:
        case CC_DECAL_RIGHT_QP:
        case CC_DECAL_SLOT_1:
        case CC_DECAL_SLOT_2:
        case CC_DECAL_SLOT_3:
        case CC_DECAL_SLOT_4:
        case CC_DECAL_SLOT_5:
        case CC_DECAL_SLOT_6:
            return 0xd2cbc510;
        default:
            return 0;
    }
}

uint32 GetNumMarkersFromCategory(eCustomizeCategory cat) {
    switch (cat) {
        case CC_PARTS: {
            int num = GetNumMarkersFromCategory(CC_BODY_KIT);
            num += GetNumMarkersFromCategory(CC_SPOILERS);
            num += GetNumMarkersFromCategory(CC_RIM_BRANDS);
            num += GetNumMarkersFromCategory(CC_HOODS);
            num += GetNumMarkersFromCategory(CC_ROOF_SCOOPS);
            return num + GetNumMarkersFromCategory(CC_CUSTOM_HUD);
        }
        case CC_PERFORMANCE: {
            int num = GetNumMarkersFromCategory(CC_ENGINE);
            num += GetNumMarkersFromCategory(CC_TRANSMISSION);
            num += GetNumMarkersFromCategory(CC_SUSPENSION);
            num += GetNumMarkersFromCategory(CC_NITROUS);
            num += GetNumMarkersFromCategory(CC_TIRES);
            num += GetNumMarkersFromCategory(CC_BRAKES);
            return num + GetNumMarkersFromCategory(CC_FORCED_INDUCTION);
        }
        case CC_VISUAL: {
            int num = GetNumMarkersFromCategory(CC_PAINT);
            num += GetNumMarkersFromCategory(CC_VINYL_TYPES);
            return num + GetNumMarkersFromCategory(CC_DECAL_LOCATION);
        }
        default:
            return TheFEMarkerManager.GetNumMarkers(static_cast<FEMarkerManager::ePossibleMarker>(TranslateCustomizeCatToMarker(cat)), 0);
    }
}

CustomizeMeter::CustomizeMeter()
    : Min(0.0f),             //
      Max(1.0f),             //
      Current(0.0f),         //
      Preview(0.0f),         //
      PreviousPreview(0.0f), //
      NumStages(5),          //
      pMultiplier(nullptr),  //
      pMeterGroup(nullptr)   //
{
    for (int i = 0; i < NUM_STAGE_SEGMENTS; i++) {
        pBases[i] = nullptr;
    }
}

void CustomizeMeter::Init(const char *pkg_name, const char *name, float min, float max, float current, float preview) {
    Min = min;
    Max = max;
    SetCurrent(current);
    SetPreview(preview);
    const u32 FEObj_HeatX = 0x5ffee1d8;
    const u32 FEObj_HeatXZOOM = 0xe637955c;
    pMultiplier = FEngFindImage(pkg_name, FEObj_HeatX);
    pMultiplierZoom = FEngFindImage(pkg_name, FEObj_HeatXZOOM);
    pMeterGroup = FEngFindObject(pkg_name, 0xf2492598);
    for (int i = 0; i < NUM_STAGE_SEGMENTS; i++) {
        pBases[i] = FEngFindImage(pkg_name, FEngHashString("HEAT_BASE_LED_%d", i + 1));
    }
}

void CustomizeMeter::SetCurrent(float current) {
    Current = bMin(bMax(current, Min), Max);
}

void CustomizeMeter::SetPreview(float preview) {
    PreviousPreview = Preview;
    Preview = bMin(bMax(preview, Min), Max);
}

// UNSOLVED
void CustomizeMeter::Draw() {
    float stage_size = 1.0f;
    float multiplier = stage_size;
    float stage_bottom = Min;
    while (Preview - stage_bottom >= stage_size) {
        multiplier += stage_size;
        stage_bottom += stage_size;
    }
    multiplier = bMin(multiplier, 5.0f);
    // TODO: no need to double hash
    FEngSetTextureHash(pMultiplier, FEngHashString("HEAT_X%.0f", multiplier));
    FEngSetTextureHash(pMultiplierZoom, FEngHashString("HEAT_X%.0f", multiplier));

    const u32 FEObj_ZOOM = 0x209c24;
    if (Preview != PreviousPreview) {
        FEngSetScript(pMultiplierZoom, FEObj_ZOOM, true);
    }

    float segment_size = stage_size * 0.1f;
    float segment_bottom = stage_bottom;
    int cur_icon = 10;
    float current_segment = segment_bottom + stage_size;
    if (current_segment >= stage_bottom) {
        do {
            current_segment -= segment_size;
            cur_icon--;
            uint32 script;
            if (current_segment + 0.0005f >= this->Current) {
                const u32 FEObj_OFF = 0xccfa;
                script = FEObj_OFF;
            } else if (current_segment + 0.0005f >= this->Preview) {
                const u32 FEObj_COOL = 0x13ff6c;
                script = 0x13ff6c;
            } else {
                const u32 FEObj_ON = 0x63c;
                script = FEObj_ON;
            }
            FEngSetScript(pBases[cur_icon], script, true);
        } while (current_segment >= stage_bottom && cur_icon >= 0);
    }
}

void CustomizeMeter::SetVisibility(bool b) {
    if (b) {
        FEngSetVisible(pMeterGroup);
    } else {
        FEngSetInvisible(pMeterGroup);
    }
}

void FEShoppingCartItem::Show() {
    FEStatWidget::Show();
    FEngSetVisible(pTradeInPrice);
    FEngSetVisible(pCheckIcon);
}

void FEShoppingCartItem::Hide() {
    FEStatWidget::Hide();
    FEngSetInvisible(pTradeInPrice);
    FEngSetInvisible(pCheckIcon);
}

void FEShoppingCartItem::Draw() {
    if (TheItem->IsActive()) {
        FEngSetTextureHash(pCheckIcon, 0x696ae039);
    } else {
        FEngSetTextureHash(pCheckIcon, 0xe719881c);
    }
    DrawPartName();
    if ((TheItem->GetTradeInPart() != nullptr) && gCarCustomizeManager.IsCareerMode() && !gCarCustomizeManager.IsInBackRoom()) {
        FEPrintf(pTradeInPrice, "%$d", TheItem->GetTradeInPrice());
    } else {
        FEPrintf(pTradeInPrice, "");
    }
    if (gCarCustomizeManager.IsCareerMode() && !gCarCustomizeManager.IsInBackRoom()) {
        FEPrintf(GetDataObject(), "%$d", TheItem->GetPartPrice());
    } else {
        FEPrintf(GetDataObject(), "");
    }
}

void FEShoppingCartItem::Position() {
    FEngSetTopLeft(pCheckIcon, GetTopLeftX(), GetTopLeftY() - 10.0f);
    FEngSetTopLeft(GetTitleObject(), GetTopLeftX() + 30.0f, GetTopLeftY());
    FEngSetTopLeftY(pTradeInPrice, GetTopLeftY());
    FEngSetBottomRightX(pTradeInPrice, GetDataPosX() + 150.0f);
    FEngSetTopLeftY(GetDataObject(), GetTopLeftY());
    FEngSetBottomRightX(GetDataObject(), GetDataPosX() + 40.0f);
    if (GetBacking() != nullptr) {
        FEngSetTopLeft(GetBacking(), GetTopLeftX() - GetBackingOffsetX(), GetTopLeftY() - GetBackingOffsetY());
    }
}

void FEShoppingCartItem::SetFocus(const char *parent_pkg) {
    FEngSetCurrentButton(parent_pkg, GetTitleObject());
    FEngSetScript(GetTitleObject(), FEHASH_HIGHLIGHT, true);
    FEngSetScript(GetDataObject(), FEHASH_HIGHLIGHT, true);
    FEngSetScript(pTradeInPrice, FEHASH_HIGHLIGHT, true);
    if (GetBacking() != nullptr) {
        FEngSetVisible(GetBacking());
        FEngSetScript(GetBacking(), FEHASH_HIGHLIGHT, true);
    }
}

void FEShoppingCartItem::UnsetFocus() {
    uint32 script = FEHASH_UNHIGHLIGHT;
    const uint32 FEObj_GREY = FEHASH_GREY;
    if (!TheItem->IsActive()) {
        script = FEObj_GREY;
    }
    FEngSetScript(GetTitleObject(), script, true);
    FEngSetScript(GetDataObject(), script, true);
    FEngSetScript(pTradeInPrice, script, true);
    if (GetBacking() != nullptr) {
        FEngSetInvisible(GetBacking());
        FEngSetScript(GetBacking(), FEHASH_UNHIGHLIGHT, true);
    }
}

void FEShoppingCartItem::SetCheckScripts() {
    if (TheItem->IsActive()) {
        const uint32 FEObj_CHECKED = FEHASH_CHECKED;
        FEngSetScript(pCheckIcon, FEObj_CHECKED, true);
    } else {
        const uint32 FEObj_UNCHECKED = FEHASH_UNCHECKED;
        FEngSetScript(pCheckIcon, FEObj_UNCHECKED, true);
    }
}

void FEShoppingCartItem::SetActiveScripts() {
    if (!TheItem->IsActive()) {
        const uint32 FEObj_GREY = FEHASH_GREY;
        FEngSetScript(pCheckIcon, FEObj_GREY, true);
    }
}

void FEShoppingCartItem::DrawPartName() {
    if (TheItem->GetBuyingPart()->IsPerformancePkg()) {
        Physics::Upgrades::Type phys_type = TheItem->GetBuyingPart()->GetPhysicsType();
        if (TheItem->GetBuyingPart()->GetUpgradeLevel() == PPL_LEVEL_JUNKMAN) {
            if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                FEPrintf(GetTitleObject(), "%s : %s", GetLocalizedString(GetPerfPkgCatHash(phys_type)), GetLocalizedString(0xedd14807));
            } else {
                FEPrintf(GetTitleObject(), "%s: %s", GetLocalizedString(GetPerfPkgCatHash(phys_type)), GetLocalizedString(0xedd14807));
            }
        } else {
            int level = TheItem->GetBuyingPart()->GetUpgradeLevel() - (gCarCustomizeManager.GetNumPackages(phys_type) - 6);
            if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                FEPrintf(GetTitleObject(), "%s : %s", GetLocalizedString(GetPerfPkgCatHash(phys_type)),
                         GetLocalizedString(GetPerfPkgLevelHash(level)));
            } else {
                FEPrintf(GetTitleObject(), "%s: %s", GetLocalizedString(GetPerfPkgCatHash(phys_type)),
                         GetLocalizedString(GetPerfPkgLevelHash(level)));
            }
        }
    } else {
        SelectablePart *part = TheItem->GetBuyingPart();
        switch (part->GetSlotID()) {
            case CARSLOTID_PAINT_RIM:
                if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                    FEPrintf(GetTitleObject(), "%s : %s %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), GetLocalizedString(0xb3100a3e),
                             GetLocalizedString(part->GetPart()->GetAppliedAttributeUParam(bStringHash("SPEECHCOLOUR"), 0)));
                } else {
                    FEPrintf(GetTitleObject(), "%s: %s %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), GetLocalizedString(0xb3100a3e),
                             GetLocalizedString(part->GetPart()->GetAppliedAttributeUParam(bStringHash("SPEECHCOLOUR"), 0)));
                }
                break;

            case CARSLOTID_BASE_PAINT: {
                uint32 paint_type = 0x452b5481;
                switch (part->GetPart()->GetBrandNameHash()) {
                    case 0x2daab07:
                        paint_type = 0xb6763cde;
                        break;
                    case 0x3797533:
                        paint_type = 0xb715070a;
                        break;
                    case 0xda27:
                        paint_type = 0xb3100a3e;
                        break;
                    case 0x3437a52:
                        break;
                }
                if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                    FEPrintf(GetTitleObject(), "%s : %s %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), GetLocalizedString(paint_type),
                             GetLocalizedString(part->GetPart()->GetAppliedAttributeUParam(bStringHash("SPEECHCOLOUR"), 0)));
                } else {
                    FEPrintf(GetTitleObject(), "%s: %s %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), GetLocalizedString(paint_type),
                             GetLocalizedString(part->GetPart()->GetAppliedAttributeUParam(bStringHash("SPEECHCOLOUR"), 0)));
                }
                break;
            }

            case CARSLOTID_DECAL_RIGHT_DOOR_LNUMBER: {
                ShoppingCartItem *left_num_item = gCarCustomizeManager.IsPartTypeInCart(CARSLOTID_DECAL_RIGHT_DOOR_LNUMBER);
                ShoppingCartItem *right_num_item = gCarCustomizeManager.IsPartTypeInCart(CARSLOTID_DECAL_RIGHT_DOOR_RNUMBER);
                if ((left_num_item != nullptr) && (right_num_item != nullptr)) {
                    CarPart *left_part = left_num_item->GetBuyingPart()->GetPart();
                    CarPart *right_part = right_num_item->GetBuyingPart()->GetPart();
                    if ((left_part != nullptr) && (right_part != nullptr)) {
                        if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                            FEPrintf(GetTitleObject(), "%s : %s%s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), left_part->GetName(),
                                     right_part->GetName());
                        } else {
                            FEPrintf(GetTitleObject(), "%s: %s%s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), left_part->GetName(),
                                     right_part->GetName());
                        }
                    } else {
                        if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                            FEPrintf(GetTitleObject(), "%s : %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                     GetLocalizedString(0xbe434a38));
                        } else {
                            FEPrintf(GetTitleObject(), "%s: %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                     GetLocalizedString(0xbe434a38));
                        }
                    }
                }
                break;
            }

            case CARSLOTID_DECAL_FRONT_WINDOW_TEX0:
            case CARSLOTID_DECAL_REAR_WINDOW_TEX0:
            case CARSLOTID_DECAL_LEFT_DOOR_TEX0:
            case CARSLOTID_DECAL_LEFT_DOOR_TEX1:
            case CARSLOTID_DECAL_LEFT_DOOR_TEX2:
            case CARSLOTID_DECAL_LEFT_DOOR_TEX3:
            case CARSLOTID_DECAL_LEFT_DOOR_TEX4:
            case CARSLOTID_DECAL_LEFT_DOOR_TEX5:
            case CARSLOTID_DECAL_RIGHT_DOOR_TEX0:
            case CARSLOTID_DECAL_RIGHT_DOOR_TEX1:
            case CARSLOTID_DECAL_RIGHT_DOOR_TEX2:
            case CARSLOTID_DECAL_RIGHT_DOOR_TEX3:
            case CARSLOTID_DECAL_RIGHT_DOOR_TEX4:
            case CARSLOTID_DECAL_RIGHT_DOOR_TEX5:
            case CARSLOTID_DECAL_LEFT_QUARTER_TEX0:
            case CARSLOTID_DECAL_RIGHT_QUARTER_TEX0:
                if (part->GetPart() == nullptr) {
                    if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                        FEPrintf(GetTitleObject(), "%s : %s - %s", GetLocalizedString(0x955980bc),
                                 GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), GetLocalizedString(0x7177dc17));
                    } else {
                        FEPrintf(GetTitleObject(), "%s: %s - %s", GetLocalizedString(0x955980bc),
                                 GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), GetLocalizedString(0x7177dc17));
                    }

                } else {
                    uint32 name_hash = part->GetPart()->GetBrandNameHash();
                    bool black = part->GetPart()->GetAppliedAttributeUParam(bStringHash("NAME"), 0) != 0;
                    uint32 slot_hash = 0;
                    switch (part->GetSlotID()) {
                        case CARSLOTID_DECAL_LEFT_DOOR_TEX0:
                        case CARSLOTID_DECAL_RIGHT_DOOR_TEX0:
                            slot_hash = 0x7d212cfa;
                            break;
                        case CARSLOTID_DECAL_LEFT_DOOR_TEX1:
                        case CARSLOTID_DECAL_RIGHT_DOOR_TEX1:
                            slot_hash = 0x7d212cfb;
                            break;
                        case CARSLOTID_DECAL_LEFT_DOOR_TEX2:
                        case CARSLOTID_DECAL_RIGHT_DOOR_TEX2:
                            slot_hash = 0x7d212cfc;
                            break;
                        case CARSLOTID_DECAL_LEFT_DOOR_TEX3:
                        case CARSLOTID_DECAL_RIGHT_DOOR_TEX3:
                            slot_hash = 0x7d212cfd;
                            break;
                        case CARSLOTID_DECAL_LEFT_DOOR_TEX4:
                        case CARSLOTID_DECAL_RIGHT_DOOR_TEX4:
                            slot_hash = 0x7d212cfe;
                            break;
                        case CARSLOTID_DECAL_LEFT_DOOR_TEX5:
                        case CARSLOTID_DECAL_RIGHT_DOOR_TEX5:
                            slot_hash = 0x7d212cff;
                            break;
                    }
                    if (slot_hash != 0) {
                        if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                            FEPrintf(GetTitleObject(), "%s : %s %s %s", GetLocalizedString(0x955980bc),
                                     GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), GetLocalizedString(slot_hash),
                                     part->GetPart()->GetName());
                        } else {
                            FEPrintf(GetTitleObject(), "%s: %s %s %s", GetLocalizedString(0x955980bc),
                                     GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), GetLocalizedString(slot_hash),
                                     part->GetPart()->GetName());
                        }
                    } else {
                        if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                            FEPrintf(GetTitleObject(), "%s : %s %s", GetLocalizedString(0x955980bc),
                                     GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), part->GetPart()->GetName());
                        } else {
                            FEPrintf(GetTitleObject(), "%s: %s %s", GetLocalizedString(0x955980bc),
                                     GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), part->GetPart()->GetName());
                        }
                    }
                }
                break;

            case CARSLOTID_BODY:
                if (part->GetPart()->HasAppliedAttribute(bStringHash("LANGUAGEHASH"))) {
                    if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                        FEPrintf(GetTitleObject(), "%s : %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                 GetLocalizedString(part->GetPart()->GetAppliedAttributeUParam(bStringHash("LANGUAGEHASH"), 0)));
                    } else {
                        FEPrintf(GetTitleObject(), "%s: %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                 GetLocalizedString(part->GetPart()->GetAppliedAttributeUParam(bStringHash("LANGUAGEHASH"), 0)));
                    }
                } else {
                    if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                        FEPrintf(GetTitleObject(), "%s : %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), part->GetPart()->GetName());
                    } else {
                        FEPrintf(GetTitleObject(), "%s: %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), part->GetPart()->GetName());
                    }
                }
                break;

            case CARSLOTID_FRONT_WHEEL:
                if (part->GetPart() != gCarCustomizeManager.GetStockCarPart(CARSLOTID_FRONT_WHEEL)) {
                    char sztemp[64];
                    bSNPrintf(sztemp, sizeof(sztemp), "%s", part->GetPart()->GetName());
                    int len = bStrLen(sztemp);
                    if (len > 0) {
                        for (int i = len; i >= len - 6; i--) {
                            sztemp[i] = 0;
                        }
                        if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                            FEPrintf(GetTitleObject(), "%s : %s %$d\"", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), sztemp,
                                     static_cast<signed char>(part->GetPart()->GetInnerRadius()));
                        } else {
                            FEPrintf(GetTitleObject(), "%s: %s %$d\"", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), sztemp,
                                     static_cast<signed char>(part->GetPart()->GetInnerRadius()));
                        }
                    }
                } else {
                    if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                        FEPrintf(GetTitleObject(), "%s : %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                 GetLocalizedString(0x60a662f5));
                    } else {
                        FEPrintf(GetTitleObject(), "%s: %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                 GetLocalizedString(0x60a662f5));
                    }
                }
                break;

            case CARSLOTID_SPOILER:
            case CARSLOTID_ROOF:
            case CARSLOTID_HOOD:
                if (part->GetPart()->HasAppliedAttribute(bStringHash("CARBONFIBRE"))) {
                    if (part->GetPart()->GetAppliedAttributeIParam(bStringHash("CARBONFIBRE"), 0) != 0) {
                        if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                            FEPrintf(GetTitleObject(), "%s : %s %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                     GetLocalizedString(0x5415b874),
                                     GetLocalizedString(part->GetPart()->GetAppliedAttributeUParam(bStringHash("LANGUAGEHASH"), 0)));
                        } else {
                            FEPrintf(GetTitleObject(), "%s: %s %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                     GetLocalizedString(0x5415b874),
                                     GetLocalizedString(part->GetPart()->GetAppliedAttributeUParam(bStringHash("LANGUAGEHASH"), 0)));
                        }
                    }
                } else if (part->GetPart()->HasAppliedAttribute(bStringHash("LANGUAGEHASH"))) {
                    if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                        FEPrintf(GetTitleObject(), "%s : %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                 GetLocalizedString(part->GetPart()->GetAppliedAttributeUParam(bStringHash("LANGUAGEHASH"), 0)));
                    } else {
                        FEPrintf(GetTitleObject(), "%s: %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                 GetLocalizedString(part->GetPart()->GetAppliedAttributeUParam(bStringHash("LANGUAGEHASH"), 0)));
                    }
                } else {
                    if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                        FEPrintf(GetTitleObject(), "%s : %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), part->GetPart()->GetName());
                    } else {
                        FEPrintf(GetTitleObject(), "%s: %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), part->GetPart()->GetName());
                    }
                }
                break;

            case CARSLOTID_VINYL_LAYER0:
                if (part->GetPart() != nullptr) {
                    if (part->GetPart()->HasAppliedAttribute(bStringHash("LANGUAGEHASH"))) {
                        if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                            FEPrintf(GetTitleObject(), "%s : %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                     GetLocalizedString(part->GetPart()->GetAppliedAttributeUParam(bStringHash("LANGUAGEHASH"), 0)));
                        } else {
                            FEPrintf(GetTitleObject(), "%s: %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                     GetLocalizedString(part->GetPart()->GetAppliedAttributeUParam(bStringHash("LANGUAGEHASH"), 0)));
                        }
                    } else {
                        if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                            FEPrintf(GetTitleObject(), "%s : %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                     part->GetPart()->GetName());
                        } else {
                            FEPrintf(GetTitleObject(), "%s: %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                     part->GetPart()->GetName());
                        }
                    }
                } else {
                    if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                        FEPrintf(GetTitleObject(), "%s : %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                 GetLocalizedString(0x60a662f5));
                    } else {
                        FEPrintf(GetTitleObject(), "%s: %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                 GetLocalizedString(0x60a662f5));
                    }
                }
                break;

            default:
                if (part->GetPart()->HasAppliedAttribute(bStringHash("LANGUAGEHASH"))) {
                    if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                        FEPrintf(GetTitleObject(), "%s : %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                 GetLocalizedString(part->GetPart()->GetAppliedAttributeUParam(bStringHash("LANGUAGEHASH"), 0)));
                    } else {
                        FEPrintf(GetTitleObject(), "%s: %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())),
                                 GetLocalizedString(part->GetPart()->GetAppliedAttributeUParam(bStringHash("LANGUAGEHASH"), 0)));
                    }

                } else {
                    if (GetCurrentLanguage() == eLANGUAGE_FRENCH) {
                        FEPrintf(GetTitleObject(), "%s : %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), part->GetPart()->GetName());
                    } else {
                        FEPrintf(GetTitleObject(), "%s: %s", GetLocalizedString(GetCarPartCatHash(part->GetSlotID())), part->GetPart()->GetName());
                    }
                }
                break;
        }
    }
}

uint32 FEShoppingCartItem::GetPerfPkgCatHash(Physics::Upgrades::Type phys_type) {
    uint32 type_hash = 0;
    switch (phys_type) {
        case Physics::Upgrades::PUT_TIRES:
            type_hash = 0x5aa9137;
            break;
        case Physics::Upgrades::PUT_BRAKES:
            type_hash = 0x91997ee8;
            break;
        case Physics::Upgrades::PUT_CHASSIS:
            type_hash = 0x6e101aa7;
            break;
        case Physics::Upgrades::PUT_TRANSMISSION:
            type_hash = 0x29aa74ba;
            break;
        case Physics::Upgrades::PUT_ENGINE:
            type_hash = 0x9853d9a6;
            break;
        case Physics::Upgrades::PUT_INDUCTION:
            if (gCarCustomizeManager.IsTurbo()) {
                type_hash = 0x5b1255c;
            } else {
                type_hash = 0xbb6812bb;
            }
            break;
        case Physics::Upgrades::PUT_NOS:
            type_hash = 0x4ce19aa4;
            break;
        default:
            break;
    }
    return type_hash;
}

uint32 FEShoppingCartItem::GetPerfPkgLevelHash(int level) {
    uint32 pkg_hash = 0x69c270c3;
    switch (level) {
        case PPL_LEVEL_1:
            pkg_hash = 0x69c270c4;
            break;
        case PPL_LEVEL_2:
            pkg_hash = 0x69c270c5;
            break;
        case PPL_LEVEL_3:
            pkg_hash = 0x69c270c6;
            break;
        case PPL_LEVEL_4:
            pkg_hash = 0x69c270c7;
            break;
        case PPL_LEVEL_5:
            pkg_hash = 0x69c270c8;
            break;
        case PPL_LEVEL_6:
            pkg_hash = 0x69c270c9;
            break;
    }
    return pkg_hash;
}

uint32 FEShoppingCartItem::GetCarPartCatHash(uint32 slot_id) {
    switch (slot_id) {
        case CARSLOTID_BODY:
            return 0x6134c218;
        case CARSLOTID_SPOILER:
            return 0x94e73021;
        case CARSLOTID_ROOF:
            return 0x61e8f83c;
        case CARSLOTID_HOOD:
            return 0x4d4a88d;
        case CARSLOTID_FRONT_WHEEL:
            return 0xf868eb0b;
        case CARSLOTID_BASE_PAINT:
            return 0x55da70c;
        case CARSLOTID_CUSTOM_HUD:
            return 0x78980a6b;
        case CARSLOTID_WINDOW_TINT:
            return 0xd32729a6;
        case CARSLOTID_PAINT_RIM:
            return 0xe126ff53;
        case CARSLOTID_DECAL_FRONT_WINDOW_TEX0:
            return 0x301dedd3;
        case CARSLOTID_DECAL_REAR_WINDOW_TEX0:
            return 0x48e6ca49;
        case CARSLOTID_DECAL_LEFT_DOOR_TEX0:
        case CARSLOTID_DECAL_LEFT_DOOR_TEX1:
        case CARSLOTID_DECAL_LEFT_DOOR_TEX2:
        case CARSLOTID_DECAL_LEFT_DOOR_TEX3:
        case CARSLOTID_DECAL_LEFT_DOOR_TEX4:
        case CARSLOTID_DECAL_LEFT_DOOR_TEX5:
            return 0x34367c86;
        case CARSLOTID_DECAL_RIGHT_DOOR_TEX0:
        case CARSLOTID_DECAL_RIGHT_DOOR_TEX1:
        case CARSLOTID_DECAL_RIGHT_DOOR_TEX2:
        case CARSLOTID_DECAL_RIGHT_DOOR_TEX3:
        case CARSLOTID_DECAL_RIGHT_DOOR_TEX4:
        case CARSLOTID_DECAL_RIGHT_DOOR_TEX5:
            return 0xddf80259;
        case CARSLOTID_DECAL_LEFT_QUARTER_TEX0:
            return 0x8a7697d6;
        case CARSLOTID_DECAL_RIGHT_QUARTER_TEX0:
            return 0xb1f9b0c9;
        case CARSLOTID_DECAL_RIGHT_DOOR_LNUMBER:
            return 0x6857e5ac;
        case CARSLOTID_VINYL_LAYER0:
            return 0xbfa52c55;
        default:
            return 0;
    }
}

CustomizeShoppingCart::CustomizeShoppingCart(ScreenConstructorData *sd) : UIWidgetMenu(sd) {
    bScrollWrapped = false;
    if (gCarCustomizeManager.IsCareerMode()) {
        iMaxWidgetsOnScreen = 4;
    } else {
        iMaxWidgetsOnScreen = 6;
    }
    Setup();
}

void CustomizeShoppingCart::NotificationMessage(u32 msg, FEObject *pobj, u32 param1, u32 param2) {
    UIWidgetMenu::NotificationMessage(msg, pobj, param1, param2);
    switch (msg) {
        case __PAD_BUTTON4__:
            ToggleChecked();
            RefreshHeader();
            break;
        case __PAD_ACCEPT__:
            if (!gCarCustomizeManager.DoesCartHaveActiveParts()) {
                gCarCustomizeManager.EmptyCart();
                gCarCustomizeManager.ResetPreview(); // TODO: not needed, EmptyCart already resets preview
                cFEng::Get()->QueueGameMessage(0xcf91aacd, pParentPkg, 0xFF);
                cFEng::Get()->QueuePackagePop(1);
            } else {
                if (CanCheckout()) {
                    uint32 blurb_hash = 0x71d9e710;
                    if (gCarCustomizeManager.IsCareerMode()) {
                        blurb_hash = 0x8ebaa44b;
                        if (gCarCustomizeManager.IsInBackRoom()) {
                            blurb_hash = 0x4810898;
                        }
                    }
                    DialogInterface::ShowTwoButtons(GetPackageName(), "", dialog_alert, LANGUAGE_COMMON_YES, LANGUAGE_COMMON_NO, dialog_message_yes,
                                                    dialog_message_no, dialog_message_no, first_dialog_button2, blurb_hash);
                } else {
                    DialogInterface::ShowOk(GetPackageName(), "", dialog_alert, 0xa984a42);
                }
            }
            break;
        case dialog_message_yes:
            gCarCustomizeManager.Checkout();
            cFEng::Get()->QueueGameMessage(0xcf91aacd, pParentPkg, 0xFF);
            cFEng::Get()->QueuePackagePop(1);
            break;
        case __PAD_BUTTON5__:
            UncheckAllItems();
            RefreshHeader();
            break;
        case __PAD_UP__:
        case __PAD_DOWN__:
            RefreshHeader();
            break;
        case __PAD_BACK__:
            ClearUncheckedItems();
            cFEng::Get()->QueueGameMessage(0x5a928018, pParentPkg, 0xFF);
            cFEng::Get()->QueuePackagePop(1);
            break;
    }
}

void CustomizeShoppingCart::ShowShoppingCart(const char *parent_pkg) {
    pParentPkg = parent_pkg;
    cFEng::Get()->QueuePackagePush(g_pCustomizeShoppingCartPkg, 0, 0, false);
}

void CustomizeShoppingCart::ExitShoppingCart() {
    if (gCarCustomizeManager.IsInBackRoom()) {
        gCarCustomizeManager.SetInBackRoom(false);
        FEManager::Get()->SetGarageType(GARAGETYPE_CUSTOMIZATION_SHOP);
    }
    cFEng::Get()->QueuePackageSwitch(g_pCustomizeMainPkg, 0, 0, false);
}

bool CustomizeShoppingCart::IsSlotIDNumberDecal(int slotID) {
    if (slotID == CARSLOTID_DECAL_RIGHT_DOOR_TEX6 || slotID == CARSLOTID_DECAL_RIGHT_DOOR_TEX7 || slotID == CARSLOTID_DECAL_LEFT_DOOR_TEX6 ||
        slotID == CARSLOTID_DECAL_LEFT_DOOR_TEX7) {
        return true;
    }
    return false;
}

void CustomizeShoppingCart::ToggleAllNumberDecals() {
    int numOptions = gCarCustomizeManager.GetNumCartItems();
    for (int i = 0; i < numOptions; i++) {
        ShoppingCartItem *si = gCarCustomizeManager.GetCartItem(i);
        if (si != nullptr) {
            SelectablePart *sp = si->GetBuyingPart();
            if (sp != nullptr) {
                int slotID = sp->GetSlotID();
                if (IsSlotIDNumberDecal(slotID)) {
                    si->ToggleActive();
                }
            }
        }
    }
}

void CustomizeShoppingCart::ToggleChecked() {
    if (GetCurrentItem() != nullptr) {
        ShoppingCartItem *item = GetCurrentItem()->GetItem();
        if (item != nullptr) {
            item->ToggleActive();
            SelectablePart *spart = item->GetBuyingPart();
            if (spart != nullptr) {
                int slotID = spart->GetSlotID();
                if (IsSlotIDNumberDecal(slotID)) {
                    ToggleAllNumberDecals();
                    item->ToggleActive();
                }
            }
        }
        GetCurrentItem()->SetCheckScripts();
        GetCurrentItem()->Draw();
    }
}

bool CustomizeShoppingCart::CanCheckout() {
    if (gCarCustomizeManager.IsCareerMode()) {
        if (gCarCustomizeManager.IsInBackRoom()) {
            return true;
        }
        return gCarCustomizeManager.GetCartTotal(CCT_TOTAL) <= FEDatabase->GetCareerSettings()->GetCash();
    }
    return true;
}

void CustomizeShoppingCart::SetMarkerData(int num, ShoppingCartItem *item, int num_markers) {
    const u32 FEObj_GREY = FEHASH_GREY;
    const u32 FEObj_NORMAL = FEHASH_NORMAL;

    FEngSetScript(GetPackageName(), FEngHashString("MARKER_GROUP_%d", num), num_markers == 0 ? FEObj_GREY : FEObj_NORMAL, true);

    FEPrintf(GetPackageName(), FEngHashString("MARKER_NUM_%d", num), "%$d", num_markers);

    FEPrintf(GetPackageName(), FEngHashString("MARKER_BLOOM_%d", num), "%$d", num_markers);
}

int CustomizeShoppingCart::GetNumMarkersSpending(uint32 slot_id) {
    ShoppingCartItem *item = gCarCustomizeManager.IsPartTypeInCart(slot_id);
    return static_cast<int>(item != nullptr && item->IsActive());
}

// UNSOLVED
void CustomizeShoppingCart::SetMarkerAmounts() {
    const u32 FEObj_GREY = FEHASH_GREY;
    const u32 FEObj_NORMAL = FEHASH_NORMAL;
    if (gCarCustomizeManager.IsInPerformance()) {
        static int phys_type[Physics::Upgrades::PUT_MAX] = {
            Physics::Upgrades::PUT_BRAKES,  Physics::Upgrades::PUT_ENGINE, Physics::Upgrades::PUT_NOS,          Physics::Upgrades::PUT_INDUCTION,
            Physics::Upgrades::PUT_CHASSIS, Physics::Upgrades::PUT_TIRES,  Physics::Upgrades::PUT_TRANSMISSION,
        };
        static int markers[Physics::Upgrades::PUT_MAX] = {
            FEMarkerManager::MARKER_BRAKES,  FEMarkerManager::MARKER_ENGINE, FEMarkerManager::MARKER_NOS,          FEMarkerManager::MARKER_INDUCTION,
            FEMarkerManager::MARKER_CHASSIS, FEMarkerManager::MARKER_TIRES,  FEMarkerManager::MARKER_TRANSMISSION,
        };
        int num_thingies = Physics::Upgrades::PUT_MAX;
        for (int i = 0; i < num_thingies; i++) {
            ShoppingCartItem *item = gCarCustomizeManager.IsPartTypeInCart(phys_type[i]);
            int num = TheFEMarkerManager.GetNumMarkers(static_cast<FEMarkerManager::ePossibleMarker>(markers[i]), 0);
            if (item != nullptr && item->IsActive()) {
                num--;
            }
            SetMarkerData(i + 1, item, num);
        }
    } else if (gCarCustomizeManager.IsInParts()) {
        static int slot_id[5] = {CARSLOTID_BODY, CARSLOTID_HOOD, CARSLOTID_SPOILER, CARSLOTID_FRONT_WHEEL, CARSLOTID_ROOF};
        static int markers[5] = {
            FEMarkerManager::MARKER_BODY, FEMarkerManager::MARKER_HOOD,       FEMarkerManager::MARKER_SPOILER,
            FEMarkerManager::MARKER_RIMS, FEMarkerManager::MARKER_ROOF_SCOOP,
        };
        int num_thingies = 5;
        for (int i = 0; i < num_thingies; i++) {
            ShoppingCartItem *item = gCarCustomizeManager.IsPartTypeInCart(slot_id[i]);
            int num = TheFEMarkerManager.GetNumMarkers(static_cast<FEMarkerManager::ePossibleMarker>(markers[i]), 0);
            if (item != nullptr && item->IsActive()) {
                num--;
            }
            SetMarkerData(i + 1, item, num);
        }
        FEngSetInvisible(GetPackageName(), 0x47df0e22);
        FEngSetInvisible(GetPackageName(), 0x47df0e23);
    } else {
        ShoppingCartItem *item = gCarCustomizeManager.IsPartTypeInCart(CARSLOTID_VINYL_LAYER0);
        int num = TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_VINYL, 0);
        if (item != nullptr && item->IsActive()) {
            num--;
        }
        SetMarkerData(1, item, num);

        num = GetNumMarkersSpending(CARSLOTID_DECAL_FRONT_WINDOW_TEX0);
        num += GetNumMarkersSpending(CARSLOTID_DECAL_REAR_WINDOW_TEX0);
        num += GetNumMarkersSpending(CARSLOTID_DECAL_LEFT_DOOR_TEX0);
        num += GetNumMarkersSpending(CARSLOTID_DECAL_LEFT_DOOR_TEX1);
        num += GetNumMarkersSpending(CARSLOTID_DECAL_LEFT_DOOR_TEX2);
        num += GetNumMarkersSpending(CARSLOTID_DECAL_LEFT_DOOR_TEX3);
        num += GetNumMarkersSpending(CARSLOTID_DECAL_LEFT_DOOR_TEX4);
        num += GetNumMarkersSpending(CARSLOTID_DECAL_LEFT_DOOR_TEX5);
        num += GetNumMarkersSpending(CARSLOTID_DECAL_RIGHT_DOOR_TEX0);
        num += GetNumMarkersSpending(CARSLOTID_DECAL_RIGHT_DOOR_TEX1);
        num += GetNumMarkersSpending(CARSLOTID_DECAL_RIGHT_DOOR_TEX2);
        num += GetNumMarkersSpending(CARSLOTID_DECAL_RIGHT_DOOR_TEX3);
        num += GetNumMarkersSpending(CARSLOTID_DECAL_RIGHT_DOOR_TEX4);
        num += GetNumMarkersSpending(CARSLOTID_DECAL_RIGHT_DOOR_TEX5);
        num += GetNumMarkersSpending(CARSLOTID_DECAL_LEFT_QUARTER_TEX0);
        num += GetNumMarkersSpending(CARSLOTID_DECAL_RIGHT_QUARTER_TEX0);
        num = TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_DECAL, 0) - num;
        SetMarkerData(2, item, num);

        item = gCarCustomizeManager.IsPartTypeInCart(CARSLOTID_BASE_PAINT);
        num = TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_PAINT, 0);
        if (item != nullptr && item->IsActive()) {
            num--;
        }
        SetMarkerData(3, item, num);

        item = gCarCustomizeManager.IsPartTypeInCart(CARSLOTID_CUSTOM_HUD);
        num = TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_CUSTOM_HUD, 0);
        if (item != nullptr && item->IsActive()) {
            num--;
        }
        SetMarkerData(4, item, num);

        FEngSetInvisible(GetPackageName(), 0x47df0e21);
        FEngSetInvisible(GetPackageName(), 0x47df0e22);
        FEngSetInvisible(GetPackageName(), 0x47df0e23);
    }
}

void CustomizeShoppingCart::RefreshHeader() {
    if (this->GetCurrentItem() != nullptr) {
        FEngSetVisible(GetPackageName(), 0x842b0e89);
        uint32 check_text = 0xd57c95e1;
        if (this->GetCurrentItem()->GetItem()->IsActive()) {
            FEngSetLanguageHash(GetPackageName(), check_text, 0x5dabcbc0);
        } else {
            FEngSetLanguageHash(GetPackageName(), check_text, 0x28feadd);
        }
    } else {
        FEngSetInvisible(GetPackageName(), 0x842b0e89);
    }
    HeatMeter.SetCurrent(gCarCustomizeManager.GetActualHeat());
    HeatMeter.SetPreview(gCarCustomizeManager.GetCartHeat());
    HeatMeter.Draw();
    if (gCarCustomizeManager.IsCareerMode()) {
        if (gCarCustomizeManager.IsInBackRoom()) {
            SetMarkerAmounts();
            int num_markers;
            if (gCarCustomizeManager.IsInParts()) {
                FEngSetLanguageHash(GetPackageName(), 0x8cdcb8ed, 0xa03a752f);
                FEngSetLanguageHash(GetPackageName(), 0xd3d3b1f4, 0x4ac68298);
                num_markers = TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_BODY, 0);
                num_markers += TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_HOOD, 0);
                num_markers += TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_SPOILER, 0);
                num_markers += TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_RIMS, 0);
                num_markers += TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_ROOF_SCOOP, 0);
            } else if (gCarCustomizeManager.IsInPerformance()) {
                FEngSetLanguageHash(GetPackageName(), 0x8cdcb8ed, 0x358db897);
                FEngSetLanguageHash(GetPackageName(), 0xd3d3b1f4, 0x68342700);
                num_markers = TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_BRAKES, 0);
                num_markers += TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_ENGINE, 0);
                num_markers += TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_NOS, 0);
                num_markers += TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_INDUCTION, 0);
                num_markers += TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_CHASSIS, 0);
                num_markers += TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_TIRES, 0);
                num_markers += TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_TRANSMISSION, 0);
            } else {
                FEngSetLanguageHash(GetPackageName(), 0x8cdcb8ed, 0x93296e59);
                FEngSetLanguageHash(GetPackageName(), 0xd3d3b1f4, 0x78f1c602);
                num_markers = TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_VINYL, 0);
                num_markers += TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_DECAL, 0);
                num_markers += TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_PAINT, 0);
                num_markers += TheFEMarkerManager.GetNumMarkers(FEMarkerManager::MARKER_CUSTOM_HUD, 0);
            }
            FEPrintf(GetPackageName(), 0xd1497a06, "%$d", gCarCustomizeManager.GetCartTotal(CCT_PART_PRICES));
            FEPrintf(GetPackageName(), 0x18661565, "%$d", num_markers - gCarCustomizeManager.GetCartTotal(CCT_PART_PRICES));
        } else {
            FEPrintf(GetPackageName(), 0xd1497a06, "%$d", gCarCustomizeManager.GetCartTotal(CCT_PART_PRICES));
            FEPrintf(GetPackageName(), 0x34f7c0e8, "%$d", gCarCustomizeManager.GetCartTotal(CCT_TRADE_IN));
            int total = gCarCustomizeManager.GetCartTotal(CCT_TOTAL);
            FEPrintf(GetPackageName(), 0x18661565, "%$d", total);
            int remaining = FEDatabase->GetCareerSettings()->GetCash() - total;
            FEPrintf(GetPackageName(), 0x8531e22e, "%$d", remaining);
        }
    } else {
        FEngSetInvisible(GetPackageName(), 0x9ea22e0b);
    }
}

void CustomizeShoppingCart::AddItem(ShoppingCartItem *item) {
    FEShoppingCartItem *option = new ("FEShoppingCartItem", 0) FEShoppingCartItem(item);
    option->SetTitleObject(GetCurrentFEString("PART_NAME_"));
    option->SetDataObject(GetCurrentFEString("PRICE_"));
    option->SetBacking(GetCurrentFEObject(pBackingName));
    option->SetCheckIcon(GetCurrentFEImage("CHECK_ICON_"));
    option->SetTradeInString(GetCurrentFEString("TRADE_IN_"));
    option->SetTopLeft(vLastWidgetPos);
    option->SetMaxTitleSize(vMaxTitleSize);
    option->SetMaxDataSize(vMaxDataSize);
    option->SetDataPos(vDataPos);
    Options.AddTail(option);
    iIndexToAdd++;
    IncrementStartPos();
    option->Show();
    option->Draw();
    option->Position();
    float data_left = FEngGetTopLeftX(option->GetDataObject());
    float data_right = data_left + FEngGetSizeX(option->GetDataObject());
    option->SetWidth(bAbs(option->GetTopLeftX() - data_right));
}

// UNSOLVED
void CustomizeShoppingCart::ClearUncheckedItems() {
    ShoppingCartItem *item = gCarCustomizeManager.GetFirstCartItem();
    while (item != gCarCustomizeManager.GetLastCartItem()->GetNext()) {
        if (!item->IsActive()) {
            if (item->GetBuyingPart()->GetSlotID() == CARSLOTID_VINYL_LAYER0) {
                ShoppingCartItem *color_item = gCarCustomizeManager.GetFirstCartItem();
                while (color_item != gCarCustomizeManager.GetLastCartItem()->GetNext()) {
                    switch (color_item->GetBuyingPart()->GetSlotID()) {
                        case CARSLOTID_VINYL_COLOUR0_0:
                        case CARSLOTID_VINYL_COLOUR0_1:
                        case CARSLOTID_VINYL_COLOUR0_2:
                        case CARSLOTID_VINYL_COLOUR0_3: {
                            ShoppingCartItem *color_temp = color_item->GetNext();
                            gCarCustomizeManager.RemoveFromCart(color_item);
                            color_item = color_temp;
                            break;
                        }

                        default:
                            color_item = color_item->GetNext();
                            break;
                    }
                }
            }
            ShoppingCartItem *temp = item->GetNext();
            gCarCustomizeManager.RemoveFromCart(item);
            item = temp;
        } else {
            item = item->GetNext();
        }
    }
    gCarCustomizeManager.ResetPreview();
}

void CustomizeShoppingCart::UncheckAllItems() {
    ShoppingCartItem *cart_item = gCarCustomizeManager.GetFirstCartItem();
    while (cart_item != gCarCustomizeManager.GetLastCartItem()->GetNext()) {
        if (cart_item->IsActive()) {
            cart_item->ToggleActive();
        }
        cart_item = cart_item->GetNext();
    }
    for (FEShoppingCartItem *item = static_cast<FEShoppingCartItem *>(Options.GetHead()); item != Options.EndOfList();
         item = static_cast<FEShoppingCartItem *>(item->GetNext())) {
        item->SetCheckScripts();
        item->Draw();
    }
}

void CustomizeShoppingCart::SetMarkerImages() {
    if (gCarCustomizeManager.IsInPerformance()) {
        FEngSetTextureHash(GetPackageName(), 0xeb957471, 0x4887f351);
        FEngSetTextureHash(GetPackageName(), 0xeb957472, 0x4f424e0f);
        FEngSetTextureHash(GetPackageName(), 0xeb957473, 0x6fea04c8);
        FEngSetTextureHash(GetPackageName(), 0xeb957474, 0x8e284227);
        FEngSetTextureHash(GetPackageName(), 0xeb957475, 0x190eb6);
        FEngSetTextureHash(GetPackageName(), 0xeb957476, 0x7373f1ef);
        FEngSetTextureHash(GetPackageName(), 0xeb957477, 0xd142d3e3);
    } else if (gCarCustomizeManager.IsInParts()) {
        FEngSetTextureHash(GetPackageName(), 0xeb957471, 0xaf393dba);
        FEngSetTextureHash(GetPackageName(), 0xeb957472, 0xf375276e);
        FEngSetTextureHash(GetPackageName(), 0xeb957473, 0xc51a4f62);
        FEngSetTextureHash(GetPackageName(), 0xeb957474, 0xc19491cc);
        FEngSetTextureHash(GetPackageName(), 0xeb957475, 0x25a4375e);
        FEngSetInvisible(GetPackageName(), 0x47df0e22);
        FEngSetInvisible(GetPackageName(), 0x47df0e23);
    } else {
        FEngSetTextureHash(GetPackageName(), 0xeb957471, 0xd35f04c0);
        FEngSetTextureHash(GetPackageName(), 0xeb957472, 0xa9135927);
        FEngSetTextureHash(GetPackageName(), 0xeb957473, 0xdb89e17);
        FEngSetTextureHash(GetPackageName(), 0xeb957474, 0x8ba602fc);
        FEngSetInvisible(GetPackageName(), 0x47df0e21);
        FEngSetInvisible(GetPackageName(), 0x47df0e22);
        FEngSetInvisible(GetPackageName(), 0x47df0e23);
    }
}

void CustomizeShoppingCart::Setup() {
    HeatMeter.Init(GetPackageName(), "HEAT_METER", 1.0f, 5.0f, gCarCustomizeManager.GetActualHeat(), gCarCustomizeManager.GetCartHeat());

    ShoppingCartItem *item = gCarCustomizeManager.GetFirstCartItem();
    for (ShoppingCartItem *item = gCarCustomizeManager.GetFirstCartItem(); item != gCarCustomizeManager.GetLastCartItem()->GetNext();
         item = item->GetNext()) {
        switch (item->GetBuyingPart()->GetSlotID()) {
            case CARSLOTID_VINYL_COLOUR0_0:
            case CARSLOTID_VINYL_COLOUR0_1:
            case CARSLOTID_VINYL_COLOUR0_2:
            case CARSLOTID_VINYL_COLOUR0_3:
            case CARSLOTID_DECAL_LEFT_DOOR_LNUMBER:
            case CARSLOTID_DECAL_LEFT_DOOR_RNUMBER:
            // case CARSLOTID_DECAL_RIGHT_DOOR_LNUMBER: // *NOT* LNUMBER
            case CARSLOTID_DECAL_RIGHT_DOOR_RNUMBER:
            case CARSLOTID_HUD_BACKING_COLOUR:
            case CARSLOTID_HUD_NEEDLE_COLOUR:
            case CARSLOTID_HUD_CHARACTER_COLOUR:
                break;
            default:
                AddItem(item);
                break;
        }
    }

    if (gCarCustomizeManager.IsInBackRoom()) {
        SetMarkerImages();
    }

    SetInitialOption(0);

    for (FEShoppingCartItem *item = static_cast<FEShoppingCartItem *>(Options.GetHead());
         item != static_cast<FEShoppingCartItem *>(Options.EndOfList()); item = static_cast<FEShoppingCartItem *>(item->GetNext())) {
        item->SetCheckScripts();
        item->SetActiveScripts();
    }

    RefreshHeader();
}

CustomizeCategoryScreen::CustomizeCategoryScreen(ScreenConstructorData *sd)
    : IconScrollerMenu(sd), //
      bBackingOut(false),   //
      BackToPkg(nullptr),   //
      HeatMeter() {
    Category = sd->Arg & 0xFFFF;
    FromCategory = static_cast<int>(static_cast<short>(sd->Arg >> 16));
    if (Category != 0 || !gCarCustomizeManager.IsInBackRoom()) {
        GarageMainScreen::GetInstance()->SetCustomizationCategory(Category);
    }

    HeatMeter.Init(GetPackageName(), "HEAT_METER", 1.0f, 5.0f, gCarCustomizeManager.GetActualHeat(), gCarCustomizeManager.GetCartHeat());
}

CustomizeCategoryScreen::~CustomizeCategoryScreen() {}

void CustomizeCategoryScreen::RefreshHeader() {
    IconScrollerMenu::RefreshHeader();
    const u32 FEObj_APPEAR = FEHASH_APPEAR;
    uint32 unlock_status = static_cast<CustomizeMainOption *>(Options.GetCurrentOption())->UnlockStatus;
    if (unlock_status == 2) {
        FEngSetVisible(GetPackageName(), 0xcffb7033);
        FEngSetTextureHash(GetPackageName(), 0xcffb7033, 0xf0574bb2);
        FEngSetScript(GetPackageName(), 0xcffb7033, FEObj_APPEAR, true);
    } else if (unlock_status == 3) {
        FEngSetVisible(GetPackageName(), 0xcffb7033);
        FEngSetTextureHash(GetPackageName(), 0xcffb7033, 0xcffb7033);
        FEngSetScript(GetPackageName(), 0xcffb7033, FEObj_APPEAR, true);
    } else {
        FEngSetInvisible(GetPackageName(), 0xcffb7033);
    }
    if (gCarCustomizeManager.IsCareerMode()) {
        HeatMeter.SetCurrent(gCarCustomizeManager.GetActualHeat());
        HeatMeter.SetPreview(gCarCustomizeManager.GetCartHeat());
        HeatMeter.Draw();
        if (gCarCustomizeManager.IsInBackRoom()) {
            FEngSetLanguageHash(GetPackageName(), 0x63ca8308, GetMarkerNameFromCategory(static_cast<eCustomizeCategory>(Category)));
            FEPrintf(GetPackageName(), 0x83e3cd39, "%$d", GetNumMarkersFromCategory(static_cast<eCustomizeCategory>(Category)));
            FEPrintf(GetPackageName(), 0x23d918fe, "%$d", TheFEMarkerManager.GetNumCustomizeMarkers());
        } else {
            FEPrintf(GetPackageName(), 0x7a6d2f71, "%$d", gCarCustomizeManager.GetCartTotal(CCT_TOTAL));
            FEPrintf(GetPackageName(), 0xc60adcfd, "%$d", FEDatabase->GetCareerSettings()->GetCash());
        }
    } else {
        HeatMeter.SetVisibility(false);
        FEngSetInvisible(GetPackageName(), 0x8d1559a4);
    }
}

int CustomizeCategoryScreen::AddCustomOption(const char *to_pkg, unsigned int tex_hash, unsigned int name_hash, unsigned int to_cat) {
    if (gCarCustomizeManager.IsCareerMode()) {
        if (gCarCustomizeManager.IsInBackRoom()) {
            if (gCarCustomizeManager.IsCategoryLocked(to_cat, true)) {
                return -1;
            }
        }
    }
    CustomizeMainOption *opt = new ("CustomizeMainOption", 0) CustomizeMainOption(to_pkg, tex_hash, name_hash, to_cat, Category);
    AddOption(opt);
    if (gCarCustomizeManager.IsCategoryLocked(to_cat, false)) {
        opt->UnlockStatus = CPS_LOCKED;
    } else if (gCarCustomizeManager.IsCategoryNew(to_cat)) {
        opt->UnlockStatus = CPS_NEW;
    }
    return Options.GetIndexToAdd() - 3;
}

void CustomizeCategoryScreen::NotificationMessage(u32 msg, FEObject *pobj, u32 param1, u32 param2) {
    IconScrollerMenu::NotificationMessage(msg, pobj, param1, param2);
    switch (msg) {
        case __PAD_START__:
            CustomizeShoppingCart::ShowShoppingCart(GetPackageName());
            break;
        case FEHASH_EXITCOMPLETE:
            if (!bBackingOut) {
                break;
            }
            cFEng::Get()->QueuePackageSwitch(BackToPkg, FromCategory | (Category << 16), 0, false);
            break;
        case __PAD_BACK__: {
            bool leave = true;
            switch (Category) {
                case CC_PARTS:
                case CC_PERFORMANCE:
                case CC_VISUAL:
                    if (gCarCustomizeManager.DoesCartHaveActiveParts()) {
                        cFEng::Get()->QueueGameMessage(0x1720b124, GetPackageName(), 0xFF);
                        leave = false;
                        Options.SetReactToInput(true);
                    } else {
                        gCarCustomizeManager.EmptyCart();
                    }
                    break;
            }
            if (leave) {
                bBackingOut = true;
                const u32 FEObj_leavescreen = 0x587c018b;
                cFEng::Get()->QueuePackageMessage(FEObj_leavescreen, GetPackageName(), nullptr);
            }
            break;
        }
        case __PAD_BUTTON0__: {
            CustomizeMainOption *opt = static_cast<CustomizeMainOption *>(Options.GetCurrentOption());
            Showcase::FromArgs = Category | (opt->Category << 16);
            Showcase::FromPackage = GetPackageName();
            cFEng::Get()->QueuePackageSwitch("Showcase.fng", reinterpret_cast<int>(gCarCustomizeManager.GetTuningCar()), 0, false);
            break;
        }
        case dialog_message_cancelled:
            Options.SetReactToInput(true);
            break;
        case 0x7a318ee0: {
            gCarCustomizeManager.EmptyCart();
            const u32 FEObj_leavescreen = 0x587c018b;
            cFEng::Get()->QueuePackageMessage(FEObj_leavescreen, GetPackageName(), nullptr);
            break;
        }
        case 0x1720b124:
            CustomizeShoppingCart::ShowShoppingCart(GetPackageName());
            break;
    }
}

void SetStockPartOption::React(const char *pkg_name, uint32 data, FEObject *obj, uint32 param1, uint32 param2) {
    if (!ThePart->IsInstalled()) {
        gCarCustomizeManager.AddToCart(ThePart);
        ThePart->SetInCart();
    }
}

CustomizeSub::CustomizeSub(ScreenConstructorData *sd)
    : CustomizeCategoryScreen(sd), //
      InstalledPartOptionIndex(0), //
      InCartPartOptionIndex(0),    //
      TitleHash(0) {
    Setup();
    gCarCustomizeManager.ResetPreview();
}

void CustomizeSub::NotificationMessage(u32 msg, FEObject *pobj, u32 param1, u32 param2) {
    uint32 to_cat = static_cast<CustomizeMainOption *>(Options.GetCurrentOption())->Category & 0xFFFF;

    if (Category != CC_VISUAL || to_cat != CC_RIM_PAINT || msg != __BUTTON_PRESSED__) {
        CustomizeCategoryScreen::NotificationMessage(msg, pobj, param1, param2);
    }

    switch (msg) {
        case 0x5a928018: {
            CustomizeMainOption *opt = FindInCartOption();
            if (opt != nullptr) {
                int slot_id = 0;
                switch (opt->Category) {
                    case CC_RIM_BRANDS:
                        slot_id = CARSLOTID_FRONT_WHEEL;
                        break;
                    case CC_VINYL_TYPES:
                        slot_id = CARSLOTID_VINYL_LAYER0;
                        break;
                }
                if (slot_id == 0)
                    return;
                if (gCarCustomizeManager.IsPartTypeInCart(slot_id) != nullptr)
                    return;
                InCartPartOptionIndex = 0;
                RefreshHeader();
            }
            break;
        }
        case __BUTTON_PRESSED__: {
            switch (to_cat) {
                case CC_DECAL_WINDSHIELD:
                case CC_DECAL_REAR_WINDOW:
                case CC_DECAL_LEFT_DOOR:
                case CC_DECAL_RIGHT_DOOR:
                case CC_DECAL_LEFT_QP:
                case CC_DECAL_RIGHT_QP:
                    CustomizeDecals::CurrentDecalLocation = to_cat;
                    break;
            }

            CustomizeMainOption *copt = static_cast<CustomizeMainOption *>(Options.GetCurrentOption());
            copt->IsStockOption();
            bool stockOption = copt->IsStockOption();

            if (stockOption && static_cast<SetStockPartOption *>(copt)->ThePart->IsInstalled() && InCartPartOptionIndex != 0) {
                int slot_id = 0;
                switch (static_cast<unsigned short>(copt->Category)) {
                    case CC_RIM_BRAND_STOCK:
                        slot_id = CARSLOTID_FRONT_WHEEL;
                        break;
                    case CC_VINYL_GROUP_STOCK:
                        slot_id = CARSLOTID_VINYL_LAYER0;
                        for (int i = 0; i <= 2; i++) {
                            int color_slot = CARSLOTID_VINYL_COLOUR_FIRST + i;
                            ShoppingCartItem *item = gCarCustomizeManager.IsPartTypeInCart(color_slot);
                            if (item != nullptr) {
                                gCarCustomizeManager.RemoveFromCart(item);
                            }
                        }
                        break;
                }
                if (slot_id != 0) {
                    ShoppingCartItem *item = gCarCustomizeManager.IsPartTypeInCart(slot_id);
                    if (item != nullptr) {
                        gCarCustomizeManager.RemoveFromCart(item);
                        InCartPartOptionIndex = 0;
                        RefreshHeader();
                    }
                }
            }

            if (bStrICmp(GetPackageName(), g_pCustomizeSubTopPkg) == 0 || bStrICmp(GetPackageName(), g_pCustomizeSubPkg) == 0) {
                bool ok_to_leave = false;
                switch (Category) {
                    case CC_VISUAL:
                        if (to_cat == CC_RIM_PAINT) {
                            CarPart *stock_rim = gCarCustomizeManager.GetStockCarPart(CARSLOTID_FRONT_WHEEL);
                            CarPart *installed = gCarCustomizeManager.GetInstalledCarPart(CARSLOTID_FRONT_WHEEL);
                            if (stock_rim == installed) {
                                DialogInterface::ShowOneButton(GetPackageName(), "", dialog_alert, 0x417b2601, dialog_message_cancelled, 0xbdb19a9f);
                            } else {
                                CustomizeMainOption *opt = static_cast<CustomizeMainOption *>(Options.GetCurrentOption());
                                cFEng::Get()->QueuePackageSwitch(opt->ToPkg, opt->Category, 0, false);
                                ok_to_leave = true;
                            }
                        }
                        break;
                    case CC_RIM_BRANDS:
                        if (Options.GetCurrentIndex() == 1) {
                            ShoppingCartItem *item = gCarCustomizeManager.IsPartTypeInCart(CARSLOTID_FRONT_WHEEL);
                            if (item != nullptr) {
                                CarPart *car_part = item->GetBuyingPart()->GetPart();
                                InCartPartOptionIndex = GetRimBrandIndex(car_part->GetBrandNameHash());
                            }
                            CarPart *car_part = gCarCustomizeManager.GetInstalledCarPart(CARSLOTID_FRONT_WHEEL);
                            if (car_part != nullptr) {
                                InstalledPartOptionIndex = GetRimBrandIndex(car_part->GetBrandNameHash());
                            }
                            Options.SetReactToInput(true);
                            RefreshHeader();
                        } else {
                            ok_to_leave = true;
                        }
                        break;
                    case CC_VINYL_TYPES:
                        if (Options.GetCurrentIndex() == 1) {
                            ShoppingCartItem *item = gCarCustomizeManager.IsPartTypeInCart(CARSLOTID_VINYL_LAYER0);
                            if (item != nullptr) {
                                CarPart *car_part = item->GetBuyingPart()->GetPart();
                                if (car_part != nullptr) {
                                    InCartPartOptionIndex = GetVinylGroupIndex(car_part->GetGroupNumber() & 0x1f);
                                } else {
                                    InCartPartOptionIndex = 1;
                                }
                            }
                            CarPart *car_part = gCarCustomizeManager.GetInstalledCarPart(CARSLOTID_VINYL_LAYER0);
                            if (car_part != nullptr) {
                                InstalledPartOptionIndex = GetVinylGroupIndex(car_part->GetGroupNumber() & 0x1f);
                            } else {
                                InstalledPartOptionIndex = 1;
                            }
                            Options.SetReactToInput(true);
                            RefreshHeader();
                        } else {
                            ok_to_leave = true;
                        }
                        break;
                    default:
                        ok_to_leave = true;
                        break;
                }
                if (ok_to_leave) {
                    const u32 FEObj_leavescreen = 0x587c018b;
                    cFEng::Get()->QueuePackageMessage(FEObj_leavescreen, GetPackageName(), nullptr);
                }
            }
            break;
        }
        case __PAD_BUTTON4__:
            if (gCarCustomizeManager.IsCareerMode())
                return;
            if (Category == CC_PERFORMANCE) {
                DialogInterface::ShowTwoButtons(GetPackageName(), "", dialog_confirmation, LANGUAGE_COMMON_YES, LANGUAGE_COMMON_NO, 0x6820e23e,
                                                dialog_message_cancelled, first_dialog_button1, 0x892cb612);
                RefreshHeader();
            }
            break;
        case 0x6820e23e:
            gCarCustomizeManager.MaxOutPerformance();
            RefreshHeader();
            break;
        case dialog_message_cancelled: // TODO: should probably get from hash
            Options.SetReactToInput(true);
            RefreshHeader();
            break;
        case 0xcf91aacd:
            CustomizeShoppingCart::ExitShoppingCart();
            return;
    }
}

void CustomizeSub::RefreshHeader() {
    CustomizeCategoryScreen::RefreshHeader();
    char sztemp[64];
    bSNPrintf(sztemp, sizeof(sztemp), "%s", GetLocalizedString(TitleHash));
    eLanguages cLang = GetCurrentLanguage();
    if (cLang != eLANGUAGE_GERMAN && cLang != eLANGUAGE_FINNISH) {
        int n = 0;
        while (sztemp[n] != 0) {
            sztemp[n] = bToLower(sztemp[n]);
            n++;
        }
    }
    const u32 FEObj_TITLEGROUP = __TITLE_GROUP__;
    FEPrintf(GetPackageName(), FEObj_TITLEGROUP, "%s", sztemp);
    if (Category == CC_RIM_BRANDS || Category == CC_VINYL_TYPES) {
        int index = Options.GetCurrentIndex();
        if (index == InCartPartOptionIndex) {
            FEngSetVisible(GetPackageName(), 0xd0582feb);
            FEngSetTextureHash(GetPackageName(), 0xd0582feb, 0x1a777e25);
        } else if (index == InstalledPartOptionIndex) {
            FEngSetVisible(GetPackageName(), 0xd0582feb);
            FEngSetTextureHash(GetPackageName(), 0xd0582feb, 0x696ae039);
        } else {
            FEngSetInvisible(GetPackageName(), 0xd0582feb);
        }
    } else {
        FEngSetInvisible(GetPackageName(), 0xd0582feb);
    }

    uint32 maxHash = 0x5aec8d91;
    if (!gCarCustomizeManager.IsCareerMode() && Category == CC_PERFORMANCE) {
        FEngSetVisible(GetPackageName(), maxHash);
    } else {
        FEngSetInvisible(GetPackageName(), maxHash);
    }
}

CustomizeMainOption *CustomizeSub::FindInCartOption() {
    if (InCartPartOptionIndex) {
        return static_cast<CustomizeMainOption *>(Options.GetOption(InCartPartOptionIndex));
    }
    return nullptr;
}

void CustomizeSub::Setup() {
    switch (Category) {
        case 0x801:
            SetupParts();
            break;
        case 0x802:
            SetupPerformance();
            break;
        case 0x803:
            SetupVisual();
            break;
        case 0x302:
            SetupVinylGroups();
            break;
        case 0x305:
            SetupDecalLocations();
            break;
        case 0x103:
            SetupRimBrands();
            break;
        case 0x501:
        case 0x502:
        case 0x503:
        case 0x504:
        case 0x505:
        case 0x506:
            SetupDecalPositions();
            break;
    }
    RefreshHeader();
}

void CustomizeSub::SetupParts() {
    if (CustomizeIsInBackRoom()) {
        TitleHash = 0x5d285ae7;
    } else {
        TitleHash = 0x055dce1a;
    }
    CustomizeSetInParts(true);
    BackToPkg = g_pCustomizeMainPkg;
    if (!CustomizeIsInBackRoom()) {
        AddCustomOption(g_pCustomizePartsPkg, 0x028c24f6, 0x6134c218, 0x101);
        AddCustomOption(g_pCustomizeSpoilerPkg, 0xbb034ea6, 0x94e73021, 0x102);
        AddCustomOption(g_pCustomizeSubTopPkg, 0x0294d2a3, 0xf868eb0b, 0x103);
        AddCustomOption(g_pCustomizePartsPkg, 0x028f7092, 0x04d4a88d, 0x104);
        AddCustomOption(g_pCustomizePartsPkg, 0x79165861, 0x61e8f83c, 0x105);
    } else {
        AddCustomOption(g_pCustomizePartsPkg, 0xaf393dba, 0x6134c218, 0x101);
        AddCustomOption(g_pCustomizeSpoilerPkg, 0xc51a4f62, 0x94e73021, 0x102);
        AddCustomOption(g_pCustomizeSubTopPkg, 0xc19491cc, 0xf868eb0b, 0x103);
        AddCustomOption(g_pCustomizePartsPkg, 0xf375276e, 0x04d4a88d, 0x104);
        AddCustomOption(g_pCustomizePartsPkg, 0x25a4375e, 0x61e8f83c, 0x105);
    }
    SetInitialOption(FromCategory & 0xFFFF00FF);
}

void CustomizeSub::SetupPerformance() {
    if (CustomizeIsInBackRoom()) {
        TitleHash = 0xbfd5b50f;
    } else {
        TitleHash = 0xbaef8282;
    }
    BackToPkg = g_pCustomizeMainPkg;
    CustomizeSetInPerformance(true);
    if (!CustomizeIsInBackRoom()) {
        AddCustomOption(g_pCustomizePerfPkg, 0xc15c94e6, 0x9853d9a6, 0x201);
        AddCustomOption(g_pCustomizePerfPkg, 0x01a29ffa, 0x29aa74ba, 0x202);
        AddCustomOption(g_pCustomizePerfPkg, 0x178475e7, 0x6e101aa7, 0x203);
        AddCustomOption(g_pCustomizePerfPkg, 0x9701bde4, 0x4ce19aa4, 0x204);
        AddCustomOption(g_pCustomizePerfPkg, 0x06e8e477, 0x05aa9137, 0x205);
        AddCustomOption(g_pCustomizePerfPkg, 0xbaa23a28, 0x91997ee8, 0x206);
        if (gCarCustomizeManager.IsTurbo()) {
            AddCustomOption(g_pCustomizePerfPkg, 0x06ef789c, 0x05b1255c, 0x207);
        } else {
            AddCustomOption(g_pCustomizePerfPkg, 0x93603dfb, 0xbb6812bb, 0x207);
        }
    } else {
        AddCustomOption(g_pCustomizePerfPkg, 0x4f424e0f, 0x9853d9a6, 0x201);
        AddCustomOption(g_pCustomizePerfPkg, 0xd142d3e3, 0x29aa74ba, 0x202);
        AddCustomOption(g_pCustomizePerfPkg, 0x00190eb6, 0x6e101aa7, 0x203);
        AddCustomOption(g_pCustomizePerfPkg, 0x6fea04c8, 0x4ce19aa4, 0x204);
        AddCustomOption(g_pCustomizePerfPkg, 0x7373f1ef, 0x05aa9137, 0x205);
        AddCustomOption(g_pCustomizePerfPkg, 0x4887f351, 0x91997ee8, 0x206);
        if (gCarCustomizeManager.IsTurbo()) {
            AddCustomOption(g_pCustomizePerfPkg, 0x12fe30a5, 0x05b1255c, 0x207);
        } else {
            AddCustomOption(g_pCustomizePerfPkg, 0x630071e4, 0xbb6812bb, 0x207);
        }
    }
    SetInitialOption(FromCategory & 0xFFFF00FF);
}

void CustomizeSub::SetupVisual() {
    if (CustomizeIsInBackRoom()) {
        TitleHash = 0x10c3fe31;
    } else {
        TitleHash = 0xbfa7d7c4;
    }
    BackToPkg = g_pCustomizeMainPkg;
    if (!CustomizeIsInBackRoom()) {
        AddCustomOption(g_pCustomizePaintPkg, 0xa3b76154, 0x055da70c, 0x301);
        AddCustomOption(g_pCustomizeSubTopPkg, 0x55778e5a, 0xbfa52c55, 0x302);
        if (!gCarCustomizeManager.IsHeroCar()) {
            AddCustomOption(g_pCustomizePaintPkg, 0xd223f84a, 0xe126ff53, 0x303);
        }
        AddCustomOption(g_pCustomizePartsPkg, 0x3f23165c, 0xd32729a6, 0x304);
        AddCustomOption(g_pCustomizeSubTopPkg, 0xda1dae54, 0x955980bc, 0x305);
        AddCustomOption("FeCustomize_ToolBox", 0x45a1c644, 0x6857e5ac, 0x306);
        AddCustomOption(g_pCustomizeHudPkg, 0x028f88bc, 0x78980a6b, 0x307);
    } else {
        AddCustomOption(g_pCustomizePaintPkg, 0x0db89e17, 0x055da70c, 0x301);
        AddCustomOption(g_pCustomizeSubTopPkg, 0xd35f04c0, 0xbfa52c55, 0x302);
        AddCustomOption(g_pCustomizeSubTopPkg, 0xa9135927, 0x955980bc, 0x305);
        AddCustomOption(g_pCustomizeHudPkg, 0x8ba602fc, 0x78980a6b, 0x307);
    }
    SetInitialOption(FromCategory & 0xFFFF00FF);
}

int CustomizeSub::GetRimBrandIndex(unsigned int brand) {
    switch (brand) {
        case 0x352d08d1:
            return 2;
        case 0x9136:
            return 3;
        case 0x9536:
            return 4;
        case 0x2b77feb:
            return 5;
        case 0x324ac97:
            return 6;
        case 0x48e25793:
            return 7;
        case 0xdd544a02:
            return 8;
        case 0x648:
            return 9;
        case 0x1e6a3b:
            return 10;
        case 0x1c386b:
            return 0xb;
        default:
            return 1;
    }
}

void CustomizeSub::SetupRimBrands() {
    BackToPkg = g_pCustomizeSubPkg;
    TitleHash = 0xe032d89e;
    CarPart *stockCarPart = gCarCustomizeManager.GetStockCarPart(CARSLOTID_FRONT_WHEEL);
    SelectablePart *stockPart =
        new SelectablePart(stockCarPart, CARSLOTID_FRONT_WHEEL, 0, Physics::Upgrades::PUT_MAX, false, CPS_AVAILABLE, 0, false);
    if (gCarCustomizeManager.IsPartInstalled(stockPart)) {
        stockPart->SetPartState(CPS_INSTALLED);
    }
    SetStockPartOption *stockOpt = new SetStockPartOption(stockPart, 0xf3990b6, 0x701);
    AddOption(stockOpt);

    AddCustomOption(g_pCustomizeRimsPkg, 0xb0da3de4, 0x56b51a0e, 0x702);
    AddCustomOption(g_pCustomizeRimsPkg, 0xf224a729, 0xf93f2d34, 0x703);
    AddCustomOption(g_pCustomizeRimsPkg, 0xf224ab29, 0xf93f3134, 0x704);
    AddCustomOption(g_pCustomizeRimsPkg, 0xe38de9e, 0x460d1369, 0x705);
    AddCustomOption(g_pCustomizeRimsPkg, 0xea60b4a, 0x467a4015, 0x706);
    AddCustomOption(g_pCustomizeRimsPkg, 0xafc6b9cb, 0x9bb17a11, 0x707);
    AddCustomOption(g_pCustomizeRimsPkg, 0x27ebd095, 0xcca3063f, 0x708);
    AddCustomOption(g_pCustomizeRimsPkg, 0x6c2fa9db, 0xc1bc1a86, 0x709);
    AddCustomOption(g_pCustomizeRimsPkg, 0x36c53e8e, 0x213085f9, 0x70a);
    AddCustomOption(g_pCustomizeRimsPkg, 0x36c2d130, 0x212e5429, 0x70b);

    ShoppingCartItem *inCart = gCarCustomizeManager.IsPartTypeInCart(CARSLOTID_FRONT_WHEEL);
    if (inCart) {
        InCartPartOptionIndex = GetRimBrandIndex(inCart->GetBuyingPart()->GetPart()->GetAppliedAttributeUParam(0xebb03e66, 0));
    }
    CarPart *installed = gCarCustomizeManager.GetInstalledCarPart(CARSLOTID_FRONT_WHEEL);
    if (installed) {
        InstalledPartOptionIndex = GetRimBrandIndex(installed->GetAppliedAttributeUParam(0xebb03e66, 0));
    }

    if (FromCategory == 0x801) {
        int pos = InCartPartOptionIndex;
        if (pos == 0) {
            pos = InstalledPartOptionIndex;
        }
        if (pos != 0) {
            SetInitialOption(pos);
        } else {
            SetInitialOption(1);
        }
    } else {
        SetInitialOption(FromCategory & 0xFFFF00FF);
    }
    if (FromCategory - 0x701u < 0xbu) {
        FromCategory = 0x801;
    }
}

int CustomizeSub::GetVinylGroupIndex(int group) {
    switch (group) {
        case 0:
            return 2;
        case 1:
            return 3;
        case 2:
            return 4;
        case 3:
            return 5;
        case 4:
            return 6;
        case 5:
            return 7;
        case 6:
            return 8;
        case 7:
            return 9;
        default:
            return 1;
    }
}

void CustomizeSub::SetupVinylGroups() {
    TitleHash = 0xda129752;
    BackToPkg = g_pCustomizeSubPkg;
    SelectablePart *stockPart =
        new SelectablePart(static_cast<CarPart *>(nullptr), 0x4d, 0, Physics::Upgrades::PUT_MAX, false, CPS_AVAILABLE, 0, false);
    if (gCarCustomizeManager.IsPartInstalled(stockPart)) {
        stockPart->SetPartState(CPS_INSTALLED);
    }
    SetStockPartOption *stockOpt = new SetStockPartOption(stockPart, 0x21f3d114, 0x401);
    AddOption(stockOpt);

    AddCustomOption(g_pCustomizePartsPkg, 0xf8148554, 0xd9228fc6, 0x402);
    AddCustomOption(g_pCustomizePartsPkg, 0x192d84da, 0x1e8d885f, 0x403);
    AddCustomOption(g_pCustomizePartsPkg, 0xf7352706, 0x1c619fd8, 0x404);
    AddCustomOption(g_pCustomizePartsPkg, 0x1223cc89, 0x9c1b8935, 0x405);
    AddCustomOption(g_pCustomizePartsPkg, 0xbc44bbcb, 0x7956f7b0, 0x406);
    AddCustomOption(g_pCustomizePartsPkg, 0x694ca0ca, 0x2d5bff0f, 0x407);
    AddCustomOption(g_pCustomizePartsPkg, 0x1b3a8dd3, 0x209a9158, 0x408);
    AddCustomOption(g_pCustomizePartsPkg, 0x1ba508fc, 0xcd057d21, 0x409);

    ShoppingCartItem *inCart = gCarCustomizeManager.IsPartTypeInCart(static_cast<unsigned int>(0x4d));
    if (inCart && inCart->GetBuyingPart()) {
        CarPart *part = inCart->GetBuyingPart()->GetPart();
        if (part) {
            InCartPartOptionIndex = GetVinylGroupIndex(part->GetGroupNumber());
        } else {
            InCartPartOptionIndex = 1;
        }
    }
    CarPart *installed = gCarCustomizeManager.GetInstalledCarPart(0x4d);
    if (installed) {
        InstalledPartOptionIndex = GetVinylGroupIndex(installed->GetGroupNumber());
    } else {
        InstalledPartOptionIndex = 1;
    }

    if (FromCategory == 0x803) {
        if (InCartPartOptionIndex != 0) {
            SetInitialOption(InCartPartOptionIndex);
        } else if (InstalledPartOptionIndex != 0) {
            SetInitialOption(InstalledPartOptionIndex);
        } else {
            SetInitialOption(1);
        }
    } else {
        SetInitialOption(FromCategory & 0xFFFF00FF);
    }
    if (FromCategory - 0x401u < 9u) {
        FromCategory = 0x803;
    }
}

void CustomizeSub::SetupDecalLocations() {
    TitleHash = 0x9de6e6e1;
    BackToPkg = g_pCustomizeSubPkg;
    AddCustomOption(g_pCustomizeDecalsPkg, 0x52ded91d, 0x301dedd3, 0x501);
    AddCustomOption(g_pCustomizeDecalsPkg, 0xac7937b4, 0x48e6ca49, 0x502);
    AddCustomOption(g_pCustomizeSubTopPkg, 0xda88b711, 0x34367c86, 0x503);
    AddCustomOption(g_pCustomizeSubTopPkg, 0xc9a967c4, 0xddf80259, 0x504);
    AddCustomOption(g_pCustomizeDecalsPkg, 0x2c710c4d, 0x8a7697d6, 0x505);
    AddCustomOption(g_pCustomizeDecalsPkg, 0xffa7d360, 0xb1f9b0c9, 0x506);
    if (FromCategory == 0x803) {
        SetInitialOption(1);
    } else {
        SetInitialOption(FromCategory & 0xFFFF00FF);
    }
    if (FromCategory - 0x501u < 6u) {
        FromCategory = 0x803;
    }
}

void CustomizeSub::SetupDecalPositions() {
    TitleHash = 0x74d1887d;
    BackToPkg = g_pCustomizeSubTopPkg;
    switch (Category) {
        case 0x503:
            AddCustomOption(g_pCustomizeDecalsPkg, 0xfe957f48, 0x7d212cfa, 0x601);
            AddCustomOption(g_pCustomizeDecalsPkg, 0xfe957f49, 0x7d212cfb, 0x602);
            AddCustomOption(g_pCustomizeDecalsPkg, 0xfe957f4a, 0x7d212cfc, 0x603);
            AddCustomOption(g_pCustomizeDecalsPkg, 0xfe957f4b, 0x7d212cfd, 0x604);
            AddCustomOption(g_pCustomizeDecalsPkg, 0xfe957f4c, 0x7d212cfe, 0x605);
            AddCustomOption(g_pCustomizeDecalsPkg, 0xfe957f4d, 0x7d212cff, 0x606);
            break;
        case 0x504:
            AddCustomOption(g_pCustomizeDecalsPkg, 0x2e40eadb, 0x7d212cfa, 0x601);
            AddCustomOption(g_pCustomizeDecalsPkg, 0x2e40eadc, 0x7d212cfb, 0x602);
            AddCustomOption(g_pCustomizeDecalsPkg, 0x2e40eadd, 0x7d212cfc, 0x603);
            AddCustomOption(g_pCustomizeDecalsPkg, 0x2e40eade, 0x7d212cfd, 0x604);
            AddCustomOption(g_pCustomizeDecalsPkg, 0x2e40eadf, 0x7d212cfe, 0x605);
            AddCustomOption(g_pCustomizeDecalsPkg, 0x2e40eae0, 0x7d212cff, 0x606);
            break;
    }
    if (FromCategory == 0x305) {
        SetInitialOption(1);
    } else {
        SetInitialOption(FromCategory & 0xFFFF00FF);
        FromCategory = 0x305;
    }
}

CustomizeMain::CustomizeMain(ScreenConstructorData *sd) : CustomizeCategoryScreen(sd) {
    int entryPoint = g_TheCustomizeEntryPoint;
    iPerfIndex = 0;
    invalidMarkers = 0;
    if (entryPoint == 0) {
        CarViewer::haveLoadedOnce = 0;
    }
    gCarCustomizeManager.TakeControl(static_cast<eCustomizeEntryPoint>(entryPoint), g_pCustomizeCarRecordToUse);
    for (int i = 0; i < NUM_UNLOCKABLES; i++) {
        MarkUnlockableThingSeen(static_cast<eUnlockableEntity>(i), gCarCustomizeManager.GetUnlockFilter());
    }
    Setup();
    if (gCarCustomizeManager.IsCareerMode()) {
        FEDatabase->BackupCarStable();
    }
}

void CustomizeMain::SwitchRooms() {
    bool newState = !CustomizeIsInBackRoom();
    CustomizeSetInBackRoom(newState);
    SetTitle(newState);
    int savedIdx = Options.GetCurrentIndex();
    if (newState) {
        cFEng::Get()->QueuePackageMessage(0xa1caff8d, GetPackageName(), nullptr);
        FEManager::Get()->SetGarageType(static_cast<eGarageType>(4));
    } else {
        cFEng::Get()->QueuePackageMessage(0x5c01c5, GetPackageName(), nullptr);
        FEManager::Get()->SetGarageType(static_cast<eGarageType>(3));
    }
    SetScreenNames();
    Options.RemoveAll();
    Options.AddInitialBookEnds();
    BuildOptionsList();
    if (bFadeInIconsImmediately) {
        Options.StartFadeIn();
    }
    Options.SetInitialPos(savedIdx);
    RefreshHeader();
}

void CustomizeMain::NotificationMessage(u32 msg, FEObject *pobj, u32 param1, u32 param2) {
    if (!gCarCustomizeManager.IsCareerMode() || msg != __PAD_BACK__) {
        CustomizeCategoryScreen::NotificationMessage(msg, pobj, param1, param2);
    }
    switch (msg) {
        case 0x1265ece9: {
            GarageMainScreen::GetInstance()->UpdateCurrentCameraView(false);
            if (CustomizeIsInBackRoom()) {
                cFEng::Get()->QueuePackageMessage(0xa1caff8d, GetPackageName(), nullptr);
            } else {
                cFEng::Get()->QueuePackageMessage(0x5c01c5, GetPackageName(), nullptr);
            }
            break;
        }
        case __PAD_BACK__:
            if (gCarCustomizeManager.IsCareerMode()) {
                if (!CustomizeIsInBackRoom()) {
                    cFEng::Get()->QueuePackageMessage(0x6d5d86a1, GetPackageName(), nullptr);
                    cFrontendDatabase *db = FEDatabase;
                    GarageMainScreen *gms = GarageMainScreen::GetInstance();
                    gms->SetCustomizationCategory(-1);
                    char port = FEngMapJoyParamToJoyport(param1);
                    db->SetPlayersJoystickPort(0, port);
                    if (!db->IsCarStableDirty()) {
                        MemoryCard::GetInstance()->CancelNextAutoSave();
                    }
                    CarViewer::haveLoadedOnce = 0;
                    RaceStarter::StartCareerFreeRoam();
                } else {
                    SwitchRooms();
                    return;
                }
            } else {
                cFEng::Get()->QueuePackageMessage(0x6d5d86a1, GetPackageName(), nullptr);
            }
            gCarCustomizeManager.RelinquishControl();
            break;
        case 0x34dc1bec:
            if (gCarCustomizeManager.GetNumCustomizeMarkers() > invalidMarkers) {
                SwitchRooms();
            }
            invalidMarkers = 0;
            break;
        case __PAD_BUTTON5__:
            if (!gCarCustomizeManager.IsCareerMode() || gCarCustomizeManager.GetNumCustomizeMarkers() != 0) {
                if (gCarCustomizeManager.IsCareerMode() && !CustomizeIsInBackRoom() && !gCarCustomizeManager.IsHeroCar()) {
                    invalidMarkers = 0;
                    if (TheFEMarkerManager.IsMarkerAvailable(FEMarkerManager::MARKER_INDUCTION, 0) &&
                        !gCarCustomizeManager.CanInstallJunkman(Physics::Upgrades::PUT_BRAKES)) {
                        invalidMarkers++;
                    }
                    if (TheFEMarkerManager.IsMarkerAvailable(FEMarkerManager::MARKER_NOS, 0) &&
                        !gCarCustomizeManager.CanInstallJunkman(Physics::Upgrades::PUT_INDUCTION)) {
                        invalidMarkers++;
                    }
                    if (invalidMarkers > 0) {
                        DialogInterface::ShowOneButton(GetPackageName(), "", dialog_info, 0x417b2601, 0x34dc1bec, 0x3b3e83);
                    } else {
                        SwitchRooms();
                    }
                }
            }
            break;
    }
}

void CustomizeMain::SetScreenNames() {
    if (CustomizeIsInBackRoom()) {
        g_pCustomizeSubPkg = "CustomizeCategory_BACKROOM.fng";
        g_pCustomizeSubTopPkg = "CustomizeGenericTop_BACKROOM.fng";
        g_pCustomizePartsPkg = "CustomizeParts_BACKROOM.fng";
        g_pCustomizePerfPkg = "CustomizePerformance_BACKROOM.fng";
        g_pCustomizeDecalsPkg = "Decals_BACKROOM.fng";
        g_pCustomizePaintPkg = "Paint_BACKROOM.fng";
        g_pCustomizeRimsPkg = "Rims_BACKROOM.fng";
        g_pCustomizeHudColorPkg = "CustomHUDColor_BACKROOM.fng";
        g_pCustomizeShoppingCartPkg = "ShoppingCart_BACKROOM.fng";
        g_pCustomizeHudPkg = "CustomHUD_BACKROOM.fng";
        g_pCustomizeSpoilerPkg = "Spoilers_BACKROOM.fng";
    } else {
        g_pCustomizeSubPkg = "CustomizeCategory.fng";
        g_pCustomizeSubTopPkg = "CustomizeGenericTop.fng";
        g_pCustomizePartsPkg = "CustomizeParts.fng";
        g_pCustomizePerfPkg = "CustomizePerformance.fng";
        g_pCustomizeDecalsPkg = "Decals.fng";
        g_pCustomizePaintPkg = "Paint.fng";
        g_pCustomizeRimsPkg = "Rims.fng";
        g_pCustomizeHudColorPkg = "CustomHUDColor.fng";
        if (gCarCustomizeManager.IsCareerMode()) {
            g_pCustomizeShoppingCartPkg = "ShoppingCart.fng";
        } else {
            g_pCustomizeShoppingCartPkg = "ShoppingCart_QR.fng";
        }
        g_pCustomizeHudPkg = "CustomHUD.fng";
        g_pCustomizeSpoilerPkg = "Spoilers.fng";
    }
}

void CustomizeMain::RefreshHeader() {
    CustomizeCategoryScreen::RefreshHeader();
    int isCareer = gCarCustomizeManager.IsCareerMode();
    if (isCareer && !gCarCustomizeManager.IsHeroCar()) {
        int inBackRoom = CustomizeIsInBackRoom();
        if (!inBackRoom && gCarCustomizeManager.GetNumCustomizeMarkers() > 0) {
            FEngSetVisible(FEngFindObject(GetPackageName(), 0xdc6ee739));
        } else {
            FEngSetInvisible(FEngFindObject(GetPackageName(), 0xdc6ee739));
        }
    } else {
        FEngSetInvisible(FEngFindObject(GetPackageName(), 0xdc6ee739));
    }
    if (Options.GetCurrentOption()) {
        gCarCustomizeManager.IsCategoryNew(static_cast<unsigned short>(static_cast<CustomizeMainOption *>(Options.GetCurrentOption())->Category));
    }
}

void CustomizeMain::SetTitle(bool isInBackroom) {
    char local_48[64];
    if (isInBackroom) {
        const char *fmt = "%s";
        const char *str = GetLocalizedString(0x92fcdbf0);
        bSNPrintf(local_48, 0x40, fmt, str);
    } else {
        const char *fmt = "%s";
        const char *str = GetLocalizedString(0x1f242e03);
        bSNPrintf(local_48, 0x40, fmt, str);
    }
    int lang = GetCurrentLanguage();
    if (lang != 2 && lang != 0xd) {
        int n = 0;
        while (local_48[n] != 0) {
            char c = local_48[n];
            if (static_cast<unsigned int>(c - 0x41) < 0x1a) {
                c = c | 0x20;
            }
            local_48[n] = c;
            n++;
        }
    }
    FEPrintf(GetPackageName(), __TITLE_GROUP__, "%s", local_48);
}

void CustomizeMain::Setup() {
    BackToPkg = "FeGarageMain.fng";
    SetTitle(CustomizeIsInBackRoom());
    SetScreenNames();
    CustomizeSetInPerformance(false);
    CustomizeSetInParts(false);
    Category = 0;
    BuildOptionsList();
    SetInitialOption(FromCategory & 0xFFFF00FF);
    RefreshHeader();
}

void CustomizeMain::BuildOptionsList() {
    int isHero = gCarCustomizeManager.IsHeroCar();
    if (!CustomizeIsInBackRoom()) {
        if (!isHero) {
            AddCustomOption(g_pCustomizeSubPkg, 0x6e0ca66c, 0x55dce1a, 0x801);
            iPerfIndex = AddCustomOption(g_pCustomizeSubPkg, 0x3987d054, 0xbaef8282, 0x802);
        }
        AddCustomOption(g_pCustomizeSubPkg, 0x3e31ba56, 0xbfa7d7c4, 0x803);
    } else {
        if (!isHero) {
            AddCustomOption(g_pCustomizeSubPkg, 0x73272ed2, 0x55dce1a, 0x801);
            AddCustomOption(g_pCustomizeSubPkg, 0xc61c8d3a, 0xbaef8282, 0x802);
        }
        AddCustomOption(g_pCustomizeSubPkg, 0xe69d4f7c, 0xbfa7d7c4, 0x803);
    }
}

CustomizationScreenHelper::CustomizationScreenHelper(const char *pkg_name) {
    pPackageName = pkg_name;
    bInitComplete = false;
    bUnlockOverlayShowing = false;
    float actual = gCarCustomizeManager.GetActualHeat();
    float cart = gCarCustomizeManager.GetCartHeat();
    HeatMeter.Init(pkg_name, "HEAT_METER", 0.0f, 5.0f, actual, cart);
}

void CustomizationScreenHelper::DrawTitle() {
    const char *title_str = GetLocalizedString(TitleHash);
    char buf[64];
    bSNPrintf(buf, 64, "%s", title_str);
    int lang = GetCurrentLanguage();
    if (lang != 2 && lang != 13) {
        int i = 0;
        while (buf[i] != 0) {
            char c = buf[i];
            if (static_cast<unsigned int>(c - 'A') < 26u) {
                c = c | 0x20;
            }
            buf[i] = c;
            i++;
        }
    }
    FEPrintf(pPackageName, __TITLE_GROUP__, "%s", buf);
}

void CustomizationScreenHelper::SetCareerStatusIcon(eCustomizePartState state) {
    if (state == CPS_LOCKED) {
        FEngSetVisible(FEngFindObject(pPackageName, 0xcffb7033));
        FEngSetTextureHash(FEngFindImage(pPackageName, 0xcffb7033), 0xf0574bb2);
    } else if (state == CPS_NEW) {
        FEngSetVisible(FEngFindObject(pPackageName, 0xcffb7033));
        FEngSetTextureHash(FEngFindImage(pPackageName, 0xcffb7033), 0xcffb7033);
    } else {
        FEngSetInvisible(FEngFindObject(pPackageName, 0xcffb7033));
    }
}

void CustomizationScreenHelper::SetPlayerCarStatusIcon(eCustomizePartState state) {
    if (state == CPS_INSTALLED) {
        FEngSetVisible(FEngFindObject(pPackageName, 0xd0582feb));
        FEngSetTextureHash(FEngFindImage(pPackageName, 0xd0582feb), 0x696ae039);
    } else if (state < CPS_INSTALLED + 1) {
        if (state == CPS_AVAILABLE) {
            FEngSetInvisible(FEngFindObject(pPackageName, 0xd0582feb));
        }
    } else if (state == CPS_IN_CART) {
        FEngSetVisible(FEngFindObject(pPackageName, 0xd0582feb));
        FEngSetTextureHash(FEngFindImage(pPackageName, 0xd0582feb), 0x1a777e25);
    }
}

void CustomizationScreenHelper::SetCashVisibility(bool visible) {
    if (visible) {
        FEngSetVisible(FEngFindObject(pPackageName, 0x8d1559a4));
    } else {
        FEngSetInvisible(FEngFindObject(pPackageName, 0x8d1559a4));
    }
}

void CustomizationScreenHelper::SetUnlockOverlayState(bool show, unsigned int blurb_hash) {
    unsigned int script = FEHASH_APPEAR;
    bUnlockOverlayShowing = show;
    if (!show) {
        script = FEHASH_LEAVE;
    } else {
        FEngSetLanguageHash(pPackageName, 0xa6298e25, blurb_hash);
    }
    FEngSetScript(pPackageName, 0xebc3e6b7, script, true);
}

void CustomizationScreenHelper::SetCareerStuff(SelectablePart *part, unsigned int cat, unsigned int tradeInValue) {
    if (gCarCustomizeManager.IsCareerMode()) {
        if (CustomizeIsInBackRoom()) {
            FEngSetLanguageHash(GetPackageName(), 0x63ca8308, GetMarkerNameFromCategory(static_cast<eCustomizeCategory>(cat)));
            FEPrintf(GetPackageName(), 0x23d918fe, "1");
            FEPrintf(GetPackageName(), 0x83e3cd39, "%d", GetNumMarkersFromCategory(static_cast<eCustomizeCategory>(cat)));
        } else {
            if (part) {
                FEPrintf(GetPackageName(), 0xdbb80edd, "%d", part->GetPrice());
            } else {
                SelectablePart *tempPart = gCarCustomizeManager.GetTempColoredPart();
                if (tempPart) {
                    FEPrintf(GetPackageName(), 0xdbb80edd, "%d", tempPart->GetPrice());
                } else {
                    FEPrintf(GetPackageName(), 0xdbb80edd, "-1");
                }
            }
            FEPrintf(GetPackageName(), 0xc60adcfd, "%d", FEDatabase->GetCareerSettings()->GetCash());
            FEPrintf(GetPackageName(), 0x7a6d2f71, "%d", gCarCustomizeManager.GetCartTotal(static_cast<eCustomizeCartTotals>(2)));
            FEPrintf(GetPackageName(), 0xa91eda8a, "%d", tradeInValue);
        }
        SetHeatValue(gCarCustomizeManager.GetActualHeat());
        SetHeatPreview(gCarCustomizeManager.GetPreviewHeat(part));
        DrawMeters();
    } else {
        SetCareerStatusIcon(CPS_AVAILABLE);
        SetCashVisibility(false);
        HeatMeter.SetVisibility(false);
        FEngSetInvisible(FEngFindObject(GetPackageName(), 0x24c6bfad));
        FEngSetInvisible(FEngFindObject(GetPackageName(), 0xea903012));
    }
}

void CustomizationScreenHelper::SetPartStatus(SelectablePart *part, unsigned int unlock_blurb, int part_num, int max_parts) {
    if (part) {
        if (part->IsInstalled()) {
            SetPlayerCarStatusIcon(CPS_INSTALLED);
        } else if (part->IsInCart()) {
            SetPlayerCarStatusIcon(CPS_IN_CART);
        } else {
            SetPlayerCarStatusIcon(CPS_AVAILABLE);
        }
        if (part->IsLocked() && unlock_blurb) {
            if (IsInitComplete()) {
                SetUnlockOverlayState(true, unlock_blurb);
            }
            SetCareerStatusIcon(CPS_LOCKED);
        } else {
            if (bUnlockOverlayShowing) {
                SetUnlockOverlayState(false, 0);
            }
            if (part->IsNew()) {
                SetCareerStatusIcon(CPS_NEW);
            } else {
                SetCareerStatusIcon(CPS_AVAILABLE);
            }
        }
    }
    FEPrintf(GetPackageName(), 0x6f25a248, "%d", part_num);
    FEPrintf(GetPackageName(), 0xb2037bdc, "%d", max_parts);
}

void CustomizationScreenHelper::FlashStatusIcon(eCustomizePartState state, bool play_sound) {
    unsigned int hash = 0;
    if (state == CPS_INSTALLED || state == CPS_IN_CART) {
        hash = 0xd0582feb;
    } else if (state == CPS_LOCKED) {
        hash = 0xcffb7033;
    }
    FEngSetScript(pPackageName, hash, 0x280164f, true);
    if (play_sound) {
        g_pEAXSound->PlayUISoundFX(UISND_COMMON_WRONG);
    }
}

CustomizationScreen::CustomizationScreen(ScreenConstructorData *sd) : IconScrollerMenu(sd), DisplayHelper(GetPackageName()) {
    pReplacingOption = nullptr;
    bNeedsRefresh = false;
    DelayFadeIn();
    ScrollTime = 0;
    Category = sd->Arg & 0xFFFF;
    FromCategory = static_cast<int>(static_cast<short>(sd->Arg >> 16));
    unsigned int cat = Category;
    GarageMainScreen *gms;
    if (cat > 0x600 && cat < 0x607) {
        gms = GarageMainScreen::GetInstance();
        *(unsigned int *)((char *)gms + 0x8c) = CustomizeDecals::CurrentDecalLocation;
    } else {
        gms = GarageMainScreen::GetInstance();
        *(unsigned int *)((char *)gms + 0x8c) = Category;
    }
}

CustomizationScreen::~CustomizationScreen() {
    GarageMainScreen *gms = GarageMainScreen::GetInstance();
    *(unsigned int *)((char *)gms + 0x8c) = 0xFFFFFFFF;
}

void CustomizationScreen::NotificationMessage(u32 msg, FEObject *pobj, u32 param1, u32 param2) {
    if (msg == FEHASH_INITCOMPLETE) {
        DisplayHelper.SetInitComplete(true);
        RefreshHeader();
    }
    if (msg == __PAD_LEFT__ || msg == __PAD_RIGHT__) {
        ScrollTime = RealTimer;
    }
    IconScrollerMenu::NotificationMessage(msg, pobj, param1, param2);
    switch (msg) {
        case FEMSG_SCREEN_TICK:
            if (!bNeedsRefresh) {
                return;
            }
            {
                float elapsed = (RealTimer - ScrollTime).GetSeconds() * 0.001f;
                if (elapsed <= 0.25f) {
                    return;
                }
            }
            bNeedsRefresh = false;
            RefreshHeader();
            break;
        case 0x5e6ea975:
            Options.StartFadeIn();
            break;
        case __PAD_ACCEPT__: {
            SelectablePart *selected = GetSelectedPart();
            if (selected) {
                if (selected->IsLocked()) {
                    PlayLocked();
                    return;
                }
                if (selected->IsInCart()) {
                    PlayInCart();
                    return;
                }
                if (selected->IsInstalled()) {
                    ShoppingCartItem *item = gCarCustomizeManager.IsPartTypeInCart(selected);
                    if (item) {
                        gCarCustomizeManager.RemoveFromCart(item);
                        SelectablePart *part = item->GetBuyingPart();
                        FindMatchingOption(part)->GetPart()->UnSetInCart();
                    }
                    PlayInstalled();
                    return;
                }
            }
            ShoppingCartItem *item = gCarCustomizeManager.IsPartTypeInCart(GetSelectedPart());
            if (item) {
                pReplacingOption = FindMatchingOption(item->GetBuyingPart());
            }
            cFEng::Get()->QueueGameMessage(0x91dfdf84, GetPackageName(), 0xFF);
            break;
        }
        case 0x91dfdf84: {
            if (pReplacingOption) {
                SelectablePart *rp = pReplacingOption->GetPart();
                rp->SetPartState(CPS_GAME_STATE_MASK);
                pReplacingOption = nullptr;
            }
            CustomizePartOption *curOpt = static_cast<CustomizePartOption *>(Options.GetCurrentOption());
            gCarCustomizeManager.AddToCart(curOpt->GetPart());
            curOpt = static_cast<CustomizePartOption *>(Options.GetCurrentOption());
            curOpt->GetPart()->SetPartState(CPS_IN_CART);
            RefreshHeader();
            break;
        }
        case 0xcf91aacd:
            CustomizeShoppingCart::ExitShoppingCart();
            break;
        case __PAD_BUTTON0__: {
            unsigned int cat = Category;
            if (cat > 0x200 && cat < 0x208) {
                return;
            }
            if (cat == 0x307) {
                return;
            }
            if (Options.GetCurrentOption() == nullptr) {
                Showcase::FromIndex = 0;
            } else {
                Showcase::FromIndex = Options.GetCurrentIndex();
            }
            Showcase::FromPackage = GetPackageName();
            Showcase::FromArgs = Category | (FromCategory << 16);
            cFEng::Get()->QueuePackageSwitch("Showcase.fng", 0, 0, false);
            break;
        }
        case __PAD_START__:
            CustomizeShoppingCart::ShowShoppingCart(GetPackageName());
            break;
    }
}

void CustomizationScreen::RefreshHeader() {
    IconScrollerMenu::RefreshHeader();
    DisplayHelper.DrawTitle();
    if (!Options.IsEmpty()) {
        int tradeInValue = 0;
        if (gCarCustomizeManager.IsCareerMode()) {
            if (!CustomizeIsInBackRoom()) {
                SelectablePart *spart = GetSelectedPart();
                if (spart) {
                    if (gCarCustomizeManager.CanTradeIn(spart)) {
                        CarPart *cpart = gCarCustomizeManager.GetInstalledCarPart(spart->GetSlotID());
                        if (cpart) {
                            eUnlockFilters filter = gCarCustomizeManager.GetUnlockFilter();
                            tradeInValue = UnlockSystem::GetCarPartCost(filter, spart->GetSlotID(), cpart, 0);
                        }
                        tradeInValue = static_cast<int>(static_cast<float>(tradeInValue) * gTradeInFactor);
                    }
                }
            }
        }
        DisplayHelper.SetCareerStuff(GetSelectedPart(), Category, tradeInValue);

        DisplayHelper.SetPartStatus(GetSelectedPart(), static_cast<CustomizePartOption *>(Options.GetCurrentOption())->GetUnlockBlurb(),
                                    Options.GetCurrentIndex(), Options.CountElements());
    }
}

void CustomizationScreen::AddPartOption(SelectablePart *part, unsigned int tex_hash, unsigned int name_hash, unsigned int desc_hash,
                                        unsigned int unlock_hash, bool locked) {
    CustomizePartOption *opt = new CustomizePartOption(part, tex_hash, name_hash, desc_hash, unlock_hash);
    AddOption(opt);
    opt->SetLocked(locked);
}

SelectablePart *CustomizationScreen::FindInCartPart() {

    for (CustomizePartOption *opt = static_cast<CustomizePartOption *>(Options.GetHead()); !Options.IsEndOfList(opt);
         opt = static_cast<CustomizePartOption *>(opt->GetNext())) {
        SelectablePart *part = opt->GetPart();
        if (part && part->IsInCart()) {
            return part;
        }
    }
    return nullptr;
}

CustomizePartOption *CustomizationScreen::FindMatchingOption(SelectablePart *to_find) {
    for (CustomizePartOption *opt = static_cast<CustomizePartOption *>(Options.GetHead()); !Options.IsEndOfList(opt);
         opt = static_cast<CustomizePartOption *>(opt->GetNext())) {
        if (to_find->IsPerformancePkg()) {
            if (opt->GetPart()->GetPhysicsType() == to_find->GetPhysicsType() && opt->GetPart()->GetUpgradeLevel() == to_find->GetUpgradeLevel()) {
                return opt;
            }
        } else {
            if (opt->GetPart()->GetPart() == to_find->GetPart()) {
                return opt;
            }
        }
    }
    return nullptr;
}

static void UnLoadCustomHUDPacksAndTextures() {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 5; j++) {
            if (CustomizeHUDTexTextureResources[i][j] != 0) {
                uint32 handle = CustomizeHUDTexTextureResources[i][j];
                eUnloadStreamingTexture(&handle, 1);
            }
            CustomizeHUDTexTextureResources[i][j] = 0;
        }
        if (CustomizeHUDTexPackResources[i] != 0) {
            char buf[64];
            bSPrintf(buf, "HUD_TEX_%02d", i);
            eUnloadStreamingTexturePack(buf);
        }
        CustomizeHUDTexPackResources[i] = 0;
    }
    CustomizeParts::TexturePackLoaded = 0;
}

CustomizeParts::CustomizeParts(ScreenConstructorData *sd) : CustomizationScreen(sd) {
    bTexturesNeedUnload = false;
    if (GetCategory() == 0x307) {
        if (!TexturePackLoaded) {
            for (int i = 0; i < 11; i++) {
                CustomizeHUDTexPackResources[i] = 0;
                for (int j = 0; j < 5; j++) {
                    CustomizeHUDTexTextureResources[i][j] = 0;
                }
            }
        }
        TachRPM = gCarCustomizeManager.GetMaxRPM();
        if (TachRPM >= 0x251d) {
            TachRPM = 10000;
        } else if (TachRPM >= 0x2135) {
            TachRPM = 9000;
        } else if (TachRPM > 0x1d4c) {
            TachRPM = 8000;
        } else {
            TachRPM = 7000;
        }
        FEngSetInvisible(GetPackageName(), 0xdee8632b);
    }
    Setup();
}

CustomizeParts::~CustomizeParts() {
    if (TexturePackLoaded && bTexturesNeedUnload) {
        UnLoadCustomHUDPacksAndTextures();
    }
}

void CustomizeParts::NotificationMessage(u32 msg, FEObject *pobj, u32 param1, u32 param2) {
    if (msg != __PAD_ACCEPT__) {
        CustomizationScreen::NotificationMessage(msg, pobj, param1, param2);
    }
    switch (msg) {
        case __PAD_ACCEPT__:
            if (Category == 0x307) {
                if (!TexturePackLoaded) {
                    return;
                }
                SelectablePart *sel = GetSelectedPart();
                if (sel && (sel->GetPartState() & CPS_GAME_STATE_MASK) == CPS_LOCKED) {
                    DisplayHelper.FlashStatusIcon(CPS_LOCKED, true);
                    return;
                }
                if (gCarCustomizeManager.GetTempColoredPart()) {
                    gCarCustomizeManager.ClearTempColoredPart();
                }
                gCarCustomizeManager.SetTempColoredPart(new SelectablePart(sel));
                cFEng::Get()->QueuePackageSwitch(g_pCustomizeHudColorPkg, Category | (FromCategory << 16), 0, false);
            } else if (Category >= 0x402 && Category <= 0x409) {
                SelectablePart *sel = GetSelectedPart();
                if (sel && (sel->GetPartState() & CPS_GAME_STATE_MASK) == CPS_LOCKED) {
                    DisplayHelper.FlashStatusIcon(CPS_LOCKED, true);
                    return;
                }
                unsigned int tunable = sel->GetPart()->GetAppliedAttributeUParam(0x6212682b, 0);
                if (tunable == 0) {
                    CustomizationScreen::NotificationMessage(__PAD_ACCEPT__, pobj, param1, param2);
                    return;
                }
                gCarCustomizeManager.SetTempColoredPart(new SelectablePart(sel));
                cFEng::Get()->QueuePackageSwitch(g_pCustomizePaintPkg, Category | (FromCategory << 16), 0, false);
            } else {
                CustomizationScreen::NotificationMessage(__PAD_ACCEPT__, pobj, param1, param2);
                return;
            }
            break;
        case 0xcf91aacd:
            if (Category != 0x307) {
                return;
            }
            if (!TexturePackLoaded) {
                return;
            }
            bTexturesNeedUnload = true;
            break;
        case 0x5a928018: {
            SelectablePart *sel = FindInCartPart();
            if (!sel) {
                return;
            }
            if (gCarCustomizeManager.IsPartInCart(sel)) {
                return;
            }
            sel->SetPartState(sel->GetPartState() & CPS_GAME_STATE_MASK);
            RefreshHeader();
            break;
        }
        case __PAD_BACK__:
            if (Category == 0x307) {
                if (!TexturePackLoaded) {
                    return;
                }
                bTexturesNeedUnload = true;
                cFEng::Get()->QueuePackageSwitch(g_pCustomizeSubPkg, FromCategory | (0x307 << 16), 0, false);
            } else if (Category >= 0x402 && Category <= 0x409) {
                gCarCustomizeManager.ClearTempColoredPart();
                cFEng::Get()->QueuePackageSwitch(g_pCustomizeSubTopPkg, Category | (FromCategory << 16), 0, false);
            } else {
                cFEng::Get()->QueuePackageSwitch(g_pCustomizeSubPkg, FromCategory | (Category << 16), 0, false);
            }
            break;
    }
}

void CustomizeParts::Setup() {
    unsigned int icon_hash = 0;
    int car_slot_id = 0;
    unsigned int vinyl_group_number = 0;
    bool is_vinyl = false;
    CarPart *installed_part = nullptr;
    bool part_found = false;

    switch (Category) {
        case 0x101:
            SetTitleHash(0x6134c218);
            icon_hash = 0x28c24f6;
            if (CustomizeIsInBackRoom()) {
                icon_hash = 0xaf393dba;
            }
            car_slot_id = 0x17;
            goto after_switch;
        case 0x104:
            SetTitleHash(0x4d4a88d);
            icon_hash = 0x28f7092;
            if (CustomizeIsInBackRoom()) {
                icon_hash = 0xf375276e;
            }
            car_slot_id = 0x3f;
            goto after_switch;
        case 0x105:
            SetTitleHash(0x61e8f83c);
            icon_hash = 0x79165861;
            if (CustomizeIsInBackRoom()) {
                icon_hash = 0x25a4375e;
            }
            car_slot_id = 0x3e;
            goto after_switch;
        case 0x307:
            if (!CustomizeParts::TexturePackLoaded) {
                cFEng::Get()->QueuePackageMessage(0x13fd3296, GetPackageName(), nullptr);
                LoadHudTextures();
            } else {
                ShowHudObjects();
                cFEng::Get()->QueuePackageMessage(0x8cb81f09, GetPackageName(), nullptr);
            }
            if (gCarCustomizeManager.GetTempColoredPart()) {
                installed_part = gCarCustomizeManager.GetTempColoredPart()->GetPart();
                part_found = true;
            }
            SetTitleHash(0x78980a6b);
            icon_hash = 0x28f88bc;
            if (CustomizeIsInBackRoom()) {
                icon_hash = 0x8ba602fc;
            }
            car_slot_id = 0x84;
            goto after_switch;
        case 0x304:
            SetTitleHash(0xd32729a6);
            icon_hash = 0x3f23165c;
            car_slot_id = 0x83;
            goto after_switch;
        case 0x402:
            SetTitleHash(0xd9228fc6);
            icon_hash = 0xf8148554;
            car_slot_id = 0x4d;
            vinyl_group_number = 0;
            goto set_vinyl;
        case 0x403:
            SetTitleHash(0x1e8d885f);
            icon_hash = 0x192d84da;
            car_slot_id = 0x4d;
            vinyl_group_number = 1;
            goto set_vinyl;
        case 0x404:
            SetTitleHash(0x1c619fd8);
            icon_hash = 0xf7352706;
            car_slot_id = 0x4d;
            vinyl_group_number = 2;
            goto set_vinyl;
        case 0x405:
            SetTitleHash(0x9c1b8935);
            icon_hash = 0x1223cc89;
            car_slot_id = 0x4d;
            vinyl_group_number = 3;
            goto set_vinyl;
        case 0x406:
            SetTitleHash(0x7956f7b0);
            icon_hash = 0xbc44bbcb;
            car_slot_id = 0x4d;
            vinyl_group_number = 4;
            goto set_vinyl;
        case 0x407:
            SetTitleHash(0x2d5bff0f);
            icon_hash = 0x694ca0ca;
            car_slot_id = 0x4d;
            vinyl_group_number = 5;
            goto set_vinyl;
        case 0x408:
            SetTitleHash(0x209a9158);
            icon_hash = 0x1b3a8dd3;
            car_slot_id = 0x4d;
            vinyl_group_number = 6;
            goto set_vinyl;
        case 0x409:
            SetTitleHash(0xcd057d21);
            icon_hash = 0x1ba508fc;
            car_slot_id = 0x4d;
            vinyl_group_number = 7;
            goto set_vinyl;
        default:
            goto after_switch;
    }

set_vinyl:
    is_vinyl = true;

after_switch:
    if (is_vinyl && gCarCustomizeManager.GetTempColoredPart()) {
        installed_part = gCarCustomizeManager.GetTempColoredPart()->GetPart();
        part_found = true;
    }
    if (!part_found) {
        installed_part = gCarCustomizeManager.GetActivePartFromSlot(car_slot_id);
    }

    bTList<SelectablePart> part_list;
    if (is_vinyl) {
        gCarCustomizeManager.GetCarPartList(car_slot_id, part_list, vinyl_group_number);
    } else {
        gCarCustomizeManager.GetCarPartList(car_slot_id, part_list, 0);
    }

    int installed_index;
    int current_part_index;
    unsigned int original_icon_hash;
    SelectablePart *part;
    installed_index = 0;
    current_part_index = 1;
    original_icon_hash = icon_hash;
    part = part_list.GetHead();

    while (!part_list.IsEmpty()) {
        part = part_list.RemoveHead();
        unsigned int unlock_hash = gCarCustomizeManager.GetUnlockHash(static_cast<eCustomizeCategory>(Category), part->GetUpgradeLevel());

        if (is_vinyl) {
            CarPart *cpart = part->GetPart();
            if ((cpart->GetGroupNumber()) == vinyl_group_number) {
                if (UnlockSystem::IsUnlockableAvailable(cpart->GetPartNameHash())) {
                    bool locked = gCarCustomizeManager.IsPartLocked(part, 0);
                    AddPartOption(part, icon_hash, cpart->GetUpgradeLevel(), 0, unlock_hash, locked);
                } else {
                    delete part;
                    part = nullptr;
                }
            } else {
                delete part;
                part = nullptr;
            }
        } else {
            CarPart *cpart = part->GetPart();
            if (cpart->HasAppliedAttribute(bStringHash("CARBONFIBRE"))) {
                int cfVal = cpart->GetAppliedAttributeIParam(bStringHash("CARBONFIBRE"), 0);
                if (cfVal != 0) {
                    if (Category != 0x104) {
                        if (Category == 0x105) {
                            if (CustomizeIsInBackRoom()) {
                                icon_hash = 0xcd6b4e26;
                            } else {
                                icon_hash = 0xfc618215;
                            }
                        } else {
                            icon_hash = original_icon_hash;
                        }
                    } else {
                        if (CustomizeIsInBackRoom()) {
                            icon_hash = 0x2478e136;
                        } else {
                            icon_hash = 0x68495926;
                        }
                    }
                } else {
                    icon_hash = original_icon_hash;
                }
            } else {
                icon_hash = original_icon_hash;
            }
            AddPartOption(part, icon_hash, cpart->GetUpgradeLevel(), 0, unlock_hash, gCarCustomizeManager.IsPartLocked(part, 0));
        }
        if (part) {
            if (installed_part && part->GetPart() == installed_part) {
                installed_index = current_part_index;
            }
            current_part_index++;
        }
    }

    if (Showcase::FromIndex != 0) {
        SetInitialOption(Showcase::FromIndex);
        Showcase::FromIndex = 0;
    } else {
        SetInitialOption(installed_index);
    }
    RefreshHeader();

    while (!part_list.IsEmpty()) {
        delete part_list.RemoveHead();
    }
}

void CustomizeParts::LoadHudTextures() {
    PacksLoadedCount = 0;
    LoadNextHudTexturePack();
}

void CustomizeParts::LoadNextHudTexturePack() {
    char buf[64];
    bSPrintf(buf, "HUD_TEX_%02d", PacksLoadedCount);
    int result = eLoadStreamingTexturePack(buf, reinterpret_cast<void (*)(void *)>(TexturePackLoadedCallbackAccessor), this, 0);
    CustomizeHUDTexPackResources[PacksLoadedCount] = (result != 0) ? 1 : 0;
}

void CustomizeParts::TexturePackLoadedCallback() {
    int hud_num = PacksLoadedCount;
    PacksLoadedCount = hud_num + 1;
    CustomizeHUDTexTextureResources[hud_num][0] = FEngHashString("HUD_GAUGE_%02d", hud_num);
    CustomizeHUDTexTextureResources[hud_num][1] = FEngHashString("HUD_NEEDLE_%d_%02d", TachRPM, hud_num);
    CustomizeHUDTexTextureResources[hud_num][2] = FEngHashString("HUD_NEEDLE_TURBO_%02d", hud_num);
    CustomizeHUDTexTextureResources[hud_num][3] = FEngHashString("HUD_SPEEDOMETER_%02d", hud_num);
    CustomizeHUDTexTextureResources[hud_num][4] = FEngHashString("HUD_NOS_%02d", hud_num);
    eLoadStreamingTexture(CustomizeHUDTexTextureResources[hud_num], 5, TextureLoadedCallbackAccessor, reinterpret_cast<uint32>(this), 0);
}

void CustomizeParts::TextureLoadedCallback() {
    if (PacksLoadedCount < 11) {
        LoadNextHudTexturePack();
    } else {
        TexturePackLoaded = true;
        cFEng::Get()->MakeLoadedPackagesDirty();
        ShowHudObjects();
        RefreshHeader();
        cFEng::Get()->QueuePackageMessage(0x8cb81f09, GetPackageName(), nullptr);
    }
}

void CustomizeParts::ShowHudObjects() {
    FEngSetScript(GetPackageName(), 0xDEE8632B, FEHASH_APPEAR, true);
    FEngSetVisible(FEngFindObject(GetPackageName(), 0xDEE8632B));
}

void CustomizeParts::SetHUDTextures() {
    SelectablePart *sel = GetSelectedPart();
    CarPart *part = sel->GetPart();
    unsigned int hudStyleHash = FEngHashString("HUD_STYLE");
    int hudStyle = part->GetAppliedAttributeIParam(hudStyleHash, 0);
    const char *pkg = GetPackageName();
    unsigned int hash = FEngHashString("HUD_NEEDLE_%d_%02d", TachRPM, hudStyle);
    FEngSetTextureHash(FEngFindImage(pkg, 0xc0721eb9), hash);
    pkg = GetPackageName();
    hash = FEngHashString("HUD_GAUGE_%02d", hudStyle);
    FEngSetTextureHash(FEngFindImage(pkg, 0x5d19f25), hash);
    pkg = GetPackageName();
    hash = FEngHashString("HUD_SPEEDOMETER_%02d", hudStyle);
    FEngSetTextureHash(FEngFindImage(pkg, 0xd312f0cb), hash);
    if (gCarCustomizeManager.IsTurbo()) {
        pkg = GetPackageName();
        hash = FEngHashString("HUD_NEEDLE_TURBO_%02d", hudStyle);
        FEngSetTextureHash(FEngFindImage(pkg, 0xc62ad685), hash);
        pkg = GetPackageName();
        hash = FEngHashString("HUD_NOS_%02d", hudStyle);
        FEngSetTextureHash(FEngFindImage(pkg, 0x8fe2a217), hash);
        FEngSetVisible(FEngFindObject(GetPackageName(), 0xc5d551b7));
    } else {
        FEngSetInvisible(FEngFindObject(GetPackageName(), 0xc5d551b7));
    }
}

void CustomizeParts::SetHUDColors() {
    ShoppingCartItem *hudInCart = gCarCustomizeManager.IsPartTypeInCart(0x84u);
    CarPart *installedHud = gCarCustomizeManager.GetInstalledCarPart(0x84);
    SelectablePart *sel = GetSelectedPart();
    if (sel->GetPart() != installedHud) {
        if (!hudInCart)
            goto not_installed;
        SelectablePart *selPart = GetSelectedPart();
        if (selPart->GetPart() != hudInCart->GetBuyingPart()->GetPart())
            goto not_installed;
    }
    {
        unsigned int colors[3];
        int slot = 0x85;
        int idx = 0;
        do {
            ShoppingCartItem *colorInCart = gCarCustomizeManager.IsPartTypeInCart(static_cast<unsigned int>(slot));
            CarPart *colorPart;
            if (colorInCart && hudInCart) {
                SelectablePart *selPart = GetSelectedPart();
                if (selPart->GetPart() == hudInCart->GetBuyingPart()->GetPart()) {
                    colorPart = colorInCart->GetBuyingPart()->GetPart();
                } else {
                    colorPart = gCarCustomizeManager.GetInstalledCarPart(slot);
                }
            } else {
                colorPart = gCarCustomizeManager.GetInstalledCarPart(slot);
            }
            unsigned char r = colorPart->GetAppliedAttributeIParam(bStringHash("RED"), 0);
            unsigned char g = colorPart->GetAppliedAttributeIParam(bStringHash("GREEN"), 0);
            unsigned int b = colorPart->GetAppliedAttributeIParam(bStringHash("BLUE"), 0);
            colors[idx] = (static_cast<unsigned int>(r) << 16) | (static_cast<unsigned int>(g) << 8) | 0xff000000 | (b & 0xff);
            slot++;
            idx++;
        } while (idx < 3);
        FEngSetColor(FEngFindObject(GetPackageName(), 0x5d19f25), colors[0]);
        FEngSetColor(FEngFindObject(GetPackageName(), 0xc0721eb9), colors[2]);
        FEngSetColor(FEngFindObject(GetPackageName(), 0xc62ad685), colors[2]);
        FEngSetColor(FEngFindObject(GetPackageName(), 0xb8f1f802), colors[2]);
        FEngSetColor(FEngFindObject(GetPackageName(), 0xd312f0cb), colors[1]);
        FEngSetColor(FEngFindObject(GetPackageName(), 0x8fe2a217), colors[1]);
        return;
    }
not_installed:
    FEngSetColor(FEngFindObject(GetPackageName(), 0x5d19f25), 0xffffc373u);
    FEngSetColor(FEngFindObject(GetPackageName(), 0xc0721eb9), 0xffffffffu);
    FEngSetColor(FEngFindObject(GetPackageName(), 0xc62ad685), 0xffffffffu);
    FEngSetColor(FEngFindObject(GetPackageName(), 0xb8f1f802), 0xffffffffu);
    FEngSetColor(FEngFindObject(GetPackageName(), 0xd312f0cb), 0xffffae40u);
    FEngSetColor(FEngFindObject(GetPackageName(), 0x8fe2a217), 0xffffae40u);
}

void CustomizeParts::RefreshHeader() {
    CustomizationScreen::RefreshHeader();
    if (!Options.IsEmpty()) {
        SelectablePart *sel = GetSelectedPart();
        if (sel->GetPart()->HasAppliedAttribute(0x6212682b)) {
            unsigned int tunable = sel->GetPart()->GetAppliedAttributeUParam(0x6212682b, 0);
            if (tunable) {
                FEngSetLanguageHash(GetPackageName(), 0xb94139f4, 0x8098a54c);
            } else {
                FEngSetLanguageHash(GetPackageName(), 0xb94139f4, 0x649f4a65);
            }
        }
        if (Category == 0x307) {
            SetHUDTextures();
            SetHUDColors();
        } else {
            if ((RealTimer - ScrollTime).GetSeconds() > 0.3f) {
                gCarCustomizeManager.PreviewPart(sel->GetSlotID(), sel->GetPart());
            } else {
                bNeedsRefresh = true;
            }
        }
        const char *lang_str = "LANGUAGEHASH";
        if (sel->GetPart()->HasAppliedAttribute(bStringHash(lang_str))) {
            const char *pkg = GetPackageName();
            unsigned int langHash = sel->GetPart()->GetAppliedAttributeUParam(bStringHash(lang_str), 0);
            FEngSetLanguageHash(pkg, 0x5e7b09c9, langHash);
        } else {
            FEPrintf(GetPackageName(), 0x5e7b09c9, "%s", sel->GetPart()->GetName());
        }
    }
}

CustomizeSpoiler::CustomizeSpoiler(ScreenConstructorData *sd) : CustomizationScreen(sd) {
    TheFilter = 0;
    for (int i = 0; i < 4; i++) {
        SelectedIndex[i] = 1;
    }
    Setup();
}

void CustomizeSpoiler::NotificationMessage(u32 msg, FEObject *pobj, u32 param1, u32 param2) {
    CustomizationScreen::NotificationMessage(msg, pobj, param1, param2);
    switch (msg) {
        case __PAD_LTRIGGER__:
            ScrollFilters(eSD_PREV);
            break;
        case __PAD_RTRIGGER__:
            ScrollFilters(eSD_NEXT);
            break;
        case __PAD_LEFT__:
        case __PAD_RIGHT__:
            SelectedIndex[TheFilter] = Options.GetCurrentIndex();
            break;
        case __PAD_BUTTON0__:
            Showcase::FromFilter = TheFilter;
            break;
        case FEMSG_BACK_OUT: {
            SelectablePart *part = FindInCartPart();
            if (!part) {
                return;
            }
            if (gCarCustomizeManager.IsPartInCart(part)) {
                return;
            }
            part->UnSetInCart();
            RefreshHeader();
            break;
        }
        case __PAD_BACK__:
            cFEng::Get()->QueuePackageSwitch(g_pCustomizeSubPkg, GetFromCategory() | (GetCategory() << 16), 0, false);
            break;
    }
}

void CustomizeSpoiler::Setup() {
    SetTitleHash(0x94e73021);
    FEImage *img1 = FEngFindImage(GetPackageName(), 0x91c4a50);
    FEngSetButtonTexture(img1, 0x5bc);
    FEImage *img2 = FEngFindImage(GetPackageName(), 0x2d145be3);
    FEngSetButtonTexture(img2, 0x682);
    CarPart *activePart = gCarCustomizeManager.GetActivePartFromSlot(0x2c);
    if (Showcase::FromFilter != -1) {
        TheFilter = Showcase::FromFilter;
        Showcase::FromFilter = -1;
    } else if (activePart) {
        unsigned int filter = activePart->GetGroupNumber();
        if (filter != 4) {
            TheFilter = filter;
        }
    }
    BuildPartOptionListFromFilter(activePart);
    RefreshHeader();
}

void CustomizeSpoiler::BuildPartOptionListFromFilter(CarPart *activePart) {
    Options.RemoveAll();
    int activeIdx = 1;
    Options.AddInitialBookEnds();
    bTList<SelectablePart> partList;
    gCarCustomizeManager.GetCarPartList(0x2c, partList, 0);
    while (!partList.IsEmpty()) {
        SelectablePart *cur = static_cast<SelectablePart *>(partList.GetHead());
        cur->Remove();
        unsigned int groupNum = cur->GetPart()->GetGroupNumber();
        if (groupNum == static_cast<unsigned int>(TheFilter) || groupNum == 4) {
            unsigned int texHash = 0xbb034ea6;
            unsigned int unlockHash = gCarCustomizeManager.GetUnlockHash(static_cast<eCustomizeCategory>(Category), cur->GetUpgradeLevel());
            if (CustomizeIsInBackRoom()) {
                texHash = 0xc51a4f62;
            }
            CarPart *cpart = cur->GetPart();
            if (cpart->GetAppliedAttributeIParam(bStringHash("SPOILER_TYPE"), 0) != 0) {
                texHash = 0x4d1c18ba;
                if (CustomizeIsInBackRoom()) {
                    texHash = 0x611d142a;
                }
            }
            bool locked = gCarCustomizeManager.IsPartLocked(cur, 0);
            AddPartOption(cur, texHash, cpart->GetUpgradeLevel(), 0, unlockHash, locked);
            if (SelectedIndex[TheFilter] == 1) {
                if (activePart && cur->GetPart() == activePart) {
                    SelectedIndex[TheFilter] = activeIdx;
                }
                activeIdx++;
            }
        } else {
            delete cur;
        }
    }
    if (Showcase::FromIndex == 0) {
        Options.SetInitialPos(SelectedIndex[TheFilter]);
    } else {
        SelectedIndex[TheFilter] = Showcase::FromIndex;
        Options.SetInitialPos(Showcase::FromIndex);
        Showcase::FromIndex = 0;
    }
}

void CustomizeSpoiler::RefreshHeader() {
    CustomizationScreen::RefreshHeader();
    int filter = TheFilter;
    switch (filter) {
        case 0:
            FEngSetLanguageHash(GetPackageName(), 0x78008599, 0x1f0e2b2);
            break;
        case 1:
            FEngSetLanguageHash(GetPackageName(), 0x78008599, 0x205b328);
            break;
        case 2:
            FEngSetLanguageHash(GetPackageName(), 0x78008599, 0x9912746);
            break;
        case 3:
            FEngSetLanguageHash(GetPackageName(), 0x78008599, 0xe7416fc);
            break;
        default:
            break;
    }
    SelectablePart *sel = GetSelectedPart();
    int elapsed = RealTimer.GetPackedTime() - ScrollTime.GetPackedTime();
    Timer scrollDelay;
    scrollDelay.SetTime(0.3f);
    if (elapsed > scrollDelay.GetPackedTime()) {
        gCarCustomizeManager.PreviewPart(sel->GetSlotID(), sel->GetPart());
    } else {
        bNeedsRefresh = true;
    }
    const char *lang_str = "LANGUAGEHASH";
    CarPart *part = sel->GetPart();
    if (part->HasAppliedAttribute(bStringHash(lang_str))) {
        const char *pkg = GetPackageName();
        unsigned int langHash = sel->GetPart()->GetAppliedAttributeUParam(bStringHash(lang_str), 0);
        FEngSetLanguageHash(pkg, 0x5e7b09c9, langHash);
    } else {
        FEPrintf(GetPackageName(), 0x5e7b09c9, "%s", sel->GetPart()->GetName());
    }
}

void CustomizeSpoiler::ScrollFilters(eScrollDir dir) {
    int filter = TheFilter;
    if (dir == eScrollDir(-1)) {
        filter--;
        if (filter < 0) {
            filter = 3;
        }
    } else if (dir == eScrollDir(1)) {
        filter++;
        if (filter > 3) {
            filter = 0;
        }
    }
    if (filter != TheFilter) {
        TheFilter = filter;
        BuildPartOptionListFromFilter(nullptr);
        RefreshHeader();
    }
}

HUDLayerOption::HUDLayerOption(uint32 layer, uint32 icon_hash, uint32 name_hash)
    : CustomizePartOption(nullptr, icon_hash, name_hash, 0, 0), //
      HUDLayer(layer),                                          //
      SelectedPart(nullptr) {
    gCarCustomizeManager.GetCarPartList(layer, TheColors, 0);
}

CustomizeHUDColor::CustomizeHUDColor(ScreenConstructorData *sd)
    : CustomizationScreen(sd), //
      SelectedColor(nullptr),  //
      Cursor(nullptr),         //
      bTexturesNeedUnload(false) {
    Cursor = FEngFindObject(GetPackageName(), 0xB893252A);
    Setup();
}

CustomizeHUDColor::~CustomizeHUDColor() {
    if (CustomizeParts::TexturePackLoaded && bTexturesNeedUnload) {
        UnLoadCustomHUDPacksAndTextures();
    }
}

void CustomizeHUDColor::NotificationMessage(u32 msg, FEObject *pobj, u32 param1, u32 param2) {
    if (msg == __PAD_LEFT__ || msg == __PAD_RIGHT__) {
        HUDLayerOption *layer = static_cast<HUDLayerOption *>(Options.GetCurrentOption());
        layer->SelectedPart = SelectedColor->ThePart;
    }
    if (msg != 0x91dfdf84) {
        CustomizationScreen::NotificationMessage(msg, pobj, param1, param2);
    }
    switch (msg) {
        case __PAD_LEFT__:
        case __PAD_RIGHT__:
            BuildColorOptions();
            RefreshHeader();
            break;
        case __PAD_UP__:
            ScrollColors(eSD_PREV);
            break;
        case __PAD_DOWN__:
            ScrollColors(eSD_NEXT);
            break;
        case 0x91dfdf84: {
            SelectablePart *temp = gCarCustomizeManager.GetTempColoredPart();
            ShoppingCartItem *inCart = gCarCustomizeManager.IsPartTypeInCart(0x84u);
            if (inCart && temp->GetPart() == inCart->GetBuyingPart()->GetPart()) {
                int slot = 0x85;
                do {
                    ShoppingCartItem *colorItem = gCarCustomizeManager.IsPartTypeInCart(static_cast<unsigned int>(slot));
                    slot++;
                    gCarCustomizeManager.RemoveFromCart(colorItem);
                } while (slot < 0x88);
            }
            gCarCustomizeManager.AddToCart(temp);
            gCarCustomizeManager.ClearTempColoredPart();
            HUDColorOption *node = static_cast<HUDColorOption *>(ColorOptions.GetHead());
            while (node != reinterpret_cast<HUDColorOption *>(&ColorOptions)) {
                if (node->ThePart->GetPartState() != 0) {
                    gCarCustomizeManager.AddToCart(node->ThePart);
                }
                node = static_cast<HUDColorOption *>(node->Next);
            }
            cFEng::Get()->QueuePackageSwitch(g_pCustomizeHudPkg, Category | (FromCategory << 16), 0, false);
            break;
        }
        case __PAD_BACK__:
            gCarCustomizeManager.ClearTempColoredPart();
            cFEng::Get()->QueuePackageSwitch(g_pCustomizeHudPkg, Category | (FromCategory << 16), 0, false);
            break;
        case 0xcf91aacd:
            gCarCustomizeManager.ClearTempColoredPart();
            bNeedsRefresh = true;
            break;
    }
}

void CustomizeHUDColor::ScrollColors(eScrollDir dir) {
    HUDColorOption *prev = SelectedColor;
    if (dir == eSD_PREV) {
        HUDColorOption *node = static_cast<HUDColorOption *>(prev->Prev);
        if (node == reinterpret_cast<HUDColorOption *>(&ColorOptions)) {
            node = static_cast<HUDColorOption *>(ColorOptions.GetTail());
        }
        SelectedColor = node;
    } else if (dir == eSD_NEXT) {
        HUDColorOption *node = static_cast<HUDColorOption *>(prev->Next);
        if (node == reinterpret_cast<HUDColorOption *>(&ColorOptions)) {
            node = static_cast<HUDColorOption *>(ColorOptions.GetHead());
        }
        SelectedColor = node;
    }
    if (SelectedColor != prev) {
        HUDLayerOption *layer = static_cast<HUDLayerOption *>(Options.GetCurrentOption());
        layer->SelectedPart = SelectedColor->ThePart;
        FEngSetScript(prev->FEngObject, 0x7ab5521a, true);
        FEngSetScript(SelectedColor->FEngObject, 0x249db7b7, true);
        float x, y;
        FEngGetTopLeft(SelectedColor->FEngObject, x, y);
        float dx, dy;
        FEngGetTopLeft(SelectedColor->FEngObject, dx, dy);
        FEngSetTopLeft(Cursor, x + dx, y + dy);
        RefreshHeader();
    }
}

void CustomizeHUDColor::AddLayerOption(uint32 layer, uint32 icon_hash, uint32 name_hash) {
    HUDLayerOption *opt = new HUDLayerOption(layer, icon_hash, name_hash);
    AddOption(opt);
}

void CustomizeHUDColor::Setup() {
    DisplayHelper.SetTitleHash(0xb1b0e8af);
    AddLayerOption(0x86, 0x70f56628, 0xe18ddce1);
    AddLayerOption(0x87, 0xbf6682c9, 0xe18ddce0);
    AddLayerOption(0x85, 0xcc9e1ce4, 0xe18ddcdf);
    if (Showcase::FromIndex) {
        SetInitialOption(Showcase::FromIndex);
        Showcase::FromIndex = 0;
    } else {
        SetInitialOption(1);
    }
    BuildColorOptions();
    SetHUDTextures();
    SetInitialColors();
    RefreshHeader();
}

void CustomizeHUDColor::SetInitialColors() {
    ShoppingCartItem *hudInCart = gCarCustomizeManager.IsPartTypeInCart(0x84u);
    CarPart *installedHud = gCarCustomizeManager.GetInstalledCarPart(0x84);
    unsigned int colors[5];
    colors[0] = 0xffffc373u;
    colors[1] = 0xffffae40u;
    colors[2] = 0xffffffffu;
    SelectablePart *temp = gCarCustomizeManager.GetTempColoredPart();
    if (hudInCart && temp->GetPart() == hudInCart->GetBuyingPart()->GetPart()) {
        int slot = 0x85;
        int idx = 0;
        do {
            ShoppingCartItem *colorItem = gCarCustomizeManager.IsPartTypeInCart(static_cast<unsigned int>(slot));
            slot++;
            if (colorItem) {
                CarPart *colorPart = colorItem->GetBuyingPart()->GetPart();
                unsigned int r = colorPart->GetAppliedAttributeIParam(bStringHash("RED"), 0);
                unsigned int g = colorPart->GetAppliedAttributeIParam(bStringHash("GREEN"), 0);
                unsigned int b = colorPart->GetAppliedAttributeIParam(bStringHash("BLUE"), 0);
                colors[idx] = ((r & 0xff) << 16) | ((g & 0xff) << 8) | 0xff000000 | (b & 0xff);
            }
            idx++;
        } while (idx < 3);
    } else if (temp->GetPart() == installedHud) {
        int slot = 0x85;
        int idx = 0;
        do {
            CarPart *colorPart = gCarCustomizeManager.GetInstalledCarPart(slot);
            slot++;
            if (colorPart) {
                unsigned int r = colorPart->GetAppliedAttributeIParam(bStringHash("RED"), 0);
                unsigned int g = colorPart->GetAppliedAttributeIParam(bStringHash("GREEN"), 0);
                unsigned int b = colorPart->GetAppliedAttributeIParam(bStringHash("BLUE"), 0);
                colors[idx] = ((r & 0xff) << 16) | ((g & 0xff) << 8) | 0xff000000 | (b & 0xff);
            }
            idx++;
        } while (idx < 3);
    }
    FEngSetColor(FEngFindObject(GetPackageName(), 0x5d19f25), colors[0]);
    FEngSetColor(FEngFindObject(GetPackageName(), 0xd312f0cb), colors[1]);
    FEngSetColor(FEngFindObject(GetPackageName(), 0x8fe2a217), colors[1]);
    FEngSetColor(FEngFindObject(GetPackageName(), 0xc0721eb9), colors[2]);
    FEngSetColor(FEngFindObject(GetPackageName(), 0xc62ad685), colors[2]);
    FEngSetColor(FEngFindObject(GetPackageName(), 0xb8f1f802), colors[2]);
}

void CustomizeHUDColor::SetHUDTextures() {
    float redline = Physics::Info::Redline(*reinterpret_cast<const Attrib::Gen::pvehicle *>(0x804ab3ec));
    int rpm = static_cast<int>(redline);
    int tachRPM;
    if (rpm >= 0x251d) {
        tachRPM = 10000;
    } else if (rpm >= 0x2135) {
        tachRPM = 9000;
    } else if (rpm > 0x1d4c) {
        tachRPM = 8000;
    } else {
        tachRPM = 7000;
    }
    CarPart *part = gCarCustomizeManager.GetTempColoredPart()->GetPart();
    unsigned int hudStyleHash = FEngHashString("HUD_STYLE");
    int hudStyle = part->GetAppliedAttributeIParam(hudStyleHash, 0);
    const char *pkg = GetPackageName();
    unsigned int hash = FEngHashString("HUD_NEEDLE_%d_%02d", tachRPM, hudStyle);
    FEngSetTextureHash(FEngFindImage(pkg, 0xc0721eb9), hash);
    pkg = GetPackageName();
    hash = FEngHashString("HUD_GAUGE_%02d", hudStyle);
    FEngSetTextureHash(FEngFindImage(pkg, 0x5d19f25), hash);
    pkg = GetPackageName();
    hash = FEngHashString("HUD_SPEEDOMETER_%02d", hudStyle);
    FEngSetTextureHash(FEngFindImage(pkg, 0xd312f0cb), hash);
    if (gCarCustomizeManager.IsTurbo()) {
        pkg = GetPackageName();
        hash = FEngHashString("HUD_NEEDLE_TURBO_%02d", hudStyle);
        FEngSetTextureHash(FEngFindImage(pkg, 0xc62ad685), hash);
        pkg = GetPackageName();
        hash = FEngHashString("HUD_NOS_%02d", hudStyle);
        FEngSetTextureHash(FEngFindImage(pkg, 0x8fe2a217), hash);
        FEngSetVisible(FEngFindObject(GetPackageName(), 0xc5d551b7));
    } else {
        FEngSetInvisible(FEngFindObject(GetPackageName(), 0xc5d551b7));
    }
}

void CustomizeHUDColor::RefreshHeader() {
    CustomizationScreen::RefreshHeader();
    HUDColorOption *sel = SelectedColor;
    switch (sel->ThePart->GetSlotID()) {
        case 0x85: {
            unsigned int color = sel->color;
            FEngSetColor(FEngFindObject(GetPackageName(), 0x5d19f25), color);
            break;
        }
        case 0x87: {
            unsigned int color = sel->color;
            FEngSetColor(FEngFindObject(GetPackageName(), 0xc0721eb9), color);
            color = SelectedColor->color;
            FEngSetColor(FEngFindObject(GetPackageName(), 0xc62ad685), color);
            color = SelectedColor->color;
            FEngSetColor(FEngFindObject(GetPackageName(), 0xb8f1f802), color);
            break;
        }
        case 0x86: {
            unsigned int color = sel->color;
            FEngSetColor(FEngFindObject(GetPackageName(), 0xd312f0cb), color);
            color = SelectedColor->color;
            FEngSetColor(FEngFindObject(GetPackageName(), 0x8fe2a217), color);
            break;
        }
    }
}

void CustomizeHUDColor::BuildColorOptions() {
    if (SelectedColor) {
        FEngSetScript(SelectedColor->FEngObject, 0x7ab5521a, true);
        SelectedColor = nullptr;
    }
    HUDLayerOption *opt = static_cast<HUDLayerOption *>(Options.GetCurrentOption());
    if (opt && !opt->TheColors.IsEmpty()) {
        ColorOptions.DeleteAllElements();
        int i = 0;
        ShoppingCartItem *cart_item = gCarCustomizeManager.IsPartTypeInCart(0x84u);
        CarPart *installed_hud = gCarCustomizeManager.GetInstalledCarPart(0x84);
        SelectablePart *part = opt->TheColors.GetHead();
        while (part != opt->TheColors.EndOfList()) {
            i++;
            HUDColorOption *color_option = new HUDColorOption(part);
            FEImage *obj = FEngFindImage(GetPackageName(), FEngHashString("COLOR_%d", i));
            color_option->SetFEngObject(obj);
            ColorOptions.AddTail(color_option);
            unsigned char r = part->GetPart()->GetAppliedAttributeIParam(bStringHash("RED"), 0);
            unsigned char g = part->GetPart()->GetAppliedAttributeIParam(bStringHash("GREEN"), 0);
            unsigned char b = part->GetPart()->GetAppliedAttributeIParam(bStringHash("BLUE"), 0);
            unsigned int color = static_cast<unsigned int>(g) << 8;
            color |= 0xFF000000;
            color |= static_cast<unsigned int>(r) << 16;
            color |= static_cast<unsigned int>(b);
            color_option->color = color;
            FEngSetColor(obj, color);
            if (!opt->SelectedPart) {
                if (cart_item && gCarCustomizeManager.GetTempColoredPart()->GetPart() == cart_item->GetBuyingPart()->GetPart()) {
                    if (gCarCustomizeManager.IsPartInCart(part)) {
                        SelectedColor = color_option;
                        opt->SelectedPart = part;
                    }
                } else if (gCarCustomizeManager.GetTempColoredPart()->GetPart() == installed_hud) {
                    if (gCarCustomizeManager.IsPartInstalled(part)) {
                        SelectedColor = color_option;
                        opt->SelectedPart = part;
                    }
                }
            } else if (opt->SelectedPart == part) {
                SelectedColor = color_option;
            }
            part = part->GetNext();
        }
        if (!SelectedColor) {
            SelectedColor = ColorOptions.GetHead();
        }
        float x_offset = 69.0f;
        float y_offset = 56.0f;
        FEObject *cursor_obj = Cursor;
        float x = FEngGetTopLeftX(SelectedColor->FEngObject);
        x += x_offset;
        float y = FEngGetTopLeftY(SelectedColor->FEngObject);
        FEngSetTopLeft(cursor_obj, x, y + y_offset);
    }
}

CustomizeRims::CustomizeRims(ScreenConstructorData *sd)
    : CustomizationScreen(sd), //
      InnerRadius(0xf),        //
      MinRadius(0xf),          //
      MaxRadius(0xf) {
    Setup();
}

void CustomizeRims::NotificationMessage(u32 msg, FEObject *pobj, u32 param1, u32 param2) {
    CustomizationScreen::NotificationMessage(msg, pobj, param1, param2);
    switch (msg) {
        case __PAD_BUTTON0__:
            Showcase::FromFilter = InnerRadius;
            break;
        case __PAD_LTRIGGER__:
            ScrollRimSizes(eSD_PREV);
            break;
        case __PAD_RTRIGGER__:
            ScrollRimSizes(eSD_NEXT);
            break;
        case FEMSG_BACK_OUT: {
            SelectablePart *part = FindInCartPart();
            if (part && !gCarCustomizeManager.IsPartInCart(part)) {
                part->UnSetInCart();
                RefreshHeader();
            }
            break;
        }
        case __PAD_ACCEPT__:
            break;
        case __PAD_BACK__:
            cFEng::Get()->QueuePackageSwitch(g_pCustomizeSubTopPkg, GetFromCategory() | (GetCategory() << 16), 0, false);
            break;
    }
}

void CustomizeRims::ScrollRimSizes(eScrollDir dir) {
    int radius = InnerRadius;
    if (dir == eSD_PREV) {
        radius--;
        if (radius < MinRadius) {
            radius = MaxRadius;
        }
    } else if (dir == eSD_NEXT) {
        radius++;
        if (radius > MaxRadius) {
            radius = MinRadius;
        }
    }
    if (radius != InnerRadius) {
        InnerRadius = radius;
        BuildRimsList(Options.GetCurrentIndex());
        RefreshHeader();
    }
}

void CustomizeRims::Setup() {
    FEImage *leftBtn = FEngFindImage(GetPackageName(), 0x91c4a50);
    FEngSetButtonTexture(leftBtn, 0x5bc);
    FEImage *rightBtn = FEngFindImage(GetPackageName(), 0x2d145be3);
    FEngSetButtonTexture(rightBtn, 0x682);
    DisplayHelper.SetTitleHash(0xe167f7c8);
    InnerRadius = gCarCustomizeManager.GetMinInnerRadius();
    MinRadius = InnerRadius;
    MaxRadius = gCarCustomizeManager.GetMaxInnerRadius();
    CarPart *activePart = gCarCustomizeManager.GetActivePartFromSlot(CARSLOTID_FRONT_WHEEL);
    if (Showcase::FromFilter != -1) {
        InnerRadius = Showcase::FromFilter;
        Showcase::FromFilter = -1;
    } else if (activePart) {
        InnerRadius = static_cast<signed char>(activePart->GetAppliedAttributeIParam(0xeb0101e2, 0));
    }
    BuildRimsList(-1);
    RefreshHeader();
}

void CustomizeRims::BuildRimsList(int selected_index) {
    Options.RemoveAll();
    Options.AddInitialBookEnds();
    int installed_index = 0;
    int current_part_index = 1;
    CarPart *activeMatch = nullptr;
    bTList<SelectablePart> tempList;
    gCarCustomizeManager.GetCarPartList(0x42, tempList, GetCategoryBrandHash());
    if (selected_index == -1) {
        activeMatch = gCarCustomizeManager.GetActivePartFromSlot(0x42);
    }
    while (tempList.GetHead() != reinterpret_cast<bNode *>(&tempList)) {
        SelectablePart *node = static_cast<SelectablePart *>(tempList.GetHead());
        node->Prev->Next = node->Next;
        node->Next->Prev = node->Prev;
        signed char rimSize = static_cast<signed char>(node->GetPart()->GetAppliedAttributeIParam(0xeb0101e2, 0));
        if (static_cast<int>(rimSize) == InnerRadius) {
            unsigned int unlockHash = gCarCustomizeManager.GetUnlockHash(static_cast<eCustomizeCategory>(Category), node->GetUpgradeLevel());
            unsigned char gl = *reinterpret_cast<unsigned char *>(reinterpret_cast<int>(node->GetPart()) + 5);
            unsigned int wheelPos = gl >> 5;
            bool locked = gCarCustomizeManager.IsPartLocked(node, 0);
            AddPartOption(node, 0x294d2a3, wheelPos, 0, unlockHash, locked);
            if (activeMatch && node->GetPart() == activeMatch) {
                installed_index = current_part_index;
            }
            current_part_index++;
        } else {
            delete node;
        }
    }
    if (selected_index == -1) {
        selected_index = 1;
        if (activeMatch) {
            selected_index = installed_index;
        }
    }
    if (Showcase::FromIndex != 0) {
        SetInitialOption(0);
        Showcase::FromIndex = 0;
    } else {
        SetInitialOption(selected_index);
    }
    // Clean up remaining temp list nodes
    while (tempList.GetHead() != reinterpret_cast<bNode *>(&tempList)) {
        SelectablePart *del = static_cast<SelectablePart *>(tempList.GetHead());
        del->Prev->Next = del->Next;
        del->Next->Prev = del->Prev;
        delete del;
    }
}

void CustomizeRims::RefreshHeader() {
    CustomizationScreen::RefreshHeader();

    if (Options.IsEmpty()) {
        return;
    }

    SelectablePart *part = GetSelectedPart();
    gCarCustomizeManager.PreviewPart(part->GetSlotID(), part->GetPart());
    FEPrintf(GetPackageName(), 0xe6782841, "%$d\"", InnerRadius);
    char sztemp[64];
    const char *name = part->GetPart()->GetName();
    bSNPrintf(sztemp, 64, "%s", name);
    int len = bStrLen(sztemp);
    for (int i = len; i >= len - 6; i--) {
        sztemp[i] = 0;
    }
    FEPrintf(GetPackageName(), 0x5e7b09c9, "%s", sztemp);
}

uint32 CustomizeRims::GetCategoryBrandHash() {
    switch (Category) {
        case 0x702:
            return 0x352d08d1;
        case 0x703:
            return 0x9136;
        case 0x704:
            return 0x9536;
        case 0x705:
            return 0x2b77feb;
        case 0x706:
            return 0x324ac97;
        case 0x707:
            return 0x48e25793;
        case 0x708:
            return 0xdd544a02;
        case 0x709:
            return 0x648;
        case 0x70a:
            return 0x1e6a3b;
        case 0x70b:
            return 0x1c386b;
        default:
            return 0;
    }
}

CustomizePaint::CustomizePaint(ScreenConstructorData *sd)
    : CustomizationScreen(sd),            //
      TheFilter(-1),                      //
      MatchingPaint(nullptr, 0, 0, 0, 0), //
      ThePaints(sd->PackageFilename, 20, 4, true) {
    NumRemapColors = 0;
    for (int i = 0; i <= 2; i++) {
        VinylColors[i] = nullptr;
    }
    ThePaints.SetMouseDownMsg(__PAD_ACCEPT__);
    Setup();
}

eMenuSoundTriggers CustomizePaint::NotifySoundMessage(u32 msg, eMenuSoundTriggers maybe) {
    if (static_cast<unsigned int>(maybe - 0x29) < 2) {
        if (Category == 0x303) {
            return UISND_NONE;
        }
        SelectablePart *temp = gCarCustomizeManager.GetTempColoredPart();
        if (temp) {
            CarPart *part = temp->GetPart();
            if (part && part->GetAppliedAttributeUParam(0x6212682b, 0) < 2) {
                return UISND_NONE;
            }
        }
    }
    return maybe;
}

void CustomizePaint::NotificationMessage(u32 msg, FEObject *pobj, u32 param1, u32 param2) {
    switch (msg) {
        case __PAD_ACCEPT__:
            if (Category == 0x301 || Category == 0x303) {
                CustomizationScreen::NotificationMessage(__PAD_ACCEPT__, pobj, param1, param2);
            }
            break;
        default:
            CustomizationScreen::NotificationMessage(msg, pobj, param1, param2);
            break;
        case __PAD_LEFT__:
        case __PAD_RIGHT__:
            break;
    }

    ThePaints.NotificationMessage(msg, pobj, param1, param2);

    switch (msg) {
        case __PAD_BUTTON0__:
            Showcase::FromFilter = TheFilter;
            Showcase::FromIndex = ThePaints.GetCurrentDatumNum();
#ifndef EA_BUILD_A124
            for (int i = 0; i < 3; i++) {
                Showcase::FromColor[i] = VinylColors[i];
            }
#endif
            break;
        case __PAD_LTRIGGER__:
            ScrollFilters(eSD_PREV);
            break;
        case __PAD_RTRIGGER__:
            ScrollFilters(eSD_NEXT);
            break;
        case __PAD_ACCEPT__:
            if (Category == 0x301 || Category == 0x303) {
                return;
            }
            {
                CarPart *installed = gCarCustomizeManager.GetTempColoredPart()->GetPart();
                if (VinylColors[TheFilter]) {
                    delete VinylColors[TheFilter];
                }
                int savedFilter = TheFilter;
                bool add_to_cart = false;
                SelectablePart *newPart = new SelectablePart(gCarCustomizeManager.GetTempColoredPart());
                VinylColors[savedFilter] = newPart;
                if (installed != gCarCustomizeManager.GetActivePartFromSlot(0x4d)) {
                    add_to_cart = true;
                } else {
                    for (int i = 0; i < NumRemapColors; i++) {
                        CarPart *active = gCarCustomizeManager.GetActivePartFromSlot(i + 0x4f);
                        if (VinylColors[i] && active != VinylColors[i]->GetPart()) {
                            add_to_cart = true;
                            break;
                        }
                    }
                }
                if (!add_to_cart) {
                    return;
                }
                AddVinylAndColorsToCart();
            }
            {
                unsigned int cat = Category | (FromCategory << 16);
                cFEng::Get()->QueuePackageSwitch(g_pCustomizePartsPkg, cat, 0, false);
            }
            break;
        case __PAD_BACK__:
            if (Category == 0x301 || Category == 0x303) {
                unsigned int cat = Category | (FromCategory << 16);
                cFEng::Get()->QueuePackageSwitch(g_pCustomizeSubPkg, cat, 0, false);
                return;
            }
            for (int i = 0; i < 3; i++) {
                if (VinylColors[i]) {
                    delete VinylColors[i];
                }
                VinylColors[i] = nullptr;
#ifndef EA_BUILD_A124
                Showcase::FromColor[i] = nullptr;
#endif
            }
            gCarCustomizeManager.ResetPreview();
            {
                unsigned int cat = Category | (FromCategory << 16);
                cFEng::Get()->QueuePackageSwitch(g_pCustomizePartsPkg, cat, 0, false);
            }
            break;
        case 0x5a928018: {
            SelectablePart *part = GetSelectedPart();
            if (part && !gCarCustomizeManager.IsPartInCart(part)) {
                part->UnSetInCart();
                RefreshHeader();
            }
            RefreshHeader();
            break;
        }
        case __PAD_LEFT__:
        case __PAD_RIGHT__:
        case __PAD_DOWN__:
        case __PAD_UP__:
            RefreshHeader();
            break;
        case 0xcf91aacd:
            for (int i = 0; i < 3; i++) {
                if (VinylColors[i]) {
                    delete VinylColors[i];
                }
                VinylColors[i] = nullptr;
            }
            break;
    }
}

SelectablePart *CustomizePaint::FindInCartPart() {
    int count = ThePaints.GetNumDatum();
    for (int i = 0; i < count; i++) {
        CustomizePaintDatum *datum = static_cast<CustomizePaintDatum *>(ThePaints.GetDatumAt(i));
        SelectablePart *part = datum->ThePart;
        if ((part->GetPartState() & 0xF0) == CPS_IN_CART) {
            return part;
        }
    }
    return nullptr;
}

CustomizePartOption *CustomizePaint::FindMatchingOption(SelectablePart *to_find) {
    int count = ThePaints.GetNumDatum();
    CustomizePaintDatum *found = nullptr;
    for (int i = 0; i < count; i++) {
        CustomizePaintDatum *datum = static_cast<CustomizePaintDatum *>(ThePaints.GetDatumAt(i));
        if (datum->ThePart->GetPart() == to_find->GetPart()) {
            found = datum;
            break;
        }
    }
    if (found) {
        MatchingPaint.SetPart(found->ThePart);
        return &MatchingPaint;
    } else {
        return nullptr;
    }
}

void CustomizePaint::AddVinylAndColorsToCart() {
    SelectablePart *mainPart = gCarCustomizeManager.GetTempColoredPart();
    gCarCustomizeManager.AddToCart(mainPart);
    for (int i = 0; i < NumRemapColors; i++) {
        if (VinylColors[i]) {
            gCarCustomizeManager.AddToCart(VinylColors[i]);
            VinylColors[i] = nullptr;
        }
    }
}

void CustomizePaint::ScrollFilters(eScrollDir dir) {
    int maxFilter;
    if (Category == 0x301) {
        maxFilter = 2;
    } else if (Category == 0x303) {
        return;
    } else {
        maxFilter = NumRemapColors - 1;
        if (maxFilter != 0) {
            SelectablePart *current = GetSelectedPart();
            if (current != VinylColors[TheFilter]) {
                if (VinylColors[TheFilter]) {
                    delete VinylColors[TheFilter];
                }
                int savedFilter = TheFilter;
                SelectablePart *newPart = new SelectablePart(gCarCustomizeManager.GetTempColoredPart());
                VinylColors[savedFilter] = newPart;
            }
        }
    }
    int cur = TheFilter;
    int next;
    if (dir == eSD_PREV) {
        next = cur - 1;
        if (next < 0) {
            next = maxFilter;
        }
    } else if (dir == eSD_NEXT) {
        next = cur + 1;
        if (next > maxFilter) {
            next = 0;
        }
    } else {
        next = cur;
    }
    if (next != cur) {
        SelectedIndex[TheFilter] = ThePaints.GetCurrentDatumNum() - 1;
        TheFilter = next;
        if (Category == 0x301 || Category == 0x303) {
            SelectablePart *sel = GetSelectedPart();
            BuildSwatchList(sel->GetSlotID());
        } else {
            BuildSwatchList(next + 0x4f);
        }
        RefreshHeader();
    }
}

void CustomizePaint::Setup() {
    FEImage *leftBtn = FEngFindImage(GetPackageName(), 0x91c4a50);
    FEngSetButtonTexture(leftBtn, 0x5bc);
    FEImage *rightBtn = FEngFindImage(GetPackageName(), 0x2d145be3);
    FEngSetButtonTexture(rightBtn, 0x682);
    for (int i = 1; i <= 0x50; i++) {
        ArraySlot *slot = new ArraySlot(FEngFindImage(GetPackageName(), static_cast<int>(FEngHashString("COLOR_%d", i))));
        ThePaints.AddSlot(slot);
    }
    for (int i = 0; i < 3; i++) {
        SelectedIndex[i] = -1;
    }
    if (Showcase::FromFilter != -1) {
        TheFilter = Showcase::FromFilter;
    }
    switch (Category) {
        case 0x301:
            cFEng::Get()->QueuePackageMessage(0x1a7240f3, GetPackageName(), nullptr);
            DisplayHelper.SetTitleHash(0x55da70c);
            SetupBasePaint();
            break;
        case 0x303:
            DisplayHelper.SetTitleHash(0xe126ff53);
            SetupRimPaint();
            break;
        case 0x402:
        case 0x403:
        case 0x404:
        case 0x405:
        case 0x406:
        case 0x407:
        case 0x408:
        case 0x409:
            DisplayHelper.SetTitleHash(0xd8ee1a80);
            SetupVinylColor();
            break;
    }
    Showcase::FromFilter = -1;
    Options.SetInitialized();
    RefreshHeader();
}

void CustomizePaint::SetupBasePaint() {
    BuildSwatchList(0x4C);
}

void CustomizePaint::SetupRimPaint() {
    FEngSetInvisible(GetPackageName(), 0x2C3CC2D3);
    FEngSetInvisible(GetPackageName(), 0x53639A10);
    BuildSwatchList(0x4E);
}

void CustomizePaint::SetupVinylColor() {
    unsigned int slot = 0x4f;
    if (Showcase::FromFilter != -1) {
        if (Showcase::FromFilter == 1) {
            slot = 0x50;
        } else if (Showcase::FromFilter == 2) {
            slot = 0x51;
        }
        Showcase::FromFilter = -1;
    }
    BuildSwatchList(slot);
    CarPart *activePart = gCarCustomizeManager.GetActivePartFromSlot(0x4d);
    NumRemapColors = activePart->GetAppliedAttributeUParam(0x6212682b, 0);
    if (NumRemapColors < 2) {
        FEObject *obj = FEngFindObject(GetPackageName(), 0x2c3cc2d3);
        FEngSetInvisible(obj);
        obj = FEngFindObject(GetPackageName(), 0x53639a10);
        FEngSetInvisible(obj);
    } else {
        cFEng::Get()->QueuePackageMessage(0x1a7240f3, GetPackageName(), nullptr);
    }
#ifndef EA_BUILD_A124
    for (int i = 0; i < 3; i++) {
        int slotID = i + 0x4f;
        if (!Showcase::FromColor[i]) {
            CarPart *active = gCarCustomizeManager.GetActivePartFromSlot(slotID);
            if (!active) {
                VinylColors[i] = nullptr;
            } else {
                SelectablePart *sp = new SelectablePart(active, slotID, active->GetUpgradeLevel(), Physics::Upgrades::PUT_MAX, false,
                                                        static_cast<eCustomizePartState>(1), 0, false);
                VinylColors[i] = sp;
            }
        } else {
            VinylColors[i] = static_cast<SelectablePart *>(Showcase::FromColor[i]);
            Showcase::FromColor[i] = nullptr;
        }
    }
#endif
}

uint32 CustomizePaint::CalcBrandHash(CarPart *part) {
    if (Category == 0x301) {
        switch (TheFilter) {
            case 0:
                return 0x02daab07;
            case 1:
                return 0x03437a52;
            case 2:
                return 0x03797533;
            default:
                return part->GetAppliedAttributeUParam(0xebb03e66, 0);
        }
    } else if (Category == 0x303) {
        return 0xda27;
    }
    return 0x3e871f1;
}

void CustomizePaint::BuildSwatchList(unsigned int slot) {
    CarPart *matchPart = nullptr;
    ThePaints.ClearData();
    int colorIndex = 0;
    switch (slot) {
        case 0x4f:
            colorIndex = 0;
            break;
        case 0x50:
            colorIndex = 1;
            break;
        case 0x51:
            colorIndex = 2;
            break;
        default:
            goto skip_color;
    }
#ifndef EA_BUILD_A124
    if (Showcase::FromColor[colorIndex] && !VinylColors[colorIndex]) {
        matchPart = static_cast<SelectablePart *>(Showcase::FromColor[colorIndex])->GetPart();
    }
#endif
skip_color:
    if (!matchPart) {
        matchPart = gCarCustomizeManager.GetActivePartFromSlot(slot);
    }
    unsigned int brand = CalcBrandHash(matchPart);
    if (TheFilter == -1) {
        if (brand == 0x2daab07) {
            TheFilter = 0;
        } else if (brand > 0x2daab07) {
            if (brand == 0x3437a52) {
                TheFilter = 1;
            } else if (brand == 0x3797533) {
                TheFilter = 2;
            }
        } else if (brand == 0xda27) {
            TheFilter = 0;
        } else {
            TheFilter = 0;
        }
    }
    bTList<SelectablePart> partList;
    gCarCustomizeManager.GetCarPartList(slot, partList, 0);
    int datumIndex = 0;
    while (partList.GetHead() != partList.EndOfList()) {
        SelectablePart *sp = static_cast<SelectablePart *>(partList.GetHead());
        unsigned int partBrand = sp->GetPart()->GetAppliedAttributeUParam(0xebb03e66, 0);
        if (partBrand == brand) {
            sp->Remove();
            unsigned int unlockHash = gCarCustomizeManager.GetUnlockHash(static_cast<eCustomizeCategory>(Category), sp->GetPart()->GetUpgradeLevel());
            CustomizePaintDatum *datum = new CustomizePaintDatum(sp, unlockHash);
            if (SelectedIndex[TheFilter] == -1 && matchPart == sp->GetPart()) {
                SelectedIndex[TheFilter] = datumIndex;
            }
            ThePaints.AddDatum(datum);
            ArraySlot *aslot = ThePaints.GetSlotAt(datumIndex);
            if (aslot) {
                unsigned char r = datum->ThePart->GetPart()->GetAppliedAttributeIParam(bStringHash("RED"), 0);
                unsigned char g = datum->ThePart->GetPart()->GetAppliedAttributeIParam(bStringHash("GREEN"), 0);
                unsigned char b = datum->ThePart->GetPart()->GetAppliedAttributeIParam(bStringHash("BLUE"), 0);
                FEngSetColor(aslot->GetFEngObject(), 0xff000000 | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
            }
            datumIndex++;
        } else {
            sp->Remove();
            delete sp;
        }
    }
    if (Showcase::FromIndex != 0) {
        SelectedIndex[TheFilter] = Showcase::FromIndex - 1;
        Showcase::FromIndex = 0;
    } else {
        if (SelectedIndex[TheFilter] == -1) {
            SelectedIndex[TheFilter] = 0;
        }
        ThePaints.SetInitialPosition(SelectedIndex[TheFilter]);
    }
    RefreshHeader();
    while (partList.GetHead() != partList.EndOfList()) {
        SelectablePart *sp = static_cast<SelectablePart *>(partList.GetHead());
        sp->Remove();
        delete sp;
    }
}

void CustomizePaint::RefreshHeader() {
    DisplayHelper.DrawTitle();
    ThePaints.RefreshHeader();
    int filter = TheFilter;
    unsigned int hash = 0;
    switch (filter) {
        case 0:
            if (Category == 0x301) {
                hash = 0xb6763cde;
            } else if (NumRemapColors == 2) {
                hash = 0x5198ba16;
            } else if (NumRemapColors == 3) {
                hash = 0x5198ba17;
            } else {
                hash = 0xd8ee1a80;
            }
            break;
        case 1:
            if (Category == 0x301) {
                hash = 0x452b5481;
            } else if (NumRemapColors == 2) {
                hash = 0x5198be57;
            } else if (NumRemapColors == 3) {
                hash = 0x5198be58;
            }
            break;
        case 2:
            if (Category == 0x301) {
                hash = 0xb715070a;
            } else if (NumRemapColors == 3) {
                hash = 0x5198c299;
            }
            break;
    }
    FEngSetLanguageHash(GetPackageName(), 0x78008599, hash);
    if (Category == 0x301) {
        SelectablePart *sel = GetSelectedPart();
        int slotID = sel->GetSlotID();
        sel = GetSelectedPart();
        gCarCustomizeManager.PreviewPart(slotID, sel->GetPart());
    } else if (Category == 0x303) {
        SelectablePart *sel = GetSelectedPart();
        int slotID = sel->GetSlotID();
        sel = GetSelectedPart();
        gCarCustomizeManager.PreviewPart(slotID, sel->GetPart());
        FEObject *obj = FEngFindObject(GetPackageName(), 0x2c526172);
        FEngSetInvisible(obj);
        FEngSetLanguageHash(GetPackageName(), 0x78008599, 0xb3100a3e);
    } else {
        gCarCustomizeManager.PreviewPart(gCarCustomizeManager.GetTempColoredPart()->GetSlotID(),
                                         gCarCustomizeManager.GetTempColoredPart()->GetPart());
        if (NumRemapColors == 1) {
            FEObject *obj = FEngFindObject(GetPackageName(), 0x2c526172);
            FEngSetInvisible(obj);
        }
        for (int i = 0; i < 3; i++) {
            if (i < NumRemapColors && VinylColors[i]) {
                gCarCustomizeManager.PreviewPart(VinylColors[i]->GetSlotID(), VinylColors[i]->GetPart());
            }
        }
        SelectablePart *sel = GetSelectedPart();
        int slotID = sel->GetSlotID();
        sel = GetSelectedPart();
        gCarCustomizeManager.PreviewPart(slotID, sel->GetPart());
    }
    SelectablePart *sel = GetSelectedPart();
    DisplayHelper.SetCareerStuff(sel, Category, 0);
    sel = GetSelectedPart();
    unsigned int unlockBlurb = static_cast<CustomizePaintDatum *>(ThePaints.GetCurrentDatum())->UnlockBlurb;
    int curNum = ThePaints.GetCurrentDatumNum();
    int totalNum = ThePaints.GetCurrentDatumNum();
    DisplayHelper.SetPartStatus(sel, unlockBlurb, curNum, totalNum);
}

CustomizeDecals::CustomizeDecals(ScreenConstructorData *sd)
    : CustomizationScreen(sd), //
      bIsBlack(true) {
    Setup();
}

void CustomizeDecals::NotificationMessage(u32 msg, FEObject *pobj, u32 param1, u32 param2) {
    CustomizationScreen::NotificationMessage(msg, pobj, param1, param2);
    switch (msg) {
        case __PAD_BUTTON0__:
            Showcase::FromFilter = bIsBlack;
            break;
        case __PAD_LTRIGGER__:
        case __PAD_RTRIGGER__:
            bIsBlack ^= 1;
            {
                CustomizePartOption *opt = GetSelectedOption();
                if (opt->GetPart()) {
                    unsigned int nameHash = opt->GetPart()->GetPart()->GetAppliedAttributeUParam(0xebb03e66, 0);
                    BuildDecalList(nameHash);
                } else {
                    BuildDecalList(0);
                }
            }
            RefreshHeader();
            break;
        case 0x5a928018: {
            SelectablePart *sel = GetSelectedPart();
            if (sel) {
                if (gCarCustomizeManager.IsPartInCart(sel)) {
                    return;
                }
                sel->UnSetInCart();
                RefreshHeader();
            }
            break;
        }
        case __PAD_BACK__:
            cFEng::Get()->QueuePackageSwitch(g_pCustomizeSubTopPkg, FromCategory | Category << 16, 0, false);
            break;
        case __PAD_BUTTON4__:
            return;
    }
}

uint32 CustomizeDecals::GetSlotIDFromCategory() {
    switch (CurrentDecalLocation) {
        case CC_DECAL_WINDSHIELD:
            return CARSLOTID_DECAL_FRONT_WINDOW_TEX0;
        case CC_DECAL_REAR_WINDOW:
            return CARSLOTID_DECAL_REAR_WINDOW_TEX0;
        case CC_DECAL_LEFT_DOOR:
            switch (Category) {
                case CC_DECAL_SLOT_1:
                    return CARSLOTID_DECAL_LEFT_DOOR_TEX0;
                case CC_DECAL_SLOT_2:
                    return CARSLOTID_DECAL_LEFT_DOOR_TEX1;
                case CC_DECAL_SLOT_3:
                    return CARSLOTID_DECAL_LEFT_DOOR_TEX2;
                case CC_DECAL_SLOT_4:
                    return CARSLOTID_DECAL_LEFT_DOOR_TEX3;
                case CC_DECAL_SLOT_5:
                    return CARSLOTID_DECAL_LEFT_DOOR_TEX4;
                case CC_DECAL_SLOT_6:
                    return CARSLOTID_DECAL_LEFT_DOOR_TEX5;
            }
            // fall through
        case CC_DECAL_RIGHT_DOOR:
            switch (Category) {
                case CC_DECAL_SLOT_1:
                    return CARSLOTID_DECAL_RIGHT_DOOR_TEX0;
                case CC_DECAL_SLOT_2:
                    return CARSLOTID_DECAL_RIGHT_DOOR_TEX1;
                case CC_DECAL_SLOT_3:
                    return CARSLOTID_DECAL_RIGHT_DOOR_TEX2;
                case CC_DECAL_SLOT_4:
                    return CARSLOTID_DECAL_RIGHT_DOOR_TEX3;
                case CC_DECAL_SLOT_5:
                    return CARSLOTID_DECAL_RIGHT_DOOR_TEX4;
                case CC_DECAL_SLOT_6:
                    return CARSLOTID_DECAL_RIGHT_DOOR_TEX5;
            }
        case CC_DECAL_LEFT_QP:
            return CARSLOTID_DECAL_LEFT_QUARTER_TEX0;
        case CC_DECAL_RIGHT_QP:
            return CARSLOTID_DECAL_RIGHT_QUARTER_TEX0;
        default:
            return CARSLOTID_DECAL_FRONT_WINDOW_TEX0;
    }
}

void CustomizeDecals::RefreshHeader() {
    CustomizationScreen::RefreshHeader();
    SelectablePart *sel = GetSelectedPart();
    if (sel->GetPart() == nullptr) {
        FEngSetLanguageHash(GetPackageName(), 0x5e7b09c9, Options.GetCurrentName());
    } else {
        FEPrintf(GetPackageName(), 0x5e7b09c9, "%s", GetSelectedPart()->GetPart()->GetName());
    }
    uint32 hash = 0x436a98e9;
    if (bIsBlack) {
        hash = 0x41f0a3a5;
    }
    FEngSetLanguageHash(GetPackageName(), 0x889bacb6, hash);
    if ((RealTimer - ScrollTime).GetSeconds() <= 0.3f) {
        bNeedsRefresh = true;
    } else {
        uint32 slotId = GetSlotIDFromCategory();
        SelectablePart *cur = GetSelectedPart();
        gCarCustomizeManager.PreviewPart(slotId, cur->GetPart());
    }
}

void CustomizeDecals::BuildDecalList(uint32 selected_name_hash) {
    int matchIdx = 1;
    int curIdx = 2;
    bNeedsRefresh = true;
    ScrollTime = 0;
    Options.RemoveAll();
    Options.AddInitialBookEnds();

    uint32 slotID = GetSlotIDFromCategory();
    bTList<SelectablePart> tempList;
    SelectablePart *stockPart = new SelectablePart(nullptr, slotID, 0, Physics::Upgrades::PUT_MAX, false, CPS_AVAILABLE, 0, false);
    eCustomizePartState stockState = CPS_AVAILABLE;
    if (gCarCustomizeManager.IsPartInstalled(stockPart)) {
        stockState = static_cast<eCustomizePartState>(0x11);
    } else if (gCarCustomizeManager.IsPartInCart(stockPart)) {
        stockState = static_cast<eCustomizePartState>(0x21);
    }
    stockPart->SetPartState(stockState);
    AddPartOption(stockPart, 0x697b4ad4, 0x60a662f5, 0, 0, false);

    gCarCustomizeManager.GetCarPartList(slotID, tempList, 0);

    int unlockLevel = MapCarPartToUnlockable(slotID, nullptr);
    if (unlockLevel == 0x2e) {
        unlockLevel = 2;
    } else if (unlockLevel > 0x2e) {
        if (unlockLevel == 0x30) {
            unlockLevel = 3;
        }
    } else if (unlockLevel == 0x2c) {
        unlockLevel = 1;
    }

    SelectablePart *node = static_cast<SelectablePart *>(tempList.GetHead());
    SelectablePart *sentinel = reinterpret_cast<SelectablePart *>(&tempList);
    while (node != sentinel) {
        SelectablePart *next = static_cast<SelectablePart *>(node->Next);
        unsigned int nameHash = node->GetPart()->GetAppliedAttributeUParam(0xebb03e66, 0);
        if (!bIsBlack) {
            nameHash = bStringHash("_WHITE", nameHash);
        }
        unsigned int mirrorHash = node->GetPart()->GetAppliedAttributeUParam(bStringHash("DECAL_MIRROR_HASH"), 0);
        if (nameHash == mirrorHash) {
            unsigned int unlockHash = gCarCustomizeManager.GetUnlockHash(static_cast<eCustomizeCategory>(Category), unlockLevel);
            node->Prev->Next = node->Next;
            node->Next->Prev = node->Prev;
            bool locked = gCarCustomizeManager.IsPartLocked(node, 0);
            AddPartOption(node, 0x697b4ad4, nameHash, 0, unlockHash, locked);
            if (node->GetPart()->GetAppliedAttributeUParam(0xebb03e66, 0) == selected_name_hash) {
                matchIdx = curIdx;
            }
            curIdx++;
        } else {
            node->Prev->Next = node->Next;
            node->Next->Prev = node->Prev;
            delete node;
        }
        node = next;
    }
    if (Showcase::FromIndex != 0) {
        SetInitialOption(0);
        Showcase::FromIndex = 0;
    } else {
        SetInitialOption(matchIdx);
    }

    while (tempList.GetHead() != tempList.EndOfList()) {
        SelectablePart *sp = static_cast<SelectablePart *>(tempList.GetHead());
        sp->Remove();
        delete sp;
    }
}

void CustomizeDecals::Setup() {
    uint32 slot_id = GetSlotIDFromCategory();
    FEngSetButtonTexture(FEngFindImage(GetPackageName(), 0x91c4a50), 0x5bc);
    FEngSetButtonTexture(FEngFindImage(GetPackageName(), 0x2d145be3), 0x682);
    uint32 title = 0;
    switch (Category) {
        case CC_DECAL_WINDSHIELD:
            title = 0x301dedd3;
            break;
        case CC_DECAL_REAR_WINDOW:
            title = 0x48e6ca49;
            break;
        case CC_DECAL_LEFT_QP:
            title = 0x8a7697d6;
            break;
        case CC_DECAL_RIGHT_QP:
            title = 0xb1f9b0c9;
            break;
        case CC_DECAL_SLOT_1:
            title = 0x7d212cfa;
            break;
        case CC_DECAL_SLOT_2:
            title = 0x7d212cfb;
            break;
        case CC_DECAL_SLOT_3:
            title = 0x7d212cfc;
            break;
        case CC_DECAL_SLOT_4:
            title = 0x7d212cfd;
            break;
        case CC_DECAL_SLOT_5:
            title = 0x7d212cfe;
            break;
        case CC_DECAL_SLOT_6:
            title = 0x7d212cff;
            break;
        default:
            break;
    }
    DisplayHelper.SetTitleHash(title);
    uint32 installed_part_base_name = 0;
    ShoppingCartItem *item = gCarCustomizeManager.IsPartTypeInCart(slot_id);
    CarPart *activePart = nullptr;
    if (item && (activePart = item->GetBuyingPart()->GetPart(), activePart)) {
    } else {
        activePart = gCarCustomizeManager.GetInstalledCarPart(slot_id);
    }
    if (activePart) {
        unsigned int brand = activePart->GetAppliedAttributeUParam(0xebb03e66, 0);
        unsigned int mirrorHash = activePart->GetAppliedAttributeUParam(bStringHash("DECAL_MIRROR_HASH"), 0);
        bIsBlack = (brand == mirrorHash);
        installed_part_base_name = activePart->GetAppliedAttributeUParam(0xebb03e66, 0);
    }
    if (Showcase::FromFilter != -1) {
        bIsBlack = (Showcase::FromFilter != 0);
        Showcase::FromFilter = -1;
    }
    BuildDecalList(installed_part_base_name);
    RefreshHeader();
}

CustomizeNumbers::CustomizeNumbers(ScreenConstructorData *sd)
    : MenuScreen(sd),          //
      LeftNumberList(),        //
      RightNumberList(),       //
      TheLeftNumber(nullptr),  //
      TheRightNumber(nullptr), //
      LeftDisplayValue(-1),    //
      RightDisplayValue(-1),   //
      bLeft(1),                //
      DisplayHelper(sd->PackageFilename) {
    Category = sd->Arg & 0xFFFF;
    FromCategory = static_cast<int>(static_cast<short>(sd->Arg >> 16));
    Setup();
}

void CustomizeNumbers::NotificationMessage(u32 msg, FEObject *pobj, u32 param1, u32 param2) {
    switch (msg) {
        case FEHASH_INITCOMPLETE:
            DisplayHelper.SetInitComplete(true);
            FEngSetCurrentButton(GetPackageName(), 0x2a08ba92);
            break;
        case __PAD_BUTTON0__:
            Showcase::FromFilter = RightDisplayValue;
            Showcase::FromIndex = LeftDisplayValue;
            Showcase::FromArgs = GetCategory() | (GetFromCategory() << 16);
            Showcase::FromPackage = GetPackageName();
            bShowcaseOn = 1;
            cFEng::Get()->QueuePackageSwitch("Showcase.fng", reinterpret_cast<uint32>(gCarCustomizeManager.GetTuningCar()), 0, false);
            break;
        case __PAD_START__:
            CustomizeShoppingCart::ShowShoppingCart(GetPackageName());
            break;
        case __PAD_LEFT__:
        case __PAD_RIGHT__: {
            bLeft = !bLeft;
            FEngSetCurrentButton(GetPackageName(), bLeft ? 0x2a08ba92 : 0x1a88dc05);
            break;
        }
        case __PAD_UP__:
            ScrollNumbers(eSD_NEXT);
            break;
        case __PAD_DOWN__:
            ScrollNumbers(eSD_PREV);
            break;
        case __PAD_ACCEPT__:
            if (LeftDisplayValue == -1 || RightDisplayValue == -1)
                return;
            if (!TheLeftNumber || !TheRightNumber)
                return;
            if (TheLeftNumber->IsLocked() && TheRightNumber->IsLocked()) {
                DisplayHelper.FlashStatusIcon(CPS_LOCKED, true);
            } else if (TheLeftNumber->IsInCartX() && TheRightNumber->IsInCartX()) {
                DisplayHelper.FlashStatusIcon(CPS_IN_CART, true);
            } else if (TheLeftNumber->IsInstalledX() && TheRightNumber->IsInstalledX()) {
                DisplayHelper.FlashStatusIcon(CPS_INSTALLED, true);
            } else {
                cFEng::Get()->QueueGameMessage(0x91dfdf84, GetPackageName(), 0xff);
                return;
            }
            break;
        case __PAD_BUTTON4__: {
            CarPart *installed = gCarCustomizeManager.GetInstalledCarPart(0x71);
            if (installed) {
                UnsetShoppingCart();
                SelectablePart stockPart(nullptr, 0x71, 0, Physics::Upgrades::PUT_MAX, false, CPS_AVAILABLE, 0, false);
                gCarCustomizeManager.AddToCart(&stockPart);
                stockPart.SetSlotID(0x72);
                gCarCustomizeManager.AddToCart(&stockPart);
                stockPart.SetSlotID(0x69);
                gCarCustomizeManager.AddToCart(&stockPart);
                stockPart.SetSlotID(0x6a);
                gCarCustomizeManager.AddToCart(&stockPart);
            } else {
                if (TheLeftNumber->IsInCart() || TheRightNumber->IsInCart()) {
                    UnsetShoppingCart();
                    ShoppingCartItem *current = gCarCustomizeManager.GetFirstCartItem();
                    ShoppingCartItem *last = gCarCustomizeManager.GetLastCartItem();
                    while (current) {
                        ShoppingCartItem *next = static_cast<ShoppingCartItem *>(current->Next);
                        int slotID = current->GetBuyingPart()->GetSlotID();
                        if (slotID == 0x71 || slotID == 0x72 || slotID == 0x69 || slotID == 0x6a) {
                            gCarCustomizeManager.RemoveFromCart(current);
                        }
                        if (current == last)
                            break;
                        current = next;
                    }
                }
            }
            RightDisplayValue = -1;
            TheLeftNumber = static_cast<SelectablePart *>(LeftNumberList.GetHead());
            TheRightNumber = static_cast<SelectablePart *>(RightNumberList.GetHead());
            LeftDisplayValue = -1;
            RefreshHeader();
            break;
        }
        case 0x91dfdf84:
            UnsetShoppingCart();
            TheLeftNumber->SetInCartPreserve();
            TheRightNumber->SetInCartPreserve();
            gCarCustomizeManager.AddToCart(TheLeftNumber);
            gCarCustomizeManager.AddToCart(TheRightNumber);
            {
                SelectablePart *copyLeft = new SelectablePart(TheLeftNumber);
                SelectablePart *copyRight = new SelectablePart(TheRightNumber);
                copyLeft->SetPrice(0);
                copyLeft->SetInCart();
                copyRight->SetInCart();
                copyLeft->SetSlotID(0x69);
                copyRight->SetSlotID(0x6a);
                copyRight->SetPrice(0);
                gCarCustomizeManager.AddToCart(copyLeft);
                gCarCustomizeManager.AddToCart(copyRight);
                delete copyLeft;
                delete copyRight;
            }
            RefreshHeader();
            break;
        case 0xcf91aacd: {
            SelectablePart *lnode = static_cast<SelectablePart *>(LeftNumberList.GetHead());
            SelectablePart *lsentinel = reinterpret_cast<SelectablePart *>(&LeftNumberList);
            while (lnode != lsentinel) {
                if (lnode->GetPart() == gCarCustomizeManager.GetInstalledCarPart(0x69) ||
                    lnode->GetPart() == gCarCustomizeManager.GetInstalledCarPart(0x6a)) {
                    lnode->SetInstalled();
                }
                lnode = static_cast<SelectablePart *>(lnode->Next);
            }
            SelectablePart *rnode = static_cast<SelectablePart *>(RightNumberList.GetHead());
            SelectablePart *rsentinel = reinterpret_cast<SelectablePart *>(&RightNumberList);
            while (rnode != rsentinel) {
                if (rnode->GetPart() == gCarCustomizeManager.GetInstalledCarPart(0x71) ||
                    rnode->GetPart() == gCarCustomizeManager.GetInstalledCarPart(0x72)) {
                    rnode->SetInstalled();
                }
                rnode = static_cast<SelectablePart *>(rnode->Next);
            }
            CustomizeShoppingCart::ExitShoppingCart();
            break;
        }
        case 0x5a928018: {
            ShoppingCartItem *leftInCart = gCarCustomizeManager.IsPartTypeInCart(0x69u);
            ShoppingCartItem *rightInCart = gCarCustomizeManager.IsPartTypeInCart(0x6au);
            if (!leftInCart && !rightInCart) {
                SelectablePart *lnode = static_cast<SelectablePart *>(LeftNumberList.GetHead());
                SelectablePart *lsentinel = reinterpret_cast<SelectablePart *>(&LeftNumberList);
                for (; lnode != lsentinel; lnode = static_cast<SelectablePart *>(lnode->Next)) {
                    if (lnode->IsInCart()) {
                        lnode->UnSetInCart();
                        break;
                    }
                }
                SelectablePart *rnode = static_cast<SelectablePart *>(RightNumberList.GetHead());
                SelectablePart *rsentinel = reinterpret_cast<SelectablePart *>(&RightNumberList);
                for (; rnode != rsentinel; rnode = static_cast<SelectablePart *>(rnode->Next)) {
                    if (rnode->IsInCart()) {
                        rnode->UnSetInCart();
                        break;
                    }
                }
            }
            RefreshHeader();
            break;
        }
        case __PAD_BACK__:
            bShowcaseOn = 0;
            cFEng::Get()->QueuePackageSwitch(g_pCustomizeSubPkg, FromCategory | (Category << 16), 0, false);
            break;
    }
}

void CustomizeNumbers::UnsetShoppingCart() {
    for (SelectablePart *number = LeftNumberList.GetHead(); number != LeftNumberList.EndOfList(); number = number->GetNext()) {
        if (number->IsInCart()) {
            number->UnSetInCartPreserve();
            break;
        }
    }
    for (SelectablePart *number = RightNumberList.GetHead(); number != RightNumberList.EndOfList(); number = number->GetNext()) {
        if (number->IsInCart()) {
            number->UnSetInCartPreserve();
            return;
        }
    }
}

void CustomizeNumbers::ScrollNumbers(eScrollDir dir) {
    if (LeftDisplayValue == -1 || RightDisplayValue == -1) {
        RightDisplayValue = 0;
        TheLeftNumber = static_cast<SelectablePart *>(LeftNumberList.GetHead());
        TheRightNumber = static_cast<SelectablePart *>(RightNumberList.GetHead());
        LeftDisplayValue = 0;
        RefreshHeader();
    } else {
        SelectablePart *current;
        if (bLeft) {
            current = TheRightNumber;
        } else {
            current = TheLeftNumber;
        }
        if (dir == eSD_PREV) {
            if (!bLeft) {
                current = static_cast<SelectablePart *>(current->Prev);
                if (current == reinterpret_cast<SelectablePart *>(&RightNumberList)) {
                    current = static_cast<SelectablePart *>(RightNumberList.GetTail());
                }
                RightDisplayValue = static_cast<short>(RightDisplayValue - 1);
                if (RightDisplayValue < 0) {
                    RightDisplayValue = 9;
                }
            } else {
                current = static_cast<SelectablePart *>(current->Prev);
                if (current == reinterpret_cast<SelectablePart *>(&LeftNumberList)) {
                    current = static_cast<SelectablePart *>(LeftNumberList.GetTail());
                }
                unsigned short val = static_cast<unsigned short>(LeftDisplayValue - 1);
                LeftDisplayValue = static_cast<short>(val);
                if (val & 0x8000) {
                    LeftDisplayValue = 9;
                }
            }
        } else if (dir == eSD_NEXT) {
            if (!bLeft) {
                current = static_cast<SelectablePart *>(current->Next);
                if (current == reinterpret_cast<SelectablePart *>(&RightNumberList)) {
                    current = static_cast<SelectablePart *>(RightNumberList.GetHead());
                }
                RightDisplayValue = static_cast<short>(RightDisplayValue + 1);
                if (RightDisplayValue > 9) {
                    RightDisplayValue = 0;
                }
            } else {
                current = static_cast<SelectablePart *>(current->Next);
                if (current == reinterpret_cast<SelectablePart *>(&LeftNumberList)) {
                    current = static_cast<SelectablePart *>(LeftNumberList.GetHead());
                }
                short val = static_cast<short>(LeftDisplayValue + 1);
                LeftDisplayValue = val;
                if (val > 9) {
                    LeftDisplayValue = 0;
                }
            }
        }
        SelectablePart *prev;
        if (!bLeft) {
            prev = TheRightNumber;
        } else {
            prev = TheLeftNumber;
        }
        if (current != prev) {
            if (!bLeft) {
                TheRightNumber = current;
            } else {
                TheLeftNumber = current;
            }
            RefreshHeader();
        }
    }
}

void CustomizeNumbers::RefreshHeader() {
    DisplayHelper.DrawTitle();
    DisplayHelper.SetCareerStuff(TheLeftNumber, Category, 0);
    if (LeftDisplayValue != -1 && RightDisplayValue != -1) {
        FEObject *numGroup = FEngFindObject(GetPackageName(), 0x7a8355d9);
        FEngSetVisible(numGroup);
        SelectablePart part(TheLeftNumber);
        uint32 status = CPS_AVAILABLE;
        if (TheLeftNumber->IsLocked() && TheRightNumber->IsLocked()) {
            status = CPS_LOCKED;
        } else if (TheLeftNumber->IsNew() && TheRightNumber->IsNew()) {
            status = CPS_NEW;
        }
        if (TheLeftNumber->IsInstalledX() && TheRightNumber->IsInstalledX()) {
            status = status | CPS_INSTALLED;
        } else if (TheLeftNumber->IsInCartX() && TheRightNumber->IsInCartX()) {
            status = status | CPS_IN_CART;
        }
        part.SetPartState(status);
        DisplayHelper.SetPartStatus(&part, gCarCustomizeManager.GetUnlockHash(static_cast<eCustomizeCategory>(Category), 1), 0, 0);
        FEPrintf(GetPackageName(), 0x2a08ba92, "%$d", static_cast<int>(LeftDisplayValue));
        FEPrintf(GetPackageName(), 0x1a88dc05, "%$d", static_cast<int>(RightDisplayValue));
        gCarCustomizeManager.PreviewPart(0x71, TheLeftNumber->GetPart());
        gCarCustomizeManager.PreviewPart(0x72, TheRightNumber->GetPart());
        gCarCustomizeManager.PreviewPart(0x69, TheLeftNumber->GetPart());
        gCarCustomizeManager.PreviewPart(0x6a, TheRightNumber->GetPart());
    } else {
        FEObject *numGroup = FEngFindObject(GetPackageName(), 0x7a8355d9);
        FEngSetInvisible(numGroup);
        ShoppingCartItem *inCart = gCarCustomizeManager.IsPartTypeInCart(TheLeftNumber);
        CarPart *installed = gCarCustomizeManager.GetInstalledCarPart(0x71);
        if (!installed) {
            DisplayHelper.SetPlayerCarStatusIcon(CPS_INSTALLED);
        } else if (inCart && !inCart->GetBuyingPart()->GetPart()) {
            DisplayHelper.SetPlayerCarStatusIcon(CPS_IN_CART);
        } else {
            DisplayHelper.SetPlayerCarStatusIcon(CPS_AVAILABLE);
        }
        FEPrintf(GetPackageName(), 0x2a08ba92, "-");
        FEPrintf(GetPackageName(), 0x1a88dc05, "-");
        gCarCustomizeManager.ResetPreview();
    }
}

void CustomizeNumbers::Setup() {
    DisplayHelper.SetTitleHash(0x6857e5ac);
    gCarCustomizeManager.GetCarPartList(0x71, LeftNumberList, 0);
    gCarCustomizeManager.GetCarPartList(0x72, RightNumberList, 0);
    bool leftFound = false;
    int leftIdx = 0;
    CarPart *activeLeft = gCarCustomizeManager.GetActivePartFromSlot(0x71);
    SelectablePart *node = static_cast<SelectablePart *>(LeftNumberList.GetHead());
    while (node != reinterpret_cast<SelectablePart *>(&LeftNumberList)) {
        unsigned int attrVal = node->GetPart()->GetAppliedAttributeUParam(0xebb03e66, 0);
        unsigned int expectedHash = bStringHash("NUMBER_LEFT");
        if (attrVal == expectedHash) {
            if (!leftFound) {
                if (bShowcaseOn == 1 && Showcase::FromIndex == leftIdx) {
                    TheLeftNumber = node;
                    if (gCarCustomizeManager.IsPartInCart(node)) {
                        TheLeftNumber->SetInCartPreserve();
                    }
                    LeftDisplayValue = static_cast<short>(leftIdx);
                    leftFound = true;
                    Showcase::FromIndex = 0;
                } else if (node->GetPart() == activeLeft) {
                    TheLeftNumber = node;
                    if (gCarCustomizeManager.IsPartInCart(node)) {
                        TheLeftNumber->SetInCartPreserve();
                    }
                    LeftDisplayValue = static_cast<short>(leftIdx);
                }
            }
            leftIdx++;
            node = static_cast<SelectablePart *>(node->Next);
        } else {
            SelectablePart *next = static_cast<SelectablePart *>(node->Next);
            node->Prev->Next = node->Next;
            node->Next->Prev = node->Prev;
            delete node;
            node = next;
        }
    }
    if (!TheLeftNumber) {
        LeftDisplayValue = -1;
        TheLeftNumber = static_cast<SelectablePart *>(LeftNumberList.GetHead());
    }

    bool rightFound = false;
    int rightIdx = 0;
    CarPart *activeRight = gCarCustomizeManager.GetActivePartFromSlot(0x72);
    node = static_cast<SelectablePart *>(RightNumberList.GetHead());
    while (node != reinterpret_cast<SelectablePart *>(&RightNumberList)) {
        unsigned int attrVal = node->GetPart()->GetAppliedAttributeUParam(0xebb03e66, 0);
        unsigned int expectedHash = bStringHash("NUMBER_RIGHT");
        if (attrVal == expectedHash) {
            if (!rightFound) {
                if (bShowcaseOn == 1 && Showcase::FromFilter == rightIdx) {
                    TheRightNumber = node;
                    if (gCarCustomizeManager.IsPartInCart(node)) {
                        TheRightNumber->SetInCartPreserve();
                    }
                    RightDisplayValue = static_cast<short>(rightIdx);
                    rightFound = true;
                    Showcase::FromFilter = -1;
                } else if (node->GetPart() == activeRight) {
                    TheRightNumber = node;
                    if (gCarCustomizeManager.IsPartInCart(node)) {
                        TheRightNumber->SetInCartPreserve();
                    }
                    RightDisplayValue = static_cast<short>(rightIdx);
                }
            }
            rightIdx++;
            node = static_cast<SelectablePart *>(node->Next);
        } else {
            SelectablePart *next = static_cast<SelectablePart *>(node->Next);
            node->Prev->Next = node->Next;
            node->Next->Prev = node->Prev;
            delete node;
            node = next;
        }
    }
    if (!TheRightNumber) {
        RightDisplayValue = -1;
        TheRightNumber = static_cast<SelectablePart *>(RightNumberList.GetHead());
    }
    RefreshHeader();
}

CustomizePerformance::CustomizePerformance(ScreenConstructorData *sd) : CustomizationScreen(sd) {
    Setup();
}

eMenuSoundTriggers CustomizePerformance::NotifySoundMessage(u32 msg, eMenuSoundTriggers maybe) {
    eMenuSoundTriggers toBeReturned = maybe;
    if (toBeReturned == static_cast<eMenuSoundTriggers>(4)) {
        switch (GetCategory()) {
            case 0x201:
                toBeReturned = static_cast<eMenuSoundTriggers>(0x31);
                break;
            case 0x202:
                toBeReturned = static_cast<eMenuSoundTriggers>(0x35);
                break;
            case 0x204:
                toBeReturned = static_cast<eMenuSoundTriggers>(0x34);
                break;
            case 0x205:
                toBeReturned = static_cast<eMenuSoundTriggers>(0x36);
                break;
            case 0x203:
            case 0x206:
                toBeReturned = static_cast<eMenuSoundTriggers>(0x32);
                break;
            case 0x207:
                toBeReturned = static_cast<eMenuSoundTriggers>(0x33);
                break;
        }
    }
    return toBeReturned;
}

void CustomizePerformance::NotificationMessage(u32 msg, FEObject *pobj, u32 param1, u32 param2) {
    CustomizationScreen::NotificationMessage(msg, pobj, param1, param2);
    switch (msg) {
        case FEHASH_EXITCOMPLETE:
            cFEng::Get()->QueuePackageSwitch(g_pCustomizeSubPkg, FromCategory | (Category << 16), 0, false);
            break;
        case 0x5a928018: {
            SelectablePart *part = FindInCartPart();
            if (!part)
                return;
            if (gCarCustomizeManager.IsPartInCart(part))
                return;
            part->UnSetInCart();
            RefreshHeader();
            break;
        }
        case __PAD_BACK__:
            cFEng::Get()->QueuePackageMessage(0x587c018b, GetPackageName(), nullptr);
            break;
    }
}

unsigned int CustomizePerformance::GetPerfPkgDesc(Physics::Upgrades::Type type, int level, int num_packages, bool has_turbo) {
    if (level == 0) {
        switch (type) {
            case Physics::Upgrades::PUT_TIRES:
                return 0xe5c1020c;
            case Physics::Upgrades::PUT_BRAKES:
                return 0x927db4fd;
            case Physics::Upgrades::PUT_CHASSIS:
                return 0x8c96b853;
            case Physics::Upgrades::PUT_TRANSMISSION:
                return 0x2f525e4f;
            case Physics::Upgrades::PUT_ENGINE:
                return 0xe74dedbb;
            case Physics::Upgrades::PUT_INDUCTION:
                if (has_turbo)
                    return 0x5317eb31;
                return 0x704a6d50;
            case Physics::Upgrades::PUT_NOS:
                return 0x9a0ef8f9;
            default:
                return 0;
        }
    }
    const char *fmt;
    switch (type) {
        case Physics::Upgrades::PUT_TIRES:
            fmt = "PD_TIRES_%d_%d";
            break;
        case Physics::Upgrades::PUT_BRAKES:
            fmt = "PD_BRAKES_%d_%d";
            break;
        case Physics::Upgrades::PUT_CHASSIS:
            fmt = "PD_CHASSIS_%d_%d";
            break;
        case Physics::Upgrades::PUT_TRANSMISSION:
            fmt = "PD_TRANSMISSION_%d_%d";
            break;
        case Physics::Upgrades::PUT_ENGINE:
            if (gCarCustomizeManager.IsCastrolCar() && level == 4 && num_packages == 3) {
                return FEngHashString("PD_ENGINE_%d_%d_CASTROL", 4, 3);
            }
            if (gCarCustomizeManager.IsRotaryCar() && (level == 2 || level == 4) && num_packages == 1) {
                return FEngHashString("PD_ENGINE_%d_%d_ROTARY", level, 1);
            }
            fmt = "PD_ENGINE_%d_%d";
            break;
        case Physics::Upgrades::PUT_INDUCTION:
            if (!has_turbo) {
                fmt = "PD_SUPERCHARGER_%d_%d";
            } else {
                fmt = "PD_TURBO_%d_%d";
            }
            break;
        case Physics::Upgrades::PUT_NOS:
            fmt = "PD_NITROUS_%d_%d";
            break;
        default:
            return 0;
    }
    return FEngHashString(fmt, level, num_packages);
}

uint32 CustomizePerformance::GetPerfPkgBrand(Physics::Upgrades::Type type, int level, int num_packages) {
    uint32 hash = 0;
    Attrib::Gen::frontend fe_attrib(gCarCustomizeManager.GetTuningCar()->FEKey, 0, nullptr);
    switch (type) {
        case Physics::Upgrades::PUT_TIRES:
            switch (level) {
                case 0:
                    hash = 0xad6a0504;
                    break;
                case 1:
                    hash = fe_attrib.p_tires_1(num_packages).hash;
                    break;
                case 2:
                    hash = fe_attrib.p_tires_2(num_packages).hash;
                    break;
                case 3:
                    hash = fe_attrib.p_tires_3(num_packages).hash;
                    break;
                case 4:
                    hash = fe_attrib.p_tires_4(num_packages).hash;
                    break;
                default:
                    break;
            }
            break;
        case Physics::Upgrades::PUT_BRAKES:
            switch (level) {
                case 0:
                    hash = 0xa1a5e9e5;
                    break;
                case 1:
                    hash = fe_attrib.p_brakes_1(num_packages).hash;
                    break;
                case 2:
                    hash = fe_attrib.p_brakes_2(num_packages).hash;
                    break;
                case 3:
                    hash = fe_attrib.p_brakes_3(num_packages).hash;
                    break;
                case 4:
                    hash = fe_attrib.p_brakes_4(num_packages).hash;
                    break;
                default:
                    break;
            }
            break;
        case Physics::Upgrades::PUT_CHASSIS:
            switch (level) {
                case 0:
                    hash = 0xad6a0504;
                    break;
                case 1:
                    hash = fe_attrib.p_suspension_1(num_packages).hash;
                    break;
                case 2:
                    hash = fe_attrib.p_suspension_2(num_packages).hash;
                    break;
                case 3:
                    hash = fe_attrib.p_suspension_3(num_packages).hash;
                    break;
                case 4:
                    hash = fe_attrib.p_suspension_4(num_packages).hash;
                    break;
                default:
                    break;
            }
            break;
        case Physics::Upgrades::PUT_TRANSMISSION:
            switch (level) {
                case 0:
                    hash = 0x98ed935e;
                    break;
                case 1:
                    hash = fe_attrib.p_transmission_1(num_packages).hash;
                    break;
                case 2:
                    hash = fe_attrib.p_transmission_2(num_packages).hash;
                    break;
                case 3:
                    hash = fe_attrib.p_transmission_3(num_packages).hash;
                    break;
                case 4:
                    hash = fe_attrib.p_transmission_4(num_packages).hash;
                    break;
                default:
                    break;
            }
            break;
        case Physics::Upgrades::PUT_ENGINE:
            if (gCarCustomizeManager.IsCastrolCar() && level == 4 && num_packages == 2) {
                return 0xb95d4df;
            }
            switch (level) {
                case 0:
                    hash = 0x7d0ac98f;
                    break;
                case 1:
                    hash = fe_attrib.p_engine_1(num_packages).hash;
                    break;
                case 2:
                    hash = fe_attrib.p_engine_2(num_packages).hash;
                    break;
                case 3:
                    hash = fe_attrib.p_engine_3(num_packages).hash;
                    break;
                case 4:
                    hash = fe_attrib.p_engine_4(num_packages).hash;
                    break;
                default:
                    break;
            }
            break;
        case Physics::Upgrades::PUT_INDUCTION:
            switch (level) {
                case 0:
                    hash = 0x9e8f71ad;
                    break;
                case 1:
                    hash = fe_attrib.p_induction_1(num_packages).hash;
                    break;
                case 2:
                    hash = fe_attrib.p_induction_2(num_packages).hash;
                    break;
                case 3:
                    hash = fe_attrib.p_induction_3(num_packages).hash;
                    break;
                case 4:
                    hash = fe_attrib.p_induction_4(num_packages).hash;
                    break;
                default:
                    break;
            }
            break;
        case Physics::Upgrades::PUT_NOS:
            switch (level) {
                case 0:
                    hash = 0x98ed935e;
                    break;
                case 1:
                    hash = fe_attrib.p_nitrous_1(num_packages).hash;
                    break;
                case 2:
                    hash = fe_attrib.p_nitrous_2(num_packages).hash;
                    break;
                case 3:
                    hash = fe_attrib.p_nitrous_3(num_packages).hash;
                    break;
                case 4:
                    hash = fe_attrib.p_nitrous_4(num_packages).hash;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    return hash;
}

void CustomizePerformance::RefreshHeader() {
    int num_lines = 3;

    SelectablePart *sel = GetSelectedPart();
    int phys_type = sel->GetPhysicsType();
    int upg_level = GetSelectedPart()->GetUpgradeLevel();

    gCarCustomizeManager.PreviewPerfPkg(static_cast<Physics::Upgrades::Type>(phys_type), upg_level);

    AccelSlider.SetValue(gCarCustomizeManager.GetPerformanceRating(PRT_ACCELERATION, true));
    HandlingSlider.SetValue(gCarCustomizeManager.GetPerformanceRating(PRT_HANDLING, true));
    TopSpeedSlider.SetValue(gCarCustomizeManager.GetPerformanceRating(PRT_TOP_SPEED, true));

    AccelSlider.Draw();
    HandlingSlider.Draw();
    TopSpeedSlider.Draw();

    sel = GetSelectedPart();
    phys_type = sel->GetPhysicsType();
    int level = GetSelectedPart()->GetUpgradeLevel();

    int maxPkgs = gCarCustomizeManager.GetMaxPackages(static_cast<Physics::Upgrades::Type>(phys_type));
    int numPkgs = gCarCustomizeManager.GetNumPackages(static_cast<Physics::Upgrades::Type>(phys_type));
    int pkg_index = (maxPkgs - numPkgs) + level;

    if (CustomizeIsInBackRoom() || level == 7) {
        level = 0;
        pkg_index = 0;
        num_lines = 1;
    }

    int i = 0;
    while (i < num_lines) {
        int line_idx = i;
        unsigned int desc_hash =
            GetPerfPkgDesc(static_cast<Physics::Upgrades::Type>(phys_type), pkg_index, line_idx + 1, gCarCustomizeManager.IsTurbo());
        i = line_idx + 1;
        if (DoesStringExist(desc_hash)) {
            FEngSetVisible(DescLines[line_idx]);
            FEngSetVisible(DescBullets[line_idx]);
            FEngSetLanguageHash(GetPackageName(), DescLines[line_idx]->NameHash, desc_hash);
        } else {
            FEngSetInvisible(DescLines[line_idx]);
            FEngSetInvisible(DescBullets[line_idx]);
        }

        Attrib::Gen::frontend inst(Attrib::FindCollection(0x85885722, gCarCustomizeManager.GetTuningCar()->FEKey), 0, nullptr);

        unsigned int brand_hash = GetPerfPkgBrand(static_cast<Physics::Upgrades::Type>(phys_type), pkg_index, line_idx);
        unsigned int brand_icon_hash = FEngHashString("BRAND_ICON_%d", i);

        if (GetTextureInfo(brand_hash, 0, 0)) {
            FEngSetVisible(GetPackageName(), brand_icon_hash);
            FEngSetTextureHash(GetPackageName(), brand_icon_hash, brand_hash);
        } else {
            FEngSetInvisible(GetPackageName(), brand_icon_hash);
        }
    }

    while (i < 3) {
        int line_idx = i;
        i = line_idx + 1;
        FEngSetInvisible(DescLines[line_idx]);
        FEngSetInvisible(DescBullets[line_idx]);
        unsigned int icon_hash = FEngHashString("BRAND_ICON_%d", i);
        FEngSetInvisible(GetPackageName(), icon_hash);
    }

    CustomizationScreen::RefreshHeader();

    unsigned int level_hash;
    if (GetSelectedPart()->GetUpgradeLevel() == 7) {
        level_hash = 0xedd14807;
    } else {
        int num = gCarCustomizeManager.GetNumPackages(static_cast<Physics::Upgrades::Type>(phys_type));
        level_hash = FEngHashString("PN_LEVEL_%d", level - (num - 6));
    }
    FEngSetLanguageHash(pOptionName, level_hash);
}

void CustomizePerformance::Setup() {
    if (!gCarCustomizeManager.IsCareerMode()) {
        const u32 FEObj_QUICKRACE = 0xde511657;
        cFEng::Get()->QueuePackageMessage(FEObj_QUICKRACE, GetPackageName(), nullptr);
    }

    for (int i = 0; i < 3; i++) {
        DescLines[i] = FEngFindString(GetPackageName(), FEngHashString("DETAIL_TEXT_LINE%d", i + 1));
        DescBullets[i] = FEngFindImage(GetPackageName(), FEngHashString("PERFORMANCE_DETAILS_ICON%d", i + 1));
    }

    AccelSlider.Init(GetPackageName(), "ACCELERATION", 0.0f, 10.0f, 0.0f, gCarCustomizeManager.GetPerformanceRating(PRT_ACCELERATION, true),
                     gCarCustomizeManager.GetPerformanceRating(PRT_ACCELERATION, false), 1.0f);
    HandlingSlider.Init(GetPackageName(), "HANDLING", 0.0f, 10.0f, 0.0f, gCarCustomizeManager.GetPerformanceRating(PRT_HANDLING, true),
                        gCarCustomizeManager.GetPerformanceRating(PRT_HANDLING, false), 1.0f);
    TopSpeedSlider.Init(GetPackageName(), "TOPSPEED", 0.0f, 10.0f, 0.0f, gCarCustomizeManager.GetPerformanceRating(PRT_TOP_SPEED, true),
                        gCarCustomizeManager.GetPerformanceRating(PRT_TOP_SPEED, false), 1.0f);

    Physics::Upgrades::Type type = Physics::Upgrades::PUT_TIRES;
    switch (Category) {
        case CC_ENGINE:
            SetTitleHash(0x9853d9a6);
            break;
        case CC_TRANSMISSION:
            type = Physics::Upgrades::PUT_NOS;
            SetTitleHash(0x29aa74ba);
            break;
        case CC_SUSPENSION:
            type = Physics::Upgrades::PUT_CHASSIS;
            SetTitleHash(0x6e101aa7);
            break;
        case CC_NITROUS:
            type = Physics::Upgrades::PUT_INDUCTION;
            SetTitleHash(0x4ce19aa4);
            break;
        case CC_TIRES:
            type = Physics::Upgrades::PUT_ENGINE;
            SetTitleHash(0x5aa9137);
            break;
        case CC_BRAKES:
            type = Physics::Upgrades::PUT_TRANSMISSION;
            SetTitleHash(0x91997ee8);
            break;
        case CC_FORCED_INDUCTION:
            type = Physics::Upgrades::PUT_BRAKES;
            if (gCarCustomizeManager.IsTurbo()) {
                SetTitleHash(0x5b1255c);
            } else {
                SetTitleHash(0xbb6812bb);
            }
            break;
    }

    unsigned int icon_hash = 0xb8c8c0d4;
    bTList<SelectablePart> part_list;
    int j;
    bool is_locked;
    unsigned int desc_hash = 0;
    SelectablePart *part;

    if (!gCarCustomizeManager.IsInBackRoom()) {
        goto get_part_list;
    }
    if (!gCarCustomizeManager.IsCareerMode()) {
        goto get_part_list;
    }
    if (gCarCustomizeManager.IsHeroCar()) {
        goto get_part_list;
    }

    {
        unsigned int unlock_hash = 0;
        if (!gCarCustomizeManager.IsInBackRoom()) {
            unlock_hash = gCarCustomizeManager.GetUnlockHash(static_cast<eCustomizeCategory>(Category), 7);
        }
        SelectablePart *new_part = new SelectablePart(nullptr, 0, 7, type, true, CPS_AVAILABLE, 0, true);
        AddPartOption(new_part, icon_hash, 7, desc_hash, unlock_hash, false);
        if (gCarCustomizeManager.IsPartInstalled(new_part)) {
            new_part->SetInstalled();
        } else if (gCarCustomizeManager.IsPartInCart(new_part)) {
            new_part->SetInCart();
        }
        goto after_initial_part_list;
    }

get_part_list:
    gCarCustomizeManager.GetPerformancePartsList(type, part_list);

after_initial_part_list:
    for (j = 1;; j++) {
        bNode *end = part_list.GetHead();
        if (part_list.IsEmpty()) {
            break;
        }
        part_list.RemoveHead();
        int unlock_level = gCarCustomizeManager.GetMaxPackages(type) - gCarCustomizeManager.GetNumPackages(type) + part->GetUpgradeLevel();
        unsigned int unlock_hash = gCarCustomizeManager.GetUnlockHash(static_cast<eCustomizeCategory>(Category), unlock_level);
        is_locked = gCarCustomizeManager.IsPartLocked(part, 0);
        AddPartOption(part, icon_hash, j, desc_hash, unlock_hash, is_locked);
    }

    if (((FEDatabase->GetCareerSettings()->HasBeenAwardedBKReward() && !FEDatabase->IsCareerMode()) ||
         (FEDatabase->GetUserProfile(0)->CareerModeHasBeenCompletedAtLeastOnce && !gCarCustomizeManager.IsHeroCar())) &&
        gCarCustomizeManager.CanInstallJunkman(type)) {
        SelectablePart *new_part = new SelectablePart(nullptr, 0, 7, type, true, CPS_AVAILABLE, 0, true);
        AddPartOption(new_part, icon_hash, 7, desc_hash, 0, false);
        if (gCarCustomizeManager.IsPartInstalled(new_part)) {
            new_part->SetInstalled();
        } else if (gCarCustomizeManager.IsPartInCart(new_part)) {
            new_part->SetInCart();
        }
    }

    if (!gCarCustomizeManager.IsInBackRoom()) {
        goto set_installed_option;
    }
    if (!gCarCustomizeManager.IsCareerMode()) {
        goto set_installed_option;
    }
    SetInitialOption(1);
    goto after_initial_option;

set_installed_option: {
    int installed_index = gCarCustomizeManager.GetInstalledPerfPkg(type);
    ShoppingCartItem *item = gCarCustomizeManager.IsPartTypeInCart(type);
    if (item) {
        installed_index = item->GetBuyingPart()->GetUpgradeLevel();
    }
    SetInitialOption(installed_index);
}

after_initial_option:
    RefreshHeader();
}
