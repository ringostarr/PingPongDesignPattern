#include <iostream>
#include <cstdlib>
#include <vector>

class SortBase {
private:
	 std::vector<int> initialize(std::string x)
	{
		std::cout << "\nBase class Initialize called -Convert string to Int vector\n";
		std::vector<int> arr;
		char *c = const_cast<char*>(x.c_str());
		for (int i = 0; i < x.length(); i++)
		{
			arr.push_back(c[i]-'0');
		}
		return arr;
	}

	virtual std::vector<int> sort(std::vector<int> arr) = 0;
	
	virtual void display(std::vector<int> arr)
	{
		std::cout << "\nBase Class Display array:";
		for (int i = 0; i < arr.size(); i++)
			std::cout << arr[i] << ",";
		std::cout << "\n";
	}
public:
	 void execute(std::string abc) 
	{
		std::cout << "\n Calling Template Method--\n";
		std::vector<int> narr = initialize(abc);
		narr = sort(narr);
		display(narr);
	}
};


class BubbleSort:public SortBase
{
private:
	void swap(int *xp, int *yp)
	{
		int temp = *xp;
		*xp = *yp;
		*yp = temp;
	}
	std::vector<int> sort(std::vector<int> arr) override
	{
		std::cout << "\nDervied class(Bubblesort) Sort called \n";
		int i, j;
		int n = arr.size();
		for (i = 0; i < n-1; i++)   
			for (j = 0; j < n - i - 1; j++)
				if (arr[j] > arr[j + 1])
					swap(&arr[j], &arr[j + 1]);
		return arr;
	}
};
class Selection :public SortBase
{
private:
	void swap(int *xp, int *yp)
	{
		int temp = *xp;
		*xp = *yp;
		*yp = temp;
	}
	std::vector<int> sort(std::vector<int> arr) override
	{
		std::cout << "Dervied Class(SelectionSort) sort function called \n";
			int i, j, min_idx;
			int n = arr.size();
			
			for (i = 0; i < n - 1; i++)
			{
				min_idx = i;
				for (j = i + 1; j < n; j++)
					if (arr[j] < arr[min_idx])
						min_idx = j;
				swap(&arr[min_idx], &arr[i]);	
			}
			return arr;
	}
	void display(std::vector<int> arr) override
	{
		std::cout << "\nDerived class(SelectionSort) display function called \n";
		for (int i = 0; i < arr.size(); i++)
			std::cout << arr[i] << " ";
		std::cout << "\n";
	}
};
