#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
using namespace std;
std::ifstream inputFile;

void writeVectorToFile(const std::vector<std::vector<int>> &content,
		const std::string &filename) {
	std::ofstream outputFile(filename);

	if (!outputFile.is_open()) {
		std::cout << "Error opening the file: " << filename << std::endl;
		return;
	}

	for (const auto &inner_vec : content) {
		for (int val : inner_vec) {
			outputFile << val << " ";
		}
		outputFile << std::endl;
	}

	outputFile.close();
	std::cout << "Vector data has been written to the file: " << filename
			<< std::endl;
}

std::vector<std::vector<int>> getUniqueValuesPerColumn(
		const std::vector<std::vector<int>> data) {
	std::vector<std::vector<int>> datacopy;

	for (const auto &inner_vec : data) {
		std::set<int> unique_elements(inner_vec.begin(), inner_vec.end());
		datacopy.emplace_back(unique_elements.begin(), unique_elements.end());
	}

	return datacopy;


}


//function for transposing the dataset ( lines become rows and viseversa)
//Input: vector representing the dataset
//Output: vector of the transposed dataset
std::vector<std::vector<int>> transposeData(
		std::vector<std::vector<int>> data) {
	std::vector<std::vector<int>> transposedData(data[0].size(),
			std::vector<int>(data.size()));
	for (size_t i = 0; i < data.size(); ++i) {
		for (size_t j = 0; j < data[i].size(); ++j) {
			transposedData[j][i] = data[i][j];
		}
	}

	return transposedData;
}


//Function for reading the datasets.
//input: Integer Dataset  _T.dat
//output: The dataset in a vector each vector correspond to a column in the dataset
std::vector<std::vector<int>> readFile(string dataset) {
	std::ifstream inputFile;
	inputFile.open(dataset,
			std::ios::binary);

	if (!inputFile.is_open()) {
		std::cerr << "Error opening the file." << std::endl;
	}

	std::vector<std::vector<int>> data; // Vector to store all the data

	bool isFirstRow = true; // Flag to ignore the first row

	std::string line;
	while (std::getline(inputFile, line)) {
		if (isFirstRow) {
			isFirstRow = false;
			continue; // Skip the first row
		}

		std::istringstream iss(line);
		int value;
		std::vector<int> rowValues;

		while (iss >> value) {
			rowValues.push_back(value);
		}

		data.push_back(rowValues); // Store the row data into the main vector
	}


	// Transpose the data vector


	/*	for(std::vector<int> col: data) {

	}
	std::unordered_set<int> uniqueValues(data.begin(), data.end());

	std::vector<std::vector<int>> uniqueValues;
	std::copy(uniqueValues.begin(), uniqueValues.end(),
	 std::back_inserter(uniqueVector));*/

	inputFile.close();

	return data;

}



std::vector<std::vector<int>> IS_Binrization(
		std::vector<std::vector<int>> dataset,
		std::vector<std::vector<int>> transposeddata,
		std::vector<std::vector<int>> UniqueValues) {
	std::vector<std::vector<int>> IS_data;

	for (int i = 0; i < UniqueValues.size(); i++) { //std::vector<int> col : UniqueValues
		for (int j = 0; j < UniqueValues.at(i).size(); j++) {  //int value : col
			std::vector<int> smallerOrEqual;
			std::vector<int> higherOrEqual;

			for (int y = 0; y < transposeddata.at(i).size(); y++) {

				if (transposeddata.at(i).at(y) <= UniqueValues.at(i).at(j)) {
					smallerOrEqual.push_back(1);
				} else {
					smallerOrEqual.push_back(0);
				}

				if (transposeddata.at(i).at(y) >= UniqueValues.at(i).at(j)) {
					higherOrEqual.push_back(1);
				} else {
					higherOrEqual.push_back(0);
				}

				}

			IS_data.push_back(smallerOrEqual);
			IS_data.push_back(higherOrEqual);
		}


	}

	return IS_data;
}


std::vector<std::string> writeFeaturesNames(int FeaturesSize) {
	std::vector<std::string> mStrings;
	for (int i = 0; i < FeaturesSize; ++i) {
		mStrings.push_back("m" + std::to_string(i));
	}

	return mStrings;
}

int writeContentInFile(string OutputFileName,
		std::vector<std::vector<int>> Binarized_dataset, int Ncolumns) {

	// Open the file for writing
	std::ofstream outfile(OutputFileName);

	if (!outfile.is_open()) {
		std::cerr << "Error opening the file " << OutputFileName << std::endl;
		return 1;
	}

	// Write the vector of vectors to the file


	std::vector<std::string> mStrings = writeFeaturesNames(Ncolumns);
	;
	for (const auto &m : mStrings) {
		outfile << m << " ";
	}
	outfile << "\n"; // Separate the "m" strings from the dataset with a newline


	for (const auto &innerVector : Binarized_dataset) {
		for (size_t i = 0; i < innerVector.size(); ++i) {
			outfile << innerVector[i];
			if (i < innerVector.size() - 1) {
				outfile << " "; // Separate elements within the inner vector with spaces
			}
		}
		outfile << "\n"; // Separate outer vectors with newlines
	}

	// Close the file
	outfile.close();

	std::cout << "Data has been written to " << OutputFileName << std::endl;
}

string getNewFileName(string inputPath) {
	std::string filename;
	size_t slashPos = inputPath.find_last_of('/');
	if (slashPos != std::string::npos) {
		filename = inputPath.substr(slashPos + 1);
	} else {
		filename = inputPath;
	}

	size_t extensionPos = filename.find_last_of('.');
	if (extensionPos != std::string::npos) {
		filename = filename.substr(0, extensionPos);
	}

	return filename + "_IS_BIN.dat";
}

int main(int argc, char *argv[]) {

	string path = string(argv[1]);//"/home/bekkouc221/Documents/dev/CPP/data/NT/NT_T.dat"
	bool showResults = false;

	if (argc == 3 && std::string(argv[2]) == "--show") {
		showResults = true;
	}

	std::vector<std::vector<int>> data = readFile(
			path);
	std::vector<std::vector<int>> transposedData = transposeData(data);

	std::vector<std::vector<int>> unique_percol = getUniqueValuesPerColumn(
			transposedData);
	std::vector<std::vector<int>> IS_data = IS_Binrization(data, transposedData,
			unique_percol);



	std::vector<std::vector<int>> getDataBack = transposeData(IS_data);
	if (showResults) {
		//feature names
		std::vector<std::string> mStrings = writeFeaturesNames(IS_data.size());
		for (const std::string &str : mStrings) {
			cout << str << " ";
		}
	cout << endl;

		//Bins
		for (const auto &row : getDataBack) {
			for (int val : row) {
				std::cout << val << " ";
			}
			std::cout << std::endl;
		}

	}



//	writeContentInFile(getNewFileName("."), getDataBack, IS_data.size());

	return 0;
}
