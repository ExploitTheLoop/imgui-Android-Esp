#include <cstdio>
#include <cstdlib>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <linux/input.h>
#include <linux/uinput.h>
#include <ctime>
#include <array>
#include "Includes.h"

#define maxF 10
#define UNGRAB 0
#define GRAB 1

void Touch_Init();
void Touch_Down(int x, int y);
void Touch_Move(int x, int y);
void Touch_Up();

struct touchObj {
    bool isDown = false;
    int x = 0;
    int y = 0;
};

struct touchObj Finger[maxF];

static pthread_t touchloop;

static struct input_event event[128];

int origfd, fd;

int tnum = 9;

void Upload() {
    memset(event, 0, sizeof(struct input_event) * 128);
    int32_t tmpCnt = 0;
    for (int i = 0; i <= maxF - 1; i++) {
        if (Finger[i].isDown) {
            event[tmpCnt].type = EV_ABS;
            event[tmpCnt].code = ABS_MT_POSITION_X;
            event[tmpCnt].value = Finger[i].x;
            tmpCnt++;

            event[tmpCnt].type = EV_ABS;
            event[tmpCnt].code = ABS_MT_POSITION_Y;
            event[tmpCnt].value = Finger[i].y;
            tmpCnt++;

            event[tmpCnt].type = EV_SYN;
            event[tmpCnt].code = SYN_MT_REPORT;
            event[tmpCnt].value = 0;
            tmpCnt++;
        }
    }
    if (tmpCnt == 0) {
        event[tmpCnt].type = EV_SYN;
        event[tmpCnt].code = SYN_MT_REPORT;
        event[tmpCnt].value = 0;
        tmpCnt++;
    }

    event[tmpCnt].type = EV_SYN;
    event[tmpCnt].code = SYN_REPORT;
    event[tmpCnt].value = 0;
    tmpCnt++;

    write(fd, event, sizeof(struct input_event) * tmpCnt);
}

void *TypeA(void *) {
    struct input_event ie{};
    int latest = 0;
    struct input_event key{};
    while (read(origfd, &ie, sizeof(struct input_event))) {
        if (ie.code == ABS_MT_SLOT) {
            latest = ie.value;
        }
        if (ie.code == ABS_MT_TRACKING_ID) {
            if (ie.value == -1) {
                Finger[latest].isDown = false;
            } else {
                Finger[latest].isDown = true;
            }
        }
        if (ie.code == ABS_MT_POSITION_X) {
            Finger[latest].x = ie.value;
        }
        if (ie.code == ABS_MT_POSITION_Y) {
            Finger[latest].y = ie.value;
        }
        if (ie.code == SYN_REPORT) {
            Upload();
        }
        if (ie.code == KEY_APPSELECT) {
            key.type = ie.type;
            key.code = ie.code;
            key.value = ie.value;
            write(fd, &key, sizeof(key));
        }
        if (ie.code == KEY_BACK) {
            key.type = ie.type;
            key.code = ie.code;
            key.value = ie.value;
            write(fd, &key, sizeof(key));
        }
    }
    return nullptr;
}

int GetEventCount() {
    DIR *dir = opendir("/dev/input/");
    dirent *ptr = nullptr;
    int count = 0;
    while ((ptr = readdir(dir)) != nullptr) {
        if (strstr(ptr->d_name, "event"))
            count++;
    }
    return count;
}

int GetEventId() {
    int EventCount = GetEventCount();
    int *fdArray = (int *) malloc(EventCount * 4 + 4);

    for (int i = 0; i < EventCount; i++) {
        char temp[128];
        sprintf(temp, "/dev/input/event%d", i);
        fdArray[i] = open(temp, O_RDWR | O_SYNC | O_NONBLOCK);
    }

    input_event ev{};
    while (true) {
        for (int i = 0; i < EventCount; i++) {
            memset(&ev, 0, sizeof(ev));
            read(fdArray[i], &ev, sizeof(ev));
            if (ev.type == EV_ABS) {
                //LOGI("id:%d\n", i);
                free(fdArray);
                return i;
            }
        }
        usleep(100);
    }
}

bool shit = false;

void Touch_Init() {
    char origI[256];
    if (!shit) {
        sprintf(origI, "/dev/input/event%d", GetEventId());
        shit = true;
    }
    origfd = open(origI, O_RDWR);
    struct input_absinfo absX{}, absY{};
    ioctl(origfd, EVIOCGABS(ABS_MT_POSITION_X), &absX);
    ioctl(origfd, EVIOCGABS(ABS_MT_POSITION_Y), &absY);
    struct uinput_user_dev ui_dev{};
    int uinp_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (uinp_fd <= 0) {
        //LOGI("could not open uinput, %s\n", strerror(errno));
        return;
    }

    memset(&ui_dev, 0, sizeof(ui_dev));
    strncpy(ui_dev.name, "MaTouchScreen"/*"VirtualTouch"*/, UINPUT_MAX_NAME_SIZE);
    ui_dev.id.bustype = BUS_USB;
    ui_dev.id.vendor = 0x1341;
    ui_dev.id.product = 0x0001;
    ui_dev.id.version = 5;

    ui_dev.absmin[ABS_MT_POSITION_X] = 0;
    ui_dev.absmax[ABS_MT_POSITION_X] = absX.maximum;
    ui_dev.absmin[ABS_MT_POSITION_Y] = 0;
    ui_dev.absmax[ABS_MT_POSITION_Y] = absY.maximum;
    ioctl(uinp_fd, UI_SET_PROPBIT, INPUT_PROP_DIRECT);

    ioctl(uinp_fd, UI_SET_EVBIT, EV_ABS);
    ioctl(uinp_fd, UI_SET_ABSBIT, ABS_MT_POSITION_X);
    ioctl(uinp_fd, UI_SET_ABSBIT, ABS_MT_POSITION_Y);
    ioctl(uinp_fd, UI_SET_EVBIT, EV_SYN);
    ioctl(uinp_fd, UI_SET_EVBIT, EV_KEY);
    ioctl(uinp_fd, UI_SET_KEYBIT, KEY_BACK);
    ioctl(uinp_fd, UI_SET_KEYBIT, KEY_APPSELECT);

    write(uinp_fd, &ui_dev, sizeof(ui_dev));

    if (ioctl(uinp_fd, UI_DEV_CREATE)) {
        //LOGI("Unable to create UINPUT device.\n");
        return;
    }

    fd = uinp_fd;

    if (ioctl(origfd, EVIOCGRAB, GRAB)) {
        //LOGI("Handle error.\n");
        return;
    }
}

void Touch_Down(int x, int y) {
    Finger[tnum].x = x;
    Finger[tnum].y = y;
    Finger[tnum].isDown = true;
    Upload();
}

void Touch_Move(int x, int y) {
    Finger[tnum].x = x;
    Finger[tnum].y = y;
    Finger[tnum].isDown = true;
    Upload();
}

void Touch_Up() {
    Finger[tnum].isDown = false;
    Upload();
}