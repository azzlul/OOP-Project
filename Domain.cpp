#include "Domain.h"
#include <cassert>
void testConstr()
{
    Film fl("Titanic","Drama",1997,"Leonardo DiCaprio");
    assert(fl.getTitle() == "Titanic");
    assert(fl.getGenre() == "Drama");
    assert(fl.getYear() == 1997);
    assert(fl.getActor() == "Leonardo DiCaprio");
}

void testeDomain()
{
    testConstr();
}
