#include <iostream>
#include "ofxGPIO.h"

int main()
{
	Zenity z;

	/* popup confirm */
        Log( z.dialog("Are you sure?", "No", "Yes") ) << "\n";

	/* popup warning */
        Log( z.warning("Attention danger!") ) << "\n";

	/* slide */
        Log( z.slide("Time LED blink", 0,10,5,1) ) << "\n";

	/* text area */
        Log( z.info("Text Information") ) << "\n";

	/*
		Use struct: Grid for creation Radio or Check list
		Grid expected: 
			vector<string> colum   
			vector<string> listnam 
			vector<bool>   check   


		     check         listname
		--------------------------------
	colum:	|    Value     |   Name        |  
		--------------------------------
		|    true      |   desc 1      |
		|    false     |   desc 2      |
		|    false     |   desc 3      |
		|    false     |   desc 4      |
		--------------------------------		     
	*/

        Grid g;
        g.colum.push_back("Value"); g.colum.push_back("Name Led");
        g.check.push_back(true);    g.listname.push_back("led 1");
        g.check.push_back(false);   g.listname.push_back("led 2"); 
        g.check.push_back(false);   g.listname.push_back("led 3");
        g.check.push_back(false);   g.listname.push_back("led 4"); 
        
	/* radio list (single selection) */
        Log( z.radiolist("Run single Led",g) ) << "\n"; 

	/* checkbox list (single selection) */
        Log( z.checklist("Run multiple Led",g) ) << "\n";

	return 0;
}
