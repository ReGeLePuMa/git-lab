#include <bits/stdc++.h>

using namespace std;

int random_number1()
{
	srand(time(NULL));
	return rand();
}

int random_number2()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distribution(0, INT_MAX);
	return distribution(gen);
}

int random_number3()
{
	ifstream fin("/dev/random", ios::binary);
	if(!fin)
	{
		cerr<<"Error opening '/dev/random'\n";
		exit(1);
	}
	int nr;
	fin.read((char*)&nr, sizeof(nr));
	fin.close();
	return abs(nr);
}

int random_number4()
{
	vector<int> numbers(1000000);
	iota(numbers.begin(), numbers.end(), 1);
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(numbers.begin(), numbers.end(), default_random_engine(seed));
	return numbers[0];
}


function<int()> random_number5(int seed)
{
	static unsigned int rseed = seed;
	return [&]() {
		rseed = (rseed * 1103515245 + 12345) % INT_MAX;
		return rseed;
	};
}

int main(int argc, char** args)
{
	if(argc < 2)
	{
		cerr<<"Usage: "<<args[0]<<" <nr_method> [seed_for_5th_method]\n";
		exit(1);
	}
	int method = atoi(args[1]);
	if(method > 5 || method < 1)
	{
		cerr<<"Invalid method number.\n";
		exit(1);
	}
	int seed = argc >= 3 ? atoi(args[2]) : 696969;
	map<int, function<int()>> random_strategy = {
                {1, random_number1},
                {2, random_number2},
                {3, random_number3},
                {4, random_number4},
                {5, random_number5(seed)}
	};
	cout<<"Random number from method "<<method<<" is "<<random_strategy[method]()<<"\n";
	return 0;
}
