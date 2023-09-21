//
// Created by Sayan on 22-07-2023.
//

#ifndef COOLESP_UTILITY_H
#define COOLESP_UTILITY_H


ImColor GetRandomBackgroundByTeamID(int index, int bright, int alpha)
{
    return ImColor::HSV((index + 3.6) / 360.f, bright / 255.f, 1.0f, alpha / 255.f);
}

uint32_t Colors[] = {0x9241EB, 0x9EFF00, 0x006EF4, 0xCA2876, 0x0A31DE, 0xBAA7FD, 0xCEDB3F, 0x286A45, 0x58F014, 0x45CAE6, 0x773702, 0xB0CEF0, 0x3C5F51, 0x453CD7, 0x364024, 0x439997, 0x4CB612, 0xC6B564, 0x17F250, 0xE41BC0, 0xAF8E27, 0x8E382E, 0x47A101, 0x9DAC33, 0x66F4CF, 0x59A9F0, 0x798D1A, 0x2EBB59, 0xBF66C3, 0x4BD8FB, 0xBBFA54, 0x6B9881, 0x144967, 0xBAA3AE, 0xE80B9D, 0x7BA552, 0x96A456, 0x17D7B4, 0x130C39, 0x3C06A8, 0x62737E, 0xA87E89, 0xB6D3E4, 0x66B77D, 0x66E304, 0x1B80E1, 0x7A06BC, 0xBFFB1B, 0x618506, 0x7E4D34};

ImColor GetRandomColorByIndex(int index) {
    srand(index);

    float a = 255;
    float r = ((Colors[rand() % sizeof(Colors)] & 0xFF0000) >> 16);
    float g = ((Colors[rand() % sizeof(Colors)] & 0x00FF00) >> 8);
    float b = (Colors[rand() % sizeof(Colors)] & 0x0000FF);

    return {r / 255, g / 255, b / 255, a / 255};
}

#endif //COOLESP_UTILITY_H
