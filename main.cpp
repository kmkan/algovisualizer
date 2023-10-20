#include <SDL2/SDL.h>

#include <iostream>
#include <random>
#include <algorithm>
#include <string>

void intro();
void controls();
void draw_state(std::vector<int>& v, SDL_Renderer* renderer, int red, int blue);
void selection_sort(std::vector<int>& v, SDL_Renderer* renderer);
void bubble_sort(std::vector<int>& v, SDL_Renderer* renderer);
void insertion_sort(std::vector<int>& v, SDL_Renderer* renderer);

int main(int argc, char* args[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL had an error. SDL Error: " << SDL_GetError() << std::endl;
	}

	intro();
	controls();

	int n;

	std::cin >> n;

	if (n == -1) {
		SDL_Quit();
		return 0;
	}

	std::random_device rd;
	std::uniform_int_distribution<int> d(1, 49);
	std::vector<int> v;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_CreateWindowAndRenderer(100 * 5, 100 * 5, 0, &window, &renderer);
	SDL_RenderSetScale(renderer, 10, 10);

	for (int i = 0; i < 50; i++) {
		v.push_back(d(rd));
	}

	if (n == 1)
		selection_sort(v, renderer);
	else if (n == 2)
		bubble_sort(v, renderer);
	else if (n == 3)
		insertion_sort(v, renderer);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}

void intro()
{
	std::cout << "==============================Sorting Visualizer==============================\n\n"
	          << "Visualize various sorting algorithms in C++ using the SDL2 Library.\n Sorting algorithms arrange list elements in a specific order. This implementation\n showcases Selection Sort, Insertion Sort, Bubble Sort, Merge Sort, Quick Sort, \nand Heap Sort with a fixed list size of 50 elements. \n The list is randomized and you can select a sorting algorithm. Keep in mind that the sorting time shown isn't the same\n as their actual time complexities; the algorithms are intentionally delayed for better visualization. \nPress ENTER for controls.";

	std::string s;
	std::getline(std::cin, s);
	if (s == "\n")
	{
		return;
	}
}

void controls()
{
	std::cout << "Available Controls inside Sorting Visualizer:-\n"
	          << "    Use 1 to start Selection Sort Algorithm.\n"
	          << "    Use 2 to start Bubble Sort Algorithm.\n"
	          << "    Use 3 to start Insertion Sort Algorithm.\n"
	          << "PRESS ENTER TO START SORTING VISUALIZER...\n\n"
	          << "Or type -1 and press ENTER to quit the program.";
	return;
}

void draw_state(std::vector<int>& v, SDL_Renderer* renderer, int red, int blue) {

	int index = 0;
	for (int i : v) {
		if (index == red) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		} else if (index == blue) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		} else {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		SDL_RenderDrawLine(renderer, index, 49, index, i);
		index++;
	}

}

void present_draw(std::vector<int>& v, SDL_Renderer* renderer, unsigned int i, unsigned int j) {
	// clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	draw_state(v, renderer, i, j);

	// show to window
	SDL_RenderPresent(renderer);

	// delay
	SDL_Delay(10);
}

void selection_sort(std::vector<int>& v, SDL_Renderer* renderer) {
	for (unsigned int i = 0; i < v.size(); i++) {
		for (unsigned int j = i; j < v.size(); j++) {
			if (v[j] < v[i]) {
				std::swap(v[j], v[i]);
			}

			present_draw(v, renderer, i, j);
		}
	}
}

void bubble_sort(std::vector<int>& v, SDL_Renderer* renderer) {
	for (unsigned int i = 0; i < v.size(); i++) {
		for (unsigned int j = 0; j < v.size() - i - 1; j++) {
			if (v[j] > v[j + 1]) {
				std::swap(v[j], v[j + 1]);
			}

			present_draw(v, renderer, i, j);
		}
	}
}

void insertion_sort(std::vector<int>& v, SDL_Renderer* renderer)
{
	int j, key;
	for (unsigned int i = 1; i < v.size(); i++) {
		key = v[i];
		j = i - 1;

		// Move elements of arr[0..i-1],
		// that are greater than key,
		// to one position ahead of their
		// current position
		while (j >= 0 && v[j] > key) {
			v[j + 1] = v[j];
			j = j - 1;

			present_draw(v, renderer, i, j);
		}
		v[j + 1] = key;
		present_draw(v, renderer, i, j);
	}
}
