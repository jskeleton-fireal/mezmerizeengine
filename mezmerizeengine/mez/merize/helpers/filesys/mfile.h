#pragma once

//unfinished. dont let the compiler know!
#define MFILE_ENABLED 0

#if MFILE_ENABLED
//A file :)
class MFile
{
	enum
	{
		MFILE_DETERMINE_SIZE=0
	};
public:
	MFile(const char* f_filename,int f_expected_size = MFILE_DETERMINE_SIZE);
	~MFile();
	void close();
private:
	class MFile_Internal;
	MFile_Internal* m_ptr;
};

#endif