/*
 *  main.cpp
 *
 *  COSC 052 Fall 2019
 *  Project #3
 *
 *  Due on: NOV 1, 2019
 *  Author: jsk142
 *
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 *
 *  References not otherwise commented within the program source code.
 *  Note that you should not mention any help from the TAs, the professor,
 *  or any code taken from the class textbooks.
 */

#include "main.h"


int main(int argc, const char * argv[])
{
    try
    {
        string inputFileName = "";

        // Check if argc is less than 2
        if ( argc < 2)
        {
           string errMsg = "Not enough command line arguments, ";
           errMsg += "please pass the complete path and name\n";
           errMsg += "processing cannot continue... goodbye.\n";

           throw invalid_argument(errMsg);
        }

        // Get full path and file name for the input data file
        inputFileName = argv[1];

        std::ifstream inFile;
        inFile.open(inputFileName);

        std::string errInStream = "the input stream is in a failed state,";
                    errInStream += " no processing can take place...\n";

        // Attemp to open the file
        if (!inFile)
        {
            throw std::logic_error(errInStream);
        }

        // Instantiate an object of class LL<char>
        LL<char> obj;
        
        // Populate the linked list
        obj.push_back('a');
        obj.push_front('z');
        obj.insert(0, 'e');
 
        cout << obj;

    }

    // Catch blocks for any exceptions objects that could be potentially thrown
    catch( bad_vehicle_code &bvc )
    {
        cout << "ERROR: caught bad_vehicle_code exception in function main\n";
        cout << bvc.what() << endl;
    }
    catch( invalid_argument &ia )
    {
        cout << "ERROR: caught invalid_argument exception in function main\n";
        cout << ia.what() << endl;
    }
    catch ( std::out_of_range &oor )
    {
        cout << "ERROR: caught out_of_range exception in function main\n";
        cout << oor.what() << endl;
    }
    catch( no_such_object &nso )
    {
        cout << "ERROR: caught no_such_object exception in function main\n";
        cout << nso.what() << endl;
    }
    catch( std::logic_error &le )
    {
        cout << "ERROR: caught logic_error exception in function main\n";
        cout << le.what() << endl;
    }
    catch( std::bad_alloc &ba )
    {
        cout << "ERROR: caught bad_alloc exception in function main\n";
        cout << ba.what() << endl;
    }
    catch(...)
    {
        cout << "ERROR: unknown exception caught in function main\n";
    }
        
    return 0;  

} // END function main	
