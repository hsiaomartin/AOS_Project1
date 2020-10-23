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
#define REFERENCE_RANGE_MAX 25 //
#define REFERENCE_RANGE_MIN 15
#define NUMBER_OF_MEMORY_REFERENCE 200000 //how many number we need



#define NUMBER_OF_BLOCKS 100 //how many block in reference

#include <iostream>
#include <iomanip>
#include <string>
#include<algorithm>
using namespace std;
enum {random_String,locality_String,my_String};
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
    void print_Refernece_String(int get_num) {
        cout << setw(3) << setfill(' ') << get_Reference_String(get_num) << " ";

    }
    void set_Reference_String(short mode) {
        //  (1) Random: Arbitrarily pick [1,25] continuous numbers for each reference. 
        if (mode == random_String) { 
            int reference_Count = 0;
            while (reference_Count < NUMBER_OF_MEMORY_REFERENCE) {
                short block_Length = (short)rand() % REFERENCE_RANGE_MAX + 1;
                short number_Start = (short)(rand() % REFERENCE_STRING_MAX) + REFERENCE_STRING_MIN;
                if (NUMBER_OF_MEMORY_REFERENCE - reference_Count < block_Length) 
                    block_Length = NUMBER_OF_MEMORY_REFERENCE - reference_Count;
                
                for ( int i = 0; i < block_Length ; i++ ) {                    
                    my_Reference_String[reference_Count] = number_Start;
                    (number_Start + 1 > REFERENCE_STRING_MAX) ? number_Start = REFERENCE_STRING_MIN : number_Start++;
                    //cout << setw(3) << setfill(' ') << my_Reference_String[reference_Count] << " ";
                    reference_Count++; 
                }
                //cout << "\r\n";
                //--------------------------------

               
                //--------------------------------
            }

        }
        //  (2) Locality: Simulate function calls.Each function call may refer a subset of 1 / 25~1 / 15 string(the length of string can be random).
        else if (mode == locality_String) {
            int number_In_Block = NUMBER_OF_MEMORY_REFERENCE / NUMBER_OF_BLOCKS;
            for ( int block_Count = 0 ; block_Count < NUMBER_OF_BLOCKS; block_Count++ ) {
                short number_Fraction = (short)(rand() % REFERENCE_RANGE_MIN + 1) + (REFERENCE_RANGE_MAX - REFERENCE_RANGE_MIN);
                short random_Number_Start = (short)(rand() % REFERENCE_STRING_MAX) + REFERENCE_STRING_MIN;
                short random_Number_Range = REFERENCE_STRING_MAX / number_Fraction;

                for (int number_Count = block_Count * number_In_Block; number_Count < (block_Count+1) * number_In_Block; number_Count++) {
                    short random_Number_Temp = random_Number_Start + (short)(rand() % random_Number_Range);
                    if (random_Number_Temp > REFERENCE_STRING_MAX) {
                        random_Number_Temp = REFERENCE_STRING_MIN + (random_Number_Temp - REFERENCE_STRING_MAX);
                    }
                    my_Reference_String[number_Count] = random_Number_Temp;
                   // if(my_Reference_String[number_Count]> REFERENCE_STRING_MAX)
                   // cout << setw(3) << setfill(' ') << my_Reference_String[number_Count] << " ";
                }
            }

            //for (int i = 0; i < NUMBER_OF_MEMORY_REFERENCE; i++) {
            //    cout << setw(3) << setfill(' ') << my_Reference_String[i] << " ";
            //    cout << ((i + 1) % 5 == 0) ? "\r\n" : "";
            //}

        }
        else if (mode == my_String) {

        }



        
    }

};

class page_Replacement_algo {

};

int main()
{
    my_Reference_Data myReferenceData;

    myReferenceData.set_Reference_String(locality_String);//random_String , locality_String , my_String

    

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
