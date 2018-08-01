// Sorting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BaseSort.h"

int main()
{
	std::cout << "\n\n------------------BubbleSort--------------\n";
	std::string x = "21345";
	BubbleSort bs;
	bs.execute(x);
	std::cout << "\n\n------------------SelectionSort--------------\n";
	Selection s;
	s.execute(x);
    return 0;
}

