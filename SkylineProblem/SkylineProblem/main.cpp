//
//  main.cpp
//  CS300 HW4
//
//  Created by caghank on 11.12.2018.
//  Copyright © 2018 caghank. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
//#include "Heap.hpp"
#include "BinaryHeap.hpp"

using namespace std ;

int main(int argc, const char * argv[]) {
   
    ifstream reader ;
    reader.open("input1.txt") ;
    string takenInput ;
    string parsed ;
    reader>>takenInput ; // #number of buildings
    int NumberofBuildings = stoi(takenInput) ;
    
    
    enum EntryType { LEFT, RIGHT , NOTBOTH};
    struct Item
    {
        EntryType direction ;
        int value ;
        int height ;
        int readedOrder ;
        Item (int value2 = -1 , int height2 = -1 , int readorder = -1) :direction(NOTBOTH), value(value2), height(height2),readedOrder(readorder) {}
    };
    
    int leftCoordinate ;
    int readHeight ;
    int rightCoordinate ;
    vector<Item> LeftAndRights ;
    
    int order = 0 ;
    Item Dummy ;
    LeftAndRights.push_back(Dummy) ;
    
    while(getline(reader, takenInput))
    {
        if(takenInput != "")
        {
        ++order ;
        istringstream iss(takenInput) ;
        iss >> leftCoordinate;
        Item k ;
        k.direction = LEFT ;
        k.value =  int(leftCoordinate) ;
        iss >> readHeight ;
        k.height = readHeight ;
        k.readedOrder  = order ;
            
            
        LeftAndRights.push_back(k) ;

        iss >> rightCoordinate ;
        k.direction = RIGHT ;
        k.value =  int(rightCoordinate) ;
        k.readedOrder  = order ;
        LeftAndRights.push_back(k) ;
        
        }
    }
    heapsort(LeftAndRights) ;
    
    struct HeapNode {
        int value ;
        int label ;
    } ;
    
    HeapNode ObjectToExecute ;
    BinaryHeap<HeapNode> MainHeapForOutput(NumberofBuildings) ;
    for(int j = 1 ; j < LeftAndRights.size() ; j++)
    {
        ObjectToExecute.label = LeftAndRights[j].readedOrder ;
        ObjectToExecute.value  = LeftAndRights [j].height ;
        
        if(0 <LeftAndRights[j].value && j == 1)
        {
            cout<<"0 0" <<endl ;
        }
        
        
        if(LeftAndRights[j].direction == LEFT )
        {
            MainHeapForOutput.insert(ObjectToExecute,ObjectToExecute.label) ;
            
        }
        else if ( LeftAndRights[j].direction == RIGHT )
        {
            MainHeapForOutput.Remove(LeftAndRights[j].readedOrder) ;
        }
        
        //cout<<MainHeapForOutput.GetMax()<<endl ;
        //cout<<"ReturnPrevMax is :"<<MainHeapForOutput.ReturnPrevMax() <<endl ;
        if( MainHeapForOutput.GetMax()  != MainHeapForOutput.ReturnPrevMax())
        {
            cout<<LeftAndRights[j].value<<" "<<MainHeapForOutput.GetMax() <<endl  ;
        }
        
        MainHeapForOutput.SetPrevMax(MainHeapForOutput.GetMax()) ;
        
    }

    
        
    return 0;
}
