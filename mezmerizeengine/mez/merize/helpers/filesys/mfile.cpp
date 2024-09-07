#include "mfile.h"
#if MFILE_ENABLED
#include <iostream>
#include <cassert>
#include <fstream>

class MFile_Internal {
public:
	unsigned char* m_data;
	MFile_Internal(int expectedsize)
	{
		m_data = new unsigned char[expectedsize];
	}
	~MFile_Internal()
	{
		delete[] m_data;
	}
};

MFile::MFile(const char* f_filename, int f_expected_size)
{
	std::ifstream file;
	file.open(f_filename);
	assert(file.good());
	if (!f_expected_size)
	{
		f_expected_size = file.;
	}

	m_ptr = new MFile_Internal(f_expected_size);
}

MFile::~MFile()
{
	close();
}

void MFile::close()
{
	delete m_ptr;
	m_ptr = 0;
}
#endif