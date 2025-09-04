#include <iostream>
#include "HexCore/HexTermCore.h"

using json = nlohmann::json;

vector<any> jsonConfig();

int main() {
    SetConsoleOutputCP(CP_UTF8);
    HexTermCore api;
    vector<any> data = jsonConfig();
    api.init(any_cast<bool>(data[2]),any_cast<bool>(data[3]),any_cast<int>(data[1]),any_cast<int>(data[0]));
    system("pause");
    return 0;
}

vector<any> jsonConfig() {

    int defaultResponseColor = 6;
    int defaultPromptColor   = 2;
    bool defaultMusic        = true;
    bool defaultMode         = true;


    int responseColor = defaultResponseColor;
    int promptColor   = defaultPromptColor;
    bool music        = defaultMusic;
    bool mode         = defaultMode;

    fstream ConfigFile("Config\\Config.json");
    if (ConfigFile.is_open()) {
        json Config;
        try {
            ConfigFile >> Config;

            if (Config.contains("HexTermResponseColor")) {
                if (Config["HexTermResponseColor"].is_number_integer()) {
                    responseColor = Config["HexTermResponseColor"].get<int>();
                } else if (Config["HexTermResponseColor"].is_string()) {
                    try {
                        responseColor = stoi(Config["HexTermResponseColor"].get<string>());
                    } catch (...) {}
                }
            }

            // رنگ پرامپت
            if (Config.contains("HexTermPromptColor")) {
                if (Config["HexTermPromptColor"].is_number_integer()) {
                    promptColor = Config["HexTermPromptColor"].get<int>();
                } else if (Config["HexTermPromptColor"].is_string()) {
                    try {
                        promptColor = stoi(Config["HexTermPromptColor"].get<string>());
                    } catch (...) {}
                }
            }


            if (Config.contains("HexTermMusic") && Config["HexTermMusic"].is_boolean()) {
                music = Config["HexTermMusic"].get<bool>();
            }


            if (Config.contains("HexTermMode") && Config["HexTermMode"].is_boolean()) {
                mode = Config["HexTermMode"].get<bool>();
            }

        } catch (json::parse_error& e) {
            cout << "Error parsing JSON file" << endl;
        }
    } else {
        cout << "Error opening file" << endl;
    }

    return {responseColor, promptColor, music, mode};
}
