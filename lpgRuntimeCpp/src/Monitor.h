#pragma once
struct Monitor
{
	virtual ~Monitor() = default;
	virtual  bool isCancelled() = 0;
};
