#ifndef _output

#define _output
#include <sstream>
#include <fstream>
#include <ctime>
#include <iostream>
#include <iomanip>
#include "tools.hpp"


//takes only filename and k, no sort type, i do every at one time
template <typename T>
void statsToFile(std::string *params)
{
    uint8_t const numOfAlgos = 5;
    uint16_t k;

    T *array;
    T *arrayCp;

    bool ascending = true;
    if (params[1].compare(">=") == 0)
        ascending = false;
    auto *d = new myData<T>();
    d->comparator = getComparator<T>(ascending);
    
    Stats *s = new Stats;
    //s->print = true;

    clock_t time;
    uint64_t *mid_swaps, *mid_compares; //i will divide by k
    clock_t *mid_time;
    double *swaps_n, *compares_n;

    std::istringstream(params[3]) >> k;

    std::cout << "k=" << k << " "
         << "Ascending: " << [](bool ascending) {
                if (ascending)
                    return "yes";
                return "no";
            }(ascending)
         << std::endl;
    mid_compares = new uint64_t[numOfAlgos];
    mid_swaps = new uint64_t[numOfAlgos];
    mid_time = new clock_t[numOfAlgos];

    std::string file_name;
    file_name = params[2];
    std::ofstream file[numOfAlgos];
   
    std::string algoType;
    for (int i = 0; i < numOfAlgos; i++)
    {
        switch (i)
        {
        case 0:
            algoType = "Insertion";
            break;
        case 1:
            algoType = "Merge";
            break;
        case 2:
            algoType = "Quick";
            break;
        case 3:
            algoType = "QDP";
            break;
        case 4:
            algoType = "Hybrid";
            break;
        }
        file[i].open(file_name + "-" + algoType + ".csv", std::ios::trunc | std::ios::out); //erease the file
        file[i]<<algoType<<"Sort;  k="<<k<<";"<<std::endl;
        file[i]<<"n;compares;shifts;time(microsecs);"<<std::endl;
    }

    for (int n = 100; n <= 10000; n += 100)
    {

        d->length = n;
        //maybe memcpy would be better;   or mid_swaps = {0};
        for (int z = 0; z < numOfAlgos; z++)
        {
            mid_swaps[z] = 0;
            mid_compares[z] = 0;
            mid_time[z] = 0;
        }
        T *array = new T[n];
        T *arrayCp = new T[n];

        d->length = n;

        for (int j = 0; j < k; j++)
        {
            fillWithRandom<T>(array, n);
            
            for (int m = 0; m < numOfAlgos; m++)
            {

                s->cmp_count = 0;
                s->shift_count = 0;
                std::copy(array, array + n, arrayCp);
                d->array = arrayCp;

                switch (m)
                {
                    case 0:
                        time = clock();
                        insertionSort<T>(d, s);
                        time = clock() - time;
                        break;
                    case 1:
                        time = clock();
                        mergeSort<T>(d, s, 0, n - 1);
                        time = clock() - time;
                        break;
                    case 2:
                        time = clock();
                        quickSort<T>(d, s, 0, n - 1);
                        time = clock() - time;
                        break;
                    case 3:
                        time = clock();
                        quickSortDP<T>(d, s, 0, n - 1);
                        time = clock() - time;
                        break;
                    case 4:
                        time = clock();
                        hybridSort<T>(d, s, 0, n-1, 10);
                        time = clock() - time;
                        break; 
                }
                if (!isSorted<T>(d)){
                    std::cerr << "Not sorted!!!" << std::endl;
                    exit(EXIT_FAILURE);
                }
                mid_compares[m] += s->cmp_count;
                mid_swaps[m] += s->shift_count;
                mid_time[m] += time;
            }
        }
        delete[] array;
        delete[] arrayCp;
        //after performing k measures
        for (int i = 0; i < numOfAlgos; i++)
        {   
            //!!!!!!   double was bad idea  maybe uint32_t would be also sufficient
            uint64_t final_compares = (uint64_t)(mid_compares[i] / k);
            uint64_t final_shifts = (uint64_t)(mid_swaps[i] / k);
            double final_time = (double)((double)mid_time[i] / CLOCKS_PER_SEC) / ((double)k) * 1000000.0;
            file[i] << n << ";" << final_compares << ";" << final_shifts << ";" 
                << std::fixed << std::setprecision(2) << final_time << ";" << std::endl;
        }
    }
    //freeing memory
    for (int i = 0; i < numOfAlgos; i++)
        file[i].close();
    delete[] mid_compares;
    delete[] mid_swaps;
    delete[] mid_time;
    delete s;
    delete d;
};

template <typename T>
void testInConsole(std::string *params)
{
    bool ascending= true;
    if (params[1].compare(">=") == 0)
        ascending = false;

    clock_t time;
    int n = 10;
    Stats *s = new Stats;
    auto *d = new myData<T>();
    d->comparator = getComparator<T>(ascending);
    //s->print = true;
    int numOfAlgos = 5;
    int numOfArrays = 3;
    std::string type;
    std::string arrType;

    while (n <= 100)
    {
        std::cout << std::endl
             << "Size of array: " << n << std::endl
             << std::endl;
        d->length = n;
        T *prevArr = nullptr;
        T *arrAscSorted = new T[n];
        T *arrDescSorted = new T[n];
        T *arrRandom = new T[n];
        T *arrCurrent = new T[n];
        //when we have strings in arrays, this part with arrAsc and arrDesc is not working 
        //bcs assigning number to string doesn't give use proper data representation in ascii code
        for (int i = 0; i < n; i++)
        {
            arrAscSorted[i] = i + 1;
            arrDescSorted[i] = n - i;
        }

        fillWithRandom<T>(arrRandom, n);

        for (int i = 0; i < numOfArrays; i++)
        {

            switch (i)
            {
                case 0:
                    arrType = "Asc";
                    prevArr = arrAscSorted;
                    break;
                case 1:
                    arrType = "Des";
                    prevArr = arrDescSorted;
                    break;
                case 2:
                    arrType = "Random";
                    prevArr = arrRandom;
                    break;
            }

            for (int k = 0; k < numOfAlgos; k++)
            {

                std::copy(prevArr, prevArr + n, arrCurrent); //!important
                d->array = arrCurrent;
                
                switch (k)
                {
                    case 0:
                        type = "Insertion";
                        time = clock();
                        insertionSort<T>(d, s);
                        time = clock() - time;
                        break;
                    case 1:
                        type = "Merge";
                        time = clock();
                        mergeSort<T>(d, s, 0, n - 1);
                        time = clock() - time;
                        break;
                    case 2:
                        type = "Quick";
                        time = clock();
                        quickSort<T>(d, s, 0, n - 1);
                        time = clock() - time;
                        break;
                    case 3:
                        type = "QDP";
                        time = clock();
                        quickSortDP<T>(d, s, 0, n - 1);
                        time = clock() - time;
                        break;
                    case 4:
                        type = "hybrid";
                        time = clock();
                        hybridSort<T>(d, s, 0, n-1, 10);
                        time = clock() - time;
                        break;
                }
                if(!isSorted<T>(d)){
                    std::cout<<"Not sorted by: "<<type<<std::endl;
                    exit(EXIT_FAILURE);
                }
                std::cout << std::endl
                     << "----------------------------------------" << std::endl;
                std::cout << "Type: " << type << " ; ArrayType: " << arrType << std::endl;
                std::cerr<< "Compares: " << s->cmp_count << std::endl;
                std::cerr<< "Shifts: " << s->shift_count << std::endl;
                std::cerr<< "Time (micro-s): " << ((double)time) / CLOCKS_PER_SEC * 1000000 << std::endl;
                std::cout << "Sorted: " << [](bool sorted) {
                    if (sorted)
                        return "yes";
                    return "no";
                }(isSorted(d))
                     << std::endl;
                s->cmp_count = 0;
                s->shift_count = 0;
            }
            std::cout << std::endl
                 << "----------------------------------------" << std::endl
                 << std::endl
                 << "Sorted elems-counter: " << countSortedElems(prevArr, d) << std::endl;
            std::cout<<std::endl;
                 displayArray(d);
            std::cout<<std::endl;
            //delete[] prevArr;   //works for ints not for string
            //delete[] d->array;
        }

        if (n == 10)
            n += 40;
        else if (n == 50)
            n += 50;
        else
            break;
    }
    delete d;
    delete s;
}

template<typename T>
void defaultExecution(std::string *params){
    clock_t time;
    int n;

    auto* data = new myData<T>();
    Stats* stats = new Stats;
    bool ascending = true;
        if(params[1].compare(">=") == 0) ascending = false;
    data->comparator = getComparator<T>(ascending);
    std::string type = params[0];

    std::cout<<"Enter lenght of data: ";
    std::cin>>n;
    T* array = new T[n];
    T* arrBefore = new T[n];
    data->length=n;

    stats->print = true;
    for(int i=0; i<n; i++){
        std::cin>>array[i];
    }
    std::copy(array, array+n, arrBefore);
    data->array=array;
    
    if(type=="insert"){
        time = clock();
        insertionSort<T>(data, stats);
        time = clock() - time;
    }
    else if(type=="merge"){
        time = clock();
        mergeSort<T>(data, stats, 0, data->length-1);
        time = clock() - time;
    }
    else if(type=="quick"){
        time = clock();
        quickSort<T>(data, stats, 0, data->length-1);
        time = clock() - time;
    }
    else if(type=="dual"){
        time = clock();
        quickSortDP<T>(data, stats, 0, data->length-1);
        time = clock() - time;
    }
    else if(type=="hybrid"){
        time = clock();
        hybridSort<T>(data, stats, 0, data->length-1, 10);
        time = clock() - time;
    }
    std::cout<<"Compares: "<<stats->cmp_count<<std::endl;
    std::cout<<"Shifts: "<<stats->shift_count<<std::endl;
    std::cerr<<"Time (ms): "<<((double)time/CLOCKS_PER_SEC)*1000000.0<<std::endl;
    std::cout<<"Sorted: "<<[](bool sorted){ 
        if(sorted)
            return "yes";
        return "no";
    }(isSorted(data))<<std::endl<<"After sorting, using: "<<type<<std::endl;
    displayArray(data);
}
#endif