#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <thread>
#include <random>

using namespace std;

uint8_t FilterTest(uint8_t** arr);

void convert(uint8_t* converted, uint8_t* source, uint32_t N, uint32_t M);

void calculate();
static uint8_t* convetedArr;

int main()
{
    uint8_t** testCase = new uint8_t*[3];
    for (int i = 0; i < 3; i++)
    {
        testCase[i] = new uint8_t[3];
    }
    testCase[0][0] = 37;
    testCase[0][1] = 49;
    testCase[0][2] = 72;
    testCase[1][0] = 14;
    testCase[1][1] = 48;
    testCase[1][2] = 74;
    testCase[2][0] = 23;
    testCase[2][1] = 16;
    testCase[2][2] = 82;


    uint8_t result = FilterTest(testCase);
    cout << (int)result << endl;

    delete[] testCase;
    return 0;
}

uint8_t FilterTest(uint8_t** arr)
{
    uint8_t result = 0;
    //순서가 잘못됨
    //for (int i = 0; i < 3; i++)
    //{
    //    for (int j = 0; j < 3; j++)
    //    {
    //        if (i != 1 || j != 1)
    //        {
    //            //cout << "i : " << i << " j : " << j << endl;
    //            result *= 2;
    //            if (arr[i][j] > arr[1][1])
    //            {
    //                cout << arr[i][j]<<endl;
    //                result++;
    //            }
    //        }
    //    }
    //}
    if (arr[0][0] > arr[1][1])
    {
        result += 128;
    }
    if (arr[0][1] > arr[1][1])
    {
        result += 64;
    }
    if (arr[0][2] > arr[1][1])
    {
        result += 32;
    }
    if (arr[1][2] > arr[1][1])
    {
        result += 16;
    }
    if (arr[2][2] > arr[1][1])
    {
        result += 8;
    }
    if (arr[2][1] > arr[1][1])
    {
        result += 4;
    }
    if (arr[2][0] > arr[1][1])
    {
        result += 2;
    }
    if (arr[1][0] > arr[1][1])
    {
        result += 1;
    }
    return result;
}



void convert(uint8_t* converted, uint8_t* source, uint32_t N, uint32_t M)
{
    for (int i = 1; i < N - 1; i++)
    {
        for (int j = 1; j < M - 1; j++)
        {
            //source에서 3x3 생성
            uint8_t** arr = new uint8_t*[3];
            for (int k = 0; k < 3; k++)
            {
                arr[k] = new uint8_t[3];
            }
            arr[0][0] = source[(i - 1) * M + j - 1];
            arr[0][1] = source[(i - 1) * M + j];
            arr[0][2] = source[(i - 1) * M + j + 1];
            arr[1][0] = source[i * M + j - 1];
            arr[1][1] = source[i * M + j];
            arr[1][2] = source[i * M + j + 1];
            arr[2][0] = source[(i + 1) * M + j - 1];
            arr[2][1] = source[(i + 1) * M + j];
            arr[2][2] = source[(i + 1) * M + j + 1];

            //
            converted[i*M + j] = FilterTest(arr);
            

            delete[] arr;
        }
    }

    

}

void calculate()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> dis(10, 245);
    int N = dis(gen);
    int M = dis(gen);

    while (1)
    {
        uint8_t** testCase = new uint8_t * [N];
        for (int i = 0; i < N; i++)
        {
            testCase[i] = new uint8_t[M];
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                testCase[i][j] = dis(gen);
            }
        }
        
        delete[] testCase;
    }
}

void output()
{

}