#pragma once

class ReferenceCounter
{
public:
	ReferenceCounter() { countOfReference = 0; }
	int addReference() { return(++countOfReference); }
	int decreaseReference() { return(--countOfReference); };
	int getCount() { return(countOfReference); }
private:
	int countOfReference;
};