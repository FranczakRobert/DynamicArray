/*
 * ALGO2 IN1 20C LAB01
 * Robert Franczak
 * fr47434@zut.edu.pl
 */

#include <iostream>
#include <stdlib.h>
#include <random>

#define EXTEND_ARRAY 2
#define DEFAULT_SIZE sizeof (T) * u32SizeArray

template<class T>
class DynamicArray
{
private:
    T* pTArray;
    uint32_t u32SizeArray;
    uint32_t u32ElementsArray;

    void extendArray()
    {
        if(nullptr != (pTArray = (T*)realloc(pTArray, DEFAULT_SIZE * EXTEND_ARRAY)))
        {
            u32SizeArray *= EXTEND_ARRAY;
            std::cout << "Reallocate memory - successful\n" << std::endl;
        }
        else
        {
            printf("Can't reallocate memory\n");
        }
    }

public:
    DynamicArray(): u32SizeArray(2), u32ElementsArray(0), pTArray(nullptr){};


    ~DynamicArray()
    {
        delete[] pTArray;
    }

    // a)
    void add(const T& a_array)
    {
        if(nullptr == pTArray)
        {
            if( nullptr != (pTArray = (T*)malloc( DEFAULT_SIZE)))
            {
                std::cout << "Default memory successful allocated\n" << std::endl;
            }
            else
            {
                printf("Can't alloc memory\n");
            }
        }

        if(u32ElementsArray < u32SizeArray)
        {
            pTArray[u32ElementsArray] = a_array;
        }
        else
        {
            extendArray();
            pTArray[u32ElementsArray] = a_array;
        }
        u32ElementsArray++;
    }

    // b)
    T& getElement(const uint32_t a_u32Index)
    {
        if(a_u32Index > u32ElementsArray)
        {
            std::cout << "Index out of range..." << std::endl;
            abort();
        }
        return pTArray[a_u32Index];
    }

    // c)
    void swapData(const uint32_t a_u32Index, const T& a_rTElement)
    {
        if(a_u32Index > u32ElementsArray)
        {
            std::cout << "Index out of range..." << std::endl;
        }
        else
        {
            pTArray[a_u32Index] = a_rTElement;
        }
    }

    // d)
    void clearArray()
    {
        if(pTArray != nullptr)
        {
            delete[] pTArray;
            pTArray = nullptr;
            u32SizeArray = 2;
            u32ElementsArray = 0;
            std::cout << "Array cleard..." << std::endl;
        }
        else
        {
            std::cout << "Array already cleared..." << std::endl;
        }

    }

    // e) 
    void showArray()
    {
        if(nullptr != pTArray)
        {
            for(uint32_t u32Index = 0; u32Index < u32ElementsArray; u32Index++)
            {
                std::cout << "Element [" << u32Index << "] " <<" = "<< pTArray[u32Index] << std::endl;
            }
            std::cout << std::endl;
            std::cout << "Size/elements:  " << u32SizeArray << " / " <<u32ElementsArray << std::endl;
        }
        else
        {
            std::cout << "Array is empty... " << "size/elements:  " << u32SizeArray << " / " <<u32ElementsArray << std::endl;
        }
    }
    
    // f)
    void bubbleSort()
    {
        bool isSorted = true;

        for (uint32_t u32index = 0; u32index < u32ElementsArray; ++u32index)
        {
            for (uint32_t j = 1; j < u32ElementsArray - u32index; ++j)
            {
                if(pTArray[j] < pTArray[j-1])
                {
                    std::swap(pTArray[j],pTArray[j-1]);
                    isSorted = false;
                }
            }
            if(isSorted)
                break;
        }
    }
};

int main()
{
    DynamicArray<long> sample;

    srand(time(nullptr));
    int size = 10000000;

    clock_t start,end;
    float max = 0;

    for (uint32_t u32index = 0; u32index < size; ++u32index)
    {
        uint32_t randomValue = rand();
        start = clock();
        sample.add(randomValue);
        end = clock() - start;
        float val = (float)end/ CLOCKS_PER_SEC;

        if(val > max)
        {
            std::cout << " Index:  "<< u32index <<"  Add time: " << val << std::endl;
            max = val;
        }

    }

    return 0;
}