//
//  Status.h
//  tester
//
//  Created by Zach Waterson on 3/26/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#ifndef __tester__Status__
#define __tester__Status__

#include <iostream>

class Status {
private:
    int statusPower; //amount status does
    int turnsToGo; //turns until wears off
    
public:
    virtual void actStatusOnTarget();
    
};

#endif /* defined(__tester__Status__) */
