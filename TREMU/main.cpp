/*
**
** Made by T4lus
** Trinary Emulator
** 
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <ncurses.h>

#include <Trinary/trinary.h>
#include <Utils/utils.h>

#include "cpu.h"
#include "memory.h"

std::string execPath;

WINDOW *createVideoWindow() {
	WINDOW *localWin;

	localWin = subwin(stdscr, 13, 81, 0, 28);
	box(localWin, 0, 0);
	wrefresh(localWin);
	return localWin;
}

WINDOW *createCPUWindow() {
	WINDOW *localWin;

	localWin = subwin(stdscr, 11, 27, 0, 0);
	box(localWin, 0, 0);
	mvwprintw(localWin, 1, 1, "CPU");
	wrefresh(localWin);
	return localWin;
}

void displayCPU(WINDOW *win, CPU *cpu) {
	char i = 0;

	// register
	for(auto gpr:cpu->getGPR()) {
		char gpr_name[4] = {'r', 97+(char)i, ' ', ':' };
		mvwprintw(win, 2+i, 2, gpr_name);
		mvwprintw(win, 2+i, 7, str_pad(dechept(gpr.to_int()), 3, 'D', STR_PAD_LEFT).c_str()) ;
		i++;	
	}
	mvwprintw(win, 2+(++i), 2, "ip :");
	mvwprintw(win, 2+i, 7, str_pad(dechept(cpu->getIP().to_int()), 3, 'D', STR_PAD_LEFT).c_str());
	mvwprintw(win, 2+(++i), 2, "sp :");
	mvwprintw(win, 2+i, 7, str_pad(dechept(cpu->getSP().to_int()), 3, 'D', STR_PAD_LEFT).c_str());

	//flag
	char flag_z[6] = {'z', ' ', ':', ' ', cpu->getZero().to_char(), NULL};
	char flag_c[6] = {'c', ' ', ':', ' ', cpu->getCarry().to_char(), NULL};
	char flag_f[6] = {'f', ' ', ':', ' ', cpu->getFault().to_char(), NULL};

	mvwprintw(win, 2, 13, flag_z);
	mvwprintw(win, 3, 13, flag_c);
	mvwprintw(win, 4, 13, flag_f);



	wrefresh(win);
}

WINDOW *createMemoryWindow() {
	WINDOW *localWin;

	localWin = subwin(stdscr, (LINES / 3)*2, COLS, LINES / 3, 0);
	box(localWin, 0, 0);
	mvwprintw(localWin, 1, 1, "Memory");
	wrefresh(localWin);
	return localWin;
}

void displayMemory(WINDOW *win, Memory *mem) {
	int maxX, maxY;
	int y = 2;
	int page = 0;
	int i = 0;

	getmaxyx(win, maxX, maxY);

	for(auto tryte:mem->getData()) {
		mvwprintw(win, y, ((i+1)*4)+(page*56), str_pad(dechept(tryte.second.to_int()), 3, 'D', STR_PAD_LEFT).c_str()) ;
		i++;
		if (!(i % 13)) {
			mvwprintw(win, y, ((page+1)*56), " | ") ;
			i = 0;
			y++;
		}
		if (!(y %  (maxX - 1) )) {
			page++;
			y = 2;
		}
	}
	wrefresh(win);
}

int main(int argc, char* argv[])
{
	char basePath[255] = "";
	realpath(argv[0], basePath);
	execPath = basePath;
	execPath = execPath.substr(0, execPath.find_last_of("\\/"));

	
	Memory *mem = new Memory(2187);
	CPU *cpu = new CPU(mem);

	//load 3asm into memory
	std::ifstream infile(argv[1]);

	std::string line;
	int addr = 0;
	while (std::getline(infile, line)) {
		chomp(line);
		std::vector<std::string> v{explode(line, ' ')};
		for(auto n:v) {
			mem->store(Tryte(addr++) , Tryte(heptdec(n.c_str())));
		}
	}

	WINDOW *memoryWindow;
	WINDOW *CPUWindow;
	WINDOW *VideoWindow;
    
	int ch;
    initscr();

	raw();
	keypad(stdscr, TRUE);
	halfdelay(1);
	noecho();

	memoryWindow = createMemoryWindow();
	CPUWindow = createCPUWindow();
	VideoWindow = createVideoWindow();

    while((ch = getch()) != KEY_F(1)) {
		try {
			cpu->step();
		}
		catch(std::string const& e) {
			mvprintw(12, 2, e.c_str());
		}

		displayCPU(CPUWindow, cpu);
		displayMemory(memoryWindow, mem);
		refresh();
	}

	endwin();
	return 0;
}