/**
 * @file CensusDataSorts.cpp   Sort functions for census population data.
 * 
 * @brief
 *    Implements several different types of sorts. Data can be sorted
 * by population or by name of town. This file contains all of the sorting
 * functions and their helpers.
 *
 * @author Judy Challinger and Javier Pardo
 * @date 2/22/13
 */
#include <chrono>
#include <climits>
#include <random>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "CensusData.h"

/**
 * @brief First method of sorting, Insertion Sort.
 *
 * @param Type, which is either 0 or 1, it selects the type of sorting, by
 *        population or by name.
 *
 * @return Nothign.
 *
 */
void CensusData::insertionSort(int type) {
  if(type == 0)
  {
   int i;
   for(unsigned int j = 1; j < data.size(); j++)
   {
     Record* key = data[j];
     i = j-1;
     while(i >= 0 && (data[i]->population > key->population))
     {
       data[i+1] = data[i];
       i = i-1;
     }
     data[i+1] = key;
   }
  }
  else
  {
    int i;
    for(unsigned int j = 1; j < data.size(); j++)
    {
      Record* key = data[j];
      i = j-1;
      while(i >= 0 && *(data[i]->city) > *(key->city))
      {
        data[i+1] = data[i];
        i = i-1;
      }
      data[i+1] = key;
    }
  }
}

/**
 * @brief Function that gets the limits p and r needed for 
 *        merge sort.
 *
 * @param Type, value needed to know if the sorting has to be
 *        done regarding population or name.
 *
 * @return Nothing.
 *
 */
void CensusData::mergeSort(int type) {
  int r = data.size();
  int p = 0;
  InitialMergeSort(type,p,r-1);
}

/**
 * @brief Initial call to use Merge Sort, main fucntion
 *        where all the recursive action takes place.
 *
 * @param Type, value need to know if the sorting has to be
 *        done by population or name.
 *        P, lower limit, initially is 0.
 *        R, upper limit, initially it is the size of the vector.
 *
 * @return Nothing.
 *
 */
void CensusData::InitialMergeSort(int type, int p, int r)
{
  if(p < r)
  {
    int q = (p+r)/2;
    InitialMergeSort(type,p,q);
    InitialMergeSort(type,q+1,r);
    Merge(type,p,q,r);
  }
}

/**
 * @brief Actual sorting and merging of the data.
 *
 * @param Type, value needed to know if the sorting has to be
 *        done by population or name.
 *        P, lower limit.
 *        R, upper limit.
 *        Q, Mid point, where the vector gets divided into 2 vectors.
 *
 * @return Nothing.       
 *
 */
void CensusData::Merge(int type, int p, int q, int r)
{
    int n1 = q-p+1;
    int n2 = r-q;
    vector<Record*> Left;
    vector<Record*> Right;
    for(int i=0; i < n1; i++)
    {
      Left.push_back(data[p+i]);
    }
    for(int j=0; j < n2; j++)
    {
      Right.push_back(data[q+j+1]);
    }
    //long long int max = 1298307964911120440LL;
    //string maxstring = std::to_string(max);
    string maxstring = "~~~";
    Record* last = new Record(maxstring,maxstring,INT_MAX);
    Left.push_back(last);
    Right.push_back(last);
    int i=0;
    int j=0;
    for(int k=p; k<=r; k++)
    {
      if(type == 0)
      {
        if(Left[i]->population <= Right[j]->population)
        {
          data[k] = Left[i];
          i++;
        }
        else
        {
          data[k] = Right[j];
          j++;
        }
      }
      else
      {
        if(*(Left[i]->city) <= *(Right[j]->city))
        {
          data[k] = Left[i];
          i++;
        }
        else
        {
          data[k] = Right[j];
          j++;
        }
      }
    }
}

/**
 * @brief Function that gets the limits p and r needed for 
 *        Quicksort.
 *
 * @param Type, value needed to know if the sorting has to be
 *        done regarding population or name.
 *
 * @return Nothing.
 *
 */
void CensusData::quickSort(int type) {
  int r = data.size();
  int p = 0;
  QuickSort(type,p,r-1);
}

/**
 * @brief Initial call to use Quick Sort, main fucntion
 *        where all the recursive action takes place.
 *
 * @param Type, value need to know if the sorting has to be
 *        done by population or name.
 *        P, lower limit, initially is 0.
 *        R, upper limit, initially it is the size of the vector.
 *
 * @return Nothing.
 *
 */
void CensusData::QuickSort(int type, int p, int r)
{
  if(p < r)
  {
    int q = RandomPartition(type,p,r);
    QuickSort(type,p,q-1);
    QuickSort(type,q+1,r);
  }
}

/**
 * @brief Randomly selects the pivot point for the partition.
 *
 * @param Type, value needed to know if the sorting has to be
 *        done by population or name.
 *        P, lower limit.
 *        R, upper limit.
 *
 * @return Call to do Partition.       
 *
 */
int CensusData::RandomPartition(int type, int p, int r)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::uniform_int_distribution<int> distribution(p,r);
  int i = distribution(generator);
  std::swap(data[r],data[i]);
  return Partition(type,p,r);
}

/**
 * @brief Actual us of Quick Sort to sort the data.
 *
 * @param Type, value needed to know if the sorting has to be
 *        done by population or name.
 *        P, lower limit.
 *        R, upper limit.
 *
 * @return i+1.       
 *
 */
int CensusData::Partition(int type, int p, int r)
{
 if(type == 0)
 {
   Record* x = data[r];
   int i = p-1;
   for(int j = p; j < r; j++)
   {
     if(data[j]->population <= x->population)
     {
       i++;
       std::swap(data[i],data[j]);
     }
   }
   std::swap(data[i+1],data[r]);
   return i+1;
 }
 else
 {
   Record* x = data[r];
   int i = p-1;
   for(int j = p; j < r; j++)
   {
     if(*(data[j]->city) <= *(x->city))
     {
       i++;
       std::swap(data[i],data[j]);
     }
   }
   std::swap(data[i+1],data[r]);
   return i+1;
 }
}
