#include "stock_conball.h"

//This sucks btw. This is ONLY FOR BASE MEZMERIZE COMMS AND WHATNOT!!!! so dont worry YOU will enver have to put up with this garbage
//for future BASE comms and whatnot, use ONE FILE.

#include <mez/merize/data/entity_comms.cpp>

#define get_com_name(vRealName) __cmd__##vRealName
#define extern_com(vRealName) extern ConsoleCommand get_com_name(vRealName)

extern_com(dump_factories);

ConBall get_stock_conball()
{
    ConBall ball;
    ball.append(&get_com_name(entity_create));
    ball.append(&get_com_name(entity_destroy));
    ball.append(&get_com_name(dump_factories));
    return ball;
}
