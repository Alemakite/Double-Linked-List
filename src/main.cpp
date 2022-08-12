
/*! \mainpage Lab Book 2
 *
 * Here are implemented all functionalities, that I managed to develop, listed in the Double Linked List lab document.
 */

// Define and includes to show memory leak report
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#include <iostream>
#include "../include/doubleLinkedList.h"

void main() /** Entry point for the application */
{
	DoubleLinkedList<int> myList;
	
	myList.push_front(11);
	myList.push_back(69);
	myList.push_before_curr(26);
	myList.push_after_curr(12);

	cout << endl;

	std::cout << myList.look_front() << std::endl;
	std::cout << myList.look_back() << std::endl;
	std::cout << myList.look_current() << std::endl;

	myList.traverse_forwards();
	myList.traverse_forwards();
	std::cout << myList.look_current() << std::endl;
	myList.traverse_backwards();
	std::cout << myList.look_current() << std::endl;

	cout << endl;
	myList.printList();
	cout << endl;
	
	cout << myList.getSize() << endl;
	myList.pop_back();
	cout << myList.getSize() << endl;

	//myList.listSort();
	
	myList.printList();
	cout << endl;
	while (!myList.isEmpty())
		myList.pop_front();

	_CrtDumpMemoryLeaks(); // Look in the output window for a report
	system("pause");
}
