#pragma once

class PropertyContainer;

//class that uses properties
class MezPropertyObject
{
public:
	PropertyContainer GetProperties();
protected:
	virtual void DeclareProperties(PropertyContainer* vector) { }
};