#include "mez/merize/entity/BaseEntity.h"
#include "mez/merize/console/cmd.h"

CREATE_CONSOLECOMMAND_WFUNC(entity_create, 0)
{
	auto name = f_args->Get(1);
	if (!name.Valid()) return CONCMDRES_BADARGS;
	char entdesired[128];
	name.GetString(entdesired, 128);
	console_printf("Test: %s\n", entdesired);

	MezBaseEntity* ent = engine->CreateEntityByName<MezBaseEntity>(entdesired);
	if (!ent)
	{
	console_printf("Could not create an instance of \'%s\'\n", entdesired);
	return 0;

	}

	ent->Spawn();
	
	return 0;
}