
#define SCAN_H

#include<iostream>
#include<fstream>
#include<list>
#include<string>
#include<queue>
#include<stack>

#define MAX_LINE 2048

#define OTHER 100
#define NUM 200
#define ID 300
#define RESERVED 400
#define ENDL 500
#define ENDF 99
#define PARENT 999

#define VOID 401
#define INT 402

#define RETURN 411
#define IF 412
#define ELSE 413
#define WHILE 414

#define SEMI 101 //;
#define LSGWAL 102 //[
#define RSGWAL 103 //]
#define LGWAL 104 // (
#define RGWAL 105 //)
#define LCGWAL 106 //{
#define RCGWAL 107 //}
#define EQUAL 108 //=
#define RELOP 109 // < <= > >= == !=
#define ADDOP 110 //+ -
#define MULOP 111 //* /

#define SYNTAX_TREE 901
#define DEC_VAR 902
#define DEC_FUN 903
#define PARAM 904
#define COM_STMT 905
#define ASSIGN 906
#define SGNUM 907
#define OPERATOR 908
#define CALL 909
#define DEC 910
#define STMT 911
#define LOCDEC 912
#define EXP_STMT 913
#define EXP 914
#define VAR 915
#define AEXP 916
#define TERM 917
#define FACTOR 918
#define ARGS 919
#define IDEN 920



using namespace std;

#define LBF 512 //Line Buffer

struct lineInfo
{
	char textOfLine[LBF];
    int tokenType;
    int lineNum;
};

typedef struct lineInfo line;

typedef struct BinaryTree
{
    line token;
    int child;
    int tokenType;
    int isReturn;
}bTree;


list<line> cScanner(char * filename);