#pragma once
#include "BigIncludeFile.h"
#include "Build.h"

class MultiBuild : public Build
{
public:
	MultiBuild();
	MultiBuild(MultiBuild *a_Multibuild, Build *a_build);
	MultiBuild(Build *a_build1, Build *a_build2);
	MultiBuild(vector<Card*> a_buildlist);
	bool isMultiBuild() const;
	~MultiBuild();
};

