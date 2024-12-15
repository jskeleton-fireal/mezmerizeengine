#pragma once
#include "efactory.h"

//internal efac identifier
class efac_INTERNAL
{
public:
	struct efac_it2
	{
		stdvector< efactory_t*> factories;
	};
public:
	//Need to ensure this gets initialized before we start adding stuff to it
	efac_it2* fac = 0;
	void upload(efactory_t* ref)
	{
		if (!fac)
		{
			fac = new efac_it2();
		}
		//creating a new one here to make sure it doesnt get freed (This happens sometimes and im not sure why)
		efactory_t* clone = new efactory_t(*ref);
		fac->factories.push_back(clone);
	}
};

extern efac_INTERNAL the_efac_internal;