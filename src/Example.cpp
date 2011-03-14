#include "include/Example.h"
#include <core/Global.h>
#include <iostream>
#include <algorithm>
#include <boost/algorithm/string.hpp>

extern "C" ModuleInterface* create()
{
    return new Example;
}

extern "C" void destroy(ModuleInterface* x)
{
    delete x;
}

Example::Example()
{
}

Example::~Example()
{
    stop();
	Global::Instance().get_IrcData().DelConsumer(mpDataInterface);
    delete mpDataInterface;
}
void Example::Init(DataInterface* pData)
{
	mpDataInterface = pData;
	mpDataInterface->Init(true, false, false, true);
    Global::Instance().get_IrcData().AddConsumer(mpDataInterface);

    timerlong();
}


void Example::stop()
{
    run = false;
    mpDataInterface->stop();
    std::cout << "Example::stop" << std::endl;
    raw_parse_thread->join();
    std::cout << "raw_parse_thread stopped" << std::endl;
    privmsg_parse_thread->join();
    std::cout << "privmsg_parse_thread stopped" << std::endl;
}

void Example::read()
{
    run = true;
    assert(!raw_parse_thread);
    raw_parse_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&Example::parse_raw, this)));
    assert(!privmsg_parse_thread);
    privmsg_parse_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&Example::parse_privmsg, this)));
}

void Example::parse_raw()
{
    std::vector< std::string > data;
    while(run)
    {
        data = mpDataInterface->GetRawQueue();
        ParseData(data);
    }
}

void Example::parse_privmsg()
{
    std::vector< std::string > data;
    while(run)
    {
        data = mpDataInterface->GetPrivmsgQueue();
        ParsePrivmsg(data);
    }
}


void Example::ParseData(std::vector< std::string > data)
{
	;
}


void Example::ParsePrivmsg(std::vector< std::string > data)
{
	Sample();
}

void Example::Sample()
{
	;
}

void Example::timerrun()
{
    int Tijd;
    time_t t= time(0);
    Tijd = t;
    longtime++;
    if (longtime >= 30)
    {
    	std::cout << "timed" << std::endl;
        timerlong();
        longtime = 0;
    }
    for (int i = timer_sec.size() - 1; i >= 0; i--)
    {
        if (timer_sec[i] < Tijd)
        {
            std::cout << timer_command[i] << std::endl;
            timer_sec.erase(timer_sec.begin()+i);
            timer_command.erase(timer_command.begin()+i);
        }
    }
}

void Example::timerlong()
{
    int Tijd;
    time_t t= time(0);
    Tijd = t;
    Tijd = Tijd + 100;
    for (int i = timer_long_sec.size() - 1; i >= 0; i--)
    {
        if (timer_long_sec[i] < Tijd)
        {
            std::cout << "timer_long to timer " << timer_long_command[i] << std::endl;
            timer_sec.push_back(timer_long_sec[i]);
            timer_command.push_back(timer_long_command[i]);
            timer_long_sec.erase(timer_long_sec.begin()+i);
            timer_long_command.erase(timer_long_command.begin()+i);
        }
    }
}
