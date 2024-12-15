#include "stock_entball.h"
#define ENTITY_CLASSNAME_TO_FACTORY_NAME(vEClassType) ____fc##vEClassType
#define EXTERNAL_EFAC(vEClassType) extern efactory_t ENTITY_CLASSNAME_TO_FACTORY_NAME(vEClassType)
#define efac_name ENTITY_CLASSNAME_TO_FACTORY_NAME
#define add(CLASSNAME) EXTERNAL_EFAC(CLASSNAME); eball.append(&efac_name(CLASSNAME))

EntBall get_stock_entball()
{
    EntBall eball;

    add(MezEntityEnvironment);

    return eball;
}
