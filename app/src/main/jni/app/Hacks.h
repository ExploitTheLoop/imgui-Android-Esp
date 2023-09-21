//
// Created by Sayan on 17-07-2023.
//

#ifndef COOLESP_HACKS_H
#define COOLESP_HACKS_H

#include "jancok.h"
#include <chrono>

int screenWidth = -1, screenHeight = -1;
ImFont *font;

Request request;
Response response;
float x,y;
char extra[30];
int botCount,playerCount;
Options options{1,0,3, false,1, true,201
};
radar Radar{radarLocation,radarLocation2};

ImColor Golden = ImColor(255, 185, 15);
ImColor black = ImColor(0, 0, 0, 255);
ImColor white = ImColor(255, 255, 255, 255);
ImColor Red = ImColor(255, 0, 0,255);
ImColor Green = ImColor(0,255,0,255);

void drawEnemycount(int totalEnemies, int totalBots){
    if (totalEnemies + totalBots == 0) {

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();

        ImGui::SetNextWindowPos(ImVec2(center.x, 50), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
        //  ImGui::SetNextWindowSize(ImVec2(countenemWidth, countenemHeight));
        ImGui::SetNextWindowBgAlpha(0.50f); //25
        if (ImGui::Begin("Player Deatils", (bool *) true,
                         ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
                         ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav)) {
            ImGui::SetWindowFontScale(window_scale);
            ImGui::TextColored({1.0f, 1.0f, 1.0f, 1.0f}, "OFA CHEAT");

            // ImGui::TextColored({ 0.000f, 0.983f, 0.817f, 1.000f }, "     REDEYE CHEAT     "); //cian
            ImGui::End();
        }
    } else {
        //ImGui::SetNextWindowSize(ImVec2(countenemWidth, countenemHeight));
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(ImVec2(center.x, 50), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowBgAlpha(0.45f); //45
        if (ImGui::Begin("Player Deatils", (bool *) true,
                         ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
                         ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav)) {
            ImGui::SetWindowFontScale(window_scale);
            std::string playernear;
            playernear += "Players : " + std::to_string(totalEnemies);
            playernear += " Bots : " + std::to_string(totalBots);

            ImGui::TextColored({1.0f, 0.150f, 0.150f, 1.0f}, playernear.c_str()); //red
            ImGui::End();

        }


    }
}

void DrawStrokeText(int x, int y, ImVec4 color, const char *str) {
        ImGui::GetForegroundDrawList()->AddText(ImVec2((float) x + 1, (float) y),
                                                ImGui::ColorConvertFloat4ToU32(
                                                        ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
        ImGui::GetForegroundDrawList()->AddText(ImVec2((float) x - 0.1f, (float) y),
                                                ImGui::ColorConvertFloat4ToU32(
                                                        ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
        ImGui::GetForegroundDrawList()->AddText(ImVec2((float) x, (float) y + 1),
                                                ImGui::ColorConvertFloat4ToU32(
                                                        ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
        ImGui::GetForegroundDrawList()->AddText(ImVec2((float) x, (float) y - 1),
                                                ImGui::ColorConvertFloat4ToU32(
                                                        ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);

    ImGui::GetForegroundDrawList()->AddText(ImVec2((float) x, (float) y),
                                            ImGui::ColorConvertFloat4ToU32(color),
                                            str);
}

ImColor GetRandomBackgroundByTeamID(int index, int bright, int alpha)
{
    return ImColor::HSV((index + 3.6) / 360.f, bright / 255.f, 1.0f, alpha / 255.f);
}

std::string getWeapon(int id) {
    //AR and SMG
    if (id == 101006)
        return "AUG";
    if (id == 101008)
        return "M762";
    if (id == 101003)
        return "SCAR-L";
    if (id == 101004)
        return "M416";
    if (id == 101002)
        return "M16A-4";
    if (id == 101009)
        return "Mk47 Mutant";
    if (id == 101010)
        return "G36C";
    if (id == 101007)
        return "QBZ";
    if (id == 101001)
        return "AKM";
    if (id == 101005)
        return "Groza";
    if (id == 102005)
        return "Bizon";
    if (id == 102004)
        return "TommyGun";
    if (id == 102007)
        return "MP5K";
    if (id == 102002)
        return "UMP";
    if (id == 102003)
        return "Vector";
    if (id == 102001)
        return "Uzi";
    if (id == 105002)
        return "DP28";
    if (id == 105001)
        return "M249";

    //Snipers
    if (id == 103003)
        return "AWM";
    if (id == 103010)
        return "QBU";
    if (id == 103009)
        return "SLR";
    if (id == 103004)
        return "SKS";
    if (id == 103006)
        return "Mini14";
    if (id == 103002)
        return "M24";
    if (id == 103001)
        return "Kar98k";
    if (id == 103005)
        return "VSS";
    if (id == 103008)
        return "Win94";
    if (id == 103007)
        return "Mk14";

    //Shotguns and Hand weapons
    if (id == 104003)
        return "S12K";
    if (id == 104004)
        return "DBS";
    if (id == 104001)
        return "S686";
    if (id == 104002)
        return "S1897";
    if (id == 108003)
        return "Sickle";
    if (id == 108001)
        return "Machete";
    if (id == 108002)
        return "Crowbar";
    if (id == 107001)
        return "CrossBow";
    if (id == 108004)
        return "Pan";

    //Pistols
    if (id == 106006)
        return "SawedOff";
    if (id == 106003)
        return "R1895";
    if (id == 106008)
        return "Vz61";
    if (id == 106001)
        return "P92";
    if (id == 106004)
        return "P18C";
    if (id == 106005)
        return "R45";
    if (id == 106002)
        return "P1911";
    if (id == 106010)
        return "DesertEagle";

    return "Weapon";
}

std::string getVehicleName(char *s) {
    if (strstr(s,"Buggy"))
        return "Buggy";
    if (strstr(s,"UAZ"))
        return "UAZ";
    if (strstr(s,"MotorcycleC"))
        return "Trike";
    if (strstr(s,"Motorcycle"))
        return "Bike";
    if (strstr(s,"Dacia"))
        return "Dacia";
    if (strstr(s,"AquaRail"))
        return "Jet";
    if (strstr(s,"PG117"))
        return "Boat";
    if (strstr(s,"MiniBus"))
        return "Bus";
    if (strstr(s,"Mirado"))
        return "Mirado";
    if (strstr(s,"Scooter"))
        return "Scooter";
    if (strstr(s,"Rony"))
        return "Rony";
    if (strstr(s,"Snowbike"))
        return "Snowbike";
    if (strstr(s,"Snowmobile"))
        return "Snowmobile";
    if (strstr(s,"Tuk"))
        return "Tempo";
    if (strstr(s,"PickUp"))
        return "Truck";
    if (strstr(s,"BRDM"))
        return "BRDM";
    if (strstr(s,"LadaNiva"))
        return "LadaNiva";
    if (strstr(s,"CoupeRB"))
        return "CoupeRB";
    if(strstr(s,"CoupeRB"))
        return "CoupeRB";
    if(strstr(s,"Motorglider"))
        return "Motorglider";
    if (strstr(s,"Bigfoot"))
        return "Monster";

    return "Vehcile";
}

std::string getItemName(char *s) {
    //Scopes
    if (strstr(s,"MZJ_8X")) {
        return "8x";
    }
    if (strstr(s,"MZJ_2X")) {

        return "2x";
    }
    if (strstr(s,"MZJ_HD")) {

        return "Red Dot";
    }
    if (strstr(s,"MZJ_3X")) {

        return "3X";
    }
    if (strstr(s,"MZJ_QX")) {

        return "Hollow Sight";
    }
    if (strstr(s,"MZJ_6X")) {

        return "6x";
    }
    if (strstr(s,"MZJ_4X")) {

        return "4x";
    }
    if (strstr(s,"MZJ_SideRMR")) {

        return "Canted Sight";
    }

    //AR and SMG
    if (strstr(s,"AUG")) {

        return "AUG";
    }
    if (strstr(s,"M762")) {

        return "M762";
    }
    if (strstr(s,"SCAR")) {

        return "SCAR-L";
    }
    if (strstr(s,"M416")) {

        return "M416";
    }
    if (strstr(s,"M16A4")) {

        return "M16A-4";
    }
    if (strstr(s,"Mk47")) {

        return "Mk47 Mutant";
    }
    if (strstr(s,"G36")) {

        return "G36C";
    }
    if (strstr(s,"QBZ")) {

        return "QBZ";
    }
    if (strstr(s,"AKM")) {

        return "AKM";
    }
    if (strstr(s,"Groza")) {

        return "Groza";
    }
    if (strstr(s,"PP19")) {

        return "Bizon";
    }
    if (strstr(s,"TommyGun")) {

        return "TommyGun";
    }
    if (strstr(s,"MP5K")) {

        return "MP5K";
    }
    if (strstr(s,"UMP9")) {

        return "UMP";
    }
    if (strstr(s,"Vector")) {

        return "Vector";
    }
    if (strstr(s,"MachineGun_Uzi")) {

        return "Uzi";
    }
    if (strstr(s,"DP28")) {

        return "DP28";
    }
    if (strstr(s,"M249")) {

        return "M249";
    }

    //Snipers
    if (strstr(s,"AWM")) {

        return "AWM";
    }
    if (strstr(s,"QBU")) {

        return "QBU";
    }
    if (strstr(s,"SLR")) {

        return "SLR";
    }
    if (strstr(s,"SKS")) {

        return "SKS";
    }
    if (strstr(s,"Mini14")) {

        return "Mini14";
    }
    if (strstr(s,"Sniper_M24")) {

        return "M24";
    }
    if (strstr(s,"Kar98k")) {

        return "Kar98k";
    }
    if (strstr(s,"VSS")) {

        return "VSS";
    }
    if (strstr(s,"Win94")) {

        return "Win94";
    }
    if (strstr(s,"Mk14")) {

        return "Mk14";
    }

    //Shotguns and Hand weapons
    if (strstr(s,"S12K")) {

        return "S12K";
    }
    if (strstr(s,"ShotGun_DP12")) {

        return "DBS";
    }
    if (strstr(s,"S686")) {

        return "S686";
    }
    if (strstr(s,"S1897")) {

        return "S1897";
    }
    if (strstr(s,"Sickle")) {

        return "Sickle";
    }
    if (strstr(s,"Machete")) {

        return "Machete";
    }
    if (strstr(s,"Cowbar")) {

        return "Crowbar";
    }
    if (strstr(s,"CrossBow")) {

        return "CrossBow";
    }
    if (strstr(s,"Pan")) {

        return "Pan";
    }

    //Pistols
    if (strstr(s,"SawedOff")) {

        return "SawedOff";
    }
    if (strstr(s,"R1895")) {

        return "R1895";
    }
    if (strstr(s,"Vz61")) {

        return "Vz61";
    }
    if (strstr(s,"P92")) {

        return "P92";
    }
    if (strstr(s,"P18C")) {

        return "P18C";
    }
    if (strstr(s,"R45")) {

        return "R45";
    }
    if (strstr(s,"P1911")) {

        return "P1911";
    }
    if (strstr(s,"DesertEagle")) {

        return "DesertEagle";
    }

    //Ammo
    if (strstr(s,"Ammo_762mm")) {

        return "7.62";
    }
    if (strstr(s,"Ammo_45AC")) {

        return "45ACP";
    }
    if (strstr(s,"Ammo_556mm")) {

        return "5.56";
    }
    if (strstr(s,"Ammo_9mm")) {

        return "9mm";
    }
    if (strstr(s,"Ammo_300Magnum")) {

        return "300Magnum";
    }
    if (strstr(s,"Ammo_12Guage")) {

        return "12 Guage";
    }
    if (strstr(s,"Ammo_Bolt")) {

        return "Arrow";
    }

    //Bag, Helmet, Vest
    if (strstr(s,"Bag_Lv3")) {

        return "Bag lvl 3";
    }
    if (strstr(s,"Bag_Lv1")) {

        return "Bag lvl 1";
    }
    if (strstr(s,"Bag_Lv2")) {

        return "Bag lvl 2";
    }
    if (strstr(s,"Armor_Lv2")) {

        return "Vest lvl 2";
    }
    if (strstr(s,"Armor_Lv1")) {

        return "Vest lvl 1";
    }
    if (strstr(s,"Armor_Lv3")) {

        return "Vest lvl 3";
    }
    if (strstr(s,"Helmet_Lv2")) {

        return "Helmet lvl 2";
    }
    if (strstr(s,"Helmet_Lv1")) {

        return "Helmet lvl 1";
    }
    if (strstr(s,"Helmet_Lv3")) {

        return "Helmet lvl 3";
    }

    //Health kits
    if (strstr(s,"Pills")) {

        return "Painkiller";
    }
    if (strstr(s,"Injection")) {

        return "Adrenaline";
    }
    if (strstr(s,"Drink")) {

        return "Energy Drink";
    }
    if (strstr(s,"Firstaid")) {

        return "FirstAidKit";
    }
    if (strstr(s,"Bandage")) {

        return "Bandage";
    }
    if (strstr(s,"FirstAidbox")) {

        return "Medkit";
    }

    //Throwables
    if (strstr(s,"Grenade_Stun")) {

        return "Stung";
    }
    if (strstr(s,"Grenade_Shoulei")) {

        return "Grenade";
    }
    if (strstr(s,"Grenade_Smoke")) {

        return "Smoke";
    }
    if (strstr(s,"Grenade_Burn")) {

        return "Molotov";
    }

    //Others
    if (strstr(s,"Large_FlashHider")) {

        return "Flash Hider Ar";
    }
    if (strstr(s,"QK_Large_C")) {

        return "Ar Compensator";
    }
    if (strstr(s,"Mid_FlashHider")) {

        return "Flash Hider SMG";
    }
    if (strstr(s,"QT_A_")) {

        return "Tactical Stock";
    }
    if (strstr(s,"DuckBill")) {

        return "DuckBill";
    }
    if (strstr(s,"Sniper_FlashHider")) {

        return "Flash Hider Sniper";
    }
    if (strstr(s,"Mid_Suppressor")) {

        return "Suppressor SMG";
    }
    if (strstr(s,"HalfGrip")) {

        return "Half Grip";
    }
    if (strstr(s,"Choke")) {

        return "Choke";
    }
    if (strstr(s,"QT_UZI")) {

        return "Stock Micro UZI";
    }
    if (strstr(s,"QK_Sniper_C")) {

        return "Sniper Compensator";
    }
    if (strstr(s,"Sniper_Suppressor")) {

        return "Suppressor Sniper";
    }
    if (strstr(s,"Large_Suppressor")) {

        return "Suppressor Ar";
    }
    if (strstr(s,"Sniper_EQ_")) {

        return "Ex.Qd.Sniper";
    }
    if (strstr(s,"Mid_Q_")) {

        return "Qd.SMG";
    }
    if (strstr(s,"Mid_E_")) {

        return "Ex.SMG";
    }
    if (strstr(s,"Sniper_Q_")) {

        return "Qd.Sniper";
    }
    if (strstr(s,"Sniper_E_")) {

        return "Ex.Sniper";
    }
    if (strstr(s,"Large_E_")) {

        return "Ex.Ar";
    }
    if (strstr(s,"Large_EQ_")) {

        return "Ex.Qd.Ar";
    }
    if (strstr(s,"Large_Q_")) {

        return "Qd.Ar";
    }
    if (strstr(s,"Mid_EQ_")) {

        return "Ex.Qd.SMG";
    }
    if (strstr(s,"Crossbow_Q")) {

        return "Quiver CrossBow";
    }
    if (strstr(s,"ZDD_Sniper")) {

        return "Bullet Loop";
    }
    if (strstr(s,"ThumbGrip")) {

        return "Thumb Grip";
    }
    if (strstr(s,"Lasersight")) {

        return "Laser Sight";
    }
    if (strstr(s,"Angled")) {

        return "Angled Grip";
    }
    if (strstr(s,"LightGrip")) {

        return "Light Grip";
    }
    if (strstr(s,"Vertical")) {

        return "Vertical Grip";
    }
    if (strstr(s,"GasCan")) {

        return "Gas Can";
    }
    if (strstr(s,"Mid_Compensator")) {

        return "Compensator SMG";
    }

    //Special
    if (strstr(s,"Flare")) {

        return "Flare Gun";
    }
    if (strstr(s,"Ghillie")) {

        return "Ghillie Suit";
    }
    if (strstr(s,"QT_Sniper")) {

        return "CheekPad";
    }
    if (strstr(s,"PickUpListWrapperActor")) {

        return "Crate";
    }
    if (strstr(s,"AirDropPlane")) {

        return "DropPlane";
    }
    if (strstr(s,"AirDrop")) {

        return "AirDrop";
    }
    //return s;
    return "Item";
}


ImColor GetImColorByTeamID(int id) {

    switch (id) {
        case 1:
            return ImColor(220, 20, 60, 160);
            break;
        case 2:
            return ImColor(0, 139, 139, 160);
            break;
        case 3:
            return ImColor(255, 20, 147, 160);
            break;
        case 4:
            return ImColor(178, 34, 34, 160);
            break;
        case 5:
            return ImColor(255, 69, 0, 160);
            break;
        case 6:
            return ImColor(255, 140, 0, 160);
            break;
        case 7:
            return ImColor(255, 215, 0, 160);
            break;
        case 8:
            return ImColor(255, 0, 255, 160);
            break;
        case 9:
            return ImColor(138, 43, 226, 160);
            break;
        case 10:
            return ImColor(128, 0, 128, 160);
            break;
        case 11:
            return ImColor(75, 0, 130, 160);
            break;
        case 12:
            return ImColor(0, 128, 0, 160);
            break;
        case 13:
            return ImColor(0, 100, 0, 160);
            break;
        case 14:
            return ImColor(32, 178, 170, 160);
            break;
        case 15:
            return ImColor(199, 21, 133, 160);
            break;
        case 16:
            return ImColor(0, 206, 209, 160);
            break;
        case 17:
            return ImColor(70, 130, 180, 160);
            break;
        case 18:
            return ImColor(0, 191, 255, 160);
            break;
        case 19:
            return ImColor(30, 144, 255, 160);
            break;
        case 20:
            return ImColor(0, 0, 139, 160);
            break;
        case 21:
            return ImColor(184, 134, 11, 160);
            break;
        case 22:
            return ImColor(210, 105, 30, 160);
            break;
        case 23:
            return ImColor(165, 42, 42, 160);
            break;
        case 24:
            return ImColor(105, 105, 105, 160);
            break;
        case 25:
            return ImColor(47, 79, 79, 160);
            break;
        case 26:
            return ImColor(220, 20, 60, 160);
            break;
        case 27:
            return ImColor(178, 34, 34, 160);
            break;
        case 28:
            return ImColor(255, 20, 147, 160);
            break;
        case 29:
            return ImColor(199, 21, 133, 160);
            break;
        case 30:
            return ImColor(255, 69, 0, 160);
            break;
        case 31:
            return ImColor(255, 140, 0, 160);
            break;
        case 32:
            return ImColor(255, 215, 0, 160);
            break;
        case 33:
            return ImColor(255, 0, 255, 160);
            break;
        case 34:
            return ImColor(138, 43, 226, 160);
            break;
        case 35:
            return ImColor(128, 0, 128, 160);
            break;
        case 36:
            return ImColor(75, 0, 130, 160);
            break;
        case 37:
            return ImColor(0, 128, 0, 160);
            break;
        case 38:
            return ImColor(0, 100, 0, 160);
            break;
        case 39:
            return ImColor(32, 178, 170, 160);
            break;
        case 40:
            return ImColor(0, 139, 139, 160);
            break;
        case 41:
            return ImColor(0, 206, 209, 160);
            break;
        case 42:
            return ImColor(70, 130, 180, 160);
            break;
        case 43:
            return ImColor(0, 191, 255, 160);
            break;
        case 44:
            return ImColor(30, 144, 255, 160);
            break;
        case 45:
            return ImColor(0, 0, 139, 160);
            break;
        case 46:
            return ImColor(184, 134, 11, 160);
            break;
        case 47:
            return ImColor(210, 105, 30, 160);
            break;
        case 48:
            return ImColor(165, 42, 42, 160);
            break;
        case 49:
            return ImColor(105, 105, 105, 160);
            break;
        case 50:
            return ImColor(47, 79, 79, 160);
            break;
        case 51:
            return ImColor(220, 20, 60, 160);
            break;
        case 52:
            return ImColor(178, 34, 34, 160);
            break;
        case 53:
            return ImColor(255, 20, 147, 160);
            break;
        case 54:
            return ImColor(199, 21, 133, 160);
            break;
        case 55:
            return ImColor(255, 69, 0, 160);
            break;
        case 56:
            return ImColor(255, 140, 0, 160);
            break;
        case 57:
            return ImColor(255, 215, 0, 160);
            break;
        case 58:
            return ImColor(255, 0, 255, 160);
            break;
        case 59:
            return ImColor(138, 43, 226, 160);
            break;
        case 60:
            return ImColor(128, 0, 128, 160);
            break;
        case 61:
            return ImColor(75, 0, 130, 160);
            break;
        case 62:
            return ImColor(0, 128, 0, 160);
            break;
        case 63:
            return ImColor(0, 100, 0, 160);
            break;
        case 64:
            return ImColor(32, 178, 170, 160);
            break;
        case 65:
            return ImColor(0, 139, 139, 160);
            break;
        case 66:
            return ImColor(0, 206, 209, 160);
            break;
        case 67:
            return ImColor(70, 130, 180, 160);
            break;
        case 68:
            return ImColor(0, 191, 255, 160);
            break;
        case 69:
            return ImColor(30, 144, 255, 160);
            break;
        case 70:
            return ImColor(0, 0, 139, 160);
            break;
        case 71:
            return ImColor(184, 134, 11, 160);
            break;
        case 72:
            return ImColor(210, 105, 30, 160);
            break;
        case 73:
            return ImColor(165, 42, 42, 160);
            break;
        case 74:
            return ImColor(105, 105, 105, 160);
            break;
        case 75:
            return ImColor(47, 79, 79, 160);
            break;
        case 76:
            return ImColor(220, 20, 60, 160);
            break;
        case 77:
            return ImColor(178, 34, 34, 160);
            break;
        case 78:
            return ImColor(255, 20, 147, 160);
            break;
        case 79:
            return ImColor(199, 21, 133, 160);
            break;
        case 80:
            return ImColor(255, 69, 0, 160);
            break;
        case 81:
            return ImColor(255, 140, 0, 160);
            break;
        case 82:
            return ImColor(255, 215, 0, 160);
            break;
        case 83:
            return ImColor(255, 0, 255, 160);
            break;
        case 84:
            return ImColor(138, 43, 226, 160);
            break;
        case 85:
            return ImColor(128, 0, 128, 160);
            break;
        case 86:
            return ImColor(75, 0, 130, 160);
            break;
        case 87:
            return ImColor(0, 128, 0, 160);
            break;
        case 88:
            return ImColor(0, 100, 0, 160);
            break;
        case 89:
            return ImColor(32, 178, 170, 160);
            break;
        case 90:
            return ImColor(0, 139, 139, 160);
            break;
        case 91:
            return ImColor(0, 206, 209, 160);
            break;
        case 92:
            return ImColor(70, 130, 180, 160);
            break;
        case 93:
            return ImColor(0, 191, 255, 160);
            break;
        case 94:
            return ImColor(30, 144, 255, 160);
            break;
        case 95:
            return ImColor(0, 0, 139, 160);
            break;
        case 96:
            return ImColor(184, 134, 11, 160);
            break;
        case 97:
            return ImColor(210, 105, 30, 160);
            break;
        case 98:
            return ImColor(165, 42, 42, 160);
            break;
        case 99:
            return ImColor(105, 105, 105, 160);
            break;
        case 100:
            return ImColor(47, 79, 79, 160);
            break;
        case 101:
            return ImColor(220, 20, 60, 160);
            break;
        case 102:
            return ImColor(178, 34, 34, 160);
            break;
        case 103:
            return ImColor(255, 20, 147, 160);
            break;
        case 104:
            return ImColor(199, 21, 133, 160);
            break;
        case 105:
            return ImColor(255, 69, 0, 160);
            break;
        case 106:
            return ImColor(255, 140, 0, 160);
            break;
        case 107:
            return ImColor(255, 215, 0, 160);
            break;
        case 108:
            return ImColor(255, 0, 255, 160);
            break;
        case 109:
            return ImColor(138, 43, 226, 160);
            break;
        case 110:
            return ImColor(128, 0, 128, 160);
            break;
        case 111:
            return ImColor(75, 0, 130, 160);
            break;
        case 112:
            return ImColor(0, 128, 0, 160);
            break;
        case 113:
            return ImColor(0, 100, 0, 160);
            break;
        case 114:
            return ImColor(32, 178, 170, 160);
            break;
        case 115:
            return ImColor(0, 139, 139, 160);
            break;
        case 116:
            return ImColor(0, 206, 209, 160);
            break;
        case 117:
            return ImColor(70, 130, 180, 160);
            break;
        case 118:
            return ImColor(0, 191, 255, 160);
            break;
        case 119:
            return ImColor(30, 144, 255, 160);
            break;
        case 120:
            return ImColor(0, 0, 139, 160);
            break;
        case 121:
            return ImColor(184, 134, 11, 160);
            break;
        case 122:
            return ImColor(210, 105, 30, 160);
            break;
        case 123:
            return ImColor(165, 42, 42, 160);
            break;
        case 124:
            return ImColor(105, 105, 105, 160);
            break;
        case 125:
            return ImColor(47, 79, 79, 160);
            break;
        case 126:
            return ImColor(220, 20, 60, 160);
            break;
        case 127:
            return ImColor(178, 34, 34, 160);
            break;
        case 128:
            return ImColor(255, 20, 147, 160);
            break;
        case 129:
            return ImColor(199, 21, 133, 160);
            break;
        case 130:
            return ImColor(255, 69, 0, 160);
            break;
        case 131:
            return ImColor(255, 140, 0, 160);
            break;
        case 132:
            return ImColor(255, 215, 0, 160);
            break;
        case 133:
            return ImColor(255, 0, 255, 160);
            break;
        case 134:
            return ImColor(138, 43, 226, 160);
            break;
        case 135:
            return ImColor(128, 0, 128, 160);
            break;
        case 136:
            return ImColor(75, 0, 130, 160);
            break;
        case 137:
            return ImColor(0, 128, 0, 160);
            break;
        case 138:
            return ImColor(0, 100, 0, 160);
            break;
        case 139:
            return ImColor(32, 178, 170, 160);
            break;
        case 140:
            return ImColor(0, 139, 139, 160);
            break;
        case 141:
            return ImColor(0, 206, 209, 160);
            break;
        case 142:
            return ImColor(70, 130, 180, 160);
            break;
        case 143:
            return ImColor(0, 191, 255, 160);
            break;
        case 144:
            return ImColor(30, 144, 255, 160);
            break;
        case 145:
            return ImColor(0, 0, 139, 160);
            break;
        case 146:
            return ImColor(184, 134, 11, 160);
            break;
        case 147:
            return ImColor(210, 105, 30, 160);
            break;
        case 148:
            return ImColor(165, 42, 42, 160);
            break;
        case 149:
            return ImColor(105, 105, 105, 160);
            break;
        case 150:
            return ImColor(47, 79, 79, 160);
            break;
        case 151:
            return ImColor(220, 20, 60, 160);
            break;
        case 152:
            return ImColor(178, 34, 34, 160);
            break;
        case 153:
            return ImColor(255, 20, 147, 160);
            break;
        case 154:
            return ImColor(199, 21, 133, 160);
            break;
        case 155:
            return ImColor(255, 69, 0, 160);
            break;
        case 156:
            return ImColor(255, 140, 0, 160);
            break;
        case 157:
            return ImColor(255, 215, 0, 160);
            break;
        case 158:
            return ImColor(255, 0, 255, 160);
            break;
        case 159:
            return ImColor(138, 43, 226, 160);
            break;
        case 160:
            return ImColor(128, 0, 128, 160);
            break;
        case 161:
            return ImColor(75, 0, 130, 160);
            break;
        case 162:
            return ImColor(0, 128, 0, 160);
            break;
        case 163:
            return ImColor(0, 100, 0, 160);
            break;
        case 164:
            return ImColor(32, 178, 170, 160);
            break;
        case 165:
            return ImColor(0, 139, 139, 160);
            break;
        case 166:
            return ImColor(0, 206, 209, 160);
            break;
        case 167:
            return ImColor(70, 130, 180, 160);
            break;
        case 168:
            return ImColor(0, 191, 255, 160);
            break;
        case 169:
            return ImColor(30, 144, 255, 160);
            break;
        case 170:
            return ImColor(0, 0, 139, 160);
            break;
        case 171:
            return ImColor(184, 134, 11, 160);
            break;
        case 172:
            return ImColor(210, 105, 30, 160);
            break;
        case 173:
            return ImColor(165, 42, 42, 160);
            break;
        case 174:
            return ImColor(105, 105, 105, 160);
            break;
        case 175:
            return ImColor(47, 79, 79, 160);
            break;
        case 176:
            return ImColor(220, 20, 60, 160);
            break;
        case 177:
            return ImColor(178, 34, 34, 160);
            break;
        case 178:
            return ImColor(255, 20, 147, 160);
            break;
        case 179:
            return ImColor(199, 21, 133, 160);
            break;
        case 180:
            return ImColor(255, 69, 0, 160);
            break;
        case 181:
            return ImColor(255, 140, 0, 160);
            break;
        case 182:
            return ImColor(255, 215, 0, 160);
            break;
        case 183:
            return ImColor(255, 0, 255, 160);
            break;
        case 184:
            return ImColor(138, 43, 226, 160);
            break;
        case 185:
            return ImColor(128, 0, 128, 160);
            break;
        case 186:
            return ImColor(75, 0, 130, 160);
            break;
        case 187:
            return ImColor(0, 128, 0, 160);
            break;
        case 188:
            return ImColor(0, 100, 0, 160);
            break;
        case 189:
            return ImColor(32, 178, 170, 160);
            break;
        case 190:
            return ImColor(0, 139, 139, 160);
            break;
        case 191:
            return ImColor(0, 206, 209, 160);
            break;
        case 192:
            return ImColor(70, 130, 180, 160);
            break;
        case 193:
            return ImColor(0, 191, 255, 160);
            break;
        case 194:
            return ImColor(30, 144, 255, 160);
            break;
        case 195:
            return ImColor(0, 0, 139, 160);
            break;
        case 196:
            return ImColor(184, 134, 11, 160);
            break;
        case 197:
            return ImColor(210, 105, 30, 160);
            break;
        case 198:
            return ImColor(165, 42, 42, 160);
            break;
        case 199:
            return ImColor(105, 105, 105, 160);
            break;
        case 200:
            return ImColor(47, 79, 79, 160);
            break;
        case 201:
            return ImColor(220, 20, 60, 160);
            break;
        case 202:
            return ImColor(178, 34, 34, 160);
            break;
        case 203:
            return ImColor(255, 20, 147, 160);
            break;
        case 204:
            return ImColor(199, 21, 133, 160);
            break;
        case 205:
            return ImColor(255, 69, 0, 160);
            break;
        case 206:
            return ImColor(255, 140, 0, 160);
            break;
        case 207:
            return ImColor(255, 215, 0, 160);
            break;
        case 208:
            return ImColor(255, 0, 255, 160);
            break;
        case 209:
            return ImColor(138, 43, 226, 160);
            break;
        case 210:
            return ImColor(128, 0, 128, 160);
            break;
        case 211:
            return ImColor(75, 0, 130, 160);
            break;
        case 212:
            return ImColor(0, 128, 0, 160);
            break;
        case 213:
            return ImColor(0, 100, 0, 160);
            break;
        case 214:
            return ImColor(32, 178, 170, 160);
            break;
        case 215:
            return ImColor(0, 139, 139, 160);
            break;
        case 216:
            return ImColor(0, 206, 209, 160);
            break;
        case 217:
            return ImColor(70, 130, 180, 160);
            break;
        case 218:
            return ImColor(0, 191, 255, 160);
            break;
        case 219:
            return ImColor(30, 144, 255, 160);
            break;
        case 220:
            return ImColor(0, 0, 139, 160);
            break;
        case 221:
            return ImColor(184, 134, 11, 160);
            break;
        case 222:
            return ImColor(210, 105, 30, 160);
            break;
        case 223:
            return ImColor(165, 42, 42, 160);
            break;
        case 224:
            return ImColor(105, 105, 105, 160);
            break;
        case 225:
            return ImColor(47, 79, 79, 160);
            break;
        case 226:
            return ImColor(220, 20, 60, 160);
            break;
        case 227:
            return ImColor(178, 34, 34, 160);
            break;
        case 228:
            return ImColor(255, 20, 147, 160);
            break;
        case 229:
            return ImColor(199, 21, 133, 160);
            break;
        case 230:
            return ImColor(255, 69, 0, 160);
            break;
        case 231:
            return ImColor(255, 140, 0, 160);
            break;
        case 232:
            return ImColor(255, 215, 0, 160);
            break;
        case 233:
            return ImColor(255, 0, 255, 160);
            break;
        case 234:
            return ImColor(138, 43, 226, 160);
            break;
        case 235:
            return ImColor(128, 0, 128, 160);
            break;
        case 236:
            return ImColor(75, 0, 130, 160);
            break;
        case 237:
            return ImColor(0, 128, 0, 160);
            break;
        case 238:
            return ImColor(0, 100, 0, 160);
            break;
        case 239:
            return ImColor(32, 178, 170, 160);
            break;
        case 240:
            return ImColor(0, 139, 139, 160);
            break;
        case 241:
            return ImColor(0, 206, 209, 160);
            break;
        case 242:
            return ImColor(70, 130, 180, 160);
            break;
        case 243:
            return ImColor(0, 191, 255, 160);
            break;
        case 244:
            return ImColor(30, 144, 255, 160);
            break;
        case 245:
            return ImColor(0, 0, 139, 160);
            break;
        case 246:
            return ImColor(184, 134, 11, 160);
            break;
        case 247:
            return ImColor(210, 105, 30, 160);
            break;
        case 248:
            return ImColor(165, 42, 42, 160);
            break;
        case 249:
            return ImColor(105, 105, 105, 160);
            break;
        case 250:
            return ImColor(47, 79, 79, 160);
            break;
        case 251:
            return ImColor(220, 20, 60, 160);
            break;
        case 252:
            return ImColor(178, 34, 34, 160);
            break;
        case 253:
            return ImColor(255, 20, 147, 160);
            break;
        case 254:
            return ImColor(199, 21, 133, 160);
            break;
        case 255:
            return ImColor(255, 69, 0, 160);
            break;
        case 256:
            return ImColor(255, 140, 0, 160);
            break;
        case 257:
            return ImColor(255, 215, 0, 160);
            break;
        case 258:
            return ImColor(255, 0, 255, 160);
            break;
        case 259:
            return ImColor(138, 43, 226, 160);
            break;
        case 260:
            return ImColor(128, 0, 128, 160);
            break;
        case 261:
            return ImColor(75, 0, 130, 160);
            break;
        case 262:
            return ImColor(0, 128, 0, 160);
            break;
        case 263:
            return ImColor(0, 100, 0, 160);
            break;
        case 264:
            return ImColor(32, 178, 170, 160);
            break;
        case 265:
            return ImColor(0, 139, 139, 160);
            break;
        case 266:
            return ImColor(0, 206, 209, 160);
            break;
        case 267:
            return ImColor(70, 130, 180, 160);
            break;
        case 268:
            return ImColor(0, 191, 255, 160);
            break;
        case 269:
            return ImColor(30, 144, 255, 160);
            break;
        case 270:
            return ImColor(0, 0, 139, 160);
            break;
        case 271:
            return ImColor(184, 134, 11, 160);
            break;
        case 272:
            return ImColor(210, 105, 30, 160);
            break;
        case 273:
            return ImColor(165, 42, 42, 160);
            break;
        case 274:
            return ImColor(105, 105, 105, 160);
            break;
        case 275:
            return ImColor(47, 79, 79, 160);
            break;
        case 276:
            return ImColor(220, 20, 60, 160);
            break;
        case 277:
            return ImColor(178, 34, 34, 160);
            break;
        case 278:
            return ImColor(255, 20, 147, 160);
            break;
        case 279:
            return ImColor(199, 21, 133, 160);
            break;
        case 280:
            return ImColor(255, 69, 0, 160);
            break;
        case 281:
            return ImColor(255, 140, 0, 160);
            break;
        case 282:
            return ImColor(255, 215, 0, 160);
            break;
        case 283:
            return ImColor(255, 0, 255, 160);
            break;
        case 284:
            return ImColor(138, 43, 226, 160);
            break;
        case 285:
            return ImColor(128, 0, 128, 160);
            break;
        case 286:
            return ImColor(75, 0, 130, 160);
            break;
        case 287:
            return ImColor(0, 128, 0, 160);
            break;
        case 288:
            return ImColor(0, 100, 0, 160);
            break;
        case 289:
            return ImColor(32, 178, 170, 160);
            break;
        case 290:
            return ImColor(0, 139, 139, 160);
            break;
        case 291:
            return ImColor(0, 206, 209, 160);
            break;
        case 292:
            return ImColor(70, 130, 180, 160);
            break;
        case 293:
            return ImColor(0, 191, 255, 160);
            break;
        case 294:
            return ImColor(30, 144, 255, 160);
            break;
        case 295:
            return ImColor(0, 0, 139, 160);
            break;
        case 296:
            return ImColor(184, 134, 11, 160);
            break;
        case 297:
            return ImColor(210, 105, 30, 160);
            break;
        case 298:
            return ImColor(165, 42, 42, 160);
            break;
        case 299:
            return ImColor(105, 105, 105, 160);
            break;
        case 300:
            return ImColor(47, 79, 79, 160);
            break;
        case 301:
            return ImColor(220, 20, 60, 160);
            break;
        case 302:
            return ImColor(178, 34, 34, 160);
            break;
        case 303:
            return ImColor(255, 20, 147, 160);
            break;
        case 304:
            return ImColor(199, 21, 133, 160);
            break;
        case 305:
            return ImColor(255, 69, 0, 160);
            break;
        case 306:
            return ImColor(255, 140, 0, 160);
            break;
        case 307:
            return ImColor(255, 215, 0, 160);
            break;
        case 308:
            return ImColor(255, 0, 255, 160);
            break;
        case 309:
            return ImColor(138, 43, 226, 160);
            break;
        case 310:
            return ImColor(128, 0, 128, 160);
            break;
        case 311:
            return ImColor(75, 0, 130, 160);
            break;
        case 312:
            return ImColor(0, 128, 0, 160);
            break;
        case 313:
            return ImColor(0, 100, 0, 160);
            break;
        case 314:
            return ImColor(32, 178, 170, 160);
            break;
        case 315:
            return ImColor(0, 139, 139, 160);
            break;
        case 316:
            return ImColor(0, 206, 209, 160);
            break;
        case 317:
            return ImColor(70, 130, 180, 160);
            break;
        case 318:
            return ImColor(0, 191, 255, 160);
            break;
        case 319:
            return ImColor(30, 144, 255, 160);
            break;
        case 320:
            return ImColor(0, 0, 139, 160);
            break;
        case 321:
            return ImColor(184, 134, 11, 160);
            break;
        case 322:
            return ImColor(210, 105, 30, 160);
            break;
        case 323:
            return ImColor(165, 42, 42, 160);
            break;
        case 324:
            return ImColor(105, 105, 105, 160);
            break;
        case 325:
            return ImColor(47, 79, 79, 160);
            break;
        case 326:
            return ImColor(220, 20, 60, 160);
            break;
        case 327:
            return ImColor(178, 34, 34, 160);
            break;
        case 328:
            return ImColor(255, 20, 147, 160);
            break;
        case 329:
            return ImColor(199, 21, 133, 160);
            break;
        case 330:
            return ImColor(255, 69, 0, 160);
            break;
        case 331:
            return ImColor(255, 140, 0, 160);
            break;
        case 332:
            return ImColor(255, 215, 0, 160);
            break;
        case 333:
            return ImColor(255, 0, 255, 160);
            break;
        case 334:
            return ImColor(138, 43, 226, 160);
            break;
        case 335:
            return ImColor(128, 0, 128, 160);
            break;
        case 336:
            return ImColor(75, 0, 130, 160);
            break;
        case 337:
            return ImColor(0, 128, 0, 160);
            break;
        case 338:
            return ImColor(0, 100, 0, 160);
            break;
        case 339:
            return ImColor(32, 178, 170, 160);
            break;
        case 340:
            return ImColor(0, 139, 139, 160);
            break;
        case 341:
            return ImColor(0, 206, 209, 160);
            break;
        case 342:
            return ImColor(70, 130, 180, 160);
            break;
        case 343:
            return ImColor(0, 191, 255, 160);
            break;
        case 344:
            return ImColor(30, 144, 255, 160);
            break;
        case 345:
            return ImColor(0, 0, 139, 160);
            break;
        case 346:
            return ImColor(184, 134, 11, 160);
            break;
        case 347:
            return ImColor(210, 105, 30, 160);
            break;
        case 348:
            return ImColor(165, 42, 42, 160);
            break;
        case 349:
            return ImColor(105, 105, 105, 160);
            break;
        case 350:
            return ImColor(47, 79, 79, 160);
            break;
        case 351:
            return ImColor(220, 20, 60, 160);
            break;
        case 352:
            return ImColor(178, 34, 34, 160);
            break;
        case 353:
            return ImColor(255, 20, 147, 160);
            break;
        case 354:
            return ImColor(199, 21, 133, 160);
            break;
        case 355:
            return ImColor(255, 69, 0, 160);
            break;
        case 356:
            return ImColor(255, 140, 0, 160);
            break;
        case 357:
            return ImColor(255, 215, 0, 160);
            break;
        case 358:
            return ImColor(255, 0, 255, 160);
            break;
        case 359:
            return ImColor(138, 43, 226, 160);
            break;
        case 360:
            return ImColor(128, 0, 128, 160);
            break;
        case 361:
            return ImColor(75, 0, 130, 160);
            break;
        case 362:
            return ImColor(0, 128, 0, 160);
            break;
        case 363:
            return ImColor(0, 100, 0, 160);
            break;
        case 364:
            return ImColor(32, 178, 170, 160);
            break;
        case 365:
            return ImColor(0, 139, 139, 160);
            break;
        case 366:
            return ImColor(0, 206, 209, 160);
            break;
        case 367:
            return ImColor(70, 130, 180, 160);
            break;
        case 368:
            return ImColor(0, 191, 255, 160);
            break;
        case 369:
            return ImColor(30, 144, 255, 160);
            break;
        case 370:
            return ImColor(0, 0, 139, 160);
            break;
        case 371:
            return ImColor(184, 134, 11, 160);
            break;
        case 372:
            return ImColor(210, 105, 30, 160);
            break;
        case 373:
            return ImColor(165, 42, 42, 160);
            break;
        case 374:
            return ImColor(105, 105, 105, 160);
            break;
        case 375:
            return ImColor(47, 79, 79, 160);
            break;
        case 376:
            return ImColor(220, 20, 60, 160);
            break;
        case 377:
            return ImColor(178, 34, 34, 160);
            break;
        case 378:
            return ImColor(255, 20, 147, 160);
            break;
        case 379:
            return ImColor(199, 21, 133, 160);
            break;
        case 380:
            return ImColor(255, 69, 0, 160);
            break;
        case 381:
            return ImColor(255, 140, 0, 160);
            break;
        case 382:
            return ImColor(255, 215, 0, 160);
            break;
        case 383:
            return ImColor(255, 0, 255, 160);
            break;
        case 384:
            return ImColor(138, 43, 226, 160);
            break;
        case 385:
            return ImColor(128, 0, 128, 160);
            break;
        case 386:
            return ImColor(75, 0, 130, 160);
            break;
        case 387:
            return ImColor(0, 128, 0, 160);
            break;
        case 388:
            return ImColor(0, 100, 0, 160);
            break;
        case 389:
            return ImColor(32, 178, 170, 160);
            break;
        case 390:
            return ImColor(0, 139, 139, 160);
            break;
        case 391:
            return ImColor(0, 206, 209, 160);
            break;
        case 392:
            return ImColor(70, 130, 180, 160);
            break;
        case 393:
            return ImColor(0, 191, 255, 160);
            break;
        case 394:
            return ImColor(30, 144, 255, 160);
            break;
        case 395:
            return ImColor(0, 0, 139, 160);
            break;
        case 396:
            return ImColor(184, 134, 11, 160);
            break;
        case 397:
            return ImColor(210, 105, 30, 160);
            break;
        case 398:
            return ImColor(165, 42, 42, 160);
            break;
        case 399:
            return ImColor(105, 105, 105, 160);
            break;
        case 400:
            return ImColor(47, 79, 79, 160);
            break;
    }
}


void ESP()
{


    botCount=0;playerCount=0;
    request.ScreenHeight=screenHeight;
    request.ScreenWidth=screenWidth;
    request.Mode=InitMode;
    if(isaimbot){
        options.openState = 0;
    }else{
        options.openState = -1;
    }

    if(target == 0){
        options.aimbotmode = 1;
    }else if(target == 1){
        options.aimbotmode = 2;
    }else{
        options.aimbotmode = 3;
    }
    options.aimingRange = fov+1;
    options.pour = isAimKnocked;
    options.tracingStatus = isBulletTrack;

    Radar.x = radarLocation;
    Radar.y = radarLocation2;
    request.options=options;
    request.Radar= Radar;
    send((void*)&request,sizeof(request));
    receive((void*)&response);

    if(response.Success) {
        isDataReciving = true;
        if(options.openState==0)
            ImGui::GetForegroundDrawList()->AddCircle(ImVec2((float) screenWidth / 2, (float) screenHeight / 2), options.aimingRange, white);
        for (int i = 0; i < response.PlayerCount; i++) {
            x = response.Players[i].HeadLocation.x;
            y = response.Players[i].HeadLocation.y;
            if (response.Players[i].isBot) {
                botCount++;
            } else {
                playerCount++;
            }
            Vec2 screen(screenWidth, screenHeight);
            float mScale = screenHeight / (float) 1080;
            float magic_number = (response.Players[i].Distance * response.fov);
            float mx = (screenWidth / 4) / magic_number;
            float my = (screenWidth / 1.38) / magic_number;
            float mz = (screenWidth / 1.20) / magic_number;
            float top = y - my + (screenWidth / 1.7) / magic_number;
            float bottom = response.Players[i].Bone.lAn.y + my - (screenWidth / 1.7) / magic_number;
            if (response.Players[i].HeadLocation.z != 1) {
                if (x > -50 && x < screenWidth + 50) {

                    //causingcrash //probably the name
                    if(isEsp){
                        ImGui::GetForegroundDrawList()->AddLine({screenWidth / 2, 0}, {x, top - screenHeight / 34}, white, {1});

                        //name and team idbox
                        ImGui::GetForegroundDrawList()->AddRect({x - mx, top}, {x + mx, bottom},white, {2.5}, 5,{2.5});

                        //name
                        ImGui::GetForegroundDrawList()->AddRectFilled({x - screenWidth / 21, top - screenHeight / 18}, {x + screenWidth / 21, top - screenHeight / 33.5},GetImColorByTeamID(response.Players[i].TeamID), {2.5});
                        ImGui::GetForegroundDrawList()->AddRect({x - screenWidth / 21, top - screenHeight / 18}, {x + screenWidth / 21, top - screenHeight / 33.5},GetImColorByTeamID(response.Players[i].TeamID), {2.5});
                        if(response.Players[i].isBot){
                            ImGui::GetForegroundDrawList()->AddText(font, fontsize, ImVec2(x -textpos, top - screenHeight / 20), white, "[AI]");
                        }else{
                          //  sprintf(extra, "%s", response.Players[i].PlayerNameByte);
                            ImGui::GetForegroundDrawList()->AddText(font, fontsize, ImVec2(x -textpos, top - screenHeight / 20), white, "[ Player ]");
                        }

                        //team id
                        ImGui::GetForegroundDrawList()->AddRect({x - screenWidth / 21, top - screenHeight / 18}, {x - screenWidth / 33, top - screenHeight / 33.5},ImColor(0, 0, 0, 60), {2.5});
                        ImGui::GetForegroundDrawList()->AddRectFilled({x - screenWidth / 21, top - screenHeight / 18}, {x - screenWidth / 33, top - screenHeight / 33.5},ImColor(0, 0, 0, 60), {2.5});
                        sprintf(extra, "%d", response.Players[i].TeamID);
                        ImGui::GetForegroundDrawList()->AddText(font, fontsize, ImVec2(x - teamidpos, top - screenHeight / 20), white, extra);

                        //distance
                        sprintf(extra, "%0.0fM", response.Players[i].Distance);
                        //top
                        //  ImGui::GetForegroundDrawList()->AddText(font, 18, ImVec2(x + 55, top - screenHeight / 20), white, extra);
                        //bottom
                       // ImGui::GetForegroundDrawList()->AddText(font, 18, ImVec2(x - 15, bottom + screenHeight / 60), white, extra);
                        DrawStrokeText(x -15,bottom + screenHeight / 60,Red,extra);

                        if(response.Players[i].Weapon.isWeapon){
                            DrawStrokeText(x -15,bottom + screenHeight / 25,Golden,getWeapon(response.Players[i].Weapon.id).c_str());
                        }


                    }

                    if(isPlayerHealth){
                        //health bar
                        if(response.Players[i].Health == 0.0f){ //knock

                            ImGui::GetForegroundDrawList()->AddRectFilled({x - screenWidth / 21, top - screenHeight / 33.5}, {x - screenWidth / 21 + (2 * screenWidth / 21) * response.Players[i].Health /100, top - screenHeight / 42},ImColor(255, 0, 0, 200), {2.5});
                            ImGui::GetForegroundDrawList()->AddRect({x - screenWidth / 21, top - screenHeight / 33.5}, {x - screenWidth / 21 + (2 * screenWidth / 21) * response.Players[i].Health /100, top - screenHeight / 42},ImColor(255, 0, 0, 200), {2.5});

                        }else{
                            ImColor clrHealth;
                            if (response.Players[i].Health < 35)
                                clrHealth = ImColor(204, 51, 51, 200);
                            else if (response.Players[i].Health < 75)
                                clrHealth = ImColor(255, 153, 153, 200);
                            else
                                clrHealth = ImColor(255, 255, 255, 200);

                            ImGui::GetForegroundDrawList()->AddRectFilled({x - screenWidth / 21, top - screenHeight / 33.5}, {x - screenWidth / 21 + (2 * screenWidth / 21) * response.Players[i].Health /100, top - screenHeight / 42},clrHealth, {2.5});

                        }
                    }


                    if(isSkelton){
                        //skeleton
                        ImGui::GetForegroundDrawList()->AddLine({response.Players[i].Bone.neck.x, response.Players[i].Bone.neck.y}, {response.Players[i].Bone.cheast.x, response.Players[i].Bone.cheast.y}, Red, {1.5});
                        ImGui::GetForegroundDrawList()->AddLine({response.Players[i].Bone.cheast.x, response.Players[i].Bone.cheast.y}, {response.Players[i].Bone.pelvis.x, response.Players[i].Bone.pelvis.y}, Red, {1.5});
                        ImGui::GetForegroundDrawList()->AddLine({response.Players[i].Bone.neck.x, response.Players[i].Bone.neck.y}, {response.Players[i].Bone.lSh.x, response.Players[i].Bone.lSh.y}, Red, {1.5});
                        ImGui::GetForegroundDrawList()->AddLine({response.Players[i].Bone.neck.x, response.Players[i].Bone.neck.y}, {response.Players[i].Bone.rSh.x, response.Players[i].Bone.rSh.y}, Red, {1.5});
                        ImGui::GetForegroundDrawList()->AddLine({response.Players[i].Bone.lSh.x, response.Players[i].Bone.lSh.y}, {response.Players[i].Bone.lElb.x, response.Players[i].Bone.lElb.y}, Red, {1.5});
                        ImGui::GetForegroundDrawList()->AddLine({response.Players[i].Bone.rSh.x, response.Players[i].Bone.rSh.y}, {response.Players[i].Bone.rElb.x, response.Players[i].Bone.rElb.y}, Red, {1.5});
                        ImGui::GetForegroundDrawList()->AddLine({response.Players[i].Bone.lElb.x, response.Players[i].Bone.lElb.y}, {response.Players[i].Bone.lWr.x, response.Players[i].Bone.lWr.y}, Red, {1.5});
                        ImGui::GetForegroundDrawList()->AddLine({response.Players[i].Bone.rElb.x, response.Players[i].Bone.rElb.y}, {response.Players[i].Bone.rWr.x, response.Players[i].Bone.rWr.y}, Red, {1.5});
                        ImGui::GetForegroundDrawList()->AddLine({response.Players[i].Bone.pelvis.x, response.Players[i].Bone.pelvis.y}, {response.Players[i].Bone.lTh.x, response.Players[i].Bone.lTh.y}, Red, {1.5});
                        ImGui::GetForegroundDrawList()->AddLine({response.Players[i].Bone.pelvis.x, response.Players[i].Bone.pelvis.y}, {response.Players[i].Bone.rTh.x, response.Players[i].Bone.rTh.y}, Red, {1.5});
                        ImGui::GetForegroundDrawList()->AddLine({response.Players[i].Bone.lTh.x, response.Players[i].Bone.lTh.y}, {response.Players[i].Bone.lKn.x, response.Players[i].Bone.lKn.y}, Red, {1.5});
                        ImGui::GetForegroundDrawList()->AddLine({response.Players[i].Bone.rTh.x, response.Players[i].Bone.rTh.y}, {response.Players[i].Bone.rKn.x, response.Players[i].Bone.rKn.y}, Red, {1.5});
                        ImGui::GetForegroundDrawList()->AddLine({response.Players[i].Bone.lKn.x, response.Players[i].Bone.lKn.y}, {response.Players[i].Bone.lAn.x, response.Players[i].Bone.lAn.y}, Red, {1.5});
                        ImGui::GetForegroundDrawList()->AddLine({response.Players[i].Bone.rKn.x, response.Players[i].Bone.rKn.y}, {response.Players[i].Bone.rAn.x, response.Players[i].Bone.rAn.y}, Red, {1.5});
                        ImGui::GetForegroundDrawList()->AddCircle({response.Players[i].Bone.neck.x,
                                                                   response.Players[i].Bone.neck.y - 3}, screenHeight / 8.5/ magic_number,
                                                                  Red,
                                                                  0,
                                                                  1.5f);
                    }




                }
            }

            Vec2 location(response.Players[i].HeadLocation.x, response.Players[i].HeadLocation.y);
            if (isr360Alert && isOutsideSafeZone(location, screen)) {
                ImVec2 hintDotRenderPos = pushToScreenBorder(location, screen, (int) ((mScale * 100) / 3));
                ImVec2 hintTextRenderPos = pushToScreenBorder(location, screen, -(int) ((mScale * 36)));

                ImGui::GetForegroundDrawList()->AddCircleFilled(hintDotRenderPos, (mScale * 85),GetImColorByTeamID(response.Players[i].TeamID), 0); //Background
                sprintf(extra, "%0.0fm", response.Players[i].Distance);
               // ImGui::GetForegroundDrawList()->AddText(font, 18,hintTextRenderPos,white, extra);
            }
            if (response.Players[i].HeadLocation.z == 1.0f) {
                if (y > screenHeight - screenHeight / 12)
                    y = screenHeight - screenHeight / 12;
                else if (y < screenHeight / 12)
                    y = screenHeight / 12;
            }
            else if (x < -screenWidth / 10 || x > screenWidth + screenWidth / 10) {
                if (y > screenHeight - screenHeight / 12)
                    y = screenHeight - screenHeight / 12;
                else if (y < screenHeight / 12)
                    y = screenHeight / 12;
            }

        }

        if(isvehcile){
            for(int i = 0; i < response.VehicleCount; i++) {
                if (response.Vehicles[i].Location.z != 1.0f) {

                  //  sprintf(extra, "%s", response.Vehicles[i].VehicleName);
                    DrawStrokeText(response.Vehicles[i].Location.x,response.Vehicles[i].Location.y,Red,
                                   getVehicleName(response.Vehicles[i].VehicleName).c_str());
                    sprintf(extra, "[ %0.0fm ]", response.Vehicles[i].Distance);
                    DrawStrokeText(response.Vehicles[i].Location.x,response.Vehicles[i].Location.y + 30,Golden,extra);
                   // ImGui::GetForegroundDrawList()->AddText(font, 18, ImVec2(response.Vehicles[i].Location.x,response.Vehicles[i].Location.y), white,extra);
                }
            }
        }

        if (isItems) {
            for(int i = 0; i < response.ItemsCount; i++) { //Items
                if(response.Items[i].Location.z!=1.0f) {
                    DrawStrokeText(response.Items[i].Location.x,response.Items[i].Location.y,
                                   Golden,getItemName(response.Items[i].ItemName).c_str());
                }
            }
        }

        for (int i = 0; i < response.GrenadeCount; i++) {
            char grenadecn[100];
            sprintf(grenadecn, "! WARNING THERE IS [%d] GRENADE NEAR YOU !",
                    (int) response.GrenadeCount);
            if (response.Grenade[i].Location.z != 1.0f) {
                char grenadeAlert[100];
                ImColor grnd;
                if (response.Grenade[i].type == 1) {
                    sprintf(grenadeAlert, "Grenade! [%dm]", (int) response.Grenade[i].Distance);
                    grnd = ImColor(255, 0, 0);
                }
                else {
                    sprintf(grenadeAlert, "Molotov [%dm]", (int) response.Grenade[i].Distance);
                    grnd = ImColor(255, 158, 89);
                }
                DrawStrokeText(response.Grenade[i].Location.x, response.Grenade[i].Location.y + 25,grnd,grenadeAlert);
                if (x > -50 && x < screenWidth + 50) {

                    ImGui::GetForegroundDrawList()->AddCircle(ImVec2(response.Grenade[i].Location.x, response.Grenade[i].Location.y), 8, grnd);
                }
            }
            DrawStrokeText(screenWidth / 2, screenHeight / 6.6,ImColor(255, 0, 0),grenadecn);
        }


        drawEnemycount(playerCount,botCount);


        }else{
        //enemy counter
       // ImGui::GetForegroundDrawList()->AddText(font, 40, ImVec2(screenWidth / 2, screenHeight / 11), Golden, "NULL");
        isDataReciving = false;
    }


}
#endif //COOLESP_HACKS_H
