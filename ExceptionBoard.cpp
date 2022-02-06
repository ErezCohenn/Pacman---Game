#include "ExceptionBoard.h"
//-----------------------------------------------------------------------------------------------//
void ExceptionBoard::printExceptions() const
{
	clear_screen();

	cout << "For " << screenName << " file were found " << messages.size() << " Errors as follows:" << endl;

	for (size_t i = 0; i < messages.size(); i++)
	{
		cout << i + 1 << ". " << messages[i] << endl;
	}
}
//-----------------------------------------------------------------------------------------------//