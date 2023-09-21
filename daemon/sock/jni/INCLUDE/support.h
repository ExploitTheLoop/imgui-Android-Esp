#ifndef SHOOLIN_SUPPORT_H
#define SHOOLIN_SUPPORT_H

#include "socket.h"
#include "Vector3.hpp"
#include "struct.h"
#include <thread>

#define PI 3.141592653589793238

ssize_t process_v(pid_t __pid,   struct iovec* __local_iov, unsigned long __local_iov_count, struct iovec* __remote_iov, unsigned long __remote_iov_count, unsigned long __flags) {
	return syscall(process_vm_readv_syscall, __pid, __local_iov, __local_iov_count, __remote_iov, __remote_iov_count, __flags);
}
//----------Credit -> @pakgamerz
ssize_t process_v2(pid_t __pid,   struct iovec* __local_iov, unsigned long __local_iov_count, struct iovec* __remote_iov, unsigned long __remote_iov_count, unsigned long __flags) {
	return syscall(process_vm_writev_syscall, __pid, __local_iov, __local_iov_count, __remote_iov, __remote_iov_count, __flags);
}
//----------Credit -> @pakgamerz
int pvm(uintptr_t address, void* buffer,int size) {
	struct iovec local[1];
	struct iovec remote[1];

	local[0].iov_base = (void*)buffer;
	local[0].iov_len = size;
	remote[0].iov_base = (void*)address;
	remote[0].iov_len = size;
	ssize_t bytes = process_v(pid, local, 1, remote, 1, 0);
	return bytes == size;
}
//----------Credit -> @pakgamerz
void pvm2(uintptr_t address, void* buffer,int size) {
	struct iovec local[1];
	struct iovec remote[1];

	local[0].iov_base = (void*)buffer;
	local[0].iov_len = size;
	remote[0].iov_base = (void*)address;
	remote[0].iov_len = size;

	process_v2(pid, local, 1, remote, 1, 0);
}


int vm_writev(uintptr_t address, void* buffer,int size) {
    return pvm(address, buffer, size);
}

//----------Credit -> @pakgamerz
struct D3DMatrix ToMatrixWithScale(struct Vec3 translation,struct Vec3 scale,struct Vec4 rot)
{
	struct D3DMatrix m;

	m._41 = translation.X;
	m._42 = translation.Y;
	m._43 = translation.Z;

	float x2 = rot.X + rot.X;
	float y2 = rot.Y + rot.Y;
	float z2 = rot.Z + rot.Z;

	float xx2 = rot.X * x2;
	float yy2 = rot.Y * y2;
	float zz2 = rot.Z * z2;

	m._11 = (1.0f - (yy2 + zz2)) * scale.X;
	m._22 = (1.0f - (xx2 + zz2)) * scale.Y;
	m._33 = (1.0f - (xx2 + yy2)) * scale.Z;

	float wx2 = rot.W * x2;
	float yz2 = rot.Y * z2;

	m._23 = (yz2 + wx2) * scale.Y;
	m._32 = (yz2 - wx2) * scale.Z;

	float xy2 = rot.X * y2;
	float wz2 = rot.W * z2;

	m._12 = (xy2 + wz2) * scale.X;
	m._21 = (xy2 - wz2) * scale.Y;

	float xz2 = rot.X * z2;
	float wy2 = rot.W * y2;

	m._13 = (xz2 - wy2) * scale.X;
	m._31 = (xz2 + wy2) * scale.Z;

	m._14 = 0.0f;
	m._24 = 0.0f;
	m._34 = 0.0f;
	m._44 = 1.0f;

	return m;
}
//----------Credit -> @pakgamerz
struct Vec3 mat2Cord(struct D3DMatrix pM1,struct D3DMatrix pM2)
{
	struct  Vec3 pOut;

	pOut.X = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut.Y = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut.Z = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;

	return pOut;
}

float get2dDistance(float x, float y, float x1, float y1)
{
	float xx1 = x - x1;
	float yy2 = y - y1;
	// 取平方根
	return sqrt(xx1 * xx1 + yy2 * yy2);
}

//----------Credit -> @pakgamerz
uintptr_t getBase()
{
    FILE *fp;
    uintptr_t addr = 0;
    char filename[40], buffer[1024];
    snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    fp = fopen(filename, "rt");
    if (fp != NULL)
    {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strstr(buffer, "libUE4.so")) {
                addr = (uintptr_t)strtoul(buffer, NULL, 16);
                break;
            }
        }
        fclose(fp);
    }
    return addr;
}
//----------Credit -> @pakgamerz
pid_t getPid(char * name)
{
	char text[69];
	pid_t pid = 0;
	sprintf(text,"pidof %s",name);
	FILE *chkRun = popen(text, "r");
	if (chkRun)
	{
		char output[10];
		fgets(output ,10,chkRun);
		pclose(chkRun);
		pid= atoi(output);
	}
	if (pid < 10)
	{
		DIR* dir = NULL;
		struct dirent* ptr = NULL;
		FILE* fp = NULL;
		char filepath[256];
		char filetext[128];
		dir = opendir("/proc");
		if (NULL != dir)
		{
			while ((ptr = readdir(dir)) != NULL)
			{
				if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
					continue;
				if (ptr->d_type != DT_DIR)
					continue;
				sprintf(filepath, "/proc/%s/cmdline", ptr->d_name);
				fp = fopen(filepath, "r");
				if (NULL != fp)
				{
					fgets(filetext, sizeof(filetext), fp);
					if (strcmp(filetext, name) == 0)
					{
						fclose(fp);
						break;
					}
					fclose(fp);
				}
			}
		}
		if (readdir(dir) == NULL)
		{
			closedir(dir);
			return 0;
		}
		closedir(dir);
		pid= atoi(ptr->d_name);
	}
	return pid;
}
//----------Credit -> @pakgamerz
int isValidPlayer(int oType) {
	if (oType == 0x3ec2a00 || oType == 0x3ec2800)
		return 1;
    return 0;
}
//get address (uintptr_t)
uintptr_t getA(uintptr_t address)
{
	uintptr_t buff;
    pvm(address, &buff, SIZE);
    return buff;
}

template<typename T>
T Read(uintptr_t address) {
    T data;
    pvm(address, &data, sizeof(T));
    return data;
}


//----------Credit -> @pakgamerz
int isValid(uintptr_t addr)
{
    if (addr < 0x10000000 || addr>0xefffffff || addr % SIZE != 0)
        return 0;
    return 1;
}
//----------Credit -> @pakgamerz
float getDistance(struct Vec3 mxyz,struct Vec3 exyz)
{
	return sqrt ((mxyz.X-exyz.X)*(mxyz.X-exyz.X)+(mxyz.Y-exyz.Y)*(mxyz.Y-exyz.Y)+(mxyz.Z-exyz.Z)*(mxyz.Z-exyz.Z))/100;
}
//----------Credit -> @pakgamerz
struct Vec3 World2Screen(struct D3DMatrix viewMatrix, struct Vec3 pos)
{
	struct Vec3 screen;
	float screenW = (viewMatrix._14 * pos.X) + (viewMatrix._24 * pos.Y) + (viewMatrix._34 * pos.Z) + viewMatrix._44;

	if (screenW < 0.01f)
		screen.Z = 1;
	else
		screen.Z = 0;

	float screenX = (viewMatrix._11 * pos.X) + (viewMatrix._21 * pos.Y) + (viewMatrix._31 * pos.Z) + viewMatrix._41;
	float screenY = (viewMatrix._12 * pos.X) + (viewMatrix._22 * pos.Y) + (viewMatrix._32 * pos.Z) + viewMatrix._42;
	
	screen.Y = (height / 2) - (height / 2) * screenY / screenW;
	screen.X = (width / 2) + (width / 2) * screenX / screenW;

	return screen;
}
//----------Credit -> @pakgamerz
struct Vec2 World2ScreenMain(struct D3DMatrix viewMatrix, struct Vec3 pos)
{
	struct Vec2 screen;
	float screenW = (viewMatrix._14 * pos.X) + (viewMatrix._24 * pos.Y) + (viewMatrix._34 * pos.Z) + viewMatrix._44;
	float screenX = (viewMatrix._11 * pos.X) + (viewMatrix._21 * pos.Y) + (viewMatrix._31 * pos.Z) + viewMatrix._41;
	float screenY = (viewMatrix._12 * pos.X) + (viewMatrix._22 * pos.Y) + (viewMatrix._32 * pos.Z) + viewMatrix._42;
	
	screen.Y = (height / 2) - (height / 2) * screenY / screenW;
	screen.X = (width / 2) + (width / 2) * screenX / screenW;

	return screen;
}
//----------Credit -> @pakgamerz
struct D3DMatrix getOMatrix(uintptr_t boneAddr)
{
    float oMat[11];
    pvm(boneAddr,&oMat,sizeof(oMat));
	
    rot.X=oMat[0];
	rot.Y=oMat[1];
	rot.Z=oMat[2];
	rot.W=oMat[3];
			
	tran.X=oMat[4];
	tran.Y=oMat[5];
	tran.Z=oMat[6];
			
	scale.X=oMat[8];
	scale.Y=oMat[9];
	scale.Z=oMat[10];
			
	return ToMatrixWithScale(tran,scale,rot);
}
//----------Credit -> @pakgamerz
struct Vec2 getPointingAngle(struct Vec3 camera, struct Vec3 xyz, float distance)
{
	struct Vec2 PointingAngle;
	float ytime = distance / 88000;

	xyz.Z = xyz.Z + 360 * ytime * ytime;

	float zbcx = xyz.X - camera.X;
	float zbcy = xyz.Y - camera.Y;
	float zbcz = xyz.Z - camera.Z;
	PointingAngle.Y = atan2(zbcy, zbcx) * 180 / PI;	// 57.3
	PointingAngle.X = atan2(zbcz, sqrt(zbcx * zbcx + zbcy * zbcy)) * 180 / PI;

	return PointingAngle;
}

//----------Credit -> @pakgamerz
char* getText(uintptr_t addr)
{
	static char txt[42];
	memset(txt, 0, 42);
	char buff[41];
	pvm(addr + 4+SIZE, &buff, 41);
	int i;
	for (i = 0; i < 41; i++) {
		if (buff[i] == 0)
			break;
		txt[i] = buff[i];
		if (buff[i] == 67 && i > 10)
			break;
	}
	txt[i + 1] = '\0';
	return txt;
}
//----------Credit -> @pakgamerz
char *getNameByte(uintptr_t address)
{
	char static lj[64];
	memset(lj, 0, 64);
	unsigned short int nameI[32];
	pvm(address, nameI, sizeof(nameI));
	char s[10];
	int i;
	for (i = 0; i < 32; i++)
	{
		if (nameI[i] == 0)
			break;
		sprintf(s, "%d:", nameI[i]);
		strcat(lj, s);
	}
	lj[63] = '\0';

	return lj;
}
//----------Credit -> @pakgamerz
enum type {
	TYPE_DWORD,
	TYPE_FLOAT
};
//----------Credit -> @pakgamerz
void WriteDword(uintptr_t address, int value) {
	pvm2(address, &value, 4);
}
//----------Credit -> @pakgamerz
void WriteFloat(uintptr_t address, float value) {
	pvm2(address, &value, 4);
}
//----------Credit -> @pakgamerz
void Write(uintptr_t address, const char *value, type TYPE) {
	switch(TYPE) {
		case TYPE_DWORD:
			WriteDword(address, atoi(value));
			break;
		case TYPE_FLOAT:
			WriteFloat(address, atoi(value));
			break;
	}
}
//----------Credit -> @pakgamerz
#endif
