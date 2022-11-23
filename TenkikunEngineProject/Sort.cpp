#include "Sort.h"

//void Sort::RadixSort(int array[], int array_size)
//{
//    // find the maximum value in the array
//    int max = array[0];
//    for (int i = 1; i < array_size; i++) {
//        if (array[i] > max) {
//            max = array[i];
//        }
//    }
//
//    // sorting based on 10^i, where i = 1, 2, ...
//    for (int exp = 1; max / exp > 0; exp *= 10) {
//        Sort::CountSort(array, array_size, exp);
//    }
//}

//void Sort::CountSort(int array[], int array_size, int exp) {
//
//    int sorted_array[array_size];
//    int count[10] = { 0 };
//
//    for (int i = 0; i < array_size; i++) {
//        count[(array[i] / exp) % 10]++;
//    }
//
//    for (int i = 1; i < 10; i++) {
//        count[i] += count[i - 1];
//    }
//
//    for (int i = array_size - 1; i >= 0; i--) {
//        sorted_array[count[(array[i] / exp) % 10] - 1] = array[i];
//        count[(array[i] / exp) % 10]--;
//    }
//
//    for (int i = 0; i < array_size; i++) {
//        array[i] = sorted_array[i];
//    }
//}
