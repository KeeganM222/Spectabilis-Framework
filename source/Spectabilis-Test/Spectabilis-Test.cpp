/*
File:		Spectabilis-Test.cpp
Author:		Keegan MacDonald
Created:	2025.01.16@20:29
Purpose:	Test the functionality of the build configuration of the
			Spectabilis-Test project.
*/

#include "Spectabilis-Test.h"

#include <Spectabilis/Spectabilis.h>

#include <iostream>

void SpectabilisTest::spectabilis_test_test() {
	std::cout << "Spectabilis Test test" << std::endl;
}

int main(int argc, char** argv) {
	Spectabilis spectabilis;
	spectabilis.spectabilis_test();
	SpectabilisTest spectabilisTest;
	spectabilisTest.spectabilis_test_test();
	return EXIT_SUCCESS;
}