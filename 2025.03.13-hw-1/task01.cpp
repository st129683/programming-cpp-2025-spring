#include <iostream>

class ArrayList
{
private:
	int len;
	int* data;
	void init(int length = 10)
	{
		//(*this).len = len;
		this->len = length;
		this->data = (int*)malloc(sizeof(int) * length);
	}
	bool indexValid(int index)
	{
		return (0 <= index && index < this->len);
	}
	void expand(int n)
	{
		if (n <= 0)
		{
			return;
		}

		int new_len = this->len + n;
		int* new_data = (int*) malloc(sizeof(int) * new_len);
		if (new_data == nullptr)
		{
			return;
		}

		for (int i = 0; i < this->len; ++i)
		{
			new_data[i] = this->data[i];
		}
		for (int i = this->len; i < new_len; ++i)
		{
			new_data[i] = 0;
		}
		this->len = new_len;
		free(this->data);
		this->data = new_data;
	}

public:
	ArrayList(int len = 10)
	{
		this->init(len);
		for (int i = 0; i < this->len; ++i)
		{
			this->data[i] = 0;
		}
	}
	ArrayList(ArrayList& list)
	{
		//this->len = list.len;
		//this->data = list.data;
		this->init(list.len);
		for (int i = 0; i < list.len; ++i)
		{
			this->set(i, list.get(i));
		}
	}
	~ArrayList()
	{
		//for (int i = 0; i < this->len; ++i)
		//{
		//	this->data[i] = 0;
		//}
		free(this->data);
		//this->data = nullptr;
		//this->len = 0;
	}
	void randomize(int min = 10, int max = 99)
	{
		for (int i = 0; i < len; ++i)
		{
			this->data[i] = rand() % (max - min + 1) + min;
		}
	}
	void print()
	{
		for (int i = 0; i < this->len; ++i)
		{
			std::cout << this->data[i] << ' ';
		}
		std::cout << std::endl;
	}
	int get(int index)
	{
		if (indexValid(index))
		{
			return this->data[index];
		}
		return -1;
	}
	void set(int index, int value)
	{
		if (indexValid(index))
		{
			this->data[index] = value;
		}
	}
	int count()
	{
		return this->len;
	}

	void pushBack(int element)
	{
		int* new_data = (int*) malloc(sizeof(int) * (this->len + 1));
		if (new_data == nullptr)
		{
			return;
		}

		for (int i = 0; i < this->len; ++i)
		{
			new_data[i] = this->data[i];
		}
		new_data[this->len] = element;

		++(this->len);
		free(this->data);
		this->data = new_data;
	}
	void pushFront(int element)
	{
		int* new_data = (int*) malloc(sizeof(int) * (this->len + 1));
                if (new_data == nullptr)
                {
                        return;
                }

                for (int i = 0; i < this->len; ++i)
                {
                        new_data[i + 1] = this->data[i];
                }
                new_data[0] = element;

		++(this->len);
                free(this->data);
                this->data = new_data;
	}
	void insert(int index, int element)
	{
                int* new_data = (int*) malloc(sizeof(int) * (this->len + 1));
                if (! indexValid(index) || new_data == nullptr)
                {
                        return;
                }

                for (int i = 0; i < index; ++i)
                {
                        new_data[i] = this->data[i];
                }
                new_data[index] = element;
		for (int i = index + 1; i < this->len + 1; ++i)
		{
			new_data[i] = this->data[i - 1];
		}
		++(this->len);
                free(this->data);
                this->data = new_data;
        }
	int popBack()
	{
		int res = this->data[this->len - 1];
		int* new_data = (int*) malloc(sizeof(int) * (this->len - 1));
		if (new_data == nullptr)
		{
			return -1;
		}

		for (int i = 0; i + 1 < this->len; ++i)
		{
			new_data[i] = this->data[i];
		}
		--(this->len);
		free(this->data);
		this->data = new_data;

		return res;
	}
	int popFront()
	{
		int res = this->data[0];
                int* new_data = (int*) malloc(sizeof(int) * (this->len - 1));
                if (new_data == nullptr)
                {
                        return -1;
                }

                for (int i = 0; i + 1 < this->len; ++i)
                {
                        new_data[i] = this->data[i + 1];
                }
		--(this->len);
                free(this->data);
                this->data = new_data;

                return res;
	}
	int extract(int index)
	{
		int* new_data = (int*) malloc(sizeof(int) * (this->len - 1));
		if (! indexValid(index) || new_data == nullptr)
		{
			return -1;
		}
		int res = this->data[index];
		for (int i = 0; i < index; ++i)
		{
			new_data[i] = this->data[i];
		}
		for (int i = index + 1; i < this->len; ++i)
		{
			new_data[i - 1] = this->data[i];
		}
		--(this->len);
		free(this->data);
		this->data = new_data;
	}
	void reverse(int start, int end)
	{
		for (int i = start, j = end; i < j; ++i, --j)
		{
			std::swap(this->data[i], this->data[j]);
		}
	}
	int sum()
	{
		int res = 0;
		for (int i = 0; i < this->len; ++i)
		{
			res += this->data[i];
		}
		return res;
	}
	int secondMax()
	{
		int mx1 = this->data[0];
		int mx2 = this->data[0];
		for (int i = 1; i < this->len; ++i)
		{
			if (mx1 < this->data[i])
			{
				mx2 = mx1;
				mx1 = this->data[i];
			}
		}
		return mx2;
	}
	int lastMinIndex()
	{
		int res = 0;
		for (int i = 1; i < this->len; ++i)
		{
			if (this->data[res] >= this->data[i])
			{
				res = i;
			}
		}
		return res;
	}
	void shift(int k)
	{
		k = (k % this->len + this->len) % this->len;
		int* new_data = (int*) malloc(sizeof(int) * this->len);
		if (new_data == nullptr)
		{
			return;
		}
		for (int i = 0; i < k; ++i)
		{
			new_data[i] = this->data[this->len - k + i];
		}
		for (int i = k; i < this->len; ++i)
		{
			new_data[i] = this->data[i - k];
		}
		free(this->data);
		this->data = new_data;
	}
	int countOdd()
	{
		int res = 0;
		for (int i = 0; i < this->len; ++i)
		{
			if (this->data[i] % 2 != 0)
			{
				++res;
			}
		}
		return res;
	}
	int sumEven()
	{
		int res = 0;
		for (int i = 0; i < this->len; ++i)
		{
			if (this->data[i] % 2 == 0)
			{
				res += this->data[i];
			}
		}
		return res;
	}
};

int max(ArrayList list)
{
	int mx = list.get(0);
	for (int i = 0; i < list.count(); ++i)
	{
		mx = (mx > list.get(i) ? mx : list.get(i));
	}
	return mx;
}

int main(int argc, char* argv[])
{
	ArrayList list(10);
	list.randomize();
	list.print();
	std::cout << max(list) << std::endl;
	return 0;
}
