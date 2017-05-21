#include "mesh.hpp"

Mesh::Mesh(uint8_t _M, uint8_t _N): M(_M), N(_N) {
	volumes.reserve(M, std::vector<Volume>(N));
}

void Mesh::printMatrix() {
	for (uint8_t i = 0; i < M; ++i) {
		for (uint8_t j = 0; j < N; ++j) {
			std::cout << volumes[i][j] << "\t";
		}
		std::cout << "\n";
	}
	std::cout << std::endl; // flush the stream
}
