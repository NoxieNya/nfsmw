#include "uiRapSheetRankingsDetail.hpp"
#include "Speed/Indep/Src/Frontend/Database/RaceDB.hpp"
#include "Speed/Indep/Src/Frontend/FEngHashes/ScriptHashes.hpp"
#include "Speed/Indep/Src/Frontend/Localization/Localize.hpp"
#include "uiRapSheetRankings.hpp"
#include "Speed/Indep/Src/Frontend/FEngInterfaces/FEngInterface.hpp"
#include "Speed/Indep/Src/Frontend/Database/FEDatabase.hpp"
#include "Speed/Indep/Src/Generated/AttribSys/Classes/frontend.h"

bool uiRapSheetRankingsDetail::career_view = false;

void RapSheetRankingsArraySlot::Update(ArrayDatum *datum, bool isSelected) {
    ArraySlot::Update(datum, isSelected);
    if (datum != nullptr) {
        RapSheetRankingsDatum *dat = static_cast<RapSheetRankingsDatum *>(datum);
        FEPrintf(pValue, "%$.0f", dat->getValue());
        if (dat->getItemNum() != 0x10) {
            FEPrintf(pItemNum, "%$d", dat->getItemNum());
        } else {
            FEngSetLanguageHash(pItemNum, 0xFC1BF40);
        }
        if (dat->getCarName() != 0) {
            FEngSetLanguageHash(pCarName, dat->getCarName());
        } else {
            FEPrintf(pCarName, "");
        }
        if (dat->getPlayerName() != 1) {
            FEngSetLanguageHash(pPlayerName, dat->getPlayerName());
        } else {
            FEPrintf(pPlayerName, "%s", FEDatabase->GetUserProfile(0)->GetProfileName());
        }
    }
}

void RapSheetRankingsTimerArraySlot::Update(ArrayDatum *datum, bool isSelected) {
    ArraySlot::Update(datum, isSelected);
    if (datum != nullptr) {
        RapSheetRankingsDatum *dat = static_cast<RapSheetRankingsDatum *>(datum);
        if (dat->getItemNum() != 0x10) {
            FEPrintf(pItemNum, "%$d", dat->getItemNum());
        } else {
            FEPrintf(pItemNum, "--");
        }
        if (dat->getCarName() != 0) {
            FEngSetLanguageHash(pCarName, dat->getCarName());
        } else {
            FEPrintf(pCarName, "");
        }
        char time_str[16];
        Timer(dat->getValue()).PrintToString(time_str, 16);
        FEPrintf(pValue, "%s", time_str);
        if (dat->getPlayerName() != 1) {
            FEngSetLanguageHash(pPlayerName, dat->getPlayerName());
        } else {
            FEPrintf(pPlayerName, "%s", FEDatabase->GetUserProfile(0)->GetProfileName());
        }
    }
}

uiRapSheetRankingsDetail::uiRapSheetRankingsDetail(ScreenConstructorData *sd)
    : ArrayScrollerMenu(sd, 1, 10, false), rank_type(static_cast<ePursuitDetailTypes>(sd->Arg)), player_rank(0x10) {
    for (int i = 0; i < GetWidth() * GetHeight(); i++) {
        FEString *pItemNum = FEngFindString(GetPackageName(), FEngHashString("RANK_%d", i + 1));
        FEString *pPlayerName = FEngFindString(GetPackageName(), FEngHashString("PLAYER_NAME_%d", i + 1));
        FEString *pCarName = FEngFindString(GetPackageName(), FEngHashString("VEHICLE_%d", i + 1));
        FEString *pValue = FEngFindString(GetPackageName(), FEngHashString("TIME_%d", i + 1));
        if (rank_type == PD_PURUSIT_LENGTH) {
            AddSlot(new ("RapSheetRankingsTimerArraySlot", 0) RapSheetRankingsTimerArraySlot(pItemNum, pPlayerName, pCarName, pValue));
        } else {
            AddSlot(new ("RapSheetRankingsArraySlot", 0) RapSheetRankingsArraySlot(pItemNum, pPlayerName, pCarName, pValue));
        }
    }
    Setup();
}

void uiRapSheetRankingsDetail::NotificationMessage(u32 msg, FEObject *pobj, u32 param1, u32 param2) {
    ArrayScrollerMenu::NotificationMessage(msg, pobj, param1, param2);
    switch (msg) {
        case 0xC519BFC4:
            career_view = !career_view;
            Setup();
            break;
        case 0x911C0A4B:
        case 0x35F8620B:
        case 0x72619778:
            UpdateHighlight();
            break;
        case FEHASH_EXITCOMPLETE:
            uiRapSheetRankings::career_view = career_view;
            cFEng::Get()->QueuePackageSwitch("RapSheetRankings.fng", 0, 0, false);
            break;
    }
}

void uiRapSheetRankingsDetail::Setup() {
    ClearData();
    uint32 category_str_hash;
    UserProfile &prof = *FEDatabase->GetUserProfile(0);
    Attrib::Key key;
    player_rank = prof.GetHighScores()->CalcPursuitRank(rank_type, career_view);
    switch (rank_type) {
        case PD_PURUSIT_LENGTH:
            if (career_view) {
                key = Attrib::StringToKey("pursuit_length_in_pursuit");
            } else {
                key = Attrib::StringToKey("pursuit_length");
            }
            category_str_hash = 0xD70811D1;
            break;
        case PD_COPS_INVOLVED:
            if (career_view) {
                key = Attrib::StringToKey("cops_involved_in_pursuit");
            } else {
                key = Attrib::StringToKey("cops_involved");
            }
            category_str_hash = 0xC6113FCF;
            break;
        case PD_COPS_DAMAGED:
            if (career_view) {
                key = Attrib::StringToKey("cops_damaged_in_pursuit");
            } else {
                key = Attrib::StringToKey("cops_damaged");
            }
            category_str_hash = 0x2A1815D9;
            break;
        case PD_COPS_DESTROYED:
            if (career_view) {
                key = Attrib::StringToKey("cops_destroyed_in_pursuit");
            } else {
                key = Attrib::StringToKey("cops_destroyed");
            }
            category_str_hash = 0x189EAF7B;
            break;
        case PD_SPIKESTRIPS_DODGED:
            if (career_view) {
                key = Attrib::StringToKey("tire_spikes_dodged_in_pursuit");
            } else {
                key = Attrib::StringToKey("tire_spikes_dodged");
            }
            category_str_hash = 0xDCD6B9BA;
            break;
        case PD_ROADBLOCKS_DODGED:
            if (career_view) {
                key = Attrib::StringToKey("roadblocks_dodged_in_pursuit");
            } else {
                key = Attrib::StringToKey("roadblocks_dodged");
            }
            category_str_hash = 0x9EF589BE;
            break;
        case PD_HELICOPTERS_INVOLVED:
            if (career_view) {
                key = Attrib::StringToKey("helis_involved_in_pursuit");
            } else {
                key = Attrib::StringToKey("helis_involved");
            }
            category_str_hash = 0x39A1413C;
            break;
        case PD_COST_TO_STATE:
            if (career_view) {
                key = Attrib::StringToKey("cost_to_state_in_pursuit");
            } else {
                key = Attrib::StringToKey("cost_to_state");
            }
            category_str_hash = 0xB3F963F8;
            break;
        case PD_NUM_INFRACTIONS:
            if (career_view) {
                key = Attrib::StringToKey("total_infractions_in_pursuit");
            } else {
                key = Attrib::StringToKey("total_infractions");
            }
            category_str_hash = 0xE34B2E6F;
            break;
        case PD_BOUNTY:
            if (career_view) {
                key = Attrib::StringToKey("bounty_in_pursuit");
            } else {
                key = Attrib::StringToKey("bounty");
            }
            category_str_hash = 0x48B4B99C;
            break;
        default:
            key = 0;
            category_str_hash = 0;
            break;
    }
    // UNSOLVED
    Attrib::Gen::frontend rapsheet(key, 0, nullptr);
    if (rapsheet.IsValid()) {
        if (rapsheet.Num_RapSheetRanks() == 15) {
            int last;
            int rival_offset = 0;
            bool is_time;
            int player_rank_index = player_rank - 1;
            int num_rankings_to_show = rapsheet.Num_RapSheetRanks();
            if (player_rank == 0x10) {
                num_rankings_to_show = 0x10;
            }
            for (int i = 0; i < num_rankings_to_show; i++) {
                if (i == player_rank_index) {
                    uint32 car_hash = 0;
                    float player_value;
                    if (career_view) {
                        player_value = prof.GetHighScores()->GetCareerPursuitScore(rank_type);
                    } else {
                        car_hash = GetFECarNameHashFromFEKey(prof.GetHighScores()->GetBestPursuitScore(rank_type).CarFEKey);
                        player_value = prof.GetHighScores()->GetBestPursuitScore(rank_type).Value;
                    }
                    player_value = rank_type == PD_COST_TO_STATE ? player_value * 0.00025f : player_value;

                    AddDatum(new ("RapSheetRankingsDatum", 0) RapSheetRankingsDatum(player_rank, 1, car_hash, player_value));
                    rival_offset--;
                } else {
                    uint32 aka_name = FEngHashString("BLACKLIST_RIVAL_%.2d_AKA", rapsheet.NameId(i + rival_offset));
                    uint32 car_name;
                    if (career_view) {
                        car_name = 0;
                    } else {
                        car_name = FEngHashString("BLACKLIST_RIVAL_%.2d_CAR", rapsheet.NameId(i + rival_offset));
                    }
                    AddDatum(new ("RapSheetRankingsDatum", 0)
                                 RapSheetRankingsDatum(i + 1, aka_name, car_name, rapsheet.RapSheetRanks(i + rival_offset)));
                }
            }

            SetInitialPosition(0);
            int dist_off_screen = player_rank - GetHeight() + 4;
            for (; dist_off_screen > 0; dist_off_screen--) {
                ScrollDown();
            }
        }
    }
    FEngSetLanguageHash(GetPackageName(), 0x8224E17C, category_str_hash);
    UpdateHighlight();
    ArrayScroller *scroller = this;
    scroller->RefreshHeader();
}

void uiRapSheetRankingsDetail::RefreshHeader() {
    UserProfile &prof = *FEDatabase->GetUserProfile(0);
    FEPrintf(GetPackageName(), 0x1232703A, GetLocalizedString(0xE21D083C), prof.GetCareer()->GetCaseFileName());
    FEngSetLanguageHash(GetPackageName(), 0x1E4FDA, career_view ? 0x96DDF504 : 0x56E940F4);
    FEngSetLanguageHash(GetPackageName(), 0xDD2F4FB, career_view ? 0x554BBDB5 : 0xA88B3FC5);
    FEngSetLanguageHash(GetPackageName(), 0x9AE9B5CD, career_view ? 0x554BBDB5 : 0xA88B3FC5);
    ArrayScrollerMenu::RefreshHeader();
}

void uiRapSheetRankingsDetail::UpdateHighlight() {
    int player_pos = player_rank - GetStartDatumNum();
    if (player_pos > 0) {
        if (player_pos <= GetNumSlots()) {
            cFEng::Get()->QueuePackageMessage(FEngHashString("POS%d", player_pos), nullptr, nullptr);
            return;
        }
    }
    cFEng::Get()->QueuePackageMessage(0x58B123F7, nullptr, nullptr);
}
