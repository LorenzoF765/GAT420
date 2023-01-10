#include <iostream>
#include <vector>
#include <array>

using namespace std;

vector<bool> ProcessCells(const vector<bool>& cells, const array<bool, 8>& rule)
{
	// create cells that will store the cell states after being processed 
	// use constructor that takes the number of elements to create 
	vector<bool> processed(cells.size());

	for (size_t i = 0; i < processed.size(); i++)
	{
		// get the current and neighboring cell states using (i)ndex 
		// left = i - 1 
		// center = i 
		// right = i + 1 

		// wrap left and right index if past the edges (left < 0 or right >= size) 
		// left = (i - 1) < 0 -> size - 1  
		// right = (i + 1) == size -> 0 
		bool states[3];
		states[0] = cells[(i - 1) % cells.size()];
		states[1] = cells[i];
		states[2] = cells[(i + 1) % cells.size()];

		bool state = false;

		// current pattern 111 110 101 100 011 010 001 000 
		// rule    0   1   2   3   4   5   6   7 
		if (states[0] && states[1] && states[2]) state = rule[0];
		else if (states[0] && states[1] && !states[2]) state = rule[1];
		else if (states[0] && !states[1] && states[2]) state = rule[2];
		else if (states[0] && !states[1] && !states[2]) state = rule[3];
		else if (!states[0] && states[1] && states[2]) state = rule[4];
		else if (!states[0] && states[1] && !states[2]) state = rule[5];
		else if (!states[0] && !states[1] && states[2]) state = rule[6];
		else if (!states[0] && !states[1] && !states[2]) state = rule[7];

		processed[i] = state;
	}

	return processed;
}

void DisplayCellsRow(const vector<bool>& cells)
{
	// display a row of cells to the console 
	// display a 'X' if the cell is alive (true) or a '-' if dead (false) 
	// place a space between characters 
	// example: - - X X - - X - - - X - - 
	for (auto cell : cells)
	{
		if (cell == true) cout << "X ";
		else cout << "- ";
	}

	// go to the next line after displaying the row 
	cout << "" << endl;
}

int main()
{
	// declare a variable for the number of cells in a row (50) 
	int numCells = 50;
	// declare a variable for the number of iterations (40) 
	int numIter = 40;

	// create vector of cell states boolean (true = alive/false = dead) 
	// there is a constructor that allows you to provided the number of elementsand the default value(int, bool)
	vector<bool> cells(numCells, false);
	srand((unsigned int)time(nullptr));
	//cells[numCells / 2] = true;
	for (int i = 0; i < 5; i++)
	{
		cells[rand() % (cells.size() - 1)] = true;
	}

	// set the text to a different color (experiment with different colors 
	// the values are in hex (0-A) 
	// the first value is the background and the second the foreground 
	// https://www.geeksforgeeks.org/how-to-print-colored-text-in-c/ 
	system("Color 0C");

	// rules 
	array<bool, 8> rule30 = { 0, 0, 0, 1, 1, 1, 1, 0 };
	array<bool, 8> rule90 = { 0, 1, 0, 1, 1, 0, 1, 0 };
	array<bool, 8> rule110 = { 0, 1, 1, 0, 0, 1, 1, 0 };
	array<bool, 8> rule182 = { 1, 0, 1, 1, 0, 1, 1, 0 };

	// display each iteration 
	for (int i = 0; i < numIter; i++)
	{
		DisplayCellsRow(cells);
		cells = ProcessCells(cells, rule182);
	}
}