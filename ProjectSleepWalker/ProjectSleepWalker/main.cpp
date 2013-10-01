#include "Application.h"
#include "ResourceManager.h"
#include <iostream>

void main()
{
	// Pre-load resources for app
	if(resourceManager.Load())
	{
		std::cout << "Resources successfully loaded." << std::endl;

		// Create and run app
		Application app;
		app.Run();
	}
	else
	{
		std::cout << "Error: One or more resources failed to load." << std::endl;
		std::cin.get(); // Hang program
	}
}
