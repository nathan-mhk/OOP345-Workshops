// Workshop 9 - Multi-Threading, Thread Class

/**
 * Name:  Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-07-19
 * I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider  
*/

#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <thread>
#include "ProcessData.h"

namespace seneca
{
	// The following function receives array (pointer) as the first argument, number of array 
	//   elements (size) as second argument, divisor as the third argument, and avg as fourth argument. 
	//   size and divisor are not necessarily same. When size and divisor hold same value, avg will 
	//   hold average of the array elements. When they are different, avg will hold a value called 
	// 	 as average-factor. For part 1, you will be using same value for size and double. Use of 
	//   different values for size and divisor will be useful for multi-threaded implementation in part-2.
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++)
		{
			avg += arr[i];
		}
		avg /= divisor;
	}

	// The following function receives array (pointer) as the first argument, number of array elements  
	//   (size) as second argument, divisor as the third argument, computed average value of the data items
	//   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the 
	//   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of 
	//   the array elements. When they are different, var will hold a value called as variance factor. 
	//   For part 1, you will be using same value for size and double. Use of different values for size 
	//   and divisor will be useful for multi-threaded implementation in part-2.
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++)
		{
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data != nullptr && num_threads>0 && averages && variances && p_indices;
	}

	// The following constructor of the functor receives name of the data file, opens it in 
	//   binary mode for reading, reads first int data as total_items, allocate memory space 
	//   to hold the data items, and reads the data items into the allocated memory space. 
	//   It prints first five data items and the last three data items as data samples.
	ProcessData::ProcessData(const std::string& filename, int n_threads) {
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.
		std::ifstream file(filename, std::ios::in | std::ios::binary);

		if (file.good()) {
			// `char` is 1B
			char cPtr[sizeof(int)]{};

			// First 4B is the total number of data items
			file.read(cPtr, sizeof(int));

			// Reinterpret the char* as an int* and dereference it
			total_items = *(reinterpret_cast<int*>(cPtr));

			data = new int[total_items];

			for (int i = 0; file.good() && i < total_items; ++i) {
				file.read(cPtr, sizeof(int));
				data[i] = *(reinterpret_cast<int*>(cPtr));
			}
		}

		file.close();

		std::cout << "Item's count in file '"<< filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
		          << data[total_items - 3] << ", " << data[total_items - 2] << ", "
		          << data[total_items - 1] << "]\n";

		// Following statements initialize the variables added for multi-threaded 
		//   computation
		num_threads = n_threads; 
		averages = new double[num_threads] {};
		variances = new double[num_threads] {};
		p_indices = new int[num_threads+1] {};
		for (int i = 0; i < num_threads+1; i++)
			p_indices[i] = i * (total_items / num_threads);
	}

	ProcessData::~ProcessData() {
		delete[] data;
		delete[] averages;
		delete[] variances;
		delete[] p_indices;
	}

	// TODO Improve operator() function from part-1 for multi-threaded operation. Enhance the
	//   function logic for the computation of average and variance by running the
	//   functions `computeAvgFactor` and `computeVarFactor` in multiple threads.
	// The function divides the data into a number of parts, where the number of parts is
	//   equal to the number of threads. Use multi-threading to compute average-factor for
	//   each part of the data by calling the function `computeAvgFactor`. Add the obtained
	//   average-factors to compute total average. Use the resulting total average as the
	//   average value argument for the function computeVarFactor, to compute variance-factors
	//   for each part of the data. Use multi-threading to compute variance-factor for each
	//   part of the data. Add computed variance-factors to obtain total variance.
	// Save the data into a file with filename held by the argument `target_file`.
	// Also, read the workshop instruction.
	int ProcessData::operator()(const std::string& fileName, double& avg, double& var) {
		// Average
		auto avgFn = std::bind(computeAvgFactor, std::placeholders::_1, std::placeholders::_2, total_items, std::placeholders::_3);

		std::vector<std::thread> threads;
		for (int i = 0; i < num_threads; ++i) {
			threads.push_back(
				std::thread(
					avgFn,
					&data[p_indices[i]],	// Address of the first element of each partition
					p_indices[i + 1] - p_indices[i],	// Number of elements in the partition
					std::ref(averages[i])
				)
			);
		}

		for (std::thread& thread : threads) {
			thread.join();
		}

		for (int i = 0; i < num_threads; ++i) {
			avg += averages[i];
		}

		// Variance
		auto varFn = std::bind(computeVarFactor, std::placeholders::_1, std::placeholders::_2, total_items, avg, std::placeholders::_3);

		threads.clear();
		for (int i = 0; i < num_threads; ++i) {
			threads.push_back(
				std::thread(
					varFn,
					&data[p_indices[i]],	// Address of the first element of each partition
					p_indices[i + 1] - p_indices[i],	// Number of elements in the partition
					std::ref(variances[i])
				)
			);
		}

		for (std::thread& thread : threads) {
			thread.join();
		}

		for (int i = 0; i < num_threads; ++i) {
			var += variances[i];
		}

		// Write to file
		std::fstream file(fileName, std::ios::out | std::ios::binary | std::ios::trunc);

		if (file.good()) {
			char cPtr[sizeof(int)]{};

			// The other way around, reinterpret cPtr as an int* and dereference it
			*(reinterpret_cast<int*>(cPtr)) = total_items;
			file.write(cPtr, sizeof(int));

			for (int i = 0; file.good() && i < total_items; ++i) {
				*(reinterpret_cast<int*>(cPtr)) = data[i];
				file.write(cPtr, sizeof(int));
			}
		}

		file.close();
		return 0;
	}
}
