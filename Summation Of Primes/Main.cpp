#include <iostream>
#include <thread>
#include <future>
#include <time.h>
#include <vector>
#include <string>
using std::vector;
using std::shared_future;

bool isPrimeV2(long long number) {
	int count = 2;
	if (number < 2) {
		return false;
	}
	if (number == 2) {
		return true;
	}
	for (int i = 2; i <= number / 2; i++) {
		if (number % i == 0) {
			count++;
		}
	}
	if (count == 2) {
		return true;
	}
	else {
		return false;
	}
}

long doWork(long index, int inc) {
	//std::cout << "Starting at index " << index << std::endl;
	long tally = 0;
	if (index < 2) {
		tally += 2;
	}
	long privateIndex = index;
	if (privateIndex % 2 == 0) {
		privateIndex += 1;
	}
	for (long i = privateIndex; i < privateIndex + inc; i += 2) {
		if (isPrimeV2(i)) {
			tally += i;
		}
	}
	return tally;
}


void Solve() {
	long long answer = 0;
	//answer = doWork(0, 100000);
	std::cout << "Creating threads...\n";
	int max = 2000000;
	int threadCount = 100;
	int increment = max / threadCount;
	long start = 0;
	int returnCount = 0;
	std::vector<std::shared_future<long>> threads;
	for (int i = 0; i < threadCount; i++) {
		std::shared_future<long> ret = std::async(&doWork, start, increment);
		threads.push_back(ret);
		start += increment;
	}
	std::cout << "Getting values from threads...\n";
	for (vector<shared_future<long>>::iterator i = threads.begin(); i < threads.end(); i++) {
		shared_future<long> ret = *i;
		answer += ret.get();
		std::cout << "Got return from thread " << returnCount << std::endl;
		returnCount++;
	}
	std::cout << "Answer: " << answer << std::endl;
}

int main()
{
	clock_t tStart = clock();
	Solve();
	double time = (clock() - tStart) / CLOCKS_PER_SEC;
	std::cout << "Solve time: " << time << " secs.\n";
	return 0;
}