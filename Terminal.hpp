#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

class Terminal {
public:
	uint8_t MASK_VC : 4;
	uint8_t MASK_VR : 5;

	vector<vector<char>> coll;

	Terminal() {
		coll.resize(19);

		MASK_VC = 0;
		MASK_VR = 0;

		for (int i = 0; i < 18; ++i) {
			coll[i].resize(34, ' ');
		}

	}
};