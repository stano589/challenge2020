#include <iostream>
#include <map>
#include <string>
#include <iostream>

#include <functional>

//
// supporting tools and software
//
// Validate and test your json commands
// https://jsonlint.com/

// RapidJSON : lots and lots of examples to help you use it properly
// https://github.com/Tencent/rapidjson
//

// std::function
// std::bind
// std::placeholders
// std::map
// std::make_pair

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;

/** @brief Implementation of some math functions
 * */
class MyMath{
    public:
    /** @brief Returns factorial of n, using recursion
     *  @param [in] n - value to calculate the factorial of
     *  @returns unsinged long long - calculated n!
     * */
    static unsigned long long factorial(int n){
        // end of recursion condition
        if(n==1) return 1;
        // recure for n-1
        return n*factorial(n-1);
    }

    /** @brief returns the n-th element of the fibbonaci series, 0 indexed
     *  @param [in] n - the number of the element to return
     *  @return int - n-th fibbonaci element
     * 
     *  @note if this was to be called frequently, switch to iterative method
     *        and memoisation with a table
     * */
    static int fibbonaci(int n){
        // end of recursion
        if(n==0 || n==1) return 1;
        // recure for (n-1) + (n-2)
        return fibbonaci(n-1) + fibbonaci(n-2);
    }

    /** @brief returns the x^y where x is the base and y the exponent
     *  @param [in] x - the base of the exponentiation
     *  @param [in] y - the exponent
     *  @returns int - x^y
     * 
     *  @note only positive base and exponent for this example, can be handled by exceptions
     *        Using square and multiply, could use std::pow(x,y), but since I implemented the other funcs
     *        I implemented this one as well
     * */
    static int exp(int x, unsigned int y){
        int result = 1;
        while(y > 0){
            if(y & 1){
                // y is odd, multiply
                result = result * x;
            }
            y = y >> 1; // division by 2
            x = x*x; // always square
        }
        return result;
    }
    private:
};


bool g_done = false;

//
// TEST COMMANDS
//
auto help_command = R"(
 {
  "command":"help",
  "payload": {
    "usage":"Enter json command in 'command':'<command>','payload': { // json payload of arguments }",
  }
 }
)";

auto exit_command = R"(
 {
  "command":"exit",
  "payload": {
     "reason":"Exiting program on user request."
  }
 }
)";

auto exp_command = R"(
 {
  "command":"exp",
  "payload": {
     "ops": [2, 10]
  }
 }
)";

auto fib_command = R"(
 {
  "command":"fib",
  "payload": {
     "n": 9
  }
 }
)";

auto fac_command = R"(
 {
  "command":"fac",
  "payload": {
     "n": 8
  }
 }
)";

auto non_existing = R"(
 {
  "command":"random",
  "payload": {
     "n": 8
  }
 }
)";

class Controller {
public:

    /**
     * @brief Prints help text
     * @param [in] payload - json payload to parse
     * @return bool - true if operation was succesful, false otherwise
     * */
    bool help(rapidjson::Value &payload)
    {
        cout << "Controller::help: command: ";

        // implement
        // payload should have a "usage" member
        bool rv = true;
        rapidjson::Value::ConstMemberIterator itrUsg = payload.FindMember("usage");

        if(itrUsg != payload.MemberEnd()){
            cout << itrUsg->value.GetString();
        }
        else{
            cout << "Member \"usage\" must be present in JSON payload" << endl;
            rv = false;
        }
        return rv;
    }

    /**
     * @brief Exits the dispatcher
     * @param [in] payload - json payload to parse
     * @return bool - true if operation was succesful, false otherwise
     * */
    bool exit(rapidjson::Value &payload)
    {
        cout << "Controller::exit: command: \n";

        // implement
        // payload should have a "reason"
        bool rv = true;
        rapidjson::Value::ConstMemberIterator itrRsn = payload.FindMember("reason");
        if(itrRsn != payload.MemberEnd()){
            // "reason" is present, print it and set global variable for exit to true
            cout << itrRsn->value.GetString() << endl;
            g_done = true;
        }
        else{
            cout << "Member \"reason\" must be present in JSON payload" << endl;
            rv = false;
        }

        return rv;
    }

    // implement 3-4 more commands

    /**
     * @brief Calculates x^y
     * @param [in] payload - json payload to parse
     * @return bool - true if operation was succesful, false otherwise
     * */
    bool exp(rapidjson::Value &payload)
    {   
        
        cout << "Controller::exp: command: \n";

        // implement
        // payload should have a "ops" member
        bool rv = true;
        rapidjson::Value::ConstMemberIterator itrOps = payload.FindMember("ops");
        if(itrOps != payload.MemberEnd()){
            const rapidjson::Value& array = payload["ops"];
            if(array.IsArray()){
                if(array.Size() == 2){
                    int x = array[0].GetInt();
                    int y = array[1].GetInt();
                    int result = MyMath::exp(x,y);
                    cout << "Result of func exp: " << result << endl;
                }
                else{
                    cout << "Member \"ops\" has wrong number of arguments." << endl;
                    rv = false;
                }
            }
            else{
                cout << "Member \"ops\" is not an array." << endl;
                rv = false;
            }

        }
        else{
            cout << "Member \"ops\" must be present in JSON payload" << endl;
            rv = false;
        }
        return rv;
    }

    /**
     * @brief Calculates the n-th element of the Fibbonaci series
     * @param [in] payload - json payload to parse
     * @return bool - true if operation was succesful, false otherwise
     * */
    bool fibbonaci(rapidjson::Value &payload)
    {
        cout << "Controller::fibbonaci: command: \n";

        // implement
         // payload should have a "n" member
        bool rv = true;
        rapidjson::Value::ConstMemberIterator itrN = payload.FindMember("n");
        if(itrN != payload.MemberEnd()){
            int n = itrN->value.GetInt();
            int result = MyMath::fibbonaci(n);
            cout << "Result of func fib: " << n << "-th value is: " << result << endl;
        }
        else{
            cout << "Member \"n\" must be present in JSON payload" << endl;
            rv = false;
        }

        return rv;
    }

    /**
     * @brief Calculates the n! = n*(n-1)*..*1
     * @param [in] payload - json payload to parse
     * @return bool - true if operation was succesful, false otherwise
     * */
    bool factorial(rapidjson::Value &payload)
    {
        cout << "Controller::factorial: command: \n";

        // implement
        // payload should have a "n" member
        bool rv = true;
        rapidjson::Value::ConstMemberIterator itrN = payload.FindMember("n");
        if(itrN != payload.MemberEnd()){
            int n = itrN->value.GetInt();
            unsigned long long int result = MyMath::factorial(n);
            cout << "Result of func factorial: n! = " << result << endl;
        }
        else{
            cout << "Member \"n\" must be present in JSON payload" << endl;
            rv = false;
        }

        return rv;
    }
};

// gimme ... this is actually tricky
// Bonus Question: why did I type cast this?
/*
    we only use the type CommandHandler, instead of bool(*)(rapidjson::Value &);
    it saves typing and is more clean

    later in main() we use std::bind to bind our command functions,
    which are also of bool(*)(rapidjson::Value &), and std::bind will return a std::function,
    so we can add those to our map and then call them from the dispatch method
*/
typedef std::function<bool(rapidjson::Value &)> CommandHandler;

class CommandDispatcher {
public:
    // ctor - need impl
    CommandDispatcher()
    {
        // using implicit constructor
    }

    // dtor - need impl
    virtual ~CommandDispatcher()
    {
        // question why is it virtual? Is it needed in this case?

        /** I dont think it is needed in this case.
         *  It would be needed if this class was a base class,
         *  and we would delete a dynamically alocated derived class from this class
         * */
    }

    bool addCommandHandler(std::string command, CommandHandler handler)
    {
        cout << "CommandDispatcher: addCommandHandler: " << command << std::endl;

        bool isInserted = true;

        auto rv = command_handlers_.insert(std::make_pair(command, handler));
        if(!rv.second){
            cout << "addCommandHandler error: Command \"" << command << "\" already exists!" << endl;
            isInserted = false;
        }

        //return true;
        return isInserted;
    }

    bool dispatchCommand(std::string command_json)
    {
        cout << "COMMAND: " << command_json << endl;

        // implement
        // result is true unless it changes along the execution
        bool result = true;

        // will use this to parse the json command
        rapidjson::Document doc;

        // parse the json command
        doc.Parse(command_json.c_str());

        if(doc.HasParseError()){
            result = false;
            cout << "dispatchCommand error: JSON Parse Error." << endl;
            return result;
        }

        // members "command" and "payload" should always be present
        // so we check if they are present
        // according to rapidjson docu this checks if member exists and obtains the value
        rapidjson::Value::ConstMemberIterator itrCmd = doc.FindMember("command");
        rapidjson::Value::ConstMemberIterator itrPld = doc.FindMember("payload");

        if(itrCmd != doc.MemberEnd()){
            // if we found the member, debug print its value
            cout << "Command is: " << itrCmd->value.GetString() << endl;
        }
        else{
            // not found, return false
            result = false;
            cout << "dispatchCommand error: member \"command\" not found" << endl;
            return result;
        }

        if(itrPld != doc.MemberEnd()){
            // if we found the member, debug print its value
            // we need to convert it to string first
            rapidjson::StringBuffer buff;
            rapidjson::Writer<StringBuffer> writer(buff);
            itrPld->value.Accept(writer);

            cout << "Payload is: " << buff.GetString() << endl;
        }
        else{
            // not found, return false
            result = false;
            cout << "dispatchCommand error: member \"payload\" not found" << endl;
            return result;
        }

        // at this point both member exist, lets call the corresponding function if it was added
        auto it = command_handlers_.find(itrCmd->value.GetString());
        if(it != command_handlers_.end()){
            // we have this handler stored, call it
            it->second(doc["payload"]);
        }
        else{
            cout << "dispatchCommand error: handler for command: " << itrCmd->value.GetString()
                 <<  " not found." << endl;
            result = false;
        }

        return result;
    }

private:

    // gimme ...
    // Maps a command to a handler function
    // e.g: command_handlers_["help"] has a pointer to the help command funuction
    std::map<std::string, CommandHandler> command_handlers_;


    // another gimme ...
    // Question: why delete these?
    /*
    * Answer: Generate a compiler error when copy is tried
    *         Meant to be uncopiable
    */

    // delete unused constructors
    CommandDispatcher (const CommandDispatcher&) = delete;
    CommandDispatcher& operator= (const CommandDispatcher&) = delete;

};

int main()
{
    std::cout << "COMMAND DISPATCHER: STARTED" << std::endl;

    CommandDispatcher command_dispatcher;
    Controller controller;                 // controller class of functions to "dispatch" from Command Dispatcher

    // Implement
    // add command handlers in Controller class to CommandDispatcher using addCommandHandler
    auto help_bind = std::bind(&Controller::help, controller, std::placeholders::_1);
    auto exit_bind = std::bind(&Controller::exit, controller, std::placeholders::_1);
    auto exp_bind = std::bind(&Controller::exp, controller, std::placeholders::_1);
    auto fib_bind = std::bind(&Controller::fibbonaci, controller, std::placeholders::_1);
    auto fac_bind = std::bind(&Controller::factorial, controller, std::placeholders::_1);

    command_dispatcher.addCommandHandler("help", help_bind);
    command_dispatcher.addCommandHandler("exit", exit_bind);
    command_dispatcher.addCommandHandler("exp", exp_bind);
    command_dispatcher.addCommandHandler("fib", fib_bind);
    command_dispatcher.addCommandHandler("fac", fac_bind);

    // gimme ...
    // command line interface

    // for testing
    string testStrings[] = {
        help_command,
        exp_command,
        fib_command,
        fac_command,
        non_existing
    };

    for(auto s : testStrings){
        cout << "TEST: Dispatching Command " << s << endl;
        command_dispatcher.dispatchCommand(s);
    }

    string command;
    while( ! g_done ) {
        cout << endl << endl << endl;
        cout << "COMMANDS: {\"command\":\"exit\", \"payload\":{\"reason\":\"User requested exit.\"}}\n";
        cout << "\tenter command : ";
        getline(cin, command);
        if(command == "\n" || command == "") continue;
        command_dispatcher.dispatchCommand(command);
    }

    std::cout << "COMMAND DISPATCHER: ENDED" << std::endl;
    return 0;
}