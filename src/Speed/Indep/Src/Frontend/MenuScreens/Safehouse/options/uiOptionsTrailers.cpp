#include "uiOptionsTrailers.hpp"

#include "Speed/Indep/Src/Frontend/FEPackageData.hpp"
#include "Speed/Indep/Src/Frontend/FEngHashes/ScriptHashes.hpp"
#include "Speed/Indep/Src/Frontend/FEngInterfaces/FEngInterface.hpp"
#include "Speed/Indep/Src/Frontend/Database/FEDatabase.hpp"
#include "Speed/Indep/Src/Frontend/MenuScreens/Safehouse/FEPkg_GarageMain.hpp"

UIOptionsTrailers::UIOptionsTrailers(ScreenConstructorData *sd) : IconScrollerMenu(sd) {
    Setup();
}

void UIOptionsTrailers::NotificationMessage(u32 msg, FEObject *pobj, u32 param1, u32 param2) {
    if (msg != 0x0c407210) {
        IconScrollerMenu::NotificationMessage(msg, pobj, param1, param2);
    }

    switch (msg) {
        case 0x911ab364:
            StorePrevNotification(0x911ab364, pobj, param1, param2);
            cFEng::Get()->QueuePackageMessage(0x587c018b, GetPackageName(), nullptr);
            break;
        case 0x0c407210:
            cFEng::Get()->QueuePackageMessage(0x8cb81f09, nullptr, nullptr);
            Options.GetCurrentOption()->React(GetPackageName(), 0x0c407210, pobj, param1, param2);
            break;
        case 0xd05fc3a3:
            Options.GetCurrentOption()->React(GetPackageName(), 0xd05fc3a3, pobj, param1, param2);
            break;
        case FEHASH_EXITCOMPLETE:
            if (PrevButtonMessage == 0x911ab364) {
                FEDatabase->ClearGameMode(eFE_GAME_TRAILERS);
                FEDatabase->GetOptionsSettings()->CurrentCategory = static_cast<eOptionsCategory>(-1);
                cFEng::Get()->QueuePackageSwitch("MainMenu_Sub.fng", 0, 0, false);
            }
            break;
    }
}

void UIOptionsTrailers::Setup() {
    const u32 FEObj_TITLEGROUP = 0xb71b576d;

    SetInitialOption(FEngGetLastButton(GetPackageName()));
    GarageMainScreen::GetInstance()->CancelCameraPush();
    FEngSetLanguageHash(GetPackageName(), FEObj_TITLEGROUP, 0xb65a46d8);
    RefreshHeader();
}
