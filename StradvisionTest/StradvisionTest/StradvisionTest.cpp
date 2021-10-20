// StradvisionTest.cpp : 애플리케이션의 진입점을 정의합니다.
//

#define _CRT_SECURE_NO_WARNINGS

#include "StradvisionTest.h"


#include <iostream>
#include <string>
#include <thread>
#include <random>
#include <mutex>
#include <conio.h>

using namespace std;

uint8_t FilterTest(uint8_t* arr);

void convert(uint8_t* converted, uint8_t* source, uint32_t N, uint32_t M);

void calculateFunc(int N, int M);
void outputFunc(int T, int N, int M);

uint8_t* convetedArr;
int convetedArrSize;
mutex arrayMutex;
bool isInitConvertedArr;


int main()
{
    uint8_t testCase[9];
    testCase[0] = 37;
    testCase[1] = 49;
    testCase[2] = 72;
    testCase[3] = 14;
    testCase[4] = 48;
    testCase[5] = 74;
    testCase[6] = 23;
    testCase[7] = 16;
    testCase[8] = 82;

    uint8_t result = FilterTest(testCase);
    cout << "Test 1 : " << (int)result << endl;
    cout << endl;


    uint8_t source[16];
    source[0] = 37;
    source[1] = 49;
    source[2] = 72;
    source[3] = 36;
    source[4] = 14;
    source[5] = 48;
    source[6] = 74;
    source[7] = 28;
    source[8] = 23;
    source[9] = 16;
    source[10] = 82;
    source[11] = 77;
    source[12] = 14;
    source[13] = 13;
    source[14] = 12;
    source[15] = 89;


    uint8_t converted[16] = { 0 };
    for (int i = 0; i < 16; i++)
    {
        converted[i] = 1;
    }
    convert(converted, source, 4, 4);
    cout << "Test 2 : ";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout.width(3);
            cout << (int)converted[j * 4 + i];
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 10);
    int T = dis(gen);

    int N = dis(gen);
    int M = dis(gen);
    convetedArrSize = N * M;
    isInitConvertedArr = false;

    cout << "Test 3 : ";
    thread t1(calculateFunc, N, M);
    thread t2(outputFunc, T, N, M);

    //int a;
    //cin >> a;
    t1.join();
    t2.join();
    cout << "end" << endl;

    return 0;
}

uint8_t FilterTest(uint8_t* arr)
{
    uint8_t result = 0;
    if (arr[0] > arr[4])
    {
        result += 128;
    }
    if (arr[1] > arr[4])
    {
        result += 64;
    }
    if (arr[2] > arr[4])
    {
        result += 32;
    }
    if (arr[5] > arr[4])
    {
        result += 16;
    }
    if (arr[8] > arr[4])
    {
        result += 8;
    }
    if (arr[7] > arr[4])
    {
        result += 4;
    }
    if (arr[6] > arr[4])
    {
        result += 2;
    }
    if (arr[3] > arr[4])
    {
        result += 1;
    }
    return result;
}



void convert(uint8_t* converted, uint8_t* source, uint32_t N, uint32_t M)
{
    //init boundary value to zero
    for (int i = 0; i < N; i++)
    {
        converted[i] = 0;
        converted[N * (M - 1) + i] = 0;
    }
    for (int j = 0; j < M; j++)
    {
        converted[j * N] = 0;
        converted[(j + 1) * N - 1] = 0;
    }

    for (int i = 1; i < N - 1; i++)
    {
        for (int j = 1; j < M - 1; j++)
        {
            //source에서 3x3 생성
            uint8_t arr[9];
            arr[0] = source[(j - 1) * N + i - 1];
            arr[1] = source[(j - 1) * N + i];
            arr[2] = source[(j - 1) * N + i + 1];
            arr[3] = source[j * N + i - 1];
            arr[4] = source[j * N + i];
            arr[5] = source[j * N + i + 1];
            arr[6] = source[(j + 1) * N + i - 1];
            arr[7] = source[(j + 1) * N + i];
            arr[8] = source[(j + 1) * N + i + 1];

            //
            converted[j * N + i] = FilterTest(arr);


        }
    }



}

void calculateFunc(int N, int M)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(10, 245);
    uint8_t* testCase;
    testCase = new uint8_t[convetedArrSize];
    convetedArr = new uint8_t[convetedArrSize];
    while (1)
    {
        arrayMutex.lock();
        for (int i = 0; i < convetedArrSize; i++)
        {
            testCase[i] = dis(gen);
        }
        convert(convetedArr, testCase, N, M);

        arrayMutex.unlock();

        if (!isInitConvertedArr)
        {
            isInitConvertedArr = true;
        }
        if (_kbhit())
        {
            break;
        }
    }


    delete[] testCase;
    delete[] convetedArr;
}

void outputFunc(int T, int N, int M)
{
    while (1)
    {
        if (!isInitConvertedArr)
        {
            continue;
        }
        arrayMutex.lock();
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                cout.width(3);
                cout << (int)convetedArr[j * N + i];
                if (j == M - 1)
                {
                    cout << endl;
                }
                else
                {
                    cout << ", ";
                }
            }

        }
        arrayMutex.unlock();
        if (_kbhit())
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(T));
    }
    
}