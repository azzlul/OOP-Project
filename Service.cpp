#include "Service.h"
#include "cassert"
#include "utility"
#include <algorithm>
#include <random>
#include <chrono>
#include "fstream"
using std::make_pair;
using std::make_unique;
const vector<Film>& Service::getAll() {
    return rep.getAll();
}
void Service::addSrv(const std::string &title, const std::string &genre, const int year, const std::string &author) {
    Film fl(title, genre, year, author);
    Validator::validate(fl);
    rep.add(fl);
    notify();
    undoActions.push_back(make_unique<UndoAdauga>(rep,fl));
}

void Service::updateSrv(const std::string &title, const std::string &genre, const int year, const std::string &actor) {
    Film fl(title, genre, year, actor);
    Validator::validate(fl);
    Film fl2 = rep.update(fl);
    notify();
    undoActions.push_back(make_unique<UndoModifica>(rep, fl2));
}
void Service::deleteSrv(const std::string &title) {
    Validator::validateString(title);
    Film fl = rep.del(title);
    undoActions.push_back(make_unique<UndoSterge>(rep, fl));
    auto it = find_if(cart.begin(), cart.end(), [=](Film& el){return el.getTitle() == title;});
    if(it != cart.end())cart.erase(it);
    notify();
}

const Film& Service::findSrv(const string &title) {
    Validator::validateString(title);
    return rep.find(title);
}

vector<Film> Service::filter(const int option, const string &parameter) {
    Validator::validateString(parameter);
    if(option == 1)
    {
        return filterFct([&](const Film& fl){return (fl.getTitle().find(parameter) != std::string::npos);});
    }
    else
    {
        int year = std::stoi(parameter);
        return filterFct([&](const Film& fl){return fl.getYear() <= year;});
    }
}

vector<Film> Service::filterFct(const function<bool(const Film &)>& fct) {
    vector<Film> rez;
    copy_if(rep.getAll().begin(), rep.getAll().end(), std::back_inserter(rez),fct);
    return rez;
}
vector<Film> Service::sort(int option) {
    if(option == 1)
    {
        return sortFct([](const Film& fl1, const Film& fl2) {return fl1.getTitle() <= fl2.getTitle();});
    }
    else if(option == 2)
    {
        return sortFct([&](const Film& fl1, const Film& fl2) {return fl1.getActor() <= fl2.getActor();});
    }
    else
    {
        return sortFct([&](const Film& fl1, const Film& fl2) {
            return make_pair(fl1.getYear(), fl1.getGenre()) <=
                make_pair(fl2.getYear(),fl2.getGenre());});
    }
}

vector<Film> Service::sortFct(const function<bool(const Film &, const Film &)> &fct) {
    vector<Film> rez{rep.getAll()};
    std::sort(rez.begin(), rez.end(),fct);
    return rez;
}

void Service::emptyCart() {
    cart.clear();
    notify();
}

void Service::addCart(const string& title) {
    Validator::validateString(title);
    cart.push_back(rep.find(title));
    notify();
}

void Service::generateCart(unsigned long long nr) {
    Validator::validatePozInt(nr);
    vector<Film> aux = rep.getAll();
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(aux.begin(),aux.end(), std::default_random_engine(seed));
    if(nr > aux.size()) nr = aux.size();
    for(unsigned long long  i = 0;i<nr;i++)
        cart.push_back(aux.at(i));
    notify();
}

size_t Service::showCartSize() {
    return cart.size();
}

vector<Film> &Service::getAllCart() {
    return cart;
}

map<string, int> Service::getRapport() {
    map<string, int> rez;
    for(const auto& el:rep.getAll())
    {
        if(rez.find(el.getGenre()) == rez.end()) rez[el.getGenre()] = 1;
        else rez[el.getGenre()]++;
    }
    return rez;
}

void Service::exportCVS(const string& fileName) {
    std::ofstream fout(fileName + ".csv");
    for(const auto& el:cart)
    {
        fout<<el.getTitle()<<','<<el.getGenre()<<','<<el.getYear()<<','<<el.getActor()<<'\n';
    }
    fout.close();
}

bool Service::undo() {
    if(undoActions.empty()) return false;
    unique_ptr<ActiuneUndo>& act = undoActions.back();
    act->doUndo();
    undoActions.pop_back();
    notify();
    return true;
}

void testAddSrv(){
    Repository rep;
    Service srv(rep);
    srv.addSrv("a", "a", 3, "a");
    srv.addSrv("b", "b", 4, "b");
    assert(srv.getAll().size() == 2);
}
void testUpdateSrv(){
    Repository rep;
    Service srv(rep);
    srv.addSrv("a", "a", 3, "a");
    srv.updateSrv("a", "a", 4, "a");
    assert(srv.getAll().at(0).getYear() == 4);
}
void testDeleteSrv(){
    Repository rep;
    Service srv(rep);
    srv.addSrv("a", "a", 3, "a");
    srv.deleteSrv("a");
    assert(srv.getAll().size() == 0);
}
void testFindSrv(){
    Repository rep;
    Service srv(rep);
    srv.addSrv("a", "a", 3, "a");
    assert(srv.findSrv("a").getYear() == 3);
}
void testFilterSrv(){
    Repository rep;
    Service srv(rep);
    srv.addSrv("a1", "a", 10, "a");
    srv.addSrv("a2", "a",7,"a");
    srv.addSrv("b", "a", 15,"a");
    assert(srv.filter(1,"a").size() == 2);
    assert(srv.filter(2, "10").size() == 2);
}
void testSortSrv(){
    Repository rep;
    Service srv(rep);
    srv.addSrv("a", "b", 3, "c");
    srv.addSrv("c", "c",10,"b");
    srv.addSrv("b", "a", 10,"a");
    vector<Film> rez1 = srv.sort(1), rez2 = srv.sort(2), rez3 = srv.sort(3);
    assert(rez1.at(0).getTitle() == "a");
    assert(rez1.at(1).getTitle() == "b");
    assert(rez1.at(2).getTitle() == "c");
    assert(rez2.at(0).getTitle() == "b");
    assert(rez2.at(1).getTitle() == "c");
    assert(rez2.at(2).getTitle() == "a");
    assert(rez3.at(0).getTitle() == "a");
    assert(rez3.at(1).getTitle() == "b");
    assert(rez3.at(2).getTitle() == "c");
}
void testCart(){
    Repository rep;
    Service srv(rep);
    srv.addSrv("a", "b", 3, "c");
    srv.addSrv("c", "c",10,"b");
    srv.addSrv("b", "a", 10,"a");
    srv.addCart("a");
    assert(srv.showCartSize() == 1);
    assert(srv.getAllCart().at(0).getYear() == 3);
    srv.deleteSrv("a");
    assert(srv.showCartSize() == 0);
    srv.addSrv("a", "b", 3, "c");
    srv.generateCart(3);
    assert(srv.showCartSize() == 3);
    srv.exportCVS("test");
    remove("test.csv");
    srv.emptyCart();
    assert(srv.showCartSize() == 0);
}
void testRapport(){
    Repository rep;
    Service srv(rep);
    srv.addSrv("a", "b", 3, "c");
    srv.addSrv("b", "c",10,"b");
    srv.addSrv("c", "a", 10,"a");
    srv.addSrv("d", "b", 3, "c");
    srv.addSrv("e", "c",10,"b");
    srv.addSrv("f", "a", 10,"a");
    auto rez = srv.getRapport();
    assert(rez["a"] == 2);
    assert(rez["b"] == 2);
    assert(rez["c"] == 2);
}
void testUndo(){
    Repository rep;
    Service srv(rep);
    srv.addSrv("a", "a", 3, "c");
    srv.undo();
    assert(srv.getAll().size() == 0);
    srv.addSrv("a", "a", 3, "a");
    srv.updateSrv("a", "b", 45, "b");
    srv.undo();
    assert(srv.getAll().at(0).getYear() == 3);
    srv.deleteSrv("a");
    srv.undo();
    assert(srv.getAll().size() == 1);
    srv.undo();
    assert(srv.undo() == 0);
}
void testeSrv(){
    testAddSrv();
    testUpdateSrv();
    testDeleteSrv();
    testFindSrv();
    testFilterSrv();
    testSortSrv();
    testCart();
    testRapport();
    testUndo();
}