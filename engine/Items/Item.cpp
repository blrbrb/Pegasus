//
//  Item.cpp
//  Project Pegasus
//
//  Created by Eli Reynolds on 3/2/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#include "stdafx.h"
#include "Item.hpp"


Item::Item(unsigned value)
{
    this->value = value; 
    this->type = ItemTypes::REG;
   

}


Item::~Item()
{
    
    
    
}
