#include <iostream>
#include <cstdlib>

class Base
{
private:
	virtual void step1()
	{}
	virtual void step2()
	{}
	virtual void step3()
	{}
	virtual void step4() = 0;
	virtual void hookuse()
	{}
public:
	void TemplateMethod()
	{
		step1();
		step2();
		step3();
		step4();
		if (hookcheck())
			hookuse();
		else
			std::cout << "\nNo hook!\n";
	}
	bool hookcheck()
	{
		return true;
	}
};


class Derived :public Base
{
	void step1() override
	{
		std::cout << "class Derived Overriding Step1 .. Changing\n";
		
	}
	void step2() override
	{
		std::cout << "class Derived Overriding Step2 .. Changing\n";

	}
	void step3() override
	{
		std::cout << "class Derived Overriding Step3 .. Changing\n";

	}
	void step4() override
	{
		std::cout << "\nHave to override step4 -Pure virtual function";
	}
	void hookuse()
	{
		std::cout << "\nUsing Hook!\n";
	}
	bool hookcheck()
	{
		std::cout << "Hook Function--\n";
		return true;
	}
};

class DerivedTwo : public Base
{
	void step1() override
	{
		std::cout << "\n class Derived2 overriding step 1 ...";
	}
	void step2() override
	{
		std::cout << "\n class Derived2 overriding step 2 ...";
	}
	void step3() override
	{
		std::cout << "\n class Derived2 overriding step 3 ...";
	}
	void step4() override
	{
		std::cout << "\nHave to override step4 -Pure virtual function";
	}
	
};