#ifndef Example_H
#define Example_H
#include <interfaces/ModuleInterface.h>
#include <interfaces/DataInterface.h>
#include <string>
#include <vector>
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>

class DataInterface;
class Example : public ModuleInterface
{
public:
    Example();
    ~Example();
    void read();
    void stop();
    void Init(DataInterface* pData);
    void timerrun();

private:
	//vars

    bool run;

	//classes
    DataInterface* mpDataInterface;

	//timer vars
    std::vector<int> timer_sec;
    std::vector< std::string > timer_command;
    std::vector<int> timer_long_sec;
    std::vector< std::string > timer_long_command;
    int longtime;

	//thread vars
    boost::shared_ptr<boost::thread> raw_parse_thread;
    boost::shared_ptr<boost::thread> privmsg_parse_thread;

	//functions

	//parse functions
    void parse_raw();
    void parse_privmsg();
    void ParseData(std::vector< std::string > data);
    void ParsePrivmsg(std::vector< std::string > data);

    //post parse functions
    void Sample();

	//timer
    void timerlong();

};

#endif // Example_H

