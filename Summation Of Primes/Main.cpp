//A program to calculate the sum of all prime numbers below two million.
//https://github.com/Kango-Senpai/euler-10
//This code is a solution to project euler problem #10. This is intended solely as a learning tool.
#include <iostream>
#include <thread>
#include <future>
#include <time.h>
#include <vector>
#include <string>
#include <cmath>
using std::vector;
using std::shared_future;

bool isPrime(long long number) {
	//Loop up until the floored square root of the number and count the multiples.
	long x = floor(sqrt(number));
	int count = 2;
	if (number < 2) {
		return false;
	}
	if (number == 2) {
		return true;
	}
	for (int i = 2; i <= x; i++) {
		if (number % i == 0) {
			count++;
		}
	}
	//If the number has more than 2 multiples, it is not prime.
	if (count == 2) {
		return true;
	}
	else {
		return false;
	}
}
long childThread(long work) {
	//Simple child thread for doing the isPrime calculation.
	if (isPrime(work)) {
		return work;
	}
	else {
		return 0;
	}
}
void Solve() {//18-21 secs

	vector<long> pool;
	vector<long>::iterator backwardIndex;
	vector<shared_future<long>> threads;
	int threadCount = 16;//One million must be divisible by the thread count.
	//Create a work pool.
	for (long i = 1; i < 2000000; i += 2) {
		pool.push_back(i);
	}
	long long answer = 2;//Two is prime, but is not in our work pool. Start the answer at two.
	while (!pool.empty()) {
		
		for (int i = 0; i < threadCount; i++) {
			backwardIndex = pool.end() - 1;//Set the iterator to the last value in the vector.
			shared_future<long> ret = std::async(&childThread, *backwardIndex);//Assign the child thread work from the pool.
			pool.erase(backwardIndex);//Remove work from the pool.
			threads.push_back(ret); //Add shared future to vector for later value retrieval.
		}
		for (vector<shared_future<long>>::iterator i = threads.begin(); i < threads.end(); i++) {
			shared_future<long> ret = *i;//Create a shared future object by pointing to iterator 'i'.
			answer += ret.get();//Get the value from the task.
		}
		threads.clear();//Clear threads vector.
	}
	std::cout << "The answer is: " << answer << std::endl;//...Print the answer.
}


int main()
{
	clock_t tStart = clock();//New clock_t instance to time the solve.
	Solve();
	double time = (clock() - tStart) / CLOCKS_PER_SEC;//Calculate the solve time and write to the console.
	std::cout << "Solve time: " << time << " secs.\n";
	return 0;
}