#include <gtest/gtest.h>
#include "utAtom.h"
#include "utStruct.h"
#include "utVariable.h"
#include "utList.h"
#include "utScanner.h"
#include "utParser.h"
#include "utIterator.h"
#include "expression.h"
#include "exception.h"

int main( int argc , char **argv )
{
    testing :: InitGoogleTest( &argc , argv ) ;
    return RUN_ALL_TESTS( ) ;
}
