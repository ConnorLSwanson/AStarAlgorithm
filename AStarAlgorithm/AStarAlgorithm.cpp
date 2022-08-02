// AStarAlgorithm.cpp 
// Connor Swanson
// Activision Blizzard
// 8/1/2022

#include <iostream>
using namespace std;

struct Point
{
    int x;
    int y;
    Point(int a, int b)
    {
        x = a;
        y = b;
    }
};

void DrawMap(char arr[][15], int width, int height);
void UpdateMap(char arr[][15], Point lastPos, Point newPos);
Point LocateChar(char arr[][15], int width, int height, char c);
Point CalculateDistance(Point s, Point e);
Point CalculateDirection(Point d);
bool CanForwardMove(char arr[][15], Point start, Point dir, char axis);
bool CanLateralMove(char arr[][15], Point start, Point dir, char axis);
int GetLateralDir(char arr[][15], Point start, Point dir, char axis);
bool CanBackwardsMove(char arr[][15], Point start, Point dir, char axis);

int main()
{
    bool endReached = false;
    const char kClear = ' ';
    const char kMud = 'M';
    const char kWater = 'W';
    const char kWall = 'X';
    const char kStart = 'S';
    const char kEnd = 'E';

    const int kWidth = 15;
    const int kHeight = 10;
    char map[kHeight][kWidth] = {
        { ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ' }, // 1
        { ' ', ' ', 'X', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', 'X', ' ', 'X', ' ' },
        { ' ', ' ', 'X', ' ', ' ', 'X', 'X', 'X', ' ', ' ', ' ', 'X', ' ', 'X', ' ' },
        { ' ', ' ', 'X', ' ', ' ', ' ', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ' },
        { 'S', ' ', 'X', ' ', ' ', ' ', ' ', 'X', ' ', 'X', ' ', 'X', ' ', ' ', 'E' }, // 5
        { ' ', ' ', 'X', ' ', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ' },
        { ' ', ' ', 'X', ' ', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ' },
        { ' ', ' ', ' ', ' ', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ' }, 
        { ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', 'X', ' ', 'X', ' ' },
        { ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', 'X', ' ', 'X', ' ' }  // 10
    };

    Point start = LocateChar(map, kWidth, kHeight, kStart);
    Point lastPos = start;
    Point end = LocateChar(map, kWidth, kHeight, kEnd);
    Point dist = CalculateDistance(start, end);
    Point dir = CalculateDirection(dist);
    Point newPos = start;

    while (!endReached)
    {
        DrawMap(map, kWidth, kHeight);
        dist = CalculateDistance(start, end);
        dir = CalculateDirection(dist);
        newPos = start;

        if (dist.x > dist.y && dist.x != 0)
        {
            // check x-axis for possible move
            if (CanForwardMove(map, start, dir, 'X'))
            {
                newPos.x += dir.x;
            }
            else if (CanLateralMove(map, start, dir, 'Y'))
            {
                dir.y = GetLateralDir(map, start, dir, 'Y');
                newPos.y += dir.y;
            }
            else if (CanBackwardsMove(map, start, dir, 'X'))
            {
                newPos.x += -dir.x;
            }

            // If move is possible, set lastPos to start and move start to new location
            lastPos = start;
            start = newPos;
            UpdateMap(map, lastPos, newPos);
        }
        else if (dist.y > dist.x && dist.y != 0)
        {
            // check y-axis for possible move
            if (CanForwardMove(map, start, dir, 'Y'))
            {
                newPos.y += dir.y;
            }
            else if (CanLateralMove(map, start, dir, 'X'))
            {
                dir.x = GetLateralDir(map, start, dir, 'X');
                newPos.x += dir.x;
            }
            else if (CanBackwardsMove(map, start, dir, 'Y'))
            {
                newPos.y += -dir.y;
            }

            // If move is possible, set lastPos to start and move start to new location
            lastPos = start;
            start = newPos;
            UpdateMap(map, lastPos, newPos);
        }

        if (start.x == end.x && start.y == end.y)
        {
            endReached = true;
        }
    }
    
    cout << "THE END HAS BEEN REACHED!!" << endl;

}

void DrawMap(char arr[][15], int width, int height)
{
    system("cls");
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            cout << arr[h][w];
        }
        cout << endl;
    }
}

void UpdateMap(char arr[][15], Point lastPos, Point newPos)
{
    arr[lastPos.y][lastPos.x] = ' ';
    arr[newPos.y][newPos.x] = 'S';
}

Point LocateChar(char arr[][15], int width, int height, char c)
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (arr[h][w] == c)
            {
                return Point(w, h);
            }
        }
    }
    
    return Point(0, 0);
}

Point CalculateDistance(Point s, Point e)
{
    return Point(e.x - s.x, e.y - s.y);
}

Point CalculateDirection(Point d)
{
    int x, y;

    x = (d.x >= 0) ? 1 : -1;
    y = (d.y >= 0) ? 1 : -1;

    return Point(x, y);
}

bool CanForwardMove(char arr[][15], Point start, Point dir, char axis)
{
    if (axis == 'X')
    {
        if (arr[start.y][start.x + dir.x] == ' ')
        {
            return true;
        }
        return false;
    }
    else if (axis == 'Y')
    {
        if (arr[start.y + dir.y][start.x] == ' ')
        {
            return true;
        }
        return false;
    }
    return false;
}

bool CanLateralMove(char arr[][15], Point start, Point dir, char axis)
{
    if (axis == 'X')
    {
        if (arr[start.y][start.x + dir.x] == ' ')
        {
            return true;
        }
        else return false;
    }
    else if (axis == 'Y')
    {
        if (arr[start.y + dir.y][start.x] == ' ')
        {
            return true;
        }
        else return false;
    }
    else return false;
}

int GetLateralDir(char arr[][15], Point start, Point dir, char axis)
{
    if (axis == 'X')
    {
        if (arr[start.y][start.x + 1] == ' ')
        {
            return 1;
        }
        else if (arr[start.y][start.x - 1] == ' ')
        {
            return -1;
        }
        else return 0;
    }
    else if (axis == 'Y')
    {
        if (arr[start.y + 1][start.x] == ' ')
        {
            return 1;
        }
        else if (arr[start.y - 1][start.x] == ' ')
        {
            return -1;
        }
        else return 0;
    }
    else return false;
}

bool CanBackwardsMove(char arr[][15], Point start, Point dir, char axis)
{
    if (axis == 'X')
    {
        if (arr[start.y][start.x - dir.x] == ' ')
        {
            return true;
        }
        else return false;
    }
    else if (axis == 'Y')
    {
        if (arr[start.y - dir.y][start.x] == ' ')
        {
            return true;
        }
        else return false;
    }
    else return false;
}