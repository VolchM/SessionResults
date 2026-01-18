#include "UI/MainMenuPage.hpp"


int main() {
    system("chcp 1251 > nul");

    MainMenuPage menu("test.db");
    menu.Start();
}
