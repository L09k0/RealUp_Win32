#pragma once
#define ClickExit 1
#define CheckClickButton_1 2
#define CheckClickButton_2 3
#define TextBufferSize 100


#pragma warning(disable:4996) 

HWND DefaultPath;

char Link_1[TextBufferSize];

static TCHAR szWindowClass[] = _T("DesktopApp");

static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void mainMenu(HWND hWnd);

void Wighets(HWND hWnd);

size_t DownloadFile(void* ptr, size_t size, size_t nmemb, FILE* stream);
void ClickButton();


