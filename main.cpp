#include "2010105019_scan.h"
//Scanner source in scan.h -> scan.cpp



void dec_list(int level);
void dec(int level);
void param(int level);
void param_list(int level);
void param_list2(int level);
void compound_stmt(int level);
void local_dec(int level);
void stmt_list(int level);
void var_dec(int level);
void stmt(int level);
void exp_stmt(int level);
void return_stmt(int level);
void exp(int level);
void var(int level);
void simple_exp(int level);
void add_exp(int level);
void term(int level);
void add_exp2(int level);
void term2(int level);
void factor(int level);
void call(int level);
void args(int level);
void args_list(int level);
void args_list2(int level);
void ifstmt(int level);
void itestmt(int level);

void findType(int this_line);
void print_err( int num, char * token, string where, string expected,int type);
void id_num_check(int defined, int this_line);
void semi_check(int this_line);
void comma_check(int this_line);
void push(int type, int this_line);
void push_child(int this_line, int childType);
int push_child_else(int this_line, int childType);


void intence_go(int n);

void print_tree(int line_num);

list<line> tokens;
list<line>::iterator tokenPos;

list<bTree> pTree[MAX_LINE];
int pTreeType[MAX_LINE][2];
int line_cnt;
ofstream out;

int save_lsg;

int main(int argc, char * argv[])
{
    
    if(argc != 3)
    {
        cout << "Input the Parameter, Inputfile, Outputfile\n";
        return 0;
    }
    
    //inputfile : argv[1]
    //outputfile : argv[2]
    //enter : <endl>
    
    bTree empty;
    
    line_cnt = 0;
    tokens = cScanner(argv[1]);
    tokenPos=tokens.begin();
	out.open(argv[2]);
	/*
	line_cnt = 0;
    tokens = cScanner("2.txt");
    tokenPos=tokens.begin();
	out.open("output.txt");
	*/
    /*
    for(tokenPos = tokens.begin(); tokenPos != tokens.end(); tokenPos ++)
    {
        cout << tokenPos->textOfLine<<endl;
    }*/
    
    dec_list(0);
    
    print_tree(0);

    
    out.close();
    
    cout<<endl;
    return 0;
}



void print_tree(int line_num)
{
    list<bTree>::iterator pos1 = pTree[line_num].begin();

    int real_cnt = 0;
	int i;


    if(pTree[line_num].begin() != pTree[line_num].end())
    {
		//cout << pTreeType[line_num][0] << " " << pTreeType[line_num][1];
		if(pTreeType[line_num][0] != 0)
        {
				
				out<<endl;
				for ( i = 0 ; i < pTreeType[line_num][1] ; i ++)
				{
					out << " ";
				}
				switch(pTreeType[line_num][0])
				{
				case SYNTAX_TREE:
					out <<"Syntax Tree:";
					break;
				case DEC_VAR:
					out<<"Declare Variance: ";
					break;
				case DEC_FUN:
					out<<"Declare Function: ";
					break;
				case ASSIGN:
					out<<"Assign: ";
					break;
				case PARAM:
					out<<"Parameter: ";
					break;
				case COM_STMT:
					out<<"Compound Statement: ";
					break;
				case IF:
					out<<"If: ";
					break;
				case ELSE:
					out<<"Else: ";
					break;
				case WHILE:
					out<<"While: ";
					break;
				case RETURN:
					out<<"Return: ";
					break;
				case CALL:
					out<<"Call: ";
					break;
				case VAR:
					out<<"Identifier: ";
					break;
				case IDEN:
					out<<"Constant: ";
					break;
				case ADDOP:
				case MULOP:
				case RELOP:
					out<<"Operator: ";
					break;
				default:
					out <<"Unknown("<<pTreeType[line_num][0]<<")";
					break;
				}

        }
		//int save_lsg;
		list<bTree>::iterator pos2;
        for(pos1 = pTree[line_num].begin(); pos1 != pTree[line_num].end();pos1++)
        {
			if(strcmp((pos1->token).textOfLine,"<PARENT>") != 0)
			{
				if((pos1->token).tokenType == ID || (pos1->token).tokenType == NUM)
				{
					if(save_lsg == 1)
					{
						out<<"[ ";
						save_lsg = 0;
					}
					out<<(pos1->token).textOfLine<<" ";
				}
				else if(strcmp((pos1->token).textOfLine,"[") == 0)
				{
					pos2 = pos1;
					pos2++;
					if(strcmp((pos2->token).textOfLine,"]") == 0)
					{
						out<<(pos1->token).textOfLine<<" ";
					}
					save_lsg = 1;
				}
				else if(strcmp((pos1->token).textOfLine,"]") == 0)
				{
					save_lsg = 0;
					out<<(pos1->token).textOfLine<<" ";
				}
				else if(strcmp((pos1->token).textOfLine,"int") == 0 || strcmp((pos1->token).textOfLine,"void") == 0)
				{
					out<<(pos1->token).textOfLine<<" ";
				}
				else if(strcmp((pos1->token).textOfLine,"+") == 0 || strcmp((pos1->token).textOfLine,"-") == 0)
				{
					out<<(pos1->token).textOfLine<<" ";
				}
				else if(strcmp((pos1->token).textOfLine,"*") == 0 || strcmp((pos1->token).textOfLine,"/") == 0)
				{
					out<<(pos1->token).textOfLine<<" ";
				}
				else if(strcmp((pos1->token).textOfLine,"==") == 0 || strcmp((pos1->token).textOfLine,"!=") == 0|| strcmp((pos1->token).textOfLine,">") == 0|| strcmp((pos1->token).textOfLine,"<") == 0|| strcmp((pos1->token).textOfLine,"<=") == 0|| strcmp((pos1->token).textOfLine,">=") == 0)
				{
					out<<(pos1->token).textOfLine<<" ";
				}
			}
			else
			{
				print_tree(pos1->child);
			}
        }
    }
    
}

void push(int type, int this_line)
{
    bTree tmp;
    tmp.token = *tokenPos;
    tmp.tokenType = type;
    tmp.child = -1;
    pTree[this_line].push_back(tmp);
    tokenPos++;
}

void push_child(int this_line, int childType)
{
    bTree tmp;
    strcpy(tmp.token.textOfLine,"<PARENT>");
    tmp.child = ++line_cnt;
    tmp.tokenType = childType;
    pTree[this_line].push_back(tmp);
    
}

int push_child_else(int this_line, int childType)
{
    bTree tmp;
    strcpy(tmp.token.textOfLine,"<PARENT>");
    tmp.child = ++line_cnt;
    tmp.tokenType = childType;
    pTree[this_line].push_back(tmp);

	return line_cnt;
    
}

void dec_list(int level)
{
    int this_line = line_cnt;
    while(1)
    {
        if(tokenPos->tokenType == ENDF || tokenPos==tokens.end())
        {
            if(true)
                break;
        }
        pTreeType[this_line][0] = SYNTAX_TREE;
        pTreeType[this_line][1] = level;
        push_child(this_line,DEC);
        dec(level+1);
    }
}



void findType(int this_line)
{
    if(tokenPos -> tokenType == RESERVED && strcmp(tokenPos->textOfLine, "int"))
    {
        push(INT, this_line);
    }
    else if(tokenPos -> tokenType == RESERVED && strcmp(tokenPos->textOfLine, "void"))
    {
        push(VOID, this_line);
    }
    else
    {
        print_err(tokenPos->lineNum,tokenPos->textOfLine,"FINDTYPE","INTORVOID",tokenPos->tokenType);
    }
}

void print_err( int num, char * token, string where, string expected, int type)
{
    out<<"Syntax Error at line "<<num<<": unexpected Token -> ";
    if(type == ID)
    {
        out<<"ID, name="<<token<<endl;
    }
    else if(type == RESERVED)
    {
        out <<"reserved word: "<<token<<endl;
    }
    else if(type == NUM)
    {
        out<<"NUM, val="<<token<<endl;
    }
    else
    {
        out<<token<<endl;
    }
    
    //cout<<"where : "<<where<<"expected : "<<expected<<endl;
}

void id_num_check(int defined, int this_line)
{
    if(tokenPos->tokenType == defined)
    {
        push(defined, this_line);
    }
    else
    {
        print_err(tokenPos->lineNum,tokenPos->textOfLine,"IDNUMCHECK","IDORNUM",tokenPos->tokenType);
        
    }
}

void semi_check(int this_line)
{
    if(strcmp(tokenPos->textOfLine,";") != 0)
    {
        print_err(tokenPos->lineNum,tokenPos->textOfLine,"SEMICHECK",";",tokenPos->tokenType);
    }
    else
    {
        push(SEMI, this_line);
    }
}

void comma_check(int this_line)
{
    if(strcmp(tokenPos->textOfLine,",") != 0)
    {
        
        print_err(tokenPos->lineNum,tokenPos->textOfLine,"COMMACHECK",",",tokenPos->tokenType);
        //mustmodify
        //tokenPos++;
    }
    else
    {
        push(SEMI, this_line);
    }
}

void dec(int level)
{
    
    int expType;
    
    int this_line = line_cnt;
    
    findType(this_line);
    
    id_num_check(ID, this_line);
    
    if(strcmp(tokenPos->textOfLine,";") == 0)
    {
        push(SEMI, this_line);
        pTreeType[this_line][0] = DEC_VAR;
        pTreeType[this_line][1] = level;

    }
    else if(strcmp(tokenPos->textOfLine,"[") == 0)
    {
        //교제에 있는 C-언어의 정의에서 전역변수로 배열을 정의할때
        //ID [NUM]이 되기 때문에 다른 하위 Terminal로 넘어가지 않고 바로 종결. NUM만 있으면 되니.
		push(LSGWAL, this_line);

        
        id_num_check(NUM,this_line);
        
        if(strcmp(tokenPos->textOfLine,"]") != 0)
        {
            print_err(tokenPos->lineNum,tokenPos->textOfLine,"DEC","]",tokenPos->tokenType);

        }
        else
        {
            push(RSGWAL, this_line);

        }
        
        semi_check(this_line);
        
        pTreeType[this_line][0] = DEC_VAR;
        pTreeType[this_line][1] = level;
        
    }
    else if(strcmp(tokenPos->textOfLine,"(") == 0)//declare Function.
    {
        push(LGWAL, this_line);
        list<line>::iterator temp = tokenPos;
        temp++;
        if(strcmp(tokenPos->textOfLine,"void") == 0 && strcmp((temp)->textOfLine,")") == 0)
        {
            findType(this_line);
            push(RGWAL, this_line);
        }
        else
        {
            push_child(this_line,PARAM);
            param_list(level+1);
            
            if(strcmp(tokenPos->textOfLine,")") == 0 )
            {
                push(RGWAL, this_line);
                
            }
            else
            {
                print_err(tokenPos->lineNum,tokenPos->textOfLine,"DEC",")",tokenPos->tokenType);
            }
        }
        
        pTreeType[this_line][0] = DEC_FUN;
        pTreeType[this_line][1] = level;
        push_child(this_line,COM_STMT);
        compound_stmt(level+1);
        //semi_check(this_line);
        
    }
    else
    {
        
        print_err(tokenPos->lineNum,tokenPos->textOfLine,"DEC", "( or [",tokenPos->tokenType);
    }
    
}

void param_list(int level)
{
    int this_line = line_cnt;
    if(strcmp(tokenPos->textOfLine,")") != 0)
    {
        
        param(level);
        push_child(this_line,PARAM);
        param_list2(level);
    }
}

void param_list2(int level)
{
    int this_line = line_cnt;
    if(strcmp(tokenPos->textOfLine,",") == 0)
    {
        comma_check(this_line);
        param(level);
        push_child(this_line,PARAM);
        param_list2(level);
    }
    else
    {
        
    }
}

void param(int level)
{
    int this_line = line_cnt;
    pTreeType[this_line][0] = PARAM;
    pTreeType[this_line][1] = level;
	findType(this_line);
    id_num_check(ID,this_line);
    if(strcmp(tokenPos->textOfLine,"[") == 0)
    {
        //교제에 있는 C-언어의 정의에서 전역변수로 배열을 정의할때
        //ID [NUM]이 되기 때문에 다른 하위 Terminal로 넘어가지 않고 바로 종결. NUM만 있으면 되니.
        push(LSGWAL, this_line);
        
        if(strcmp(tokenPos->textOfLine,"]") != 0)
        {
            id_num_check(NUM,this_line);
            if(strcmp(tokenPos->textOfLine,"]") != 0)
            {
                print_err(tokenPos->lineNum,tokenPos->textOfLine,"PARAM","]",tokenPos->tokenType);
                
            }
            else
            {
                push(RSGWAL, this_line);
                
            }
        }
        else
        {
            
            push(RSGWAL, this_line);
            
        }
        
        
        
    }
    
}

void compound_stmt(int level)
{
    int this_line = line_cnt;
    if(strcmp(tokenPos->textOfLine,"{") == 0)
    {
        push(LCGWAL, this_line);
        
        push_child(this_line,LOCDEC);
        local_dec(level+1);
        
        push_child(this_line,STMT);
        stmt_list(level+1);
        
		pTreeType[this_line][0] = COM_STMT;
        pTreeType[this_line][1] = level;

        if(strcmp(tokenPos->textOfLine,"}") != 0)
        {
            print_err(tokenPos->lineNum,tokenPos->textOfLine,"COMPOUND_STMT","}",tokenPos->tokenType);
            
        }
        else
        {
            push(RCGWAL, this_line);
            
        }
    }
}

void local_dec(int level)
{
    int this_line = line_cnt;
    if(strcmp(tokenPos->textOfLine,"}") != 0)
    {
        
        while(1)
        {
            if(strcmp(tokenPos->textOfLine,"int") != 0 && strcmp(tokenPos->textOfLine,"void") !=0 )
            {
                
                break;
            }
            push_child(this_line,DEC_VAR);
            var_dec(level);
            
            if(strcmp(tokenPos->textOfLine,"}") == 0|| tokenPos ->tokenType == ENDF)
            {
                if(true)
                    break;
            }
            //semi_check(this_line);
        }
    }
}

void var_dec(int level)
{
    int this_line = line_cnt;
    

    findType(this_line);
    
    id_num_check(ID, this_line);
    
    if(strcmp(tokenPos->textOfLine,";") == 0)
    {
        push(SEMI, this_line);
        pTreeType[this_line][0] = DEC_VAR;
        pTreeType[this_line][1] = level;
    }
    else if(strcmp(tokenPos->textOfLine,"[") == 0)
    {
        //교제에 있는 C-언어의 정의에서 전역변수로 배열을 정의할때
        //ID [NUM]이 되기 때문에 다른 하위 Terminal로 넘어가지 않고 바로 종결. NUM만 있으면 되니.
        push(LSGWAL, this_line);
        
        
        id_num_check(NUM,this_line);
        
        if(strcmp(tokenPos->textOfLine,"]") != 0)
        {
            print_err(tokenPos->lineNum,tokenPos->textOfLine,"VAR_DEC","]",tokenPos->tokenType);
            
        }
        else
        {
            push(RSGWAL, this_line);
            
        }
        pTreeType[this_line][0] = DEC_VAR;
        pTreeType[this_line][1] = level;
        semi_check(this_line);
        
        
    }
    else
    {
        print_err(tokenPos->lineNum,tokenPos->textOfLine,"VAR_DEC","; or ]",tokenPos->tokenType);
    }
}

void stmt_list(int level)
{
    int this_line = line_cnt;
    if(strcmp(tokenPos->textOfLine,"}") != 0)
    {
        
        while(1)
        {
            push_child(this_line,STMT);
            stmt(level);
            if(strcmp(tokenPos->textOfLine,"}") == 0 || tokenPos ->tokenType == ENDF)
            {
                if(true)
                    break;
            }
            //semi_check(this_line);
        }
    }
}

void stmt(int level)
{
    int this_line = line_cnt;
    
    if(strcmp(tokenPos->textOfLine,"if") == 0)
    {
        push_child(this_line,IF);
        ifstmt(level);
    }
    else if(strcmp(tokenPos->textOfLine,"while") == 0)
    {
        push_child(this_line,WHILE);
        itestmt(level);
    }
    else if(strcmp(tokenPos->textOfLine,"return") == 0)
    {
        push_child(this_line,RETURN);
        return_stmt(level);
    }
    else if(strcmp(tokenPos->textOfLine,"{") == 0)
    {
        push_child(this_line,COM_STMT);
        compound_stmt(level);
    }
    else if(tokenPos->tokenType == ID || tokenPos->tokenType == NUM || strcmp(tokenPos->textOfLine,"(") == 0 || strcmp(tokenPos->textOfLine,";") == 0)
    {
        
        push_child(this_line,EXP_STMT);
        exp_stmt(level);
    }
    else
    {
        print_err(tokenPos->lineNum,tokenPos->textOfLine,"STMT","IF,WHILE,RETURN,{,ID,NUM,(,;",tokenPos->tokenType);

    }
    

}

void exp_stmt(int level)
{
    int this_line = line_cnt;
    if(strcmp(tokenPos->textOfLine,";") != 0)
    {
        push_child(this_line, EXP);
        exp(level);
    }
    semi_check(this_line);
    
}

void return_stmt(int level)
{
    int this_line = line_cnt;
    if(strcmp(tokenPos->textOfLine,"return") == 0)
    {
        push(RETURN, this_line);
        if(strcmp(tokenPos->textOfLine,";") != 0)
        {
            push_child(this_line,EXP);
            exp(level + 1);
        }
		pTreeType[this_line][0] = RETURN;
        pTreeType[this_line][1] = level;
        semi_check(this_line);
    }
}

void exp(int level)
{
    int this_line = line_cnt;
    int isAssign = 0;
    list<line>::iterator look_var;
    look_var = tokenPos;
    
    
    if(look_var->tokenType == ID)
    {
        look_var++;
        
        if(strcmp(look_var->textOfLine,"[")==0)
        {            while(1)
            {
                look_var ++;
                if(strcmp(look_var->textOfLine,"]")==0)
                {
                    
                    isAssign = 1;
                    look_var++;
                    break;
                }
                else if(look_var->tokenType == ENDF)
                {
                    break;
                }
            }
            
        }
        else
        {
            isAssign = 1;
        }
        //look_var++;
        if(strcmp(look_var->textOfLine,"=")==0 && isAssign == 1)
        {
			pTreeType[this_line][0] = ASSIGN;
			pTreeType[this_line][1] = level;
            push_child(this_line,VAR);
            var(level+1);
            push(EQUAL, this_line);
            push_child(this_line,EXP);
            exp(level+2);
            
            
        }
        else
        {
            push_child(this_line,EXP);
            simple_exp(level);
        }
    }
    else
    {
        push_child(this_line,EXP);
        simple_exp(level);
    }
    

}

void var(int level)
{
    int this_line = line_cnt;
    //cout<<tokenPos->textOfLine<<endl;

    push(ID, this_line);
    
    //cout<<tokenPos->textOfLine<<endl;

    if(strcmp(tokenPos->textOfLine,"[") == 0)
    {
        

        //push_child(this_line,EXP);
		push(LSGWAL,this_line);
		int else_to_go = push_child_else(this_line,EXP);
        
        exp(level+1);
        if(strcmp(tokenPos->textOfLine,"]") == 0)
        {
            push(RSGWAL, this_line);
        }
        else
        {
            print_err(tokenPos->lineNum,tokenPos->textOfLine,"VAR","]",tokenPos->tokenType);
        }
    }
	pTreeType[this_line][0] = VAR;
        pTreeType[this_line][1] = level;
}

void simple_exp(int level)
{
    int this_line = line_cnt;
    push_child(this_line,AEXP);
    add_exp(level);
    if(strcmp(tokenPos->textOfLine,"<=") == 0 || strcmp(tokenPos->textOfLine,"<") == 0 || strcmp(tokenPos->textOfLine,"!=") == 0 || strcmp(tokenPos->textOfLine,"==") == 0||strcmp(tokenPos->textOfLine,">=") == 0 || strcmp(tokenPos->textOfLine,">") == 0)
    {
		int else_to_go = push_child_else(this_line,RELOP);
        push(RELOP,else_to_go);
		pTreeType[else_to_go][0] = RELOP;
		pTreeType[else_to_go][1] = level;
        //push(RELOP, this_line);
        push_child(this_line,AEXP);
        add_exp(level+1);
    }

}

void add_exp(int level)
{
    int this_line = line_cnt;
    push_child(this_line,TERM);
    term(level);
    push_child(this_line,AEXP);
    add_exp2(level);
}

void add_exp2(int level)
{
    int this_line = line_cnt;
    if(strcmp(tokenPos->textOfLine,"+") == 0 || strcmp(tokenPos->textOfLine,"-") == 0 )
    {
		int else_to_go = push_child_else(this_line,ADDOP);
        push(ADDOP,else_to_go);
		pTreeType[else_to_go][0] = ADDOP;
		pTreeType[else_to_go][1] = level;

        //push(ADDOP, this_line);
        push_child(this_line,TERM);
        term(level+1);
        push_child(this_line,AEXP);
        add_exp2(level+1);
    }
    else
    {
        
    }

}

void term(int level)
{
    int this_line = line_cnt;
    push_child(this_line,FACTOR);
    factor(level);
    push_child(this_line,TERM);
    term2(level+1);
}

void term2(int level)
{
    int this_line = line_cnt;
    if(strcmp(tokenPos->textOfLine,"*") == 0 || strcmp(tokenPos->textOfLine,"/") == 0 )
    {
		int else_to_go = push_child_else(this_line,MULOP);
        push(MULOP,else_to_go);
		pTreeType[else_to_go][0] = MULOP;
		pTreeType[else_to_go][1] = level;
        //push(MULOP, this_line);
        push_child(this_line,FACTOR);
        factor(level);
        push_child(this_line,TERM);
        term2(level+1);
    }
    else
    {
        
    }

}

void factor(int level)
{
    int this_line = line_cnt;
    list<line>::iterator look_var;
    look_var = tokenPos;
    look_var ++;
    
    if(strcmp(tokenPos->textOfLine,"(") == 0 )
    {
        push(LGWAL,this_line);
        push_child(this_line,EXP);
        exp(level);
        push(RGWAL,this_line);
    }
    else if(tokenPos->tokenType == NUM )
    {
        push(NUM,this_line);
		pTreeType[this_line][0] = IDEN;
        pTreeType[this_line][1] = level;
    }
    else if(tokenPos->tokenType == ID)
    {
        if(strcmp(look_var->textOfLine,"(") == 0 )
        {
            push_child(this_line,CALL);
            call(level);
        }
        else
        {
            push_child(this_line,VAR);
            var(level);
        }
    }
    else
    {
        print_err(tokenPos->lineNum,tokenPos->textOfLine,"FACTOR","(, NUM, ID",tokenPos->tokenType);

    }
}

void call(int level)
{
    int this_line = line_cnt;
    push(ID,this_line);
    if(strcmp(tokenPos->textOfLine,"(") == 0 )
    {
        push(LGWAL,this_line);
        if(strcmp(tokenPos->textOfLine,")") == 0 )
        {
            push(RGWAL,this_line);

        }
        else
        {
            push_child(this_line,ARGS);
            args(level+1);
            if(strcmp(tokenPos->textOfLine,")") == 0 )
            {
                push(RGWAL,this_line);
                
            }
            else
            {
                print_err(tokenPos->lineNum,tokenPos->textOfLine,"CALL", ")",tokenPos->tokenType);
            }
        }
		pTreeType[this_line][0] = CALL;
        pTreeType[this_line][1] = level;
    }
    else
    {
        print_err(tokenPos->lineNum,tokenPos->textOfLine, "CALL", "(",tokenPos->tokenType);

    }
    
}

void args(int level)
{
    int this_line = line_cnt;
    push_child(this_line,ARGS);
    args_list(level);
    
}

void args_list(int level)
{
    int this_line = line_cnt;
    
    push_child(this_line,EXP);
    exp(level);
    push_child(this_line,ARGS);
    args_list2(level + 1);
}
void args_list2(int level)
{
    int this_line = line_cnt;
    if(strcmp(tokenPos->textOfLine,",") == 0 )
    {
        comma_check(this_line);
        push_child(this_line,EXP);
        exp(level);
        push_child(this_line,ARGS);
        args_list2(level+1);
    }
}

void ifstmt(int level)
{
    int this_line = line_cnt;
    
    push(IF, this_line);
    if(strcmp(tokenPos->textOfLine,"(") == 0 )
    {
        push(LGWAL, this_line);
        push_child(this_line,EXP);
        exp(level+1);
        if(strcmp(tokenPos->textOfLine,")") == 0 )
        {
            push(RGWAL,this_line);
        }
        else
        {
            print_err(tokenPos->lineNum,tokenPos->textOfLine,"IFSTMT", ")",tokenPos->tokenType);
        }
        push_child(this_line,STMT);
        
        
        //cout<<tokenPos->textOfLine<<endl;

        stmt(level+1);
        //cout<<tokenPos->textOfLine<<endl;
		pTreeType[this_line][0] = IF;
        pTreeType[this_line][1] = level;

        if( strcmp(tokenPos->textOfLine,"else") == 0 )
        {
			int else_to_go = push_child_else(this_line,STMT);
            push(ELSE,else_to_go);
			stmt(level+1);
			pTreeType[else_to_go][0] = ELSE;
			pTreeType[else_to_go][1] = level;
        }
		
    }
    else
    {
        print_err(tokenPos->lineNum,tokenPos->textOfLine, "IFSTMT","(",tokenPos->tokenType);

    }

    
}

void itestmt(int level)
{
    int this_line = line_cnt;
    push(WHILE, this_line);
    if(strcmp(tokenPos->textOfLine,"(") == 0 )
    {
        push(LGWAL, this_line);
        push_child(this_line,EXP);
        exp(level+1);
        if(strcmp(tokenPos->textOfLine,")") == 0 )
        {
            push(RGWAL,this_line);
        }
        else
        {
            print_err(tokenPos->lineNum,tokenPos->textOfLine,"ITESTMT", ")",tokenPos->tokenType);
        }
        push_child(this_line,EXP);
        stmt(level+1);
        pTreeType[this_line][0] = WHILE;
		pTreeType[this_line][1] = level;
    }
    else
    {
        print_err(tokenPos->lineNum,tokenPos->textOfLine,"ITESTMT", "(",tokenPos->tokenType);
        
    }

 
}

