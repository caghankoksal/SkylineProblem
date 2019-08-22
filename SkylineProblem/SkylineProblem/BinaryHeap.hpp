//
//  BinaryHeap.hpp
//  CS300 HW4
//
//  Created by caghank on 11.12.2018.
//  Copyright © 2018 caghank. All rights reserved.
//

#ifndef BinaryHeap_hpp
#define BinaryHeap_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std ;

template <class Comparable>
class BinaryHeap
{
    public:

    BinaryHeap( const vector<Comparable> & items );
    BinaryHeap(int capacity) ;
    void insert( const Comparable & x , int label);

    int GetMax () ;
    void heapsort ( vector <Comparable> &a);
    bool isEmpty() ;
    void Remove ( int label) ;
    void SetPrevMax(int Max) ;
    int ReturnPrevMax() ;
    
    
    private:
    
    int currentSize; // Number of elements in heap
    int PrevMax ;
    vector<Comparable> array; // The heap array
    vector<int> Location ;
    //void buildHeap( );
    void percolateDown( int hole ) ;
    void buildHeap( vector<Comparable> Input) ;

};

/**
 * Insert item x into the priority queue, maintaining heap order.
 * Duplicates are allowed.
 */  //sanırım bu  minHeap
template <class Comparable>
void BinaryHeap<Comparable>::insert( const Comparable & x ,int label )
{
    if(currentSize == array.size() -1 )
        array.resize( array.size() * 2) ;
    // Percolate up
    
    int hole = ++currentSize;
    for( ; hole > 1 && x.value > array[hole/2].value  ; hole /= 2 )
    {
        array[ hole ] = array[ hole / 2 ];
        Location[array[hole].label] =hole ;
        
    }
    
    array[ hole ] = x;
    Location[array[hole].label] = hole ;
}



inline int leftChild( int i )
{
    return 2*i;
}
inline int rightChild( int i )
{
    return 2*i +1;
}


template <class Comparable >
void BinaryHeap<Comparable> ::Remove(int label)
{
    
    
    int parent = Location[label]/2;//gives me position of the item in the heap which has a label == label ;  //Parent is parent index
    if(parent == 0)
        parent++ ;
    //Comparable restored = array[Location[label]];  //to save deleted member ;
    //std::remove
    array[Location[label]] = array[currentSize] ;
    
    //Location[array[Location[label]].label] = Location[label] ;
    //Location.erase(Location.begin() +label) ;
    
    currentSize-- ;
    
    //Location burada güncelleme gerekebilir
    
    
    if (Location[label] == 1 /*x is root*/ || (array[parent].value < array[Location[label]].value)) /* k is root */
    {
        percolateDown(Location[label]) ;
    }
    else
    {
        //item to perc up array[Location[label]]
        int parent ;
        Comparable temp ;
        
        while (Location[label] != 1)
        {
            parent = Location[label]/2 ; //parent location in the array
            if(array[Location[label]].value > array[parent].value)
            {
                temp = array [parent] ;
                array[parent] = array[Location[label]] ;
                array[Location[label]] = temp ;
                
            }
            else
            {
                break ;
            }
        }
    }
    
}



template <class Comparable > // For Delete Max
//a is the array , i is the position to perculate down from
// n is the logical size of the array
void BinaryHeap<Comparable>::percolateDown( int hole )
{
    int child ;
    Comparable temp = array[ hole] ;
    for( ; hole*2 <=currentSize ; hole = child) //current Size is valid element number like if array has 9 total  8 of them valid since 1 element is like NULL Eleement at the index 0
    {
        child = hole *2 ;
        
        if ( child != currentSize && ( array[child +1].value > array[child].value))
        {
            child = child +1 ;
        }
        if( array[child].value > temp.value ) //ESİTTİR 
        {
            array[hole] = array[ child] ;
        }
        else
            break ;
    }
    array[hole] = temp ;
}


/**
 * Establish heap order property from an arbitrary
 * arrangement of items. Runs in linear time.
 */
template <class Comparable>
void BinaryHeap<Comparable>::buildHeap( vector<Comparable> Input)
{
    array = Input; // copy input array to private array;
    //currentSize = Input.size();
    currentSize = Input.size() -1 ;
    for( int i = currentSize / 2; i > 0; i-- )
        percolateDown( i );
}

template < class Comparable >
BinaryHeap <Comparable>::BinaryHeap(const vector <Comparable> & items ) : array (items.size() + 1 ), currentSize(items.size())
{
    for ( int i = 0 ; i< items.size() ; ++i )
    {
        array [ i + 1 ] = items [ i] ;
        
    }
    buildHeap(array) ;
}




template <class Comparable > // For Delete Max
//a is the array , i is the position to perculate down from
// n is the logical size of the array
void PercDown( vector <Comparable> & a ,int i , int n)
{
    int child ;
    Comparable tmp = a[i ] ;
    for( ; 2*i <= n-1; i = child)
    {
        child = 2 * i ;
        
        if ( child != n-1 && a[child +1].value > a [child].value)
        {
            child ++ ;         }
        if( a[child].value > tmp.value )
        {
            if( a[child].value > tmp.value )
                a[i] = a[ child] ;
            else //a[child].value == tmp.value
            {
                if (a[child].height > tmp.height )
                {
                    a[i] = a[ child] ;
                }
            }
        }
        
        else
            break ;
    }
    a[i] = tmp ;
}








template <class Comparable >
int BinaryHeap<Comparable> ::GetMax ()
{
    if(currentSize >= 1)
        return array[1].value ;
    else
        return 0 ;
}



template <class Comparable >
BinaryHeap<Comparable > :: BinaryHeap (int capacity)
{
    this->array.resize(capacity +1) ;
    currentSize = 0 ;
    Location.resize(capacity) ;
}


template<class Comparable>
int BinaryHeap<Comparable>:: ReturnPrevMax()
{
    return PrevMax ;
}
template<class Comparable>
void BinaryHeap<Comparable>:: SetPrevMax(int Max)
{
    PrevMax = Max ;
}






template <class Comparable >
void heapsort ( vector <Comparable> &a) // Küçğkten büyüğe sıralayacak
{
    //buildHeap
    for( int i = a.size()/2 ; i >0 ; i--)
    {
        PercDown(a, i, a.size()) ;
    }
     
    //sort
    for(int j = a.size() -1 ; j > 0 ; j--)
    {
        
        
        swap(a[1] , a[j] ) ; // swap max to the last pos
        //Osman [j] = a[j] ;
        PercDown(a, 1, j) ; //re form the heap
    }
    
}

template< class Comparable >
bool BinaryHeap<Comparable>::isEmpty()
{
    return (currentSize==0) ;
}


#endif /* BinaryHeap_hpp */
