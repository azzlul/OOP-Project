#pragma once
#include "string"
#include "Domain.h"
#include "vector"
#include "VectorTemplate.h"
using std::vector;
using std::string;
using std::ostream;

class Validator {
    public:
        /**
         * Verifies if the film fl is valid
         * A film is valid if: title, genre and actor are not empty strings
         *                     year is between 1 and 2024
         * Throws exception if film is not valid
         * @param fl = Film
         */
        static void validate(const Film& fl);
        /**
         * Verifies if a string is valid
         * A string is valid if it is not empty
         * Throws exception if the string si not valid
         * @param str = string
         */
        static void validateString(const string& str);
        /**
         * Verifies if an year is valid
         * A year is valid if it is between 1 and 2024
         * Throws eception if the year is not valid
         * @param year = int
         */
        static void validateYear(int year);
        /**
         * Verifies if a number is pozitive
         * Throws exception if the number is negative or 0
         * @param nr = int
         */
        static void validatePozInt(int nr);
};

class ValidatorException: public std::exception {
    Vector<string> msgs;
public:
    explicit ValidatorException(const Vector<string>& errors) :msgs{ errors } {}
    Vector<string> getMessages(){
        return msgs;
    }
    friend ostream& operator<<(ostream& out, const ValidatorException& ex);
};

void testeValidator();