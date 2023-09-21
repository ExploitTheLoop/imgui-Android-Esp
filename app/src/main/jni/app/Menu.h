//
// Created by Sayan on 17-07-2023.
//

#ifndef COOLESP_MENU_H
#define COOLESP_MENU_H
/************用户自定义**************/
bool hzcsh,English,Root,NoRoot;
std::string baoESP = "OFA",GameName,Rootstring,BitName,Connection;
ImGuiWindow* g_window = NULL;
int Socket = 0;
Game ng{};

void gnzx()
{
    if (hzcsh)
    {
        if (Root)
        {
            std::thread Threadghhzp(system, "su -c /data/data/com.abenk.in/files/assets//rayan");
            Threadghhzp.detach();
        }
        if (NoRoot)
        {
            std::thread Threadgjhzn(system, "/data/data/com.abenk.in/files/assets/rayan");
            Threadgjhzn.detach();
        }


        std::thread Threadgjhzq(system, "chmod 777 /data/data/com.abenk.in/files/assets/rayan");
        Threadgjhzq.detach();
        hzcsh = false;


    }
}


struct MenuPos {
    float w;
    float h;
    float x;
    float y;
} menuPos;

void InitMenu() {

    switch (ng.Game)
    {
        case 1:
            GameName = "GLOBAL 2.7";
            break;
        case 2:
            GameName = "Korea 2.7";
            break;
        case 3:
            GameName = "Tiawn 2.7";
            break;
        case 4:
            GameName = "VNG 2.7";
            break;
        case 5:
            GameName = "BGMI 2.5";
            break;

    }
    switch (ng.GameBit)
    {
        case 4:
            BitName = "32Bit";
            break;
        case 8:
            BitName = "64Bit";
            break;
    }
    if (Root == true)
    {
        Rootstring = "Root";
    }
    else if (NoRoot == true)
    {
        Rootstring = "NoRoot";
    }
    if(Socket == 4){
        Connection = "Connected";
    }else if( Socket == 1 || Socket == 2 || Socket == 3){
        Connection = "Failed to connect to daemon !";
    }else{
        Connection = "Connecting..";
    }

    static int num = 0;
    ImGuiIO & io = ImGui::GetIO();

    if (ImGui::Begin(baoESP.c_str(),0, ImGuiWindowFlags_NoSavedSettings));

    if(num == 0){
        num=1;
        ImGui::SetWindowSize(ImVec2{650, 600});
        ImGui::SetWindowFontScale(0.67f);
    }

    g_window = ImGui::GetCurrentWindow();
    {

    if (ImGui::CollapsingHeader("PLAYER")) {


        if (ImGui::BeginTable("split", 2)) {
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableNextColumn();
            ImGui::Checkbox("ESP", &isEsp);
            ImGui::TableNextColumn();
            ImGui::Checkbox("skeleton", &isSkelton);
            ImGui::TableNextColumn();
            ImGui::Checkbox("Player Health", &isPlayerHealth);
            ImGui::TableNextColumn();
            ImGui::Checkbox("Vehcile", &isvehcile);
            ImGui::EndTable();
        }
    }
    if (ImGui::CollapsingHeader("ITEMS")) {
        if (ImGui::BeginTable("split", 2)) {
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableNextColumn();
            ImGui::Checkbox("Items", &isItems);
            ImGui::TableNextColumn();
            ImGui::EndTable();
        }
    }
    if (ImGui::CollapsingHeader("AIM")) {


       // ImGui::Checkbox("Bullet Track", &isBulletTrack);

   //     ImGui::Checkbox("Show touch", &showtouch);
     //   ImGui::SliderFloat("Touch Location X", &radarLocation, 0.f, 900.f);
     //   ImGui::SliderFloat("Touch Location Y", &radarLocation2, 0.f, 1650.f);

        if (ImGui::BeginTable("split", 2)) {
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableNextColumn();
            ImGui::Checkbox("Aimbot", &isaimbot);
            ImGui::TableNextColumn();
            ImGui::Checkbox("Bullet Track", &isBulletTrack);
            ImGui::TableNextColumn();
            ImGui::Checkbox("Aim Knocked", &isAimKnocked);
            ImGui::TableNextColumn();
            ImGui::SliderFloat("Fov", &fov, 0.f, 900.f);
            ImGui::TableNextColumn();
            const char *items[] = {"head", "Chest","stomach"};
            ImGui::Combo("", &target, items, IM_ARRAYSIZE(items));
            ImGui::TableNextColumn();
            ImGui::EndTable();

        }
    }
    if (ImGui::CollapsingHeader("Other Settings")) {
        const float MIN_SCALE = 0.3f;
        const float MAX_SCALE = 2.0f;

        ImGui::SliderInt("Esp Font Size", &fontsize, 1.0f, 30.0f);
        ImGui::SliderInt("Name Text Position", &textpos, 1.0f, 100.0f);
        ImGui::SliderInt("Team Id Text Position", &teamidpos, 1.0f, 100.0f);
        ImGui::ShowStyleSelector("Theme##Selector");
        if (ImGui::DragFloat("size", &window_scale, 0.005f, MIN_SCALE, MAX_SCALE, "%.2f",
                             ImGuiSliderFlags_AlwaysClamp)) // Scale only this window
            ImGui::SetWindowFontScale(window_scale);
        ImGuiStyle &style = ImGui::GetStyle();
        ImGui::DragFloat("Alpha", &style.Alpha, 0.005f, 0.20f, 1.0f, "%.2f");
        ImGui::PushID(1);
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4) ImColor::HSV(2.f / 7.0f, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                              (ImVec4) ImColor::HSV(2.f / 7.0f, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4) ImColor::HSV(2.f / 7.0f, 0.8f, 0.8f));
        if (ImGui::Button("SAVE")) {SaveIni();};
        if (ImGui::Button("LOAD")) {GetIni();};
        ImGui::PopStyleColor(4);
        ImGui::PopID();
    }

    if(Socket == 4){
        //green
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0,255,0,255));
    }else if(Socket >= 1 || Socket <= 3 ){
        //red
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0,255));
    }

        ImGui::Text("Daemon : %s", Connection.c_str());
        ImGui::PopStyleColor();

        if(isDataReciving){
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0,255,0,255));
            ImGui::Text("Daemon Data : Receiving Response.. ");
            ImGui::PopStyleColor();
        }else{
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0,255));
            ImGui::Text("Daemon Data : No Response.. ");
            ImGui::PopStyleColor();
        }

        ImGui::Text("Game : %s", GameName.c_str());
        ImGui::Text("Arch : %s", BitName.c_str());
        ImGui::Text("Env : %s", Rootstring.c_str());
        ImGui::Text("Frames : %.3f ms / (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
    menuPos.w = ImGui::GetWindowWidth();
    menuPos.h = ImGui::GetWindowHeight();
    menuPos.x = ImGui::GetWindowPos().x;
    menuPos.y = ImGui::GetWindowPos().y;
    }
}

void EndDraw()
{
    ImGui::End();

}
#endif //COOLESP_MENU_H
