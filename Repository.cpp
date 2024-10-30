#include "Repository.h"
#include "cassert"
#include "sstream"
using std::ostream;
using std::stringstream;

const Film& Repository::find(const std::string& title) {
    for(const auto& fl : films){
        if(fl.getTitle() == title) return fl;
    }
    throw RepositoryException("Nu exista film cu titlul dat!");
}

bool Repository::exist(const Film &fl) {
try{
    auto result = find(fl.getTitle());
    return true;
    }
catch (RepositoryException&){
    return false;
    }
}

void Repository::add(const Film& fl)
{
    if(exist(fl)) throw RepositoryException("Filmul dat exista deja!");
    films.push_back(fl);
}

const vector<Film>& Repository::getAll()
{
    return films;
}
 Film Repository::update(const Film &fl) {
    if(!exist(fl)) throw RepositoryException("Filmul dat nu exista!");
    Film fl_prev;
    for(auto& el:films)
    {
        if(el.getTitle() == fl.getTitle())
        {
            fl_prev = el;
            el = fl;
        }
    }
    return fl_prev;
}
Film Repository::del(const std::string& title) {
    auto it = find_if(films.begin(), films.end(), [=](Film& el){return el.getTitle() == title;});
    Film fl_prev;
    if (it != films.end())
    {
        fl_prev = *it;
        films.erase(it);
        return fl_prev;
    }
    throw RepositoryException("Filmul cu titlul dat nu exista!");
}
ostream& operator<<(ostream& out, const RepositoryException& ex){
    out << ex.msg;
    return out;
}

void testAdd()
{
    Repository rep;
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

void testFind()
{
    Repository rep;
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

void testUpdate()
{
    Repository rep;
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
void testDelete()
{
    Repository rep;
    rep.add(Film("a","b",2,"c"));
    rep.del("a");
    assert(rep.getAll().size() == 0);
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
void testeRepo()
{
    testAdd();
    testFind();
    testUpdate();
    testDelete();
}