#ifndef ZENITY_H
    #define ZENITY_H

#include <iostream>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>

using namespace std;

struct Grid
{
	vector<string> colum;
	vector<string> listname; 
	vector<bool>   check; // check size == listname size
};

class Zenity
{
	public:
	string dialog(string t, string ok_btn="ok", string cn_btn="cancel")  
	{ 
		return command("zenity --question --text \""+t+"\" --ok-label=\""+ok_btn+"\" --cancel-label=\""+cn_btn+"\" 2> /dev/null; echo $?");
	}

	string warning(string t, string ok_btn="ok") 
	{ 
		return command("zenity --warning --text \""+t+"\" --ok-label=\""+ok_btn+"\" 2> /dev/null; echo $?");
	}

	string info(string t, string ok_btn="ok", string cn_btn="cancel")
	{ 
		return command("echo \""+t+"\"|zenity --text-info --width 530 --ok-label=\""+ok_btn+"\" --cancel-label=\""+cn_btn+"\" 2> /dev/null");
	}

	string slide(string t, int min, int max, int current=0, int step=2, string ok_btn="ok", string cn_btn="cancel" ) 
	{ 
		return command("ans=$(zenity --scale --text \""+t+"\" --ok-label=\""+ok_btn+"\" --cancel-label=\""+cn_btn+"\" --min-value="+to_string(min)+" --max-value="+to_string(max)+" --value="+to_string(current)+" --step "+to_string(step)+" 2> /dev/null);echo $ans"); 
	}

	string radiolist(string t, Grid grid, string ok_btn="ok", string cn_btn="cancel") 
	{
		string tmp;
		for(auto & g : grid.colum)
		{
			tmp+=" --column \""+g+"\"";
		}
		for(unsigned int i = 0; i < grid.listname.size(); i++)
		{
			tmp+=(grid.check[i]==0)?" FALSE ":" TRUE ";
			tmp+=" \""+grid.listname[i]+"\" ";
		}
		string r = "ans=$(zenity --list --text \""+t+"\" --radiolist "+tmp+" --ok-label=\""+ok_btn+"\" --cancel-label=\""+cn_btn+"\" 2> /dev/null); echo $ans";
		return command(r);
	}

	string checklist(string t, Grid grid, string separ=":", string ok_btn="ok", string cn_btn="cancel")
	{
		string tmp;
		for(auto & g : grid.colum)
		{
			tmp+=" --column \""+g+"\"";
		}
		for(unsigned int i = 0; i < grid.listname.size(); i++)
		{
			tmp+=(grid.check[i]==0)?" FALSE ":" TRUE ";
			tmp+=" \""+grid.listname[i]+"\" ";
		}
		string r = "ans=$(zenity --list --text \""+t+"\" --checklist  --separator=\""+separ+"\" "+tmp+" --ok-label=\""+ok_btn+"\" --cancel-label=\""+cn_btn+"\" 2> /dev/null); echo $ans";
		return command(r);
	}

	private:
	string command(string cmd) 
	{
	    array<char, 128> buffer;
	    string result;
	    shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
	    if (!pipe) throw runtime_error("popen() failed!");
	    while (!feof(pipe.get())) {
		if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
		    result += buffer.data();
	    }
	    result.erase(remove(result.begin(), result.end(), '\n'), result.end());
	    return result;
	}
};

#endif
