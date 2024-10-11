#pragma once


#define DECLARE_CLASS(vBaseClass) private: typedef vBaseClass BaseClass;
#define DECLARE_PUBLIC_STRCLASSNAME(vClass) public: virtual const char* GetClassName() {return #vClass;}
#define DECLARE_PUBLIC_STRDISPLAYNAME(vDisplayName) public: virtual const char* GetDisplayName() {return vDisplayName;}


#define DECLARE_ENTITY(vClass) public: virtual const char* GetClassname(); private: