#define CURL_STATICLIB
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <curl\curl.h>
#include <cstdio>
#include <tchar.h>
#include <iostream>
#include "Header.h"
#include "resource.h"

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        600, 200,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_COMMAND:
        switch (wParam)
        {
        case ClickExit:
            PostQuitMessage(0);
            break;
        case CheckClickButton_1:
            GetWindowTextA(DefaultPath, Link_1, TextBufferSize);
            ClickButton();
            MessageBoxA(hWnd, "Realname update successful!", "Successful", MB_OK);
            break;
        case CheckClickButton_2:
            SetWindowTextA(DefaultPath, "c:/Program Files (x86)/Steam/steamapps/common/Half-Life/ag/realnames.txt");
        default:
            break;
        }
        break;
    case WM_CREATE:
        mainMenu(hWnd);
        Wighets(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

void mainMenu(HWND hWnd)
{
    HMENU MainMemu = CreateMenu();
    AppendMenu(MainMemu, MF_STRING, ClickExit, L"Exit");

    SetMenu(hWnd, MainMemu);
}

void Wighets(HWND hWnd)
{
    CreateWindowA("button", "Update!", WS_VISIBLE | WS_CHILD | ES_CENTER, 10, 100, 110, 30, hWnd, (HMENU)CheckClickButton_1, NULL, NULL);
    CreateWindowA("button", "Standard installation path", WS_VISIBLE | WS_CHILD | ES_CENTER, 140, 100, 190, 30, hWnd, (HMENU)CheckClickButton_2, NULL, NULL);
    CreateWindowA("button", "Exit", WS_VISIBLE | WS_CHILD | ES_CENTER, 370, 100, 110, 30, hWnd, (HMENU)ClickExit, NULL, NULL);
    CreateWindowA("static", "Выберите папку с игрой(hl/ag)", WS_VISIBLE | WS_CHILD, 5, 5, 250, 30, hWnd, NULL, NULL, NULL);
    DefaultPath = CreateWindowA("edit", Link_1, WS_VISIBLE | WS_CHILD, 5, 40, 600, 20, hWnd, NULL, NULL, NULL);
}

size_t DownloadFile(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t write = fwrite(ptr, size, nmemb, stream);
    return write;
}

void ClickButton()
{
    CURL* curl = curl_easy_init();
    CURLcode object1;
    //FILE* file = fopen("c:/Program Files (x86)/Steam/steamapps/common/Half-Life/ag/realnames.txt", "wb");
    FILE* file = fopen(Link_1, "wb");

    curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/execut4ble/realnames/master/realnames.txt");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DownloadFile);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    object1 = curl_easy_perform(curl);
}
