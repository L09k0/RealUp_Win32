#pragma once
#define CheckClickMenu_1 1
#define CheckClickButton_1 2

#pragma warning(disable:4996) 

static TCHAR szWindowClass[] = _T("DesktopApp");

static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void mainMenu(HWND hWnd);

void Wighets(HWND hWnd);

size_t DownloadFile(void* ptr, size_t size, size_t nmemb, FILE* stream);
void ClickButton();