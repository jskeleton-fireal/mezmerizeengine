#include "propobject.h"
#include "../serializable/prop_container.h"

PropertyContainer MezPropertyObject::GetProperties()
{
	PropertyContainer props;
	DeclareProperties(&props);
	return props;
}