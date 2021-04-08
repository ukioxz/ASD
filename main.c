#include <windows.h>
#include <stdio.h>
#include <math.h>

#define width 1000
#define n 10

//������ �������� ������� ����, ������� ����� ���������� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


void paint(int dx, int dy, int dtx, int nx[], int ny[], int hdc, int BPen, int nn[]) {

    for (int a = 0; a < 3; a++) {
        nx[a + 1] = nx[a] + 100;
        ny[a + 1] = ny[a];
        SelectObject(hdc, BPen);
        Ellipse(hdc, nx[a] - dx, ny[a] - dy, nx[a] + dx, ny[a] + dy);
        TextOut(hdc, nx[a] - dtx, ny[a] - dy / 2, nn[a], 1);
    }

    for (int a = 3; a < 5; a++) {
        nx[a + 1] = nx[a];
        ny[a + 1] = ny[a] + 100;
        SelectObject(hdc, BPen);
        Ellipse(hdc, nx[a] - dx, ny[a] - dy, nx[a] + dx, ny[a] + dy);
        TextOut(hdc, nx[a] - dtx, ny[a] - dy / 2, nn[a], 1);
    }

    for (int a = 5; a < 8; a++) {
        nx[a + 1] = nx[a] - 100;
        ny[a + 1] = ny[a];
        SelectObject(hdc, BPen);
        Ellipse(hdc, nx[a] - dx, ny[a] - dy, nx[a] + dx, ny[a] + dy);
        TextOut(hdc, nx[a] - dtx, ny[a] - dy / 2, nn[a], 1);
    }

    for (int a = 8; a < 10; a++) {
        nx[a + 1] = nx[a];
        ny[a + 1] = ny[a] - 100;
        SelectObject(hdc, BPen);
        Ellipse(hdc, nx[a] - dx, ny[a] - dy, nx[a] + dx, ny[a] + dy);
        TextOut(hdc, nx[a] - dtx, ny[a] - dy / 2, nn[a], 1);
    }

}

void arrow(int px, int py, int dx, int dy, HDC hdc) {
    int lx, ly = py, rx = px, ry;
    if (dx == 0) return;
    else lx = px + (dx / abs(dx)) * 10;
    if (dy == 0) {
        ly = py - 10;
        ry = py + 10;
        lx = px + (10 * dx / abs(dx));
        rx = lx;
    }
    else ry = py + (dy / abs(dy)) * 10;
    MoveToEx(hdc, lx, ly, NULL);
    LineTo(hdc, px, py);
    LineTo(hdc, rx, ry);
}

void paintLine1(int matrix[n][n], HDC hdc, int dx, int dy, int nx [], int ny []) {
    int  radius = 16, divine = 1, xDif, yDif;
    float koef = 1.0 - 0 * 0.02 - 2 * 0.005 - 0.25;
    for (int start = 0; start < n; start++) {
        for (int end = 0; end < n; end++) {
            if (matrix[start][end] == 1) {
                xDif = nx[start] - nx[end];
                yDif = ny[start] - ny[end];
                koef = sqrt(xDif * xDif + yDif * yDif) / radius;
                dx = xDif / koef;
                dy = yDif / koef;
                if (start == end) {
                    MoveToEx(hdc, nx[end], ny[end], NULL);
                    LineTo(hdc, nx[end] + 40, ny[end] + 10);
                    LineTo(hdc, nx[end] + 40, ny[end] + 40);
                    LineTo(hdc, nx[end] + 10, ny[end] + 40);
                    LineTo(hdc, nx[end], ny[end]);
                    arrow(nx[end] + 2, ny[end] + 13, 2, 13, hdc);
                }
                else if (matrix[start][end] == 1 && matrix[end][start] == 1) {
                    MoveToEx(hdc, nx[start], ny[start], NULL);
                    LineTo(hdc, nx[end] + xDif / 2 + (20 * divine), ny[end] + yDif / 2 + (20 * divine));
                    LineTo(hdc, nx[end], ny[end]);
                    arrow(nx[end] + dx, ny[end] + dy, dx, dy, hdc);
                    divine = -divine;
                }
                else {
                    MoveToEx(hdc, nx[start], ny[start], NULL);
                    if (yDif == 0 && abs(xDif) > 300 && end <= 3) {
                        LineTo(hdc, nx[end] + xDif / 2, ny[end] - 35);
                        dx = xDif / 2 / koef;
                        dy = (yDif - 35) / koef;
                    }
                    else if (abs(xDif) == 300 && abs(yDif) == 300 && (end == 0 || end == 3)) {
                        LineTo(hdc, nx[end] + xDif / 2, ny[end] + yDif / 1);
                        dx = xDif / 2 / koef;
                        dy = yDif / koef;
                    }
                    LineTo(hdc, nx[end], ny[end]);
                    arrow(nx[end] + dx, ny[end] + dy, dx, dy, hdc);
                }
            }
        }
    }
}

void paintLine2(int matrix[n][n], HDC hdc, int dx, int dy, int nx[], int ny[]) {
    int  radius = 16, divine = 1, xDif, yDif;
    float koef = 1.0 - 0 * 0.02 - 2 * 0.005 - 0.25;
    for (int start = 0; start < n; start++) {
        for (int end = 0; end < n; end++) {
            if (matrix[start][end] == 1) {
                xDif = nx[start] - nx[end];
                yDif = ny[start] - ny[end];
                koef = sqrt(xDif * xDif + yDif * yDif) / radius;
                dx = xDif / koef;
                dy = yDif / koef;
                if (start == end) {
                    MoveToEx(hdc, nx[end], ny[end], NULL);
                    LineTo(hdc, nx[end] + 40, ny[end] + 10);
                    LineTo(hdc, nx[end] + 40, ny[end] + 40);
                    LineTo(hdc, nx[end] + 10, ny[end] + 40);
                    LineTo(hdc, nx[end], ny[end]);
                    //arrow(nx[end] + 2, ny[end] + 13, 2, 13, hdc);
                }
                else if (matrix[start][end] == 1 && matrix[end][start] == 1) {
                    MoveToEx(hdc, nx[start], ny[start], NULL);
                    LineTo(hdc, nx[end] + xDif / 2 + (20 * divine), ny[end] + yDif / 2 + (20 * divine));
                    LineTo(hdc, nx[end], ny[end]);

                    divine = -divine;
                }
                else {
                    MoveToEx(hdc, nx[start], ny[start], NULL);
                    if (yDif == 0 && abs(xDif) > 300 && end <= 3) {
                        LineTo(hdc, nx[end] + xDif / 2, ny[end] - 35);
                        dx = xDif / 2 / koef;
                        dy = (yDif - 35) / koef;
                    }
                    else if (abs(xDif) == 300 && abs(yDif) == 300 && (end == 0 || end == 3)) {
                        LineTo(hdc, nx[end] + xDif / 2, ny[end] + yDif / 1);
                        dx = xDif / 2 / koef;
                        dy = yDif / koef;
                    }
                    LineTo(hdc, nx[end], ny[end]);

                }
            }
        }
    }
}
//��������� ������-��� ���������
char ProgName[] = "LabGraf";


int matrix[n][n] = {
        {0, 1, 0, 0, 0, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 1, 1, 1, 1, 0, 0},
        {1, 0, 0, 1, 0, 1, 0, 1, 0, 0},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 1, 0, 0, 1},
        {0, 1, 0, 1, 1, 0, 0, 1, 0, 1},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 0},
        {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 0, 0, 0, 1},
};

int matrixA[n][n] = {
        {0, 1, 1, 0, 1, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 1, 1, 1, 1, 0, 0},
        {1, 0, 0, 1, 0, 1, 0, 1, 1, 0},
        {0, 1, 1, 0, 1, 0, 1, 1, 1, 1},
        {1, 1, 0, 1, 0, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 0, 1, 0, 0, 0, 1, 0, 1},
        {0, 1, 1, 1, 1, 0, 1, 0, 1, 0},
        {0, 0, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w; //������ ��������� ��������� WNDCLASS

    w.lpszClassName = ProgName; //��� ��������� - ��������� ����
    w.hInstance = hInstance; //������������� �������� ����������
    w.lpfnWndProc = WndProc; //��������� �� ������� ����
    w.hCursor = LoadCursor(NULL, IDC_ARROW); //��������� ������
    w.hIcon = 0; //������ � ��� �� ����� ����
    w.lpszMenuName = 0; //� ���� ���� �� �����
    w.hbrBackground = WHITE_BRUSH; //LTGRAY_BRUSH; ���� ���� ����
    w.style = CS_HREDRAW | CS_VREDRAW; //����� - ���������������� �� � � �� �
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if (!RegisterClass(&w))
        return 0;

    //�������� ���� � ������, �������� ��������� CreateWindow
    hWnd = CreateWindow(ProgName, //��� ���������
        L"LabGraf Vasyleva", //��������� ����
        WS_OVERLAPPEDWINDOW, //����� ���� - ���������������
        100, //��������� ���� �� ������ �� �
        100, //��������� �� �
        720+360, //������ ����
        500, //������ ����
        (HWND)NULL, //������������� ������������� ����
        (HMENU)NULL, //������������� ����
        (HINSTANCE)hInstance, //������������� ���������� ���������
        (HINSTANCE)NULL); //���������� �������������� ����������


    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&lpMsg, hWnd, 0, 0)) { //�������� ��������� �� �������
        TranslateMessage(&lpMsg); //����������� ��������� ������ � �������
        DispatchMessage(&lpMsg); //������� ��������� ��������������� ������� ����
    }

    return(lpMsg.wParam);
}

//������� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
    WPARAM wParam, LPARAM lParam)
{
    HDC hdc; //������ �������� ����������
    PAINTSTRUCT ps; //������ ��������� ��������� ������������ ������


    //randMatrix(koef);


    //���� ��������� ���������
    switch (messg) {
        //��������� ���������
    case WM_PAINT:

        hdc = BeginPaint(hWnd, &ps);
        char* nn[n] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
        int nx[n+1] = {100},
            ny[n+1] = {100},
            nx2[n+1] = {600},
            ny2[n+1] = {100};
        int dx = 16, dy = 16, dtx = 5;


        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255)); // border
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5)); // line

        paint(dx, dy, dtx, nx, ny, hdc, BPen, nn);
        paint(dx, dy, dtx, nx2, ny2, hdc, BPen, nn);

        SelectObject(hdc, KPen);

        paintLine1(matrix, hdc, dx, dy,  nx, ny);
        paintLine2(matrixA, hdc, dx, dy, nx2, ny2);

        paint(dx, dy, dtx, nx, ny, hdc, BPen, nn);
        paint(dx, dy, dtx, nx2, ny2, hdc, BPen, nn);
        EndPaint(hWnd, &ps);//��������� ��������
        break;

    //��������� ������ - ���������� ����
    case WM_DESTROY:
        PostQuitMessage(0); //�������� ��������� ������ � ����� 0 - ���������� ����������
        break;

    default:
        return(DefWindowProc(hWnd, messg, wParam, lParam)); //����������� ������� ���������� �� �������������
    }
    return 0;
}

  void showMatrix(int matrix[n][n]) {
      for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
              printf("%d ", matrix[i][j]);
         }
         printf("\n");
     }
  }


int** randMatrix(float k) {
    srand(0402);
    int matrix[n][n];
    float num;
    int element;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            num = (rand() / (float)RAND_MAX * 2) * k;
            if (num < 1) element = 0;
            else element = 1;
            matrix[i][j] = element;
            printf("%d ", element);
        }
        printf("\n");
    }
    return matrix;
}

