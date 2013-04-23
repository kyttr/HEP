/* 
 * File:   kayasC_Fncs.h
 * Author: kaya
 *
 * Created on April 23, 2013, 5:22 PM
 */

#ifndef KAYASC_FNCS_H
#define	KAYASC_FNCS_H

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int *sortIndices(double *arr, int len);
int *sortIndices_Descending(double *arr, int len);
int *sortIndices(float *arr, int len);
int *sortIndices_Descending(float *arr, int len);
int *sortIndices(double *arr);

#ifdef	__cplusplus
extern "C" {
#endif


#ifdef	__cplusplus
}
#endif

/*
 * sort "arr" and return an integer array which does not contain the elements of "arr", but the indices of the elements of "arr" which reflects the sorting. 
 * Ex : arr={33,22,11,55,44}    corresponds to array of indices : {0,1,2,3,4}
 * returned array is  {2,1,0,4,3}
 * 
 * for the moment this method uses an inefficient sorting algorithm, namely "insertion sort"
 */
int* sortIndices(double *arr, int len) {
    //int *sortIndices(void *arr, int len) {
    int i;
    int* indices = new int[len];
    /*
     * DOES NOT WORK, if want to return "int*"
    //int *indices;
    //int indices[len];
     */

    // assign initial values for indices
    for (i = 0; i < len; i++)
        indices[i] = i;

    // insertion sort
    // arrange indices array in parallel with sorting
    double current;
    int current2; // corresponding index of "current" in "indices"
    int pos; //position
    for (i = 1; i < len; i++) {
        current = arr[i];
        current2 = indices[i];
        pos = i - 1;
        while (pos >= 0 && current < arr[pos]) {
            arr[pos + 1] = arr[pos];
            indices[pos + 1] = indices[pos]; // arrange values in "indices" accordingly
            pos--;
        }
        arr[pos + 1] = current;
        indices[pos + 1] = current2;
    }

    return indices;
}

/*
 * sort "arr" and return an integer array which does not contain the elements of "arr", but the indices of the elements of "arr" which reflects the sorting. 
 * Ex : arr={33,22,11,55,44}    corresponds to array of indices : {0,1,2,3,4}
 * returned array is  {2,1,0,4,3}
 * 
 * for the moment this method uses an inefficient sorting algorithm, namely "insertion sort"
 */
int* sortIndices(float *arr, int len) {
    //int *sortIndices(void *arr, int len) {
    int i;
    int* indices = new int[len];
    /*
     * DOES NOT WORK, if want to return "int*"
    //int *indices;
    //int indices[len];
     */

    // assign initial values for indices
    for (i = 0; i < len; i++)
        indices[i] = i;

    // insertion sort
    // arrange indices array in parallel with sorting
    float current;
    int current2; // corresponding index of "current" in "indices"
    int pos; //position
    for (i = 1; i < len; i++) {
        current = arr[i];
        current2 = indices[i];
        pos = i - 1;
        while (pos >= 0 && current < arr[pos]) {
            arr[pos + 1] = arr[pos];
            indices[pos + 1] = indices[pos]; // arrange values in "indices" accordingly
            pos--;
        }
        arr[pos + 1] = current;
        indices[pos + 1] = current2;
    }

    return indices;
}

/*
 * sort indices from max to min.
 * sortIndices() : in increasing order
 * sortIndices()_Descending : in decreasing order
 */
int* sortIndices_Descending(double* arr, int len)
{
    int* indices=sortIndices(arr,len);
    int i, tmp;
    for (i=0;i<len/2;i++)
    {
        tmp=indices[i];
        indices[i]=indices[len-i-1];
        indices[len-i-1]=tmp;
    }
    return indices;
}

/* 
 * sort "arr" and return an integer array which does not contain the elements of "arr", but the indices of the elements of "arr" which reflects the sorting. 
 * Ex : arr={33,22,11,55,44}    corresponds to array of indices : {0,1,2,3,4}
 * returned array is  {2,1,0,4,3}
 * 
 * runs for the where the length of "arr" is not specified.
 * 
 * DOES NOT WORK :  int len=(sizeof (arr) / sizeof (*arr));
 * I guess this code works in the scope where array "arr" is initialized.
 */
int* sortIndices(double* arr) {
    int len = (sizeof (arr) / sizeof (*arr));
    return sortIndices(arr, len);
}

#endif	/* KAYASC_FNCS_H */

