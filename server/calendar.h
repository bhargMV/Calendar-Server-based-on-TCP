#include<iostream>
#include<cstring>
#include<map>
#include<list>
#include<sstream>
using namespace std;

class entries;
class calendar
{
	map< int,list<entries> > data;
public:
	string add(int date,entries entry);
	string remove(int date,int begin);
	string update(int date,entries entry);
	string get(int date,int begin);
	string get(int date);
	string get_number();
	string get_ith(int i);
};

class entries
{
public:
	int begin;
	int end;
	string eve_name;
	entries(int,int,string);
	bool operator==(entries);
};

class calendar_users
{
public:
	map< string , calendar> data_user;
	calendar get_all_events_for_user(string username);
	void put_data_user(string username,calendar cal);
};

