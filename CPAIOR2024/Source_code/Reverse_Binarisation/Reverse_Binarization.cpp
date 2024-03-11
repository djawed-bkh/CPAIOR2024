#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include <utility>
#include <chrono>
using namespace std;
std::ifstream inputFile;
using namespace std::chrono;

struct Interval {
	int first;
	int second;
};

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
	inputFile.open(dataset, std::ios::binary);

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

//Interval inverserPaire(const Interval &p) {
//	Interval NewInterval;
//	NewInterval.first = p.second;
//	NewInterval.second = p.first;
//	return NewInterval;
//}
Interval inverserPaire(const Interval &interval) {
	Interval newInterval;
	newInterval.first = interval.second;
	newInterval.second = interval.first;
	return newInterval;
}

Interval IdToValues(std::vector<Interval> &Mapping, Interval &tempPair) {
	// Recherche de la première paire dans Mapping avec le même premier élément que tempPair
	for (const auto &pair : Mapping) {
		if (pair.first == tempPair.first) {
			// Mise à jour du premier élément de tempPair avec le deuxième élément de la paire trouvée
			tempPair.first = pair.second;
			break; // On arrête la recherche après avoir trouvé la correspondance
		}
	}

	// Recherche de la deuxième paire dans Mapping avec le même deuxième élément que tempPair
	for (const auto &pair : Mapping) {
		if (pair.first == tempPair.second) {
			// Mise à jour du deuxième élément de tempPair avec le deuxième élément de la paire trouvée
			tempPair.second = pair.second;
			break; // On arrête la recherche après avoir trouvé la correspondance
		}
	}

	return tempPair;
}

std::vector<std::vector<int> > ReadSolutionFile(string Path) {
	// Open the input file
	std::ifstream inputFile(Path);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open the file.\n";

	}

	// Create a vector to store numbers from each line
	std::vector<std::vector<int>> numbersVector;

	std::ifstream fichierEntree(Path);

	// Vérification si le fichier est ouvert avec succès
	if (!fichierEntree.is_open()) {
		std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;

	}

	std::string ligne;




	  while (std::getline(fichierEntree, ligne)) {
		// Vérification si la ligne commence par "solution "
		if (ligne.compare(0, 9, "solution ") == 0) {
			std::istringstream iss(ligne);
			std::vector<int> listeEntiers;

			// Ignorer le mot "solution"
			std::string mot;
			iss >> mot;

			// Extraction des entiers de la ligne
			int nombre;
			while (iss >> nombre) {
				listeEntiers.push_back(nombre);
			}

			// Ajout de la liste au vecteur principal
			numbersVector.push_back(listeEntiers);
		}
	}
	// Fermeture du fichier
	fichierEntree.close();
//	cout << numbersVector.at(1).at(1) << endl;
	return numbersVector;


}


std::vector<std::vector<Interval>> IntervalPatterns_Generation(
		std::vector<std::vector<int>> Solution_closedpattern,
		std::vector<std::vector<int>> UniqueValues) {


	//1- delemiter les valeurs des attributs en fonction des valeurs uniques:

	std::vector<Interval> UniqueValuesSize;
	Interval temp;
	for (int i = 0; i < UniqueValues.size(); i++) {

		if (i == 0) {
			temp.first = 0;
			temp.second = (UniqueValues.at(i).size() * 2) - 1;
			UniqueValuesSize.emplace_back(temp);
		} else {

			temp.first = temp.second + 1;
			temp.second = temp.first + ((UniqueValues.at(i).size() * 2) - 1);
			UniqueValuesSize.emplace_back(temp);

		}


	}


//	for (const auto &pair : UniqueValuesSize) {
//		std::cout << "(" << pair.first << ", " << pair.second << ")\n";
//	}

	std::vector<Interval> Mapping;


	int index = 0;
	for (int i = 0; i < UniqueValues.size(); i++) {
		for (int j = 0; j < UniqueValues.at(i).size(); j++) {
			Interval temp;

			temp.first = index;
			temp.second = UniqueValues.at(i).at(j);
			Mapping.emplace_back(temp);
			index += 1;
			temp.first = index;
			Mapping.emplace_back(temp);
			index += 1;

		}

	}
//	for (const auto &pair : Mapping) {
//		std::cout << "(" << pair.first << ", " << pair.second << ")\n";
//	}

	auto start = std::chrono::high_resolution_clock::now();
// former les intervalles
	std::vector<std::vector<Interval>> IP;

	for (int IndexSol = 0; IndexSol < Solution_closedpattern.size();
			++IndexSol) {
		std::vector<Interval> OneIntervalPattern;

		std::vector<std::vector<int>> BinsInATT;

		// Recuperer les bins pour chaque attribut
		for (int att = 0; att < UniqueValuesSize.size(); ++att) {
			std::vector<int> tempvect;

			const auto &solutionBins = Solution_closedpattern.at(IndexSol);
			for (int bin : solutionBins) {
				if (bin >= UniqueValuesSize.at(att).first
						&& bin <= UniqueValuesSize.at(att).second) {
					tempvect.emplace_back(bin);
				} else {
					if (bin > UniqueValuesSize.at(att).second) {

						break;
					}

				}
			}
			BinsInATT.emplace_back(tempvect);
		}

		// Lire les bornes pour chaque attribut
		for (int att = 0; att < BinsInATT.size(); ++att) {
			Interval tempPair = { std::numeric_limits<int>::max(),
					std::numeric_limits<int>::min() };
			const auto &binsInAtt = BinsInATT.at(att);

			for (int bin : binsInAtt) {
				if (binsInAtt.size() == 1) {
					tempPair.first = tempPair.second = binsInAtt.at(0);
				} else {
					if (bin % 2 == 0 && bin < tempPair.first) {
						tempPair.first = bin;
					} else if (bin % 2 != 0 && bin > tempPair.second) {
						tempPair.second = bin;
					}
				}
			}

			// Mapping
			Interval newPair = IdToValues(Mapping, tempPair);
			newPair = inverserPaire(newPair);
			OneIntervalPattern.emplace_back(newPair);
		}

		IP.emplace_back(OneIntervalPattern);
	}
	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
			stop - start);
	std::cout << "CPU time for converting itemset to interval patterns:  "
			<< static_cast<double>(duration.count()) / 1e6 << " seconds."
			<< std::endl;

	return IP;
}



void writeIP(std::vector<std::vector<Interval>> IP,
		string OutputFile) {

	string nomFichier = OutputFile;

	// Ouverture du fichier en mode écriture
	std::ofstream fichierSortie(nomFichier);

	// Vérification si le fichier est ouvert avec succès
	if (!fichierSortie.is_open()) {
		std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;

	}

	// Écriture du contenu du vecteur IP dans le fichier
	for (const auto &row : IP) {
		for (const auto &pair : row) {
			fichierSortie << "(" << pair.first << ", " << pair.second << ") ";
		}
		fichierSortie << '\n';
	}

	// Fermeture du fichier
	fichierSortie.close();

}




int writeContentInFile(string OutputFileName,
		std::vector<std::vector<int>> Binarized_dataset, int Ncolumns) {
//
//	// Open the file for writing
//	std::ofstream outfile(OutputFileName);
//
//	if (!outfile.is_open()) {
//		std::cerr << "Error opening the file " << OutputFileName << std::endl;
//		return 1;
//	}
//
//	// Write the vector of vectors to the file
//
//	std::vector<std::string> mStrings = writeFeaturesNames(Ncolumns);
//	;
//	for (const auto &m : mStrings) {
//		outfile << m << " ";
//	}
//	outfile << "\n"; // Separate the "m" strings from the dataset with a newline
//
//	for (const auto &innerVector : Binarized_dataset) {
//		for (size_t i = 0; i < innerVector.size(); ++i) {
//			outfile << innerVector[i];
//			if (i < innerVector.size() - 1) {
//				outfile << " "; // Separate elements within the inner vector with spaces
//			}
//		}
//		outfile << "\n"; // Separate outer vectors with newlines
//	}
//
//	// Close the file
//	outfile.close();
//
//	std::cout << "Data has been written to " << OutputFileName << std::endl;
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

	std::string numericalDatasetPath;
	std::string itemsetsResultPath;

	bool showResults = false;

	// Check if there are at least four command-line arguments
	if (argc < 5) {
		std::cerr << "Usage: " << argv[0]
				<< " --numericaldataset <dataset_path> --itemsetsResult <itemsets_path> [--show]"
				<< std::endl;
		return 1; // Return an error code
	}

	// Process command-line arguments
	for (int i = 1; i < argc; i += 2) {
		std::string flag = argv[i];

		if (flag == "--numericaldataset" && i + 1 < argc) {
			numericalDatasetPath = argv[i + 1];
		} else if (flag == "--itemsetsResult" && i + 1 < argc) {
			itemsetsResultPath = argv[i + 1];
		} else if (flag == "--show") {
			showResults = true;
			i--; // Decrement i to ensure it's not incremented for the value of --show
		} else {
			std::cerr << "Unknown or incomplete command-line argument: "
					<< argv[i] << std::endl;
			return 1; // Return an error code
		}
	}

	// Check if both paths are provided
	if (numericalDatasetPath.empty() || itemsetsResultPath.empty()) {
		std::cerr
				<< "Both --numericaldataset and --itemsetsResult paths are required."
				<< std::endl;
		return 1; // Return an error code
	}





	//string numericalDatasetPath ="/home/bekkouc221/Documents/dev/CPP/data/NT/NT_T.dat";


	std::vector<std::vector<int>> data = readFile(numericalDatasetPath);
	std::vector<std::vector<int>> transposedData = transposeData(data);

	//string itemsetsResultPath ="/home/bekkouc221/Documents/dev/CPP/Reverse_Binarization/NT_80_sol_closedPattern";

	std::vector<std::vector<int>> Myvect = ReadSolutionFile(itemsetsResultPath);


	// get unique values per columns
	std::vector<std::vector<int>> unique_percol = getUniqueValuesPerColumn(
			transposedData);



	
	std::vector<std::vector<Interval>> IPS =
			IntervalPatterns_Generation(Myvect, unique_percol);

	if (showResults) {
		//writeIP(IPS, "ItemsetToIntervalPattern.txt");
		for (const auto &vectorOfIntervals : IPS) {
			for (const Interval &interval : vectorOfIntervals) {
				std::cout << "[" << interval.first << ", " << interval.second
						<< "] ";
			}
			std::cout << std::endl;
		}
	}
	

	return 0;
}
