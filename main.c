#include<windows.h>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#define n 10
/*double** randm(int rows, int cols){
                double** matrix = (double**)malloc(rows * sizeof(double*));
                for (int i = 0; i < rows; i++)
                    matrix[i] = (double*)malloc(cols * sizeof(double));
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        if (j >= i) {
                            matrix[i][j] =  2.0 * rand()/RAND_MAX;
                        } else matrix[i][j] = matrix[j][i];
                    }
                }
                return matrix;
            }
double** mulmr(double coef, double **matrix, int rows, int cols){
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        matrix[i][j] = matrix[i][j] * coef;
                        if(matrix[i][j] > 1.0) {
                            matrix[i][j] = 1;
                        } else matrix[i][j] = 0;
                        }
                }
                return matrix;
            }

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[]="Lab 3";
matrix[n][n]={
{0, 1, 0, 0, 0, 0, 1, 1, 0, 0},
{1, 0, 0, 0, 0, 0, 1, 0, 1, 0},
{0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 0, 1, 0, 1, 0},
{0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
{0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 0, 1, 1, 0, 0, 0, 1, 0},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 0, 1, 0, 0, 1, 0, 1, 1},
{0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;
    WNDCLASS w;
    w.lpszClassName = ProgName;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = NULL_BRUSH;
    w.style = CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if(!RegisterClass(&w))
    {
        return 0;
    }

    hWnd = CreateWindow(ProgName,
                      L"vasyleva",
                      WS_OVERLAPPEDWINDOW,
                      150, 150,
                      800, 800,
                      (HWND)NULL, (HMENU)NULL,
                      (HINSTANCE)hInstance, (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while(GetMessage(&lpMsg, hWnd, 0, 0))
    {
    TranslateMessage(&lpMsg);
    DispatchMessage(&lpMsg);
    }

    return(lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch(messg)
    {
        case WM_PAINT :
        hdc=BeginPaint(hWnd, &ps);

        char *nn[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
        int nx[n] = {};
        int ny[n] = {};
        int num = 150;
        for(int i = 0; i < n; i++)
        {
            if(i == 0)
            {
                nx[i] = num;
                ny[i] = num;
            } else if(i <= 2)
            {
                nx[i] = nx[i - 1] + num;
                ny[i] = ny[i - 1];
            } else if(i <= 5)
            {
                nx[i] = nx[i - 1];
                ny[i] = ny[i - 1] + num;
            } else if(i <= 7)
            {
                nx[i] = nx[i - 1] - num;
                ny[i] = ny[i - 1];
            } else
            {
            nx[i] = nx[i - 1];
            ny[i] = ny[i - 1] - num;
            }
        }
        int dx = 16, dy = 16, dtx = 7;
        int i;

        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

        srand(0402);
        double** T = randm(n, n);
        double coef = 1.0 - 0*0.02 - 2*0.005 - 0.25;
        double** A = mulmr(coef, T, n, n);

        printf("Matrix (non directed):\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%g ", A[i][j]);
            }
            printf("\n");
        }

        SelectObject(hdc, KPen);

        int nx1, ny1;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if((A[i][j] == 1) && (j >= i)) {
                    if(i == j) {
                        Arc(hdc, nx[j], ny[j], nx[j]-30, ny[j]-30, nx[j], ny[j], nx[j], ny[j]);
                        continue;
                    }
                    if ((i == j+1)||(i == j-1)) {
                        MoveToEx(hdc, nx[i], ny[i], NULL);
                        LineTo(hdc, nx[j], ny[j]);
                        continue;
                    }
                    if((i < 2) && (j < 2)) {
                         nx1 = (nx[i] + nx[j])/2 + 70;
                         ny1 = (ny[i] + ny[j])/2 - 70;
                         MoveToEx (hdc, nx[j], ny[j], NULL);
                         LineTo (hdc, nx1, ny1);
                         MoveToEx (hdc, nx1, ny1, NULL);
                         LineTo (hdc, nx[i], ny[i]);
                         continue;
                    }
                    if ((i >= 2) &&(i <= 5) && (j >= 2) &&(j <= 5)) {
                         nx1 = (nx[i] + nx[j])/2 + 70;
                         ny1 = (ny[i] + ny[j])/2 - 70;
                         MoveToEx (hdc, nx[j], ny[j], NULL);
                         LineTo (hdc, nx1, ny1);
                         MoveToEx (hdc, nx1, ny1, NULL);
                         LineTo (hdc, nx[i], ny[i]);
                        continue;
                    }
                    if ((i > 5) &&(i < 7)&& (j > 5) &&(j < 7)) {
                        nx1 = (nx[i] + nx[j])/2 - 70;
                        ny1 = (ny[i] + ny[j])/2 + 70;
                        MoveToEx (hdc, nx[j], ny[j], NULL);
                        LineTo (hdc, nx1, ny1);
                        MoveToEx (hdc, nx1, ny1, NULL);
                        LineTo (hdc, nx[i], ny[i]);
                        continue;
                    }
                    if (((i >= 7) || (i == 0)) && ((j >= 7)||(j == 0))) {
                         nx1 = (nx[i] + nx[j])/2 - 70;
                         ny1 = (ny[i] + ny[j])/2 + 70;
                         MoveToEx (hdc, nx[j], ny[j], NULL);
                         LineTo (hdc, nx1, ny1);
                         MoveToEx (hdc, nx1, ny1, NULL);
                         LineTo (hdc, nx[i], ny[i]);
                        continue;
                    }
                    MoveToEx(hdc, nx[i], ny[i], NULL);
                    LineTo(hdc, nx[j], ny[j]);

                    }

            }
        }

        SelectObject(hdc, BPen);
            for(i=0;i < n;i++){
              Ellipse(hdc, nx[i]-dx,ny[i]-dy,nx[i]+dx,ny[i]+dy);
              TextOut(hdc, nx[i]-dtx,ny[i]-dy/2,  nn[i], 2);
            }

        EndPaint(hWnd, &ps);
        break;

        case WM_DESTROY:
        PostQuitMessage(0);
        break;

        default:
        return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}

*/


//directed
double** randm(int rows, int cols){
                double** matrix = (double**)malloc(rows * sizeof(double*));
                for (int i = 0; i < rows; i++)
                    matrix[i] = (double*)malloc(cols * sizeof(double));
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        if (j >= i) {
                            matrix[i][j] =  2.0 * rand()/RAND_MAX;
                        } else matrix[i][j] = matrix[j][i];
                    }
                }
                return matrix;
            }
double** mulmr(double coef, double **matrix, int rows, int cols){
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        matrix[i][j] = matrix[i][j] * coef;
                        if(matrix[i][j] > 1.0) {
                            matrix[i][j] = 1;
                        } else matrix[i][j] = 0;
                        }
                }
                return matrix;
            }

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[]="Lab 3";
matrix[n][n]={
{0, 1, 0, 0, 0, 0, 1, 1, 0, 0},
{1, 0, 0, 0, 0, 0, 1, 0, 1, 0},
{0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 0, 1, 0, 1, 0},
{0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
{0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 0, 1, 1, 0, 0, 0, 1, 0},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 0, 1, 0, 0, 1, 0, 1, 1},
{0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;
    WNDCLASS w;
    w.lpszClassName = ProgName;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = NULL_BRUSH;
    w.style = CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if(!RegisterClass(&w))
    {
        return 0;
    }

    hWnd = CreateWindow(ProgName,
                      L"Vasyleva",
                      WS_OVERLAPPEDWINDOW,
                      150, 150,
                      800, 800,
                      (HWND)NULL, (HMENU)NULL,
                      (HINSTANCE)hInstance, (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while(GetMessage(&lpMsg, hWnd, 0, 0))
    {
    TranslateMessage(&lpMsg);
    DispatchMessage(&lpMsg);
    }

    return(lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    void arrow(float fi, int px,int py)//add
    {
        //fi = 3.1416*(180.0 - fi)/180.0;
        int lx,ly,rx,ry;
        lx = px+15*cos(fi+0.3);
        rx = px+15*cos(fi-0.3);
        ly = py+15*sin(fi+0.3);
        ry = py+15*sin(fi-0.3);
        MoveToEx(hdc, lx, ly, NULL);
        LineTo(hdc, px, py);
        LineTo(hdc, rx, ry);
    }

    switch(messg)
    {
        case WM_PAINT :
        hdc=BeginPaint(hWnd, &ps);

        char *nn[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
        int nx[n] = {};
        int ny[n] = {};
        int num = 150;
        for(int i = 0; i < n; i++)
        {
            if(i == 0)
            {
                nx[i] = num;
                ny[i] = num;
            } else if(i <= 2)
            {
                nx[i] = nx[i - 1] + num;
                ny[i] = ny[i - 1];
            } else if(i <= 5)
            {
                nx[i] = nx[i - 1];
                ny[i] = ny[i - 1] + num;
            } else if(i <= 7)
            {
                nx[i] = nx[i - 1] - num;
                ny[i] = ny[i - 1];
            } else
            {
            nx[i] = nx[i - 1];
            ny[i] = ny[i - 1] - num;
            }
        }
        int dx = 16, dy = 16, dtx = 7;
        int i;

        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

        srand(0402);
        double** T = randm(n, n);
        double coef = 1.0 - 0*0.02 - 2*0.005 - 0.25;
        double** A = mulmr(coef, T, n, n);

        printf("Matrix (directed):\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%g ", A[i][j]);
            }
            printf("\n");
        }

        SelectObject(hdc, KPen);

        int nx1, ny1;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if((A[i][j] == 1) && (j >= i)) {
                    if(i == j) {
                        Arc(hdc, nx[j], ny[j], nx[j]-30, ny[j]-30, nx[j], ny[j], nx[j], ny[j]);
                        arrow((-115*3.1416)/180, nx[j], ny[j]-dy);//add
                        continue;
                    }
                    if ((i == j+1)||(i == j-1)) {
                        MoveToEx(hdc, nx[i], ny[i], NULL);
                        LineTo(hdc, nx[j], ny[j]);
                        arrow((-180*3.1416)/180, nx[1]-16*cos(-95), ny[1]+16*sin(-85)-3);

                        Arc(hdc, nx[0], ny[0]-47, nx[1], ny[1]+47, nx[1], ny[1], nx[0], ny[0]);
                        arrow((-30*3.1416)/180, nx[0], ny[0]-dy);
                        arrow((-270*3.1416)/180, nx[9], ny[9]+dy);//9-10

                        Arc(hdc, nx[9]-40, ny[9], nx[8]+40, ny[8], nx[8], ny[8], nx[9], ny[9]);
                        arrow((-30*3.1416)/180, nx[8]-16*cos(-34), ny[8]+16*sin(-28)-3);//10-9

                        Arc(hdc, nx[4]-40, ny[4], nx[3]+40, ny[3], nx[3], ny[3], nx[4], ny[4]);
                        arrow((-220*3.1416)/180, nx[3]+16*cos(-34), ny[3]-16*sin(-8)-3);//4-5
                        arrow((-90*3.1416)/180, nx[4], ny[4]-dy);//5

                        Arc(hdc, nx[5]-40, ny[5], nx[2]+40, ny[2], nx[2], ny[2], nx[5], ny[5]);
                        arrow((-230*3.1416)/180, nx[2]+16*cos(-35), ny[2]-16*sin(-8)-3);//6-3


                        Arc(hdc, nx[0]-180, ny[0], nx[6]+180, ny[6], nx[6], ny[6], nx[0], ny[0]);
                        arrow((-30*3.1416)/180, nx[6]-16*cos(-35), ny[6]+16*sin(-8.8)-3);
                        arrow((-290*3.1416)/180, nx[0]-16*cos(-33.3), ny[0]+16*sin(-10)+4);//7-1 perfect

                        Arc(hdc, nx[3]+120, ny[3], nx[6]-120, ny[6], nx[6], ny[6], nx[3], ny[3]);


                        Arc(hdc, nx[1]+130, ny[1], nx[8]-130, ny[8], nx[8], ny[8], nx[1], ny[1]);
                        arrow((-320*3.1416)/180, nx[1]+16*cos(-93), ny[1]-16*sin(-8)-3);//2-9
                        arrow((-350*3.1416)/180, nx[8]-16*cos(-34), ny[8]+16*sin(-28)-3);
                        arrow((-40*3.1416)/180, nx[8]-16*cos(-83.6), ny[8]+16*sin(-8)+1);//2-9 perf


                        Arc(hdc, nx[3], ny[3]-130, nx[8], ny[8]+130, nx[8], ny[8], nx[3], ny[3]);


                        Arc(hdc, nx[8]-150, ny[8], nx[6]+150, ny[6], nx[6], ny[6], nx[8], ny[8]);
                        arrow((-360*3.1416)/180, nx[8]+16*cos(-44), ny[8]-16*sin(-28)-3);//9-7

                        arrow((-40*3.1416)/180, nx[6]-16*cos(-83.6), ny[6]+16*sin(-8)+1);//7-4
                        arrow((-290*3.1416)/180, nx[3]+16*cos(-35.7), ny[3]-16*sin(-8)+1);//7-4
                        continue;
                    }
                    if((i < 2) && (j < 2)) {
                         nx1 = (nx[i] + nx[j])/2 + 70;
                         ny1 = (ny[i] + ny[j])/2 - 70;
                         MoveToEx (hdc, nx[j], ny[j], NULL);
                         LineTo (hdc, nx1, ny1);
                         MoveToEx (hdc, nx1, ny1, NULL);
                         LineTo (hdc, nx[i], ny[i]);
                         arrow((-50*3.1416)/180, nx[j], ny[j]+dy);//add
                         continue;
                    }
                    if ((i >= 2) &&(i <= 5) && (j >= 2) &&(j <= 5)) {
                         nx1 = (nx[i] + nx[j])/2 + 70;
                         ny1 = (ny[i] + ny[j])/2 - 70;
                         MoveToEx (hdc, nx[j], ny[j], NULL);
                         LineTo (hdc, nx1, ny1);
                         MoveToEx (hdc, nx1, ny1, NULL);
                         LineTo (hdc, nx[i], ny[i]);
                         //arrow((-90*3.1416)/180, nx[j], ny[j]+dy);//add
                         arrow((-70*3.1416)/180, nx[j]+dx*cos(-143), ny[j]-dy*sin(-140)-27);//6

                         Arc(hdc, nx[7]-60, ny[7], nx[0]+60, ny[0], nx[0], ny[0], nx[7], ny[7]);

                        arrow((-250*3.1416)/180, nx[0]+16*cos(-34), ny[0]-16*sin(-9)-3);

                        Arc(hdc, nx[4]-40, ny[4], nx[2]+40, ny[2], nx[2], ny[2], nx[4], ny[4]);
                        arrow((-250*3.1416)/180, nx[2]+16*cos(-34), ny[2]-16*sin(-8)-3);//3-5

                        arrow((-50*3.1416)/180, nx[4]+dx*cos(-143), ny[4]-dy*sin(-140)-30);//3-5
                        continue;
                    }
                    if ((i > 5) &&(i < 7)&& (j > 5) &&(j < 7)) {
                        nx1 = (nx[i] + nx[j])/2 - 70;
                        ny1 = (ny[i] + ny[j])/2 + 70;
                        MoveToEx (hdc, nx[j], ny[j], NULL);
                        LineTo (hdc, nx1, ny1);
                        MoveToEx (hdc, nx1, ny1, NULL);
                        LineTo (hdc, nx[i], ny[i]);
                        //arrow((-90*3.1416)/180, nx[j], ny[j]+dy);//add
                        arrow((-110*3.1416)/180, nx[j]+dx*cos(-130), ny[j]-dy*sin(-140)-27);
                        continue;
                    }
                    if (((i >= 7) || (i == 0)) && ((j >= 7)||(j == 0))) {
                         nx1 = (nx[i] + nx[j])/2 - 70;
                         ny1 = (ny[i] + ny[j])/2 + 70;
                         MoveToEx (hdc, nx[j], ny[j], NULL);
                         LineTo (hdc, nx1, ny1);
                         MoveToEx (hdc, nx1, ny1, NULL);
                         LineTo (hdc, nx[i], ny[i]);
                         arrow((-110*3.1416)/180, nx[j]+dx*cos(-130), ny[j]-dy*sin(-140)-27);/*nx[j], ny[j]-dy);*///add
                         Arc(hdc, nx[6]+40, ny[6], nx[1]-40, ny[1], nx[1], ny[1], nx[6], ny[6]);//2-7
                        // arrow((-130*3.1416)/180, nx[6]+dx*cos(-150), ny[6]-dy*sin(-120)-67);//nx[6], ny[6]-dy);
                        arrow((-110*3.1416)/180, nx[6]-16*cos(-95), ny[6]+16*sin(-85)-13);

                        Arc(hdc, nx[1], ny[1]-47, nx[6], ny[6]+47, nx[6], ny[6], nx[1], ny[1]);
                        arrow((-270*3.1416)/180, nx[1], ny[1]+dy);//7-2
                        continue;
                    }

                    MoveToEx(hdc, nx[i], ny[i], NULL);
                    LineTo(hdc, nx[j], ny[j]);

                    }

            }
        }

        SelectObject(hdc, BPen);
            for(i=0;i < n;i++){
              Ellipse(hdc, nx[i]-dx,ny[i]-dy,nx[i]+dx,ny[i]+dy);
              TextOut(hdc, nx[i]-dtx,ny[i]-dy/2,  nn[i], 2);
            }

        EndPaint(hWnd, &ps);
        break;

        case WM_DESTROY:
        PostQuitMessage(0);
        break;

        default:
        return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}









