
#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "Includes.h"
#include "jni.h"
#include "TTF/OPPOSans-H.h"

bool g_Initialized = false;
using namespace std;
char *buf = NULL;				// 设置缓冲区
char *rtn = NULL;				// 设置缓冲区
int len,sockCheck;
bool espthread = false;

// jstring转换char*
char *jstringToChar(JNIEnv * env, jstring jstr)
{
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0)
	{
		rtn = (char *)malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	env->ReleaseByteArrayElements(barr, ba, 0);
	return rtn;
}
#include <iostream>
#include <android/native_window.h>

int toUnicode(const char* str)
{
    return str[0] + (str[1] ? toUnicode(str + 1) : 0);
}


extern "C" JNIEXPORT void JNICALL Java_com_abenk_in_GLES3JNIView_init(JNIEnv * env, jclass cls)
{
    if (g_Initialized)
        return;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiStyle* style = &ImGui::GetStyle();

    style->WindowRounding = 5.5f;
    style->FrameRounding = 4;
    style->ScrollbarRounding = 1.0f;
    style->FrameBorderSize = 1.0f;
    style->WindowBorderSize = 1.00;

    style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

    ImGuiIO & io = ImGui::GetIO();

    io.IniFilename = NULL;

    ImGui::StyleColorsClassic();
    ImGui_ImplAndroid_Init();
    ImGui_ImplOpenGL3_Init("#version 300 es");


	ImFontConfig font_cfg;
    font_cfg.FontDataOwnedByAtlas = false;
    font = io.Fonts->AddFontFromMemoryTTF((void *) OPPOSans_H, OPPOSans_H_size, 35.0f, &font_cfg, io.Fonts->GetGlyphRangesChineseFull());
    IM_ASSERT(font != NULL);
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    g_Initialized = true;
}

extern "C" JNIEXPORT void JNICALL
Java_com_abenk_in_GLES3JNIView_resize(JNIEnv *env, jclass obj, jint width, jint height)
{
    screenWidth = (int) width;
    screenHeight = (int) height;
	glViewport(0, 0, width, height);
	ImGuiIO &io = ImGui::GetIO();
    io.ConfigWindowsMoveFromTitleBarOnly = true;
    io.IniFilename = NULL;
	ImGui::GetIO().DisplaySize = ImVec2((float)width, (float)height);
}

extern "C" JNIEXPORT void JNICALL
Java_com_abenk_in_GLES3JNIView_step(JNIEnv* env, jclass obj) {


	ImGuiIO& io = ImGui::GetIO();
    static bool show_MainMenu_window = true, espthread = false;

	// Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(screenWidth,  screenHeight);//？设置窗口
    ImGui::NewFrame();
    glViewport(0, 0, (int) io.DisplaySize.x, (int) io.DisplaySize.y);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);              // background color



	if (show_MainMenu_window)
	{
        //Menu();
        InitMenu();
	}


    gnzx();

    if(Socket == 4){
        ESP();
    }

    EndDraw();
    ImGui::Render();
	glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}



extern "C" JNIEXPORT void JNICALL Java_com_abenk_in_GLES3JNIView_MotionEventClick(JNIEnv* env,
                                                                                      jclass obj,jboolean down,jfloat PosX,jfloat PosY){
	ImGuiIO & io = ImGui::GetIO();
	io.MouseDown[0] = down;
	io.MousePos = ImVec2(PosX,PosY);
}

extern "C" JNIEXPORT jstring JNICALL Java_com_abenk_in_GLES3JNIView_getWindowRect(JNIEnv *env,
                                                                                      jclass thiz) {
    //获取绘制窗口
    // TODO: 实现 getWindowSizePos()
    char result[256]="0|0|0|0";
    if(g_window){
       sprintf(result,"%d|%d|%d|%d",(int)g_window->Pos.x,(int)g_window->Pos.y,(int)g_window->Size.x,(int)g_window->Size.y);
    }
    return env->NewStringUTF(result);
}

extern "C" JNIEXPORT void JNICALL Java_com_abenk_in_GLES3JNIView_Mode(JNIEnv* env, jclass obj, jint Game, jint RootMode, jint GameBit){
	ng.Game = (int) Game;
	ng.GameBit = (int) GameBit;
	if (RootMode == 64)
	{
		Root = true;
	} 
	else if (RootMode == 128)
	{
		NoRoot = true;
	}
}

extern "C"
JNIEXPORT void JNICALL
Java_com_abenk_in_MainActivity_getReady(JNIEnv *env, jclass clazz) {
    sockCheck=1;
    if (!Create()) {
        perror("设备接口创建失败\n");
		Socket = 1;
    }
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&sockCheck, sizeof(int));
    if (!Bind()) {
        perror("运行端口被其他程序占用\n");
		Socket = 2;
    }
    if (!Listen()) {
        perror("监听端口被占用\n");
		Socket = 3;
    }
    if (Accept()) {

        SetValue sv{};
        sv.mode=ng.Game;
        sv.type=2;
        send((void*)&sv,sizeof(sv));
		Socket = 4;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_abenk_in_GLES3JNIView_imgui_1Shutdown(JNIEnv *env, jclass clazz) {
    if (!g_Initialized)
        return;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    g_Initialized=false;
}