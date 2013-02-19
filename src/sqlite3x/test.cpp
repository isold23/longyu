#include <iostream>
#include <stdexcept>
using namespace std;

#include "sqlite3x.hpp"
#pragma comment( lib, "sqlite3x.lib" )
using namespace sqlite3x;

int main(void) {

	try {
		sqlite3_connection con("test.db");

		int count=con.executeint("select count(*) from sqlite_master where name='t_test';");
		if(count==0) con.executenonquery("create table t_test(number,string);");

		sqlite3_transaction trans(con);

		{
			sqlite3_command cmd(con, "insert into t_test values(?,?);");
			cmd.bind(2, "foobar", 6);

			for(int i=0; i<10000; i++) {
				cmd.bind(1, (int)i);
				cmd.executenonquery();
			}
		}

		trans.commit();

		con.close();
	}
	catch(exception &ex) {
		cerr << "Exception Occured: " << ex.what() << endl;
	}


	try {
		sqlite3_connection con("test.db");

		{
			sqlite3_command cmd(con, "select * from t_test;");
			sqlite3_reader reader=cmd.executereader();

			while(reader.read())
				cout << reader.getcolname(0) << ": " << reader.getint(0) << endl;
		}

		con.close();
	}
	catch(exception &ex) {
		cerr << "Exception Occured: " << ex.what() << endl;
	}

	return 0;
}
