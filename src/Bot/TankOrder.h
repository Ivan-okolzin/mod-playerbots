#ifndef PLAYERBOT_TANK_ORDER_H
#define PLAYERBOT_TANK_ORDER_H

#include "ObjectGuid.h"
#include <vector>

class Group;

namespace TankOrder
{
    std::vector<ObjectGuid> Get(Group const* group);
}

#endif
