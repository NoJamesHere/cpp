#include <stdio.h>
#include <string>
// this whole thing is for windows clients or stuff

#ifdef _WIN32
#include <windows.h>
void enable_virtual_terminal() {
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD dwMode = 0;
  GetConsoleMode(hOut, &dwMode);
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hOut, dwMode);
}
#endif

void Style_Formation() {
  printf("Normal Text\n");
  printf("\033[1;37mBold Text\033[0m\n");
  printf("\033[3mItalic Text\033[0m\n");
  printf("\033[4mUnderlined Text\033[0m\n");
  printf("\033[9mNormal Text\033[0m <- That is actually striked through\n");
}

void Foreground_Color_Formation() {
  printf("\033[1;39mDefault Colour \033[0m(with ansi escape code)\n");
  printf("\033[1;30mBlack Text\033[0m\n");
  printf("\033[1;31mRed Text\033[0m\n");
  printf("\033[1;32mGreen Text\033[0m\n");
  printf("\033[1;33mYellow Text\033[0m\n");
  printf("\033[1;34mBlue Text\033[0m\n");
  printf("\033[1;35mPurple Text\033[0m\n");
  printf("\033[1;36mCyan Text\033[0m\n");
  printf("\033[1;37mWhite Text\033[0m\n");
}

void Background_Color_Formation() {
  printf("\033[1;49;37mDefault Background Colour \033[0m(with ansi escape "
         "code)\n");
  printf(
      "\033[1;48;2;0;0;0m\033[38;2;255;255;255mTrue Black Background\033[0m\n");
  printf("\033[1;41;37mRed Background\033[0m\n");
  printf("\033[1;42;37mGreen Background\033[0m\n");
  printf("\033[1;43;37mYellow Background\033[0m\n");
  printf("\033[1;44;37mBlue Background\033[0m\n");
  printf("\033[1;45;37mPurple Background\033[0m\n");
  printf("\033[1;46;37mCyan Background\033[0m\n");
  printf("\033[1;47;30mWhite Background\033[0m\n");
}

// Throwing some stuff together
void Mixing_Together() {
  const std::string example{"\033[1;37mExample: \033[0m"};
  printf( // White, Bold;     Normal;              red, crossed;
          // underlined, white;     Normal;
      "%sThis is \033[9;31mcorrect\033[0m \033[0;4mnot "
      "correct\033[0m.\n",
      example.c_str());
  printf("%sC++ is \033[1;37;45;4mgreat!!\033[0m\n", example.c_str());
  printf("%s\033[1;32;45mColoursss. We love colours.\033[0m\n",
         example.c_str());
  // i kinda like this one v
  printf("%s\033[1;46;33mMore Colourssss\033[0m\n", example.c_str());
  // idk
  printf("%s\033[1;41;37mJust red.. Yeah..\033[0m\n", example.c_str());
}

int main() {
#ifdef _WIN32
  enable_virtual_terminal();
#endif
  const std::string exec = "\033[48;5;166m[EXECUTING]\033[0m";
  printf("%s Style_Formation()\n\n", exec.c_str());
  Style_Formation();
  printf("\n\n%s Foreground_Color_Formation()\n\n", exec.c_str());
  Foreground_Color_Formation();
  printf("\n\n%s Background_Color_Formation()\n\n", exec.c_str());
  Background_Color_Formation();
  printf("\n\n%s Mixing_Together()\n\n", exec.c_str());
  Mixing_Together();
  return 0;
}
