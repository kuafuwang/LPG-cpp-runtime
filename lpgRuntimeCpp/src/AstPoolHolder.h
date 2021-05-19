#pragma once

#include "IAst.h"
#include "tuple.h"


struct pool_holder
{
	Tuple<IAst*> data;
	~pool_holder()
	{
		for (int i = 0; i < data.size(); ++i) {
			delete data[i];
		}
	}
};
