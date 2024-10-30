//
// Created by galal on 26.04.2024.
//

#include "RepositoryFile.h"
#include "fstream"
#include "sstream"
#include "iostream"
using std::ifstream;
using std::ofstream;
using std::getline;
using std::stoi;
using std::stringstream;
void RepositoryFile::saveToCSV() {
    std::ofstream ofs;
    ofs.open(file_path, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofstream fout(file_path);
    for(const auto& el : films) {
        fout << el.getTitle() << ',' << el.getGenre() << ',' << el.getYear() << ',' << el.getActor() << '\n';
    }
    fout.close();
}

void RepositoryFile::loadFromCSV() {
    ifstream fin(file_path);
    string line;
    string delimiter = ",";
    films.clear();
    while(!getline(fin, line).eof())
    {
        string title = line.substr(0, line.find(delimiter));
        line.erase(0, line.find(delimiter) + delimiter.length());
        string genre = line.substr(0, line.find(delimiter));
        line.erase(0, line.find(delimiter) + delimiter.length());
        string year = line.substr(0, line.find(delimiter));
        line.erase(0, line.find(delimiter) + delimiter.length());
        string author = line.substr(0, line.find(delimiter));
        films.emplace_back(title, genre,stoi(year),author);
    }
    fin.close();
}

void RepositoryFile::add(const Film &fl) {
    loadFromCSV();
    Repository::add(fl);
    saveToCSV();
}

const Film & RepositoryFile::find(const string &title) {
    loadFromCSV();
    return Repository::find(title);
}

const vector<Film> & RepositoryFile::getAll() {
    loadFromCSV();
    return Repository::getAll();
}

Film RepositoryFile::update(const Film &fl) {
    loadFromCSV();
    auto rez = Repository::update(fl);
    saveToCSV();
    return rez;
}

Film RepositoryFile::del(const string &title) {
    loadFromCSV();
    auto rez= Repository::del(title);
    saveToCSV();
    return rez;
}

void testAddFile()
{
    std::ofstream ofs;
    ofs.open("../test.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    RepositoryFile rep("../test.csv");
    rep.add(Film("a","b",2,"c"));
    rep.add(Film("b","c", 3, "d"));
    assert(rep.getAll().size() == 2);
    assert(rep.find("a").getYear() == 2);
    try{
        rep.add(Film("a","b",2,"c"));
        assert(false);
    }
    catch (const RepositoryException& e)
    {
        stringstream os;
        os << e;
        assert(os.str() == "Filmul dat exista deja!");
    }
}

void testFindFile()
{
    std::ofstream ofs;
    ofs.open("../test.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    RepositoryFile rep("../test.csv");
    rep.add(Film("a","b",2,"c"));
    rep.add(Film("b","c", 3, "d"));
    assert(rep.find("a").getYear() == 2);
    try{
        auto result = rep.find("c");
        assert(false);
    }
    catch(const RepositoryException& e){
        stringstream os;
        os << e;
        assert(os.str() == "Nu exista film cu titlul dat!");
    }
}

void testUpdateFile()
{
    std::ofstream ofs;
    ofs.open("../test.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    RepositoryFile rep("../test.csv");
    rep.add(Film("a","b",2,"c"));
    rep.update(Film("a","c", 3, "d"));
    assert(rep.find("a").getYear() == 3);
    try{
        rep.update(Film("c","b",2,"c"));
        assert(false);
    }
    catch (const RepositoryException& e)
    {
        stringstream os;
        os << e;
        assert(os.str() == "Filmul dat nu exista!");
    }
}
void testDeleteFile()
{
    std::ofstream ofs;
    ofs.open("../test.csv", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    RepositoryFile rep("../test.csv");
    rep.add(Film("a","b",2,"c"));
    rep.del("a");
    assert(rep.getAll().empty());
    try{
        rep.del("a");
        assert(false);
    }
    catch (const RepositoryException& e)
    {
        stringstream os;
        os << e;
        assert(os.str() == "Filmul cu titlul dat nu exista!");
    }
}

void testeRepoFile()
{
    testAddFile();
    testFindFile();
    testUpdateFile();
    testDeleteFile();
}
