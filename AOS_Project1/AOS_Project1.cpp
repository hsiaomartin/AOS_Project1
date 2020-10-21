// AOS_Project1.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
/*
Page Replacement Algorithms and Evaluation

Specification:
1. Reference string : 1~800
2. Number of memory references : At least 200, 000 times
3. Number of frames in the physical memory : 20, 40, 60, 80, 100
4. Three test reference strings:
    (1) Random: Arbitrarily pick [1, 25] continuous numbers for each reference.
    (2) Locality: Simulate function calls. Each function call may refer a subset of 1/25~1/15 string (the length of string can be random).
    (3) Your own reference string. However, you should explain why you choose such a reference string in the report.
5. You can use both reference and dirty bits.

*/
#define REFERENCE_STRING_MAX 800
#define REFERENCE_STRING_MIN 1
#define REFERENCE_STRING_RANGE 25 //
#define NUMBER_OF_MEMORY_REFERENCE 200000 //how many number we need
#define NUMBER_OF_BLOCK 2000 //how many number in a block

#include <iostream>
#include <iomanip>
#include <string>
#include<algorithm>
using namespace std;

class my_Reference_Data {
private:
    short my_Reference_String[NUMBER_OF_MEMORY_REFERENCE];

public:
    my_Reference_Data(){
        //fill 0
        fill(my_Reference_String, my_Reference_String + NUMBER_OF_MEMORY_REFERENCE, 0); 
    }
    int get_Reference_String(int get_num) {
        return my_Reference_String[get_num];
    }
    //  (1) Random: Arbitrarily pick [random_Block_Number_MIN, random_Block_Number_MAX] continuous numbers for each reference. 
    // min = random_num - range/2 ,max = random_num + range/2
    // if random_min - range < REFERENCE_STRING_MIN , min = REFERENCE_STRING_MIN ,max = random_min + range
    // else random_max +range >  REFERENCE_STRING_MAX , min = random_max - range ,max = REFERENCE_STRING_MAX
    void set_Reference_String() {
        for (int number_Blocks = 0; number_Blocks < (NUMBER_OF_MEMORY_REFERENCE / NUMBER_OF_BLOCK); number_Blocks++) {
            short random_Block_Number = (short)(rand() % REFERENCE_STRING_MAX + REFERENCE_STRING_MIN);
            short random_Block_Number_Middle = REFERENCE_STRING_RANGE / 2;
            short random_Block_Number_MIN = random_Block_Number - random_Block_Number_Middle;
            short random_Block_Number_MAX = random_Block_Number + random_Block_Number_Middle;

            if (random_Block_Number_MAX > REFERENCE_STRING_MAX) {
                random_Block_Number_MIN = random_Block_Number_MIN - (random_Block_Number_MAX - REFERENCE_STRING_MAX);
                random_Block_Number_MAX = REFERENCE_STRING_MAX;
            }
            else if (random_Block_Number_MIN < REFERENCE_STRING_MIN) {
                random_Block_Number_MIN = REFERENCE_STRING_MIN;
                random_Block_Number_MAX = random_Block_Number_MAX + (-(random_Block_Number_MIN - REFERENCE_STRING_MIN));
            }
            for (int in_Block_Number = number_Blocks * NUMBER_OF_BLOCK; in_Block_Number < (number_Blocks+1) * NUMBER_OF_BLOCK ; in_Block_Number++) {
                my_Reference_String[in_Block_Number] = ((short)(random_Block_Number_MIN + rand() %( random_Block_Number_MAX- (random_Block_Number_MIN- 1))));
            }
            
        }
        
    }

};


int main()
{
    my_Reference_Data myReferenceData;

    myReferenceData.set_Reference_String();

    
    for (int i = 0; i < NUMBER_OF_MEMORY_REFERENCE; i++) {
        cout<< setw(3)<<setfill(' ')<<myReferenceData.get_Reference_String(i)<< " ";
        if(((i+1) % NUMBER_OF_BLOCK == 0 ))
            cout <<"\r\n";
    }
    //cout << "Hello World!\n"<<str;
    return 0;
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案



// 1 2 4 8 16 32 64
