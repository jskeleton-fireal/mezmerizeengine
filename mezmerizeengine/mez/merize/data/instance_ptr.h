#pragma once

//a pointer that IS GUARUNTEED to have a valid value
//If you do not set a value (or is set to null) it will create its own and set the ptr to that.


template <class Type>
struct instance_ptr final
{
private:
	Type* m_it = 0;
	bool m_allocated = false; //should be freed
public:
	instance_ptr(Type* f_ref)
	{
		m_it = f_ref;
	}
	instance_ptr()
	{
		create();
	}
	~instance_ptr()
	{
		deallocate_if_needed();
	}
	Type* get() { return m_it; }
	void change(Type* f_nu,bool f_allocated = false)
	{
		deallocate_if_needed();
		m_it = f_nu;
		m_allocated = f_allocated;
	}
	operator Type* () { return get(); }
private:
	void create()
	{
		m_it = new Type();
		m_allocated = true;
	}
	void deallocate_if_needed()
	{
		if (m_allocated)
		{
			delete m_it;
		}
	}
};