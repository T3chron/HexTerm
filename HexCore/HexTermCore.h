//
// Created by yasin on 9/2/2025.
//

#pragma once
/*libs*/
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include "json.hpp"
#include <mmsystem.h>
/*libs*/
using namespace std;
enum Color {
    BLACK = 0,
    BLUE = 4,
    GREEN = 2,
    CYAN = 6,
    WHITE = 15,
    YELLOW = 14
};
struct Mode {
    bool HexTerm;
};

class HexTermCore {
private:
    Mode mode;
    int ColorPrompt = 2;
    int ColorResponse = 6;
    bool Music = true;
    string CurrentUser = "Ghost";
    string CurrentDir = "(NULL)";
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    string Version = "1.0.0";

public:
    HexTermCore() {
        GetCurrentUser();
        GetCurrentDir();
        mode.HexTerm = true;
    }

    static void print(const string& s);
    void init(bool music,bool spacialMode,int colorPrompt,int colorResponse);
    void SetColor(int color);
    void RestColor();
    void HexTermSMode();
    void HexTermCMode();
    void GetCurrentUser();
    void GetCurrentDir();
    void shortenPath(const string &path);
    void runCommand(const string& inpu);
    bool IsProgramInstaled(const string& appName);
    void runSpcialeCommand(const string& input);
    void DevModeCLang();
    void DevModeCpp();
    void DevModePython();
    void DevModeNode();
    void devModeHex();
    void menu();

};

