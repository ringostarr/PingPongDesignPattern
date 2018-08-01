// TemplateMethodPatt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TemplateMethodPatt.h"

int main()
{
	Derived d;
	d.TemplateMethod();
	DerivedTwo d2;
	d2.TemplateMethod();
    return 0;
}

