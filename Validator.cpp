#include "Validator.h"
#include "cassert"
#include "sstream"

void Validator::validate(const Film &fl) {
    Vector<string> msgs;
    if(fl.getTitle().empty())msgs.add("Titlu vid!");
    if(fl.getGenre().empty())msgs.add("Gen vid!");
    if(fl.getYear() < 1 || fl.getYear() > 2024) msgs.add("An invalid!");
    if(fl.getActor().empty())msgs.add("Actor invalid!");
    if(msgs.size() != 0)
        throw ValidatorException(msgs);
}
void Validator::validateString(const std::string &str) {
    Vector<string> msgs;
    if(str.empty()) msgs.add("Valoare invalida!");
    if(msgs.size() != 0)
        throw ValidatorException(msgs);
}

void Validator::validateYear(int year) {
    Vector<string> msgs;
    if(year < 1 || year > 2024) msgs.add("Valoare invalida!");
    if(msgs.size()!= 0)
        throw ValidatorException(msgs);
}

void Validator::validatePozInt(int nr) {
    Vector<string> msgs;
    if(nr <= 0) msgs.add("Valoare invalida!");
    if(msgs.size()!= 0)
        throw ValidatorException(msgs);
}

ostream& operator<<(ostream& out, const ValidatorException& ex){
    for (const auto& msg : ex.msgs){
        out << msg << "\n";
    }
    return out;
}

void testValidatorFilm(){
    Film fl1("a","a", 3, "a");
    try{
        Validator::validate(fl1);
    }
    catch(const ValidatorException&){
        assert(false);
    }
    Film fl2("","",0,"");
    try{
        Validator::validate(fl2);
        assert(false);
    }
    catch(const ValidatorException& e){
        std::stringstream os;
        os << e;
        assert(os.str() == "Titlu vid!\nGen vid!\nAn invalid!\nActor invalid!\n");
    }
}

void testValidatorString(){
    try{
        Validator::validateString("a");
    }
    catch(const ValidatorException&){
        assert(false);
    }
    try{
        Validator::validateString("");
        assert(false);
    }
    catch (const ValidatorException&){}
}
void testValidatorYear(){
    try{
        Validator::validateYear(2000);
    }
    catch(const ValidatorException&){
        assert(false);
    }
    try{
        Validator::validateYear(-3);
        assert(false);
    }
    catch (const ValidatorException&){}
}
void testeValidator()
{
    testValidatorFilm();
    testValidatorString();
    testValidatorYear();
}