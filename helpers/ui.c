#include "../headers/ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(x) Sleep(x)
#else
#include <unistd.h>
#define SLEEP_MS(x) usleep((x)*1000)
#endif

void setupConsole() {
#ifdef _WIN32
  // Enable ANSI escape codes on Windows
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD dwMode = 0;
  GetConsoleMode(hOut, &dwMode);
  dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
  SetConsoleMode(hOut, dwMode);
#endif
}

void printAnimated(const char *text, int delayMs) {
  for (int i = 0; text[i] != '\0'; i++) {
    printf("%c", text[i]);
    fflush(stdout);
    SLEEP_MS(delayMs);
  }
  printf("\n");
}

void printCentered(const char *text) {
  // Simple centering assuming 80 column width
  int len = strlen(text);
  int padding = (80 - len) / 2;
  if (padding < 0)
    padding = 0;
  for (int i = 0; i < padding; i++)
    printf(" ");
  printf("%s\n", text);
}

void printTitle() {
  printf(COLOR_CYAN);
  printCentered(
      "================================================================");
  printCentered("  _   _    __  __    ____    ");
  printCentered(" | | | |  |  \\/  |  / ___|   ");
  printCentered(" | |_| |  | |\\/| |  \\___ \\   ");
  printCentered(" |  _  |  | |  | |   ___) |  ");
  printCentered(" |_| |_|  |_|  |_|  |____/   ");
  printCentered("                             ");
  printCentered(" HOSTEL MANAGEMENT SYSTEM    ");
  printCentered(
      "================================================================");
  printf(COLOR_RESET);
}

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void waitForInput() {
  printf(COLOR_YELLOW "\nPress Enter to continue..." COLOR_RESET);
  while (getchar() != '\n')
    ;        // clear buffer
  getchar(); // wait
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}
