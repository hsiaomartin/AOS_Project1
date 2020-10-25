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
#define NUMBER_OF_MEMORY_REFERENCE 200000 //how many number we need :200000
#define NUMBER_OF_FRAMES 100 //how many number in a frame :20


#define NUMBER_OF_BLOCKS 1 //how many block in reference :100
#include <bitset>
#include <iostream>
#include <iomanip>
#include <string>
#include<algorithm>
using namespace std;
enum reference_Data_Type {random_String,locality_String,my_String};
enum page_Replacement_Algorithms {FIFO ,ARB ,Enhanced_Second_Chance,my_Method};

int my_Reference_String[NUMBER_OF_MEMORY_REFERENCE];

class my_Reference_Data {
private:


public:
    my_Reference_Data(){
        //fill 0
        fill(my_Reference_String, my_Reference_String + NUMBER_OF_MEMORY_REFERENCE, 0); 
    }
    //int get_Reference_String() {
    //    return my_Reference_String;
    //}
    //void print_Refernece_String(int get_num) {
    //    cout << setw(3) << setfill(' ') << get_Reference_String() << " ";

    //}
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
//-----------------------------------------------------------
                   // cout << setw(3) << setfill(' ') << my_Reference_String[number_Count] << " ";
 //-----------------------------------------------------------
                }
            }
 //           cout << endl;
            //for (int i = 0; i < NUMBER_OF_MEMORY_REFERENCE; i++) {
            //    cout << setw(3) << setfill(' ') << my_Reference_String[i] << " ";
            //    cout << ((i + 1) % 5 == 0) ? "\r\n" : "";
            //}

        }
        else if (mode == my_String) {

        }



        
    }

};

class page_Replacement_Algo {
private:
    short reference_Bit[NUMBER_OF_FRAMES];
    int interrupt_Time;
    int page_Fault_Time;
    int my_Page[NUMBER_OF_FRAMES]={0};
    int priority[NUMBER_OF_FRAMES] = { 0 };
public:
    page_Replacement_Algo() {
        interrupt_Time = 0;
        page_Fault_Time = 0;
        for (int count = 0; count < NUMBER_OF_FRAMES; count++) {
            reference_Bit[count] = 0;
        }
    }

    void set_Replacement_Algo(int mode,int reference_String[]) {
        //(1) FIFO algorithm
        if (mode == FIFO) {
            int my_Pointer = 0;
            bool my_Check = false;
            for (int reference_Count = 0; reference_Count < NUMBER_OF_MEMORY_REFERENCE; reference_Count++) {
                my_Check = false;
                if (reference_Count < NUMBER_OF_FRAMES ) {
                    my_Page[reference_Count] = reference_String[reference_Count];
                    page_Fault_Time++;
                    (my_Pointer < NUMBER_OF_FRAMES) ? my_Pointer++ : my_Pointer = 0;
                    
                }
                else {
                    for (int check_Count = 0; check_Count < NUMBER_OF_FRAMES; check_Count++) {
                        if (my_Page[check_Count] == reference_String[reference_Count]) { 
                            my_Check = true;
                            break; 
                        }
                    }
                    if (my_Check == false) {
                        my_Pointer  = my_Pointer % NUMBER_OF_FRAMES;
                        my_Page[my_Pointer] = reference_String[reference_Count];
                        page_Fault_Time++;
                        my_Pointer++;
                    }
                }
                //cout << "Pointer :->" << my_Pointer << " page fault :" << page_Fault_Time << endl;
            }
            cout << page_Fault_Time;
        }
        //(2) ARB algorithm (8-bit information) 
        else if (mode == ARB) {
            int my_Pointer = 0;
            for (int reference_Count = 0; reference_Count < NUMBER_OF_MEMORY_REFERENCE; reference_Count++) {
//-----------------------------------------------------------------
  /*              for (int update_Count = 0; update_Count < NUMBER_OF_FRAMES; update_Count++) {
                    cout << my_Page[update_Count] << " ";
                }
                cout << endl;

                cout << "In :" << reference_String[reference_Count]  << endl;*/


//-----------------------------------------------------------------

                if (reference_Count < NUMBER_OF_FRAMES) {
                    my_Page[reference_Count] = reference_String[reference_Count];
                    page_Fault_Time++;
                    reference_Bit[my_Pointer] =( (reference_Bit[my_Pointer] >> 1) | 128) & 255;  //  0000_0000  |  1000_0000
                    priority[my_Pointer] = my_Pointer;
                    (my_Pointer < NUMBER_OF_FRAMES) ? my_Pointer++ : my_Pointer = 0;
                    
                }
                else {
                    int hit_Reference = -1;
                    // find number exist
                    for (int check_Count = 0; check_Count < NUMBER_OF_FRAMES; check_Count++) {
                        if (my_Page[check_Count] == reference_String[reference_Count]) {
                            hit_Reference = check_Count;
//-----------------------------------------------------------------
                            //cout << "hit :" << my_Page[check_Count] << endl;
//-----------------------------------------------------------------
                            break;
                        }                       
                    }
                    //if hit number ,shift reference bit 
                    if (hit_Reference > -1) {
                        for (int update_Count = 0; update_Count < NUMBER_OF_FRAMES; update_Count++) {
                            //update reference_Bit
                            if (update_Count == hit_Reference) {
                                reference_Bit[update_Count] = ((reference_Bit[update_Count] >> 1) | 128) & 255;   // ( 0000_0000  |  1000_0000 ) & 1111_1111
                            }
                            else {
                                reference_Bit[update_Count] =((reference_Bit[update_Count] >> 1) & 127) & 255;   // ( 0000_0000  &  0111_1111) & 1111_1111
                            }
                            //update all priority 
                            priority[update_Count] -= 1;
                        }
                        //update priority 
                        priority[hit_Reference] = NUMBER_OF_FRAMES - 1;
                    }
                    // doesn't hit number ,find which number is victim
                    else {
                        //replace victim by new number
                        int victim_Value = 256;
                        int victim = -1; //find out which number least use
                        int check_Redundant[256] = { 0 };//find redundant of smailest number
                        //if find out the least number then record the number
                        for (int check_Reference_Bit = 0; check_Reference_Bit < NUMBER_OF_FRAMES; check_Reference_Bit++) {
                            check_Redundant[reference_Bit[check_Reference_Bit]] += 1;//record how many redundant of  reference bit
                            //find out the least use number
                            if (victim_Value > reference_Bit[check_Reference_Bit]) {
                                victim_Value = reference_Bit[check_Reference_Bit];
                                victim = check_Reference_Bit;
                            }                         
                        }
                       // cout << "victim : " << victim << endl;
                       // for(int i =0 ; i< NUMBER_OF_FRAMES ;i++)
                           // cout << "redundant ! :" << i << " , Times : " << check_Redundant[i] << endl;
                        //if find out smailest number has redundant ,check priority and determinate which one is real victim
                        if (check_Redundant[reference_Bit[victim]] > 1) {
                        //    cout << "redundant ! :"<< victim <<" , Times : "<< check_Redundant[reference_Bit[victim]] << endl;
                            int temp_Priority = NUMBER_OF_FRAMES;
                            //check all of same reference bit victim's priority in frame 
                            for (int check_Priority = 0; check_Priority < NUMBER_OF_FRAMES; check_Priority++) {
                                if (reference_Bit[check_Priority] == victim_Value) {
                                    if (temp_Priority > priority[check_Priority]) {
                                        temp_Priority = priority[check_Priority];
                                        victim = check_Priority;
                                    }
                                }
                            }
                            //replace the lowest victim by new number
                            my_Page[victim] = reference_String[reference_Count];
                        }
                        //replace victim by new number
                        else {
                            my_Page[victim] = reference_String[reference_Count];
                        }                
                        //update reference_Bit
                        for (int update_Count = 0; update_Count < NUMBER_OF_FRAMES; update_Count++) {
                            if (update_Count == victim) {
                                reference_Bit[update_Count] = 0;
                                reference_Bit[update_Count] = ((reference_Bit[update_Count] ) | 128) & 255;   // ( 0000_0000  |  1000_0000 ) & 1111_1111
                            }
                            else {
                                reference_Bit[update_Count] = ((reference_Bit[update_Count] >> 1) & 127) & 255;   // ( 0000_0000  &  0111_1111) & 1111_1111
                            }
                            //update all priority 
                            priority[update_Count] -= 1;
                        }
                        //update priority 
                        priority[victim] = NUMBER_OF_FRAMES - 1;




                        page_Fault_Time++;
                    }
                }
 //-----------------------------------------------------------------
                //for (int update_Count = 0; update_Count < NUMBER_OF_FRAMES; update_Count++) {
                //    cout << my_Page[update_Count] << " ";
                //}
                //cout << endl;
                //for (int update_Count = 0; update_Count < NUMBER_OF_FRAMES; update_Count++) {
                //    cout << "priority : " << priority[update_Count] << " , reference bit" << update_Count << " : " << /*std::bitset<8>*/(reference_Bit[update_Count]) << endl;
                //}
                //cout << " page fault :" << page_Fault_Time;
                //
                //cout << endl;
            }
            cout << page_Fault_Time;
//-----------------------------------------------------------------
        }
        //(3) Enhanced second-chance algorithm 
        else if (mode == Enhanced_Second_Chance) {

        }
        else if (mode == my_Method) {

        }

    }
};

int main()
{
    cout << "Reference string : ( " << REFERENCE_STRING_MIN << " ~ " << REFERENCE_STRING_MAX << " )\r\n";
    cout << "Number of memory reference :  " << NUMBER_OF_MEMORY_REFERENCE << endl;
    cout << "Number of frames in the physical memory :  " << NUMBER_OF_FRAMES << endl;
    cout << "Test reference string :  " << "random_String" << endl;
    cout << "Algorithm :  " << "ARB" << endl;
    my_Reference_Data myReferenceData;
    page_Replacement_Algo pageReplacementAlgo;
    myReferenceData.set_Reference_String(random_String);//random_String , locality_String , my_String
    pageReplacementAlgo.set_Replacement_Algo(ARB, my_Reference_String);//FIFO ,ARB ,Enhanced_Second_Chance,my_Method
    

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
