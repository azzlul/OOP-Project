#include "UI.h"
#include "Domain.h"
#include "iostream"
#include "string"

using std::cout;
using std::cin;
using std::getline;

void UI::printFilms(const vector<Film> &films) {
    for(const auto& film : films){
        cout<<"Titlu: "<<film.getTitle()<<
              " Gen: "<<film.getGenre()<<
              " An: "<<film.getYear()<<
              " Actor: "<<film.getActor()<<'\n';
    }
}

void UI::addUI() {
    string title, genre, actor;
    int year = 0;
    cout<<"Input title:";
    getline(cin, title);
    cout<<"Input genre:";
    getline(cin, genre);
    cout<<"Input release year:";
    cin>>year;
    getchar();
    cout<<"Input main actor:";
    getline(cin, actor);
    srv.addSrv(title, genre, year, actor);
    cout<<"Film added!\n";
}
void UI::updateUI() {
    string title, genre, actor;
    int year = 0;
    cout<<"Input title:";
    getline(cin, title);
    cout<<"Input genre:";
    getline(cin, genre);
    cout<<"Input release year:";
    cin>>year;
    getchar();
    cout<<"Input main actor:";
    getline(cin, actor);
    srv.updateSrv(title, genre, year, actor);
    cout<<"Film updated!\n";
}
void UI::deleteUI() {
    string title;
    cout<<"Input title:";
    getline(cin, title);
    srv.deleteSrv(title);
    cout<<"Film deleted!\n";
}

void UI::findUI() {
    string title;
    cout<<"Input title:";
    getline(cin, title);
    vector<Film> rez;
    rez.push_back(srv.findSrv(title));
    printFilms(rez);
}

void UI::filterUI() {
    int option = 0;
    string parameter;
    cout<<"Input option(1 - filter by title, 2 - filter by year):";
    cin>>option;
    getchar();
    cout<<"Input parameter";
    getline(cin, parameter);
    printFilms(srv.filter(option, parameter));
}

void UI::sortUI() {
    int option = 0;
    cout<<"Input option(1 - sort by title, 2 - sort by actor, 3 - sort by year and genre):";
    cin>>option;
    getchar();
    printFilms(srv.sort(option));
}

void UI::emptyCartUI() {
    srv.emptyCart();
    cout<<"Cart emptied!\n";
}
void UI::addCartUI() {
    string title;
    cout<<"Input title:";
    getline(cin, title);
    srv.addCart(title);
    cout<<"Film addded to cart!\n";
}

void UI::generateCartUI() {
    int nr= 0;
    cout<<"Input number: ";
    cin>>nr;
    getchar();
    srv.generateCart(nr);
    cout<<"Cart generated!\n";
}

void UI::printAllCart() {
    printFilms(srv.getAllCart());
}

void UI::getRapportUI() {
    auto rez = srv.getRapport();
    for(const auto& el:rez)
        cout<<el.first<<": "<<el.second<<'\n';
}
void UI::exportCVSUI() {
    string fileName;
    cout<<"File name:";
    getline(cin, fileName);
    srv.exportCVS(fileName);
    cout<<"File exported! \n";
}

void UI::undoUI() {
    bool ok = srv.undo();
    if(ok) cout<<"Undo done!\n";
    else cout<<"Nothing left to undo!\n";
}

void UI::runUI() {
    while(true){
        cout<<"add - add film\n"
              "update - update film\n"
              "delete - delete film\n"
              "find - find film\n"
              "filter - filter films\n"
              "sort - sort films\n"
              "empty - empty cart\n"
              "addCart - adds in cart\n"
              "generate - generate cart\n"
              "print - show films\n"
              "printCart - show cart\n"
              "rapport - generate rapport\n"
              "export - export to CVS file\n"
              "undo - undoes the last action\n"
              "exit - exit app\n";
        string cmd;
       getline(cin, cmd);
       try{
       if(cmd == "add") addUI();
       else if(cmd == "update") updateUI();
       else if(cmd == "delete") deleteUI();
       else if(cmd == "find") findUI();
       else if(cmd == "filter") filterUI();
       else if(cmd == "sort") sortUI();
       else if(cmd == "empty") emptyCartUI();
       else if(cmd == "addCart") addCartUI();
       else if(cmd == "generate") generateCartUI();
       else if(cmd == "print") printFilms(srv.getAll());
       else if(cmd == "printCart") printAllCart();
       else if(cmd == "rapport") getRapportUI();
       else if(cmd == "export") exportCVSUI();
       else if(cmd == "undo") undoUI();
       else if(cmd == "exit") return;
       else cout<<"Comanda invalida!\n";
       }
       catch (const RepositoryException& ex){
           cout<< ex << '\n';
       }
       catch (const ValidatorException& ex){
           cout<< ex << '\n';
       }
       cout<<srv.showCartSize()<<" filme in cos.\n";
    }
}
