#ifndef CONSOLEUTIL_H
#define CONSOLEUTIL_H

#define CONSOLE_WIDTH 75
#define CONSOLE_HEIGHT 25
#pragma warning(disable: 4996)


void dump_key_buffer()
{
	int c = getchar();

	while (c != '\n' && c != EOF)
		c = getchar();
}

//Tested: Windows 7 + VS 2012
#if defined(WIN32) || defined(_WIN32)

#include <conio.h>
#include <windows.h>

void console_activate()
{
	fflush(stdout);
}

void console_deactivate()
{
	fflush(stdout);
}

void print_char(int x, int y, char c)
{
	COORD pos = {x , y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	printf("%c", c);
}

void print_string(int x, int y, const char* str)
{
	COORD pos = {x , y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	printf("%s", str);
}

int get_input()
{
	return _getch();
}

void get_string(char* str)
{
	scanf("%s", str);
	dump_key_buffer();
}

//Tested: Ubuntu 13.04 + GCC (repo version) with ncurses-dev
//Tested: ASU General (9/9/2013)
#elif defined(__unix__) || defined(__apple__)

#include <ncurses.h>

void console_activate()

{
	initscr();
	raw();
    noecho();

	resize_term(25, 80);
}

void console_deactivate()
{
	endwin();
}

void print_char(int x, int y, char c)
{
	mvaddch(y, x, c);
	refresh();
}

void print_string(int x, int y, const char* str)
{
	mvaddstr(y, x, str);
	refresh();
}

int get_input()
{
	return getch();
}

void get_string(char* str)
{
	getstr(str);
}

#else 

#error Unsupported platform, please contact the TA.

#endif


#endif
