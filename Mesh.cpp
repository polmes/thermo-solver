// C++ libraries
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

class Mesh {
	private:
		std::vector<double> line;
		std::string name;

	public:
		// Constructor
		Mesh(uint8_t, std::string);

		// Destructor
		// ~Mesh();

		// Methods
		void printVector() {
			for (uint8_t i = 0; i < line.size(); ++i) {
				std::cout << line[i] << std::endl;
			}
		}
		void anotherMethod();
};

Mesh::Mesh(uint8_t N, std::string str): name(str) {
	for (uint8_t i = 0; i < N; ++i) {
		line.push_back(i+1);
	}
}

void Mesh::anotherMethod() {
	std::cout << "Size: " << line.size() << std::endl; // Mesh::line, too
	std::cout << "Name: " << name << std::endl;
}

const uint8_t N = 50;

int main(int argc, char const *argv[]) {
	Mesh mesh(N, "damn");
	mesh.printVector();
	mesh.anotherMethod();
	// mesh.anotherMethod();

	return 0;
}
