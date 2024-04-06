
#include <windows.h>

LRESULT CALLBACK WindowProc1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK WindowProc2(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // Process messages for the second window
    switch (uMsg) {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        // Optionally, post quit message when the second window is closed
        // PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI
WinMain(
  HINSTANCE hInstance,     // Handle to the current instance
  HINSTANCE hPrevInstance, // Always zero. Deprecated in 32-bit and 64-bit Windows applications
  LPSTR lpCmdLine,         // Pointer to a null-terminated string specifying the command line for the application, excluding the program name
  int nCmdShow             // Specifies how the window is to be shown
  ) {
    WNDCLASS wc1 = {0};
    wc1.lpfnWndProc = WindowProc1;
    wc1.hInstance = hInstance;
    wc1.lpszClassName = "MyAppWindowClass1";

    RegisterClass(&wc1);

    WNDCLASS wc2 = {0};
    wc2.lpfnWndProc = WindowProc2;
    wc2.hInstance = hInstance;
    wc2.lpszClassName = "MyAppWindowClass2";

    RegisterClass(&wc2);

    HWND hwnd1 = CreateWindow("MyAppWindowClass1", "Main Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, wc1.hInstance, NULL);
    ShowWindow(hwnd1, nCmdShow);
    UpdateWindow(hwnd1);

    HWND hwnd2 = CreateWindow("MyAppWindowClass2", "Second Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 200, 200, NULL, NULL, wc2.hInstance, NULL);
    ShowWindow(hwnd2, nCmdShow);
    UpdateWindow(hwnd2);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

