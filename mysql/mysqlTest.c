#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>

int main(){
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
        int ret;
        char *server = "localhost";
        char *user = "root";
        char *password = "ydongj.com"; /* set me first */
        char *database = "yunpos_sit";
        conn=mysql_init(NULL);
        if (!mysql_real_connect(conn, server,
                                user, password, database, 0, NULL, 0)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
        }
        /* send SQL query */
        if (mysql_query(conn, "show tables")) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
        }

        res = mysql_use_result(conn);

        /* output table name */
        printf("MySQL Tables in mysql database:\n");
        while ((row = mysql_fetch_row(res)) != NULL)
                printf("%s \n", row[0]);

        /* close connection */
        mysql_free_result(res);
        mysql_close(conn);
        printf("%d\n",1);

}
