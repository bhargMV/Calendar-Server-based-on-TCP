#include "calendar.h"
#inclde<iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
using namespace std;

calendar_users cal_user;

entries::entries(int begin,int end,string eve_name)
{
	this->begin = begin;
	this->end = end;
	this->eve_name = eve_name;
}

string to_string(int a)
{
	ostringstream convert;   
	convert << a;      
	return convert.str();
}

bool entries::operator==(entries other)
{
	if(other.begin == begin && other.end == end &&
			other.eve_name == eve_name)
		return true;
	else
		return false;
}

string calendar::remove(int date,int begin)
{
	list<entries> list_date;
	list<entries>::iterator it;

	map<int,list<entries> >::iterator map_it;

	map_it = data.find(date);
	
	
	if(map_it == data.end())
	{
		return "There is No such date entry exists\n";
	}

	list_date = data.at(date);
	for(it=list_date.begin();it != list_date.end();it++)
	{
		if((*it).begin == begin){
			list_date.erase(it);
			data.at(date) = list_date;
			return "Successfully Removed\n";
		}
	}
	return "There is event for this begin time\n";

}

string calendar::add(int date,entries entry)
{

	list<entries> prev_entry;
	list<entries>::iterator it;
	map<int,list<entries> >::iterator prev_it;

	prev_it = data.find(date);

	if(prev_it == data.end())
	{
		data[date].push_back(entry);
		return "Date is successfully added\n"; 
	}else{

		prev_entry = data.at(date);

		if(prev_entry.empty())
		{
			prev_entry.push_back(entry);
			data.at(date) = prev_entry;
			return "Date is successfully added\n";
		}

		for (it = prev_entry.begin(); it != prev_entry.end(); it++)
		{

			if(entry.end <= (*it).begin)
			{
				prev_entry.insert(it,entry);
				data.at(date) = prev_entry;
				return "Date is successfully added\n";
			}
		
			else if(entry.begin > (*it).end)
			{

				if((*it) == prev_entry.back())
				{					
					prev_entry.push_back(entry);
					data.at(date) = prev_entry;
					return "Date is successfully added\n";
				}
				else
					continue;
			}
			else
				return "There is a conflict in date\n";
		}
	}
	return " unknown error happend\n";
}

string calendar::update(int date,entries entry)
{
	list<entries> list_date;
	list<entries>::iterator it;

	map<int,list<entries> >::iterator map_it;

	map_it = data.find(date);
	
	
	if(map_it == data.end())
	{
		return "There is  No such entry exists\n";
	}

	list_date = data.at(date);
	for(it=list_date.begin();it != list_date.end();it++)
	{
		if((*it).begin == entry.begin){
			(*it).end = entry.end;
			(*it).eve_name = entry.eve_name;
			data.at(date) = list_date;
			return "Successfully Updated\n";
		}
	}
	return "Unknown error happened\n";
}

void calendar_users::put_data_user(string username,calendar cal)
{
	data_user[username] = cal;
}



string calendar::get(int date,int begin)
{
	string result="";
	list<entries> list_date;
	list<entries>::iterator it;

	map<int,list<entries> >::iterator map_it;

	map_it = data.find(date);
	
	
	if(map_it == data.end())
	{
		return "NO ENTRY FOR "+to_string(date)+"\n";
	}

	list_date = data.at(date);

	result += to_string(date);
	result += "\n";
	for(it=list_date.begin();it != list_date.end();it++)
	{
		
		if((*it).begin == begin){
			result += "\tStart:";
			result += to_string((*it).begin);
			result += " End:";
			result += to_string((*it).end);
			result += " eve_name:";
			result += (*it).eve_name;
			result += "\n";
			return result;
		}
	}

	return "Entry not exist\n";
}


string calendar::get(int date)
{
	string result="";
	list<entries> list_date;
	list<entries>::iterator it;

	map<int,list<entries> >::iterator map_it;

	map_it = data.find(date);

	if(map_it == data.end())
	{
		return "Thers NO ENTRY FOR "+to_string(date)+"/n";
	}

	list_date = data.at(date);

	result += to_string(date);
	result += "\n";
	for(it=list_date.begin();it != list_date.end();it++){
	
		result += "\tStart:";
		result += to_string((*it).begin);
		result += " End:";
		result += to_string((*it).end);
		result += " eve_name:";
		result += (*it).eve_name;
		result += "\n";
	}

	return result;
}

string calendar::get_number()
{
	int number = 0;
	map<int,list<entries> >::iterator map_it;

	for(map_it = data.begin();map_it != data.end();map_it++){
		number += (map_it->second).size() ;
	}
	return to_string(number);
}


calendar calendar_users::get_all_events_for_user(string username)
{

	calendar a;
	map<string,calendar>::iterator c = data_user.find(username);
	if(c != data_user.end())
		return data_user.at(username);
	else
		data_user[username] = a;
	return data_user[username];
}


