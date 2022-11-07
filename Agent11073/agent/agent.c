//
//  agent.c
//  Agent11073
//
//  Created by Hugo Arevalo on 6/11/22.
//

#include "agent.h"

struct MDS CreateAgent(void) {
    struct MDS agent;
    agent.Handle = 0;
    agent.SystemType = 2438;
    
    agent.SystemModel.manufacturer.length = 1;
    intu8 manufacturerValue[1] = {0x09};
    agent.SystemModel.manufacturer.value = manufacturerValue;
    
    agent.SystemModel.model_number.length = 1;
    intu8 modelNumberValue[1] = {0x28};
    agent.SystemModel.model_number.value = modelNumberValue;
    
    agent.SystemId.length = 8;
    intu8 systemIdValue[8] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    agent.SystemId.value = systemIdValue;
}
