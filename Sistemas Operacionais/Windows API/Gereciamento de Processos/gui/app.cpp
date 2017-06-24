HINSTANCE hinst;

void drawString(HWND hwnd, const TCHAR greeting[], int x, int y);

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_PAINT:
            drawString(hwnd, _T("Hello, World!2"), 5, 5);
            break;
        case WM_DESTROY:
            PostQuitMessage (0);
            break;
        default:
            return DefWindowProc (hwnd, msg, wParam, lParam);
    }
 
    return 0;
}

BOOL InitApplication(HINSTANCE hinstance) 
{ 
    WNDCLASSEX wcx; 
 
    // Fill in the window class structure with parameters 
    // that describe the main window. 
 
    wcx.cbSize = sizeof(wcx);          // size of structure 
    wcx.style = CS_HREDRAW | CS_VREDRAW;                    // redraw if size changes 
    wcx.lpfnWndProc = MainWndProc;     // points to window procedure 
    wcx.cbClsExtra = 0;                // no extra class memory 
    wcx.cbWndExtra = 0;                // no extra window memory 
    wcx.hInstance = hinstance;         // handle to instance 
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);              // predefined app. icon 
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);                    // predefined arrow 
    wcx.hbrBackground = (HBRUSH) COLOR_WINDOW;                 // white background brush 
    wcx.lpszMenuName =  "MainMenu";    // name of menu resource 
    wcx.lpszClassName = "MainWClass";  // name of window class 
    wcx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
 
    // Register the window class. 
    return RegisterClassEx(&wcx); 
} 

HWND createWindow()
{
    if(!InitApplication(hinst)){
        return FALSE;
    }

    HWND hwnd; 

    hwnd = CreateWindow(
        "MainWClass", //_In_opt_ LPCTSTR   lpClassName,
        "Awesome!", //_In_opt_ LPCTSTR   lpWindowName,
        WS_TILEDWINDOW, //_In_     DWORD     dwStyle,
        0, //_In_     int       x,
        0, //_In_     int       y,
        640, //_In_     int       nWidth,
        480, //_In_     int       nHeight,
        (HWND) NULL, //_In_opt_ HWND      hWndParent,
        (HMENU) NULL, //_In_opt_ HMENU     hMenu,
        (HINSTANCE) NULL, //_In_opt_ HINSTANCE hInstance,
        (LPVOID) NULL //_In_opt_ LPVOID    lpParam
    );

    if (!hwnd) 
        return NULL; 

    ShowWindow(hwnd, SW_SHOW); 
    UpdateWindow(hwnd); 

    return hwnd;
}

void drawString(HWND hwnd, const TCHAR greeting[], int x, int y)
{
    PAINTSTRUCT ps;  
    HDC hdc;

    hdc = BeginPaint(hwnd, &ps);  

        // Here your application is laid out.  
        // For this introduction, we just print out "Hello, World!"  
        // in the top left corner.  
        TextOut(hdc,  
            x, y,  
            greeting, _tcslen(greeting));  
        // End application specific layout section.  

        EndPaint(hwnd, &ps);  
}