#include "Application.h"
#include "Logger.h"

using namespace OpenGLRenderer;

int main()
{
	Logger::Initialize();
	Application app {};
	app.Update();

	return 1;
}
