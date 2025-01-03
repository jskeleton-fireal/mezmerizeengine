#include "mez/merize/entity/BaseEntity.h"
#include "mez/merize/console/cmd.h"

int __cmdfunc__entity_create(ConCommandArgs* f_args); ConsoleCommand __cmd__entity_create = ConsoleCommand("entity_create", CONTHING_FLAG_CONBALL, __cmdfunc__entity_create); int __cmdfunc__entity_create(ConCommandArgs* f_args)
{
	auto name = f_args->Get(1);
	if (!name.Valid()) return CONCMDRES_BADARGS;
	char entdesired[128];
	name.GetString(entdesired, 128);
	console_printf("attempting to create an instance of: %s\n", entdesired);

	MezBaseEntity* ent = engine->CreateEntityByName<MezBaseEntity>(entdesired);
	if (!ent)
	{
	console_printf("Could not create an instance of \'%s\'\n", entdesired);
	return 0;

	}

	ent->Spawn();
	
	return 0;
}

CREATE_CONSOLECOMMAND_WFUNC(entity_destroy, CONTHING_FLAG_CONBALL)
{
	auto name = f_args->Get(1);
	if (!name.Valid()) return CONCMDRES_BADARGS;
	char entdesired[128];
	name.GetString(entdesired, 128);
	console_printf("destroying the first instance of: %s\n", entdesired);

	MezBaseEntity* ent = MezBaseEntity::Find_Typeless(entdesired);
	if (!ent)
	{
		console_printf("Could not find an instance of \'%s\'\n", entdesired);
		return 0;

	}

	ent->Destroy();
	return 0;
}