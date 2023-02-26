#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#include <iostream>
#include <pqxx/pqxx> 
/*
struct create_entry_ {

};*/

using namespace std;
using namespace pqxx;


void create_table() {
    const char* sql;

    //подумать, как можно ссылку на conn сделать, чтобы не прописывать

    connection conn("host=localhost port=5433 dbname=test_bd user=postgres password =1401");
    //connect();
    //------------------------------------------------------------------
        //cоздание тестовой таблицы company в бд

        /* Create SQL statement */
    sql = "CREATE TABLE COMPANY("  \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "AGE            INT     NOT NULL," \
        "ADDRESS        CHAR(50)," \
        "SALARY         REAL );";

    /* Create a transactional object. */
    work worker(conn);

    /* Execute SQL query */
    worker.exec(sql);
    worker.commit();
    cout << "Table created successfully" << endl;
}

void create_entry() {
    const char* sql;
    connection conn("host=localhost port=5433 dbname=test_bd user=postgres password =1401");
    //connect();
    //-------------------------------------------------------------------
        //создание записей

        /* Create SQL statement */
    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
        "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
        "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
        "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
        "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

    /* Create a transactional object. */
    work worker(conn);

    /* Execute SQL query */
    worker.exec(sql);
    worker.commit();
    cout << "Records created successfully" << endl;
}

void display_of_entry() {
    const char* sql;
    connection conn("host=localhost port=5433 dbname=test_bd user=postgres password =1401");
    //connect();
    //--------------------------------------------------
        //отображение записей

              /* Create SQL statement */
    sql = "SELECT * from COMPANY";

    /* Create a non-transactional object. */
    nontransaction non_trans(conn);

    /* Execute SQL query */
    result res(non_trans.exec(sql));

    /* List down all the records */
    for (result::const_iterator c = res.begin(); c != res.end(); ++c) {
        cout << "ID = " << c[0].as<int>() << endl;
        cout << "Name = " << c[1].as<string>() << endl;
        cout << "Age = " << c[2].as<int>() << endl;
        cout << "Address = " << c[3].as<string>() << endl;
        cout << "Salary = " << c[4].as<float>() << endl;
    }
    cout << "Operation done successfully" << endl;
}

void update() {
    const char* sql;
    connection conn("host=localhost port=5433 dbname=test_bd user=postgres password =1401");
    //connect();
    //------------------------------------------------------------------
        //обновление записи, извлечь и отобразить обновленные записи в таблице

        /* Create a transactional object. */
    work worker(conn);
    /* Create  SQL UPDATE statement */
    sql = "UPDATE COMPANY set SALARY = 25000.00 where ID=1";
    /* Execute SQL query */
    worker.exec(sql);
    worker.commit();
    cout << "Records updated successfully" << endl;

    /* Create SQL SELECT statement */
    sql = "SELECT * from COMPANY";

    /* Create a non-transactional object. */
    nontransaction non_trans(conn);

    /* Execute SQL query */
    result res(non_trans.exec(sql));

    /* List down all the records */
    for (result::const_iterator c = res.begin(); c != res.end(); ++c) {
        cout << "ID = " << c[0].as<int>() << endl;
        cout << "Name = " << c[1].as<string>() << endl;
        cout << "Age = " << c[2].as<int>() << endl;
        cout << "Address = " << c[3].as<string>() << endl;
        cout << "Salary = " << c[4].as<float>() << endl;
    }
    cout << "Operation done successfully" << endl;
}

void delete_entry_in_table() {
    const char* sql;
    connection conn("host=localhost port=5433 dbname=test_bd user=postgres password =1401");
    //connect();
    //--------------------------------------------------------
        //удаление записи, извлечь и отобразить обновленные записи в таблице

              /* Create a transactional object. */
    work worker(conn);
    /* Create  SQL DELETE statement */
    sql = "DELETE from COMPANY where ID = 2";
    /* Execute SQL query */
    worker.exec(sql);
    worker.commit();
    cout << "Records deleted successfully" << endl;

    /* Create SQL SELECT statement */
    sql = "SELECT * from COMPANY";

    /* Create a non-transactional object. */
    nontransaction non_trans(conn);

    /* Execute SQL query */
    result res(non_trans.exec(sql));

    /* List down all the records */
    for (result::const_iterator c = res.begin(); c != res.end(); ++c) {
        cout << "ID = " << c[0].as<int>() << endl;
        cout << "Name = " << c[1].as<string>() << endl;
        cout << "Age = " << c[2].as<int>() << endl;
        cout << "Address = " << c[3].as<string>() << endl;
        cout << "Salary = " << c[4].as<float>() << endl;
    }
    cout << "Operation done successfully" << endl;

}

/*
auto connect() {
    connection conn("host=localhost port=5433 dbname=test_bd user=postgres password =1401");
    if (conn.is_open()) {
        cout << "Opened database successfully: " << conn.dbname() << endl;
    }
    else {
        cout << "Can't open database" << endl;
        return 1;
    }
}*/

int main(int argc, char* argv[]) {
    const char* sql;

    try {
        connection conn("host=localhost port=5433 dbname=test_bd user=postgres password =1401");
        if (conn.is_open()) {
            cout << "Opened database successfully: " << conn.dbname() << endl;
        }
        else {
            cout << "Can't open database" << endl;
            return 1;
        }

        int var;
        cout << "Please, selec a menu item" << 
            "\n 1. Create table \n 2. Create entry \n 3. Display of entry "<<
            "\n 4. Update \n 5. Delete entry in table\n\n";
        cin >> var;
        switch (var)
        {
        case 1:
            create_table();
        case 2:
            create_entry();
        case 3:
            display_of_entry();
        case 4:
            update();
        case 5:
            delete_entry_in_table();
        }

        //connect();
        //----------------FUNC------------------
        //create_table();
        //create_entry();
        //display_of_entry();
        //update();
        //delete_entry_in_table();
        //---------------------------------------
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}