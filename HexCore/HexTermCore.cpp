//
// Created by yasin on 9/2/2025.
//

#include "HexTermCore.h"

#include <vector>
#include <Lmcons.h>
#include <unordered_set>
#include <random>


void HexTermCore::init(bool music,bool spacialMode,int colorPrompt,int colorResponse) {

    if (music == true) {
        PlaySound("Config\\HEXTERM.wav" , NULL , SND_FILENAME | SND_ASYNC);
    }
    if (spacialMode) {
        mode.HexTerm = spacialMode;
    }else {
        mode.HexTerm = true;
    }
    if (colorPrompt) {
        ColorPrompt = colorPrompt;
    }else {
        ColorPrompt = 2;
    }
    if (colorResponse) {
        ColorResponse = colorResponse;
    }else {
        ColorResponse = 6;
    }

    string Dname = "T3chron";

    string UpdateTime = "2025/9/2";
    const vector<string> WelcomeBanner = {
        "██╗  ██╗███████╗██╗  ██╗████████╗███████╗██████╗ ███╗   ███╗",
        "██║  ██║██╔════╝╚██╗██╔╝╚══██╔══╝██╔════╝██╔══██╗████╗ ████║",
        "███████║█████╗   ╚███╔╝    ██║   █████╗  ██████╔╝██╔████╔██║",
        "██╔══██║██╔══╝   ██╔██╗    ██║   ██╔══╝  ██╔══██╗██║╚██╔╝██║",
        "██║  ██║███████╗██╔╝ ██╗   ██║   ███████╗██║  ██║██║ ╚═╝ ██║",
        "╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝"
    };
    SetColor(13);
    for (const string& logo: WelcomeBanner) {
        Sleep(50);
        cout << logo << endl;
    }
    SetColor(2);
    string Developer = "Developer : "+Dname+" \nVersion : "+Version+" \nUpdate : "+UpdateTime;
    vector<char> CharList(Developer.begin(), Developer.end());
    for (char c: CharList) {
        Sleep(50);
        cout << c ;
    }
    RestColor();
    cout << endl << "Press any key to continue...";
    cin.get();
    system("cls");
    if (spacialMode == true) {
        mode.HexTerm = true;
        HexTermSMode();
    }else {
        mode.HexTerm = false;
        HexTermCMode();
    }
}

void HexTermCore::print(const string& s) {
    cout << s ;
}
void HexTermCore::SetColor(int color) {
    SetConsoleTextAttribute(hStdOut, color);
}
void HexTermCore::RestColor() {
    SetConsoleTextAttribute(hStdOut, 15);
}
void HexTermCore::HexTermSMode() {
    bool exitFlag = false;
    while (!exitFlag) {
        string input;
        SetColor(ColorPrompt);
        cout << "HexTerm@"<< CurrentUser << ": ";
        SetColor(15);
        getline(cin, input);
        SetColor(ColorPrompt);
        unordered_set<string> standard= {"cc" , "cc+" , "rt" , "py" , "nd" "ipg" , "mkd" , "mkf"
            , "rm" , "rmd" , "ip" , "show" , "ver" , "dn" , "cls" , "clear" , "help"};

        unordered_set<string> spacialeDev = {"dev-mode-c" , "dev-mode-cpp" , "dev-mode-py" , "dev-mode-node" ,
             "dev-mode-hex"};
        if (input == "") {
            continue;
        }
        if (input == "ch") {
            SetColor(15);
            cout<<"Do you want to change mode? [y/n] : ";
            SetColor(ColorPrompt);
            string ans ;
            getline(cin, ans);
            if (ans == "y" || ans == "Y" || ans == "yes" || ans == "YES") {
                mode.HexTerm = false;
                HexTermCMode();
            }else {
                continue;
            }
        }else {
            if (standard.count(input)) {
                runCommand(input);
            }else if (spacialeDev.count(input)) {
                runSpcialeCommand(input);
            }else {
                SetColor(4);
                cout<<"║"<<endl;
                cout<<"╚══► ("<< input << ") is not a valid HexTerm." << endl;
            }
        }
    }
}
void HexTermCore::HexTermCMode() {
    bool exit = false;

    while (!exit) {
        string input;
        SetColor(ColorPrompt);
        cout << "HexTerm@(cmd)" << CurrentUser << "=>" << CurrentDir << ": ";
        getline(cin, input);

        if (input.empty()) continue;

        if (input == "exit") {
            exit = true;
            break;
        }

        // دستور cd
        if (input.substr(0, 2) == "cd") {
            string target = input.length() > 3 ? input.substr(3) : "";

            if (target == "..") {
                char buffer[MAX_PATH];
                GetCurrentDirectoryA(MAX_PATH, buffer);
                string path(buffer);
                size_t pos = path.find_last_of("\\/");
                if (pos != string::npos) {
                    path = path.substr(0, pos);
                    SetCurrentDirectoryA(path.c_str());
                }
            } else if (!target.empty()) {
                if (!SetCurrentDirectoryA(target.c_str())) {
                    SetColor(ColorResponse);
                    cout << "Error : (" << target << ") Not Found In cmd" << endl;
                    continue;
                }
            }

            GetCurrentDir(); // مسیر جدید کوتاه شده در CurrentDir ست می‌شود
            continue;
        }

        if (input.substr(0,2) == "ch") {
            mode.HexTerm = true;
            exit = true;
            HexTermSMode();
        }
        SetColor(ColorResponse);
        system(input.c_str());
    }
}
void HexTermCore::GetCurrentUser() {
    char username[UNLEN + 1];
    DWORD username_size = UNLEN + 1;
    if (GetUserNameA(username, &username_size) ) {
        CurrentUser = string(username);
    }
}
void HexTermCore::GetCurrentDir() {
    char buffer[MAX_PATH];
    DWORD ret = GetCurrentDirectoryA(MAX_PATH, buffer);
    if (ret != 0) {
        shortenPath(string(buffer));
    }
}
void HexTermCore::shortenPath(const string &path) {
    constexpr char delimiter = '\\';
    vector<string> parts;
    size_t start = 0;
    size_t end = path.find(delimiter);

    while (end != string::npos) {
        parts.push_back(path.substr(start, end - start));
        start = end + 1;
        end = path.find(delimiter, start);
    }

    if (parts.size() <= 2) CurrentDir = path;

    const string result = parts[0] + "//...../" + parts[parts.size() - 1];
    CurrentDir = result;
}
void HexTermCore::runCommand(const string& input) {
    if (input == "cc") {
        if (IsProgramInstaled("gcc")) {
            string appName,appSorece;
            SetColor(15);
            cout << "Enter App Name: ";
            SetColor(ColorPrompt);
            getline(cin, appName);
            SetColor(15);

            cout << "Enter App source code File Name (with out .c) : ";
            SetColor(ColorPrompt);
            getline(cin , appSorece);
            SetColor(15);
            cout << "Do you have header File ?[y/n] : ";
            SetColor(ColorPrompt);
            string ans;
            bool haveHeader = false;
            SetColor(15);
            vector<string> parts;
            getline(cin, ans);
            string headerFiles;
            if (ans == "y" || ans == "Y" || ans == "yes" || ans == "YES") {

                bool endHFile = false;
                SetColor(6);
                string hFileName;
                while (!endHFile) {
                    cout<< "Enter Header File name [Enter 0 for end]:";
                    getline(cin, hFileName);

                    if (hFileName != "0") {
                        parts.emplace_back(hFileName+".c");
                    }else {
                        endHFile = true;
                        haveHeader = true;
                    }
                }
                for (const string& f : parts) {
                    headerFiles += " " + f;  // فاصله مهم است
                }
            }
            string build;




            if (haveHeader) {
                build = "gcc " + appSorece + ".c" + headerFiles + " -o " + appName + ".exe";
            } else {
                build = "gcc " + appSorece + ".c -o " + appName + ".exe";
            }
            int res = system(build.c_str());
            if (res == 0) {
                SetColor(2);
                cout << "\nBuild Sucssesfully..."<<endl;
                SetColor(6);
                cout <<"║"<<endl;
                cout<< "╚══►App exe file : "<<appName+".exe"<<endl;
                RestColor();
            }else {
                SetColor(4);
                cout<<"\nError To build File"<<endl;
            }
        }else {
            SetColor(4);
            cout <<"║"<<endl;
            cout <<"╚══► gcc Not Install In Your PC Please Install It And Try Again\n";
        }
    }
    if (input == "cc+") {
        if (IsProgramInstaled("g++")) {
            string appName,appSorece;
            SetColor(15);
            cout << "Enter App Name: ";
            SetColor(ColorPrompt);
            getline(cin, appName);
            SetColor(15);

            cout << "Enter App source code File Name (with out .cpp) : ";
            SetColor(ColorPrompt);
            getline(cin , appSorece);
            SetColor(15);
            cout << "Do you have header File ?[y/n] : ";
            SetColor(ColorPrompt);
            string ans;
            bool haveHeader = false;
            SetColor(15);
            vector<string> parts;
            getline(cin, ans);
            string headerFiles;
            if (ans == "y" || ans == "Y" || ans == "yes" || ans == "YES") {

                bool endHFile = false;
                SetColor(6);
                string hFileName;
                while (!endHFile) {
                    cout<< "Enter Header File name [Enter 0 for end]:";
                    getline(cin, hFileName);

                    if (hFileName != "0") {
                        parts.emplace_back(hFileName+".cpp");
                    }else {
                        endHFile = true;
                        haveHeader = true;
                    }
                }
                for (const string& f : parts) {
                    headerFiles += " " + f;  // فاصله مهم است
                }
            }
            string build;




            if (haveHeader) {
                build = "g++ " + appSorece + ".cpp" + headerFiles + " -o " + appName + ".exe";
            } else {
                build = "g++ " + appSorece + ".cpp -o " + appName + ".exe";
            }
            int res = system(build.c_str());
            if (res == 0) {
                SetColor(2);
                cout << "\nBuild Sucssesfully..."<<endl;
                SetColor(6);
                cout <<"║"<<endl;
                cout<< "╚══►App exe file : "<<appName+".exe"<<endl;
                RestColor();
            }else {
                SetColor(4);
                cout<<"\nError To build File"<<endl;
            }
        }else {
            SetColor(4);
            cout <<"║"<<endl;
            cout <<"╚══► g++ Not Install In Your PC Please Install It And Try Again\n";
        }
    }
    if (input == "py") {
        if (IsProgramInstaled("python") || IsProgramInstaled("python3")) {
            string appName;
            SetColor(15);
            cout << "Enter App Name (with out .py) :  ";
            SetColor(ColorPrompt);
            getline(cin, appName);
            string cmd = "python " + appName + ".py ";
            int result = system(cmd.c_str());
            if (result != 0) {
                SetColor(4);
                cout <<"║"<<endl;
                cout <<"╚══►Error To Build Python File"<<endl;
            }
        }
    }
    if (input == "nd") {
        if (IsProgramInstaled("node") ) {
            string appName;
            SetColor(15);
            cout << "Enter App Name (with out .js) :  ";
            SetColor(ColorPrompt);
            getline(cin, appName);
            string cmd = "node " + appName + ".js ";
            int result = system(cmd.c_str());
            if (result != 0) {
                SetColor(4);
                cout <<"║"<<endl;
                cout <<"╚══►Error To Run node File"<<endl;
            }
        }
    }
    if (input == "rt") {
        if (IsProgramInstaled("npm") ) {
            string choises;
            SetColor(15);
            cout << "Project Start In (npm / vite) : ";
            SetColor(ColorPrompt);
            getline(cin, choises);
            if (choises == "npm") {
                system("npm start");
            }
            if (choises == "vite") {
                system("npx run dev");
            }
        }
    }
    if (input == "ipg") {
            SetColor(15);
            cout<<"Enter IP Address: ";
            string ip;
            SetColor(ColorPrompt);
            getline(cin, ip);
            string cmd = "ping " + ip ;
            system(cmd.c_str());
        }
    if (input == "mkd") {
            SetColor(15);
            cout<<"Enter Dir Name : ";
            string name;
            SetColor(ColorPrompt);
            getline(cin, name);
            if (CreateDirectory(name.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
                SetColor(ColorPrompt);
                cout << "Create Directory Successfully..." << endl;
            }else {
                SetColor(4);
                cout << "Create Directory Failed..." << endl;
            }
        }
    if (input == "mkf") {
            SetColor(15);
            cout<<"Enter File Name : ";
            string name;
            SetColor(ColorPrompt);
            getline(cin, name);
            ofstream fout(name+".txt");
            if (fout.is_open()) {
                SetColor(6);
                cout<<"File Created Successfully..."<<endl;
            }else {
                SetColor(4);
                cout<<"File Creation Failed..."<<endl;
            }
        }
    if (input == "rm") {
            SetColor(15);
            cout<<"Enter File Name : ";
            string name;
            SetColor(ColorPrompt);
            getline(cin, name);
            if (remove(name.c_str()) == 0) {
                cout<<"File Removed Successfully..."<<endl;
            }else {
                SetColor(4);
                cout<<"File Removing Failed..."<<endl;
            }
        }
    if (input == "rmd") {
            SetColor(15);
            cout<<"Enter Dir Name : ";
            string name;
            SetColor(ColorPrompt);
            getline(cin, name);
            if (filesystem::exists(name) ) {
                if (filesystem::is_empty(name)) {
                    filesystem::remove(name);
                    SetColor(ColorPrompt);
                    cout<<"Dir Removed Successfully..."<<endl;
                }else {
                    string ans;
                    SetColor(15);
                    cout<<"Dir Is Not Empty Do You Want Ramove It?[y/n]: ";
                    SetColor(ColorPrompt);
                    getline(cin, ans);
                    if (ans == "y" || ans == "Y" || ans == "yes" || ans == "YES") {
                        filesystem::remove(name);
                        SetColor(ColorPrompt);
                        cout<<"Dir Removed Successfully..."<<endl;
                    }else {
                        SetColor(6);
                        cout<<"Cansel Remove Dir..."<<endl;
                    }
                }
            }
        }
    if (input == "ip") {
            system("ipconfig");
        }
    if (input == "show") {
            string target ;
            SetColor(15);
            cout<<"Enter File Name : ";
            SetColor(ColorPrompt);
            getline(cin, target);
            ifstream file(target);
            if (!file.is_open()) {
                SetColor(4);
                cout<<"║"<<endl;
                cout<<"╚══► Can't Open File..."<<endl;
            }else {
                SetColor(6);
                cout<<"-------------------------Start------------------------------"<<endl;
                SetColor(15);
                string line;
                while (getline(file, line)) {
                    cout << line << endl;
                }
                file.close();
                SetColor(6);
                cout<<"---------------------------End----------------------------"<<endl;
            }
        }
    if (input == "ver") {
            SetColor(6);
            cout<<"║"<<endl;
            cout<<"╚══► Version : "<<Version << endl;
        }
    if (input == "dn") {
            string target ;
            SetColor(15);
            cout << "Enter Url: ";
            SetColor(ColorPrompt);
            getline(cin, target);
            cout << "File Name For Save As: ";
            SetColor(ColorPrompt);
            string fname;
            getline(cin, fname);
            SetColor(15);
            string command = "curl -L -o \"" + fname + "\" \"" + target + "\"";
            int res = system(command.c_str());
            if (res == 0) {
                SetColor(6);
                cout<<"File Downloaded Successfully..."<<endl;
            }else {
                SetColor(4);
                cout<<"║"<<endl;
                cout<<"╚══► Error To Download  : "<<target << endl;
            }
        }
    if (input == "cls" || input == "clear") {
            system("cls");
        }
    if (input == "help" || input == "-h") {
        menu();
    }

}
bool HexTermCore::IsProgramInstaled(const string& appName) {
    string cmd = "where "+ appName + " >nul 2>&1";
    int result = system(cmd.c_str());
    if (result == 0) {
        return true;
    }else {
        return false;
    }
}
void HexTermCore::runSpcialeCommand(const string& input) {
    if (input == "dev-mode-c") {
        DevModeCLang();
    }
    if (input == "dev-mode-cpp") {
        DevModeCpp();
    }
    if (input == "dev-mode-py") {
        DevModePython();
    }
    if (input == "dev-mode-node") {
        DevModeNode();
    }
    if (input == "dev-mode-hex") {
        devModeHex();
    }
}


void HexTermCore::DevModeCLang() {
    string templateAsClang =
        "#include <stdlib.h>\n#include <stdio.h>\n\n"
        "int main(){\n"
        "    printf(\"Hello World\\n\");\n"
        "    return 0;\n}\n";

    bool exitFlag = false;
    string FileName;
    vector<string> headerFiles;

    while (!exitFlag) {
        string input;
        SetColor(ColorPrompt);
        cout<<"HexTerm@(C-Lang)>>"<<CurrentUser<<": ";
        getline(cin, input);

        // mkp
        if ((input.substr(0,3) == "mkp" || input.substr(0,3) == "MKP") && input.size() > 4) {
            string target = input.substr(4);
            replace(target.begin(), target.end(), ' ', '_');
            FileName = target;
            ofstream file(target+".c");
            if (file.is_open()) {
                file << templateAsClang;
                SetColor(6);
                cout<<"Project "<<FileName<<".c created.\n";
            } else {
                SetColor(4);
                cout<<"Error To Make C File\n";
            }
        }

        // run
        else if (input == "run") {
            if (FileName.empty()) {
                SetColor(6);
                cout<<"First Make A Project And Try Again (mkp Project-Name)\n";
            } else {
                if (IsProgramInstaled("gcc")) {
                    string run = "gcc " + FileName + ".c";
                    for (const string& s : headerFiles) run += " " + s;
                    run += " -o " + FileName + ".exe";

                    int res = system(run.c_str());
                    if (res == 0) {
                        SetColor(15);
                        system(string(FileName+".exe").c_str());
                        cout<<"\n\n";
                    } else {
                        SetColor(4);
                        cout<<"Compilation Failed...\n";
                    }
                } else {
                    SetColor(4);
                    cout<<"gcc Is Not Installed On your PC\n";
                }
            }
        }

        // add
        else if (input == "add") {
            bool addEnd =  false;
            while (!addEnd) {
                SetColor(15);
                cout<<"Enter header source (without .c, enter 0 to end): ";
                string name;
                SetColor(ColorPrompt);
                getline(cin, name);
                if (name != "0") {
                    headerFiles.emplace_back(name+".c");
                } else {
                    addEnd = true;
                    SetColor(6);
                    cout<<"Header Files Added...\n";
                }
            }
        }else if (input == "show -hd") {
            int i = 1;
            for (const string& s : headerFiles) {
                cout << "header: "<< i << ". " << s << endl;
                i++;
            }
        }else if (input == "help" || input == "-h") {
            vector<string> DevModeMenuC = {
                "╔════════════════════════════════════╗",
                "║           Dev Mode C Menu          ║",
                "╠════════════════════════════════════╣",
                "║ mkp        | Make a new C project  ║",
                "║ run        | Compile/Run project   ║",
                "║ add        | Add header file (.c)  ║",
                "║ show -hd   | Show added headers    ║",
                "║ help/-h    | Show this menu        ║",
                "║ exit       | Exit Dev Mode         ║",
                "╚════════════════════════════════════╝"
            };
            for (const string& s : DevModeMenuC) {
                Sleep(50);
                SetColor(5);
                cout << s << endl;
            }
        }else {
            SetColor(4);
            cout<<"Error Command ("<<input<<") not Invalid!\n";

        }
    }
}

void HexTermCore::DevModeCpp() {
    string templateAsCpp =
        "#include <iostream>\n\n"
        "using namespace std;\n\n"
        "int main(){\n"
        "    cout << \"Hello World\" << endl;\n"
        "    return 0;\n}\n";

    bool exitFlag = false;
    string FileName;
    vector<string> headerFiles;

    while (!exitFlag) {
        string input;
        SetColor(ColorPrompt);
        cout<<"HexTerm@(C++-Lang)>>"<<CurrentUser<<": ";
        getline(cin, input);

        // mkp
        if ((input.substr(0,3) == "mkp" || input.substr(0,3) == "MKP") && input.size() > 4) {
            string target = input.substr(4);
            replace(target.begin(), target.end(), ' ', '_'); // جایگزین فاصله
            FileName = target;
            ofstream file(target+".cpp");
            if (file.is_open()) {
                file << templateAsCpp;
                SetColor(6);
                cout<<"Project "<<FileName<<".cpp created.\n";
            } else {
                SetColor(4);
                cout<<"Error To Make C++ File\n";
            }
        }

        // run
        else if (input == "run") {
            if (FileName.empty()) {
                SetColor(6);
                cout<<"First Make A Project And Try Again (mkp Project-Name)\n";
            } else {
                if (IsProgramInstaled("g++")) {
                    string run = "g++ " + FileName + ".cpp";
                    for (const string& s : headerFiles) run += " " + s;
                    run += " -o " + FileName + ".exe";

                    int res = system(run.c_str());
                    if (res == 0) {
                        SetColor(15);
                        system(string(FileName+".exe").c_str());
                        cout<<"\n\n";
                    } else {
                        SetColor(4);
                        cout<<"Compilation Failed...\n";
                    }
                } else {
                    SetColor(4);
                    cout<<"g++ Is Not Installed On your PC\n";
                }
            }
        }

        // add
        else if (input == "add") {
            bool addEnd =  false;
            while (!addEnd) {
                SetColor(15);
                cout<<"Enter header source (without .cpp, enter 0 to end): ";
                string name;
                SetColor(ColorPrompt);
                getline(cin, name);
                if (name != "0") {
                    headerFiles.emplace_back(name+".cpp");
                } else {
                    addEnd = true;
                    SetColor(6);
                    cout<<"Header Files Added...\n";
                }
            }
        }else if (input == "show -hd") {
            int i = 1;
            for (const string& s : headerFiles) {
                cout << "header: "<< i << ". " << s << endl;
                i++;
            }
        }else if (input == "help" || input == "-h") {
            vector<string> DevModeMenuCPP = {
                "╔════════════════════════════════════╗",
                "║           Dev Mode C Menu          ║",
                "╠════════════════════════════════════╣",
                "║ mkp        | Make a new C project  ║",
                "║ run        | Compile/Run project   ║",
                "║ add        | Add header file (.cpp)║",
                "║ show -hd   | Show added headers    ║",
                "║ help/-h    | Show this menu        ║",
                "║ exit       | Exit Dev Mode         ║",
                "╚════════════════════════════════════╝"
            };
            for (const string& s : DevModeMenuCPP) {
                Sleep(50);
                SetColor(5);
                cout << s << endl;
            }
        }else {
            SetColor(4);
            cout<<"Error Command ("<<input<<") not Invalid!\n";

        }
    }
}
void HexTermCore::DevModeNode() {
    string templateAsNode = "console.log(\"Hello World\");\n";
    bool exitFlag = false;
    string FileName;
    vector<string> installedPackages;

    while (!exitFlag) {
        string input;
        SetColor(ColorPrompt);
        cout << "HexTerm@(Node-Lang)>>" << CurrentUser << ": ";
        getline(cin, input);

        // mkp
        if ((input.substr(0,3) == "mkp" || input.substr(0,3) == "MKP") && input.size() > 4) {
            string target = input.substr(4);
            replace(target.begin(), target.end(), ' ', '_');
            FileName = target;
            ofstream file(target + ".js");
            if (file.is_open()) {
                file << templateAsNode;
                SetColor(6);
                cout << "Project " << FileName << ".js created.\n";
            } else {
                SetColor(4);
                cout << "Error To Make Node.js File\n";
            }
        }

        // run
        else if (input == "run") {
            if (FileName.empty()) {
                SetColor(6);
                cout << "First Make A Project And Try Again (mkp Project-Name)\n";
            } else {
                string cmd = "node " + FileName + ".js";
                int res = system(cmd.c_str());
                if (res != 0) {
                    SetColor(4);
                    cout << "Error To Run Node.js File\n";
                }
            }
        }

        // install package
        else if (input.substr(0,3) == "npi") {
            if (FileName.empty()) {
                SetColor(4);
                cout << "First Make A Node.js Project!\n";
                continue;
            }
            string pkg = input.substr(4);
            string installCmd = "npm install " + pkg;
            int res = system(installCmd.c_str());
            if (res != 0) {  // try yarn
                installCmd = "yarn add " + pkg;
                res = system(installCmd.c_str());
            }

            if (res == 0) {
                SetColor(6);
                cout << "Package " << pkg << " installed successfully.\n";
                installedPackages.push_back(pkg);

                // append require/import to file if not exists
                ifstream checkFile(FileName + ".js");
                string content, line;
                bool exists = false;
                while (getline(checkFile, line)) {
                    if (line.find("require('" + pkg + "')") != string::npos || line.find("import " + pkg) != string::npos) {
                        exists = true;
                    }
                    content += line + "\n";
                }
                checkFile.close();
                if (!exists) {
                    ofstream outFile(FileName + ".js");
                    outFile << "const " << pkg << " = require('" << pkg << "');\n" << content;
                    outFile.close();
                }
            } else {
                SetColor(4);
                cout << "Failed to install package: " << pkg << "\n";
            }
        }else if (input == "help" || input == "-h") {
            vector<string> DevModeMenuNode = {
                "╔════════════════════════════════════╗",
                "║        Dev Mode Node.js Menu       ║",
                "╠════════════════════════════════════╣",
                "║ mkp        | Make a new JS project ║",
                "║ run        | Run Node.js script    ║",
                "║ npi pkg    | Install Node package  ║",
                "║ show       | Show file content     ║",
                "║ help/-h    | Show this menu        ║",
                "║ exit       | Exit Dev Mode         ║",
                "╚════════════════════════════════════╝"
            };

            for (const string& s : DevModeMenuNode) {
                Sleep(50);
                SetColor(5);
                cout << s << endl;
            }
        }

        // exit
        else if (input == "exit") {
            exitFlag = true;
        }
    }
}

void HexTermCore::DevModePython() {
    string templateAsPy = "print(\"Hello World\")\n";
    bool exitFlag = false;
    string FileName;
    vector<string> installedPackages;

    while (!exitFlag) {
        string input;
        SetColor(ColorPrompt);
        cout << "HexTerm@(Python-Lang)>>" << CurrentUser << ": ";
        getline(cin, input);

        // mkp
        if ((input.substr(0,3) == "mkp" || input.substr(0,3) == "MKP") && input.size() > 4) {
            string target = input.substr(4);
            replace(target.begin(), target.end(), ' ', '_');
            FileName = target;
            ofstream file(target + ".py");
            if (file.is_open()) {
                file << templateAsPy;
                SetColor(6);
                cout << "Project " << FileName << ".py created.\n";
            } else {
                SetColor(4);
                cout << "Error To Make Python File\n";
            }
        }

        // run
        else if (input == "run") {
            if (FileName.empty()) {
                SetColor(6);
                cout << "First Make A Project And Try Again (mkp Project-Name)\n";
            } else {
                string cmd = "python " + FileName + ".py";
                int res = system(cmd.c_str());
                if (res != 0) {
                    cmd = "python3 " + FileName + ".py";
                    system(cmd.c_str());
                }
            }
        }

        // install package
        else if (input.substr(0,2) == "pi") {
            if (FileName.empty()) {
                SetColor(4);
                cout << "First Make A Python Project!\n";
                continue;
            }
            string pkg = input.substr(3);
            string installCmd = "pip install " + pkg;
            int res = system(installCmd.c_str());
            if (res != 0) {  // try pip3
                installCmd = "pip3 install " + pkg;
                res = system(installCmd.c_str());
            }

            if (res == 0) {
                SetColor(6);
                cout << "Package " << pkg << " installed successfully.\n";
                installedPackages.push_back(pkg);

                // append import to file if not exists
                ifstream checkFile(FileName + ".py");
                string content, line;
                bool exists = false;
                while (getline(checkFile, line)) {
                    if (line == "import " + pkg) exists = true;
                    content += line + "\n";
                }
                checkFile.close();
                if (!exists) {
                    ofstream outFile(FileName + ".py");
                    outFile << "import " << pkg << "\n" << content;
                    outFile.close();
                }
            } else {
                SetColor(4);
                cout << "Failed to install package: " << pkg << "\n";
            }
        }else if (input == "help" || input == "-h") {
            vector<string> DevModeMenuPython = {
                "╔════════════════════════════════════╗",
                "║        Dev Mode Python Menu        ║",
                "╠════════════════════════════════════╣",
                "║ mkp        | Make a new Python file║",
                "║ run        | Run Python script     ║",
                "║ pip pkg    | Install Python package║",
                "║ show       | Show file content     ║",
                "║ help/-h    | Show this menu        ║",
                "║ exit       | Exit Dev Mode         ║",
                "╚════════════════════════════════════╝"
            };

            for (const string& s : DevModeMenuPython) {
                Sleep(50);
                SetColor(5);
                cout << s << endl;
            }
        }

        // exit
        else if (input == "exit") {
            exitFlag = true;
        }
    }
}
void HexTermCore::devModeHex() {
    bool exitFlag = false;
    SetColor(6);

    SetColor(ColorPrompt);

    while (!exitFlag) {
        string input;
        cout << "HexTerm@(HexMode)>>" << CurrentUser << ": ";
        getline(cin, input);

        // خروج
        if (input == "exit") {
            exitFlag = true;
        }

        // help
        else if (input == "help") {
            SetColor(6);
            cout << "╔════════════════════════════════════════════════════════════════════╗\n";
            cout << "║                          dev-mode-hex Commands                     ║\n";
            cout << "╠════════════════════════════════════════════════════════════════════╣\n";
            cout << "║ show-hex file        | Convert file to hex and save as file-hex.txt║\n";
            cout << "║ marge file-hex.txt   | Restore copy of original file from hex      ║\n";
            cout << "║ repMarge file-hex.txt| Overwrite original file from hex            ║\n";
            cout << "║ help                 | Show this menu                              ║\n";
            cout << "║ exit                 | Exit Hex mode                               ║\n";
            cout << "╚════════════════════════════════════════════════════════════════════╝\n";
            RestColor();
        }

        // show-hex
        else if (input.substr(0, 8) == "show-hex") {
            string fileName = input.substr(9);
            ifstream fin(fileName, ios::binary);
            if (!fin.is_open()) {
                SetColor(4);
                cout << "║" << endl;
                cout << "╚══► Can't open file: " << fileName << endl;
            } else {
                string outName = fileName + "-hex.txt";
                ofstream fout(outName);
                unsigned char byte;
                while (fin.read(reinterpret_cast<char*>(&byte), 1)) {
                    fout << hex << (int)byte << " ";
                }
                fin.close();
                fout.close();
                SetColor(6);
                cout << "║" << endl;
                cout << "╚══► Hex file created: " << outName << endl;
                RestColor();
            }
        }

        // marge (copy)
        else if (input.substr(0, 5) == "marge") {
            string hexFile = input.substr(6);
            ifstream fin(hexFile);
            if (!fin.is_open()) {
                SetColor(4);
                cout << "║" << endl;
                cout << "╚══► Can't open hex file: " << hexFile << endl;
            } else {
                string origFile = hexFile;
                size_t pos = origFile.find("-hex.txt");
                if (pos != string::npos) origFile = origFile.substr(0, pos);
                string newFile = "restored_" + origFile;

                ofstream fout(newFile, ios::binary);
                string hexByte;
                while (fin >> hexByte) {
                    unsigned char byte = static_cast<unsigned char>(stoi(hexByte, nullptr, 16));
                    fout.put(byte);
                }
                fin.close();
                fout.close();
                SetColor(6);
                cout << "║" << endl;
                cout << "╚══► File restored as copy: " << newFile << endl;
                RestColor();
            }
        }

        // repMarge (overwrite original)
        else if (input.substr(0, 8) == "repMarge") {
            string hexFile = input.substr(9);
            ifstream fin(hexFile);
            if (!fin.is_open()) {
                SetColor(4);
                cout << "║" << endl;
                cout << "╚══► Can't open hex file: " << hexFile << endl;
            } else {
                string origFile = hexFile;
                size_t pos = origFile.find("-hex.txt");
                if (pos != string::npos) origFile = origFile.substr(0, pos);

                ofstream fout(origFile, ios::binary);
                string hexByte;
                while (fin >> hexByte) {
                    unsigned char byte = static_cast<unsigned char>(stoi(hexByte, nullptr, 16));
                    fout.put(byte);
                }
                fin.close();
                fout.close();
                SetColor(6);
                cout << "║" << endl;
                cout << "╚══► Original file overwritten: " << origFile << endl;
                RestColor();
            }
        }

        else {
            SetColor(4);
            cout << "Error Command (" << input << ") not valid! Type 'help' for menu.\n";
        }
    }
}

void HexTermCore::menu() {
    struct MenuItem {
        string command;
        string info;
    };

    vector<MenuItem> items = {
        {"cc", "Compile C file (gcc)"},
        {"cc+", "Compile C++ file (g++)"},
        {"py", "Run Python script"},
        {"nd", "Run Node.js script"},
        {"rt", "Start React/NPM project"},
        {"ipg", "Ping an IP address"},
        {"mkd", "Make directory"},
        {"mkf", "Make file"},
        {"rm", "Remove file"},
        {"rmd", "Remove directory"},
        {"ip", "Show network info (ipconfig)"},
        {"show", "Show content of a file"},
        {"ver", "Show HexTerm version"},
        {"dn", "Download file (curl)"},
        {"cls/clear", "Clear the console screen"},
        {"ch", "Change mode to cmd mode"},
        {"dev-mode-c", "Dev for C Language"},
        {"dev-mode-cpp", "Dev for C++ Language"},
        {"dev-mode-py", "Dev for Python Language"},
        {"dev-mode-nd", "Dev for Node.js"},
        {"dev-mode-hex", "Dev for Hex Editor"},
        {"help/-h", "Show this menu"}
    };

    // چاپ هدر جدول
    vector<string> tableHeader = {
        "╔═════════════════════════════════════════════╗",
        "║               HexTerm Menu                  ║",
        "╠═════════════════════════════════════════════╣",
        "║ Command        | Info                       ║",
        "╠═════════════════════════════════════════════╣"
    };

    SetColor(2);
    for (const string& line : tableHeader) {
        Sleep(50);
        cout << line << endl;
    }

    // چاپ آیتم‌ها
    for (const auto& item : items) {
        Sleep(50);
        cout << "║ "
             << setw(13) << left << item.command
             << " | "
             << setw(28) << left << item.info
             << "║" << endl;
    }

    // چاپ فوتر جدول
    cout << "╚═════════════════════════════════════════════╝" << endl;

    SetColor(15);
    cout << "Press Enter...";
    cin.get();
}
