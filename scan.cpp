#include "scan.h"

list<line> cScanner(char* filename)
{
	//char errf[256];
	//char * filename ="1.txt";
	ifstream in(filename);
	//ofstream out(argv[2]);
	//strcpy(errf, argv[1]);
	//ofstream err(strcat(errf,".err.txt"));
	line lineSave;
	
	int linecnt = 0;

	int i;

	char wBuf[512]="";//Word Buffer
	char bClr[512] ="";//Buffer Clear
	bool comment = false; //주석 여부

	list<line> sourceline;

	bool oper = false; //연산자
	bool num = false; //순수 숫자 여부
	bool letter = false; //순수 알파벳

	int bufPos = 0;

	//괄호 내부 괄호 외부
	
	char oneLine[LBF];

	//out<<"C- COMPILATION: "<<argv[1]<<endl;
	while(!in.eof())
	{
		in.getline(oneLine, LBF);
		linecnt++;
        lineSave.lineNum = linecnt;

		//out << linecnt<<": "<< oneLine << endl;
		for ( i = 0 ; i < strlen(oneLine) ; i ++ )
		{
			if(!comment)
			{
				if(oneLine[i] == '/' && oneLine[i+1] == '*')
				{
					comment = true;
					oper = false;
					num = false;
					letter = false;
				}
				else
				{
					//토큰을 나눠주는 기준에 대하여 : 공백 세미콜론 쉼표 엔터 탭 문자
					if(oneLine[i] == ' ')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
								
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}
						letter = false;
						num = false;
						
					}
					else if(oneLine[i] == ';')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
							
						}
                        
                        strcpy(lineSave.textOfLine, ";");
                        lineSave.tokenType = OTHER;
                        sourceline.push_back(lineSave);
						oper = false;
						num = false;
						letter = false;
						//out << "\t" << linecnt <<": ;"<<endl;
					}
					else if(oneLine[i] == ',')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
                                }
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
                            }
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}
                        
                        strcpy(lineSave.textOfLine, ",");
                        lineSave.tokenType = OTHER;
                        sourceline.push_back(lineSave);
						oper = false;
						num = false;
						letter = false;
						//out << "\t" << linecnt <<": ,"<<endl;
					}
					else if(oneLine[i] == '\t')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}
						letter = false;
						num = false;
					}
					else if(oneLine[i] == '\n')
					{

					}
					

					//괄호에 관하여
					else if(oneLine[i] == '{')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
                                }
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}
						//out << "\t" << linecnt <<": {"<<endl;
						strcpy(lineSave.textOfLine, "{");
                        lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
						//brck1.push('{');
						oper = false;
						num = false;
						letter = false;
					}
					else if(oneLine[i] == '}')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}

							//out << "\t" << linecnt <<": }"<<endl;
                        strcpy(lineSave.textOfLine, "}");
                        lineSave.tokenType = OTHER;
                        sourceline.push_back(lineSave);
							//brck1.pop();
						oper = false;
						num = false;
						letter = false;
					}
					else if(oneLine[i] == '(')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}
						strcpy(lineSave.textOfLine, "(");
                        lineSave.tokenType = OTHER;
						sourceline.push_back(lineSave);
						//out << "\t" << linecnt <<": ("<<endl;
						//brck2.push('(');
						oper = false;
						num = false;
						letter = false;
					}
					else if(oneLine[i] == ')')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
                                }
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}
							strcpy(lineSave.textOfLine, ")");
                        lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
							//out << "\t" << linecnt <<": )"<<endl;
							//brck2.pop();
							
						oper = false;
						num = false;
						letter = false;
					}
					else if(oneLine[i] == '[')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
                                }
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}
						strcpy(lineSave.textOfLine, "[");
                        lineSave.tokenType = OTHER;
						sourceline.push_back(lineSave);
						//out << "\t" << linecnt <<": ["<<endl;
						//brck3.push('[');
						oper = false;
						num = false;
						letter = false;
					}
					else if(oneLine[i] == ']')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
                                }
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}
						
							//out << "\t" << linecnt <<": ]"<<endl;
						strcpy(lineSave.textOfLine, "]");
                        lineSave.tokenType = OTHER;
						sourceline.push_back(lineSave);
						//brck3.pop();
						
						oper = false;
						num = false;
						letter = false;
					}

					//연산자에 관하여
					else if(oneLine[i] == '*')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}

						if(oneLine[i+1] == '=')
						{
							//out << "\t" << linecnt <<": *="<<endl;
							strcpy(lineSave.textOfLine, "*=");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
							i++;
						}
						else
						{
							//out << "\t" << linecnt <<": *"<<endl;
							strcpy(lineSave.textOfLine, "*");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
						}
						oper = true;
						num = false;
						letter = false;
					}
					else if(oneLine[i] == '+')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}
						if(oneLine[i+1] == '=')
						{
							//out << "\t" << linecnt <<": +="<<endl;
							strcpy(lineSave.textOfLine, "+=");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
							i++;
						}
						else
						{
							//out << "\t" << linecnt <<": +"<<endl;
							strcpy(lineSave.textOfLine, "+");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
						}
						oper = true;
						num = false;
						letter = false;
					}
					else if(oneLine[i] == '/')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = OTHER;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}
						if(oneLine[i+1] == '=')
						{
							//out << "\t" << linecnt <<": /="<<endl;
							strcpy(lineSave.textOfLine, "/=");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
							i++;
						}
						else
						{
							//out << "\t" << linecnt <<": /"<<endl;
							strcpy(lineSave.textOfLine, "/");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
						}
						oper = true;
						num = false;
						letter = false;
					}
					else if(oneLine[i] == '-')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
                                }
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}
						if(oneLine[i+1] == '=')
						{
							//out << "\t" << linecnt <<": -="<<endl;
							strcpy(lineSave.textOfLine, "-=");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
							i++;
						}
						else
						{
							//out << "\t" << linecnt <<": -"<<endl;
							strcpy(lineSave.textOfLine, "-");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
						}
						oper = true;
						num = false;
						letter = false;
					}
					else if(oneLine[i] == '=')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}
						if(oneLine[i+1] == '=')
						{
							//out << "\t" << linecnt <<": =="<<endl;
							strcpy(lineSave.textOfLine, "==");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
							i++;
						}
						else
						{
							//out << "\t" << linecnt <<": ="<<endl;
							strcpy(lineSave.textOfLine, "=");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
						}
						oper = true;
						num = false;
						letter = false;
					}
					else if(oneLine[i] == '<')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}

						if(oneLine[i+1] == '=')
						{
							//out << "\t" << linecnt <<": <="<<endl;
							strcpy(lineSave.textOfLine, "<=");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
							i++;
						}
						else
						{
							//out << "\t" << linecnt <<": <"<<endl;
							strcpy(lineSave.textOfLine, "<");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
						}
						oper = true;
						num = false;
						letter = false;
					}

					else if(oneLine[i] == '>')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}

						if(oneLine[i+1] == '=')
						{
							//out << "\t" << linecnt <<": >="<<endl;
                            strcpy(lineSave.textOfLine, ">=");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
							i++;
						}
						else
						{
							//out << "\t" << linecnt <<": >"<<endl;
                            strcpy(lineSave.textOfLine, ">");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
						}
						oper = true;
						num = false;
						letter = false;
					}
					else if(oneLine[i] == '!')
					{
						if(strcmp(wBuf,bClr) != 0)
						{
							if(letter)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
							}
							else if(num)
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
							strcpy(lineSave.textOfLine, wBuf);
							sourceline.push_back(lineSave);
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}

						if(oneLine[i+1] == '=')
						{
							//out << "\t" << linecnt <<": !="<<endl;
							strcpy(lineSave.textOfLine, "!=");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
							i++;
						}
						else
						{
							//out << "\t" << linecnt <<": !"<<endl;
							strcpy(lineSave.textOfLine, "!");
                            lineSave.tokenType = OTHER;
							sourceline.push_back(lineSave);
						}
						oper = true;
						num = false;
						letter = false;
					}

					else if((oneLine[i] >= 'a' && oneLine[i] <= 'z') || (oneLine[i] >= 'A' && oneLine[i] <= 'Z'))
					{
						if(num)
						{
							//out << "\t" << linecnt <<": Num, val=: "<<wBuf<<endl;
							//err << linecnt <<": Num, val=: "<<wBuf<<endl;
                            lineSave.tokenType = NUM;
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}
						wBuf[bufPos] = oneLine[i];
						bufPos++;
						
						if( i == strlen(oneLine)-1)
						{
							if(!num)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
							}
							else
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
						}

						oper = false;
						num = false;
						letter = true;
					}
					else if((oneLine[i] >= '0' && oneLine[i] <= '9'))
					{
						
						if(letter)
						{
							if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
							{
								//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                lineSave.tokenType = RESERVED;
								letter = false;
							}
							else
							{
								//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                lineSave.tokenType = ID;
								letter = false;
							}
							//err << linecnt <<": Num, val=: "<<wBuf<<endl;
							strncpy(wBuf, bClr,bufPos);
							bufPos = 0;
						}
						wBuf[bufPos] = oneLine[i];
						bufPos++;
						oper = false;
						num = true;
						if( i == strlen(oneLine)-1)
						{
							if(!num)
							{
								if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
								{
									//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                                    lineSave.tokenType = RESERVED;
								}
								else
								{
									//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                                    lineSave.tokenType = ID;
								}
							}
							else
							{
								//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                                lineSave.tokenType = NUM;
							}
						}
			
					}
					
					else
					{
						if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
						{
							//out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                            lineSave.tokenType = RESERVED;
						}
						else if (num)
						{
							//out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                            lineSave.tokenType = NUM;
						}
						else if(bufPos > 0)
						{
							//out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                            lineSave.tokenType = ID;
						}
						strcpy(lineSave.textOfLine, wBuf);
						sourceline.push_back(lineSave);
						//out << "\t" << linecnt <<": Error: "<<oneLine[i]<<endl;
						//err << linecnt <<": Error: "<<oneLine[i]<<endl;
						strncpy(wBuf, bClr,bufPos);
						bufPos = 0;
						num = false;
						letter = false;
					}
				}
			}
			else
			{
				if(oneLine[i] == '*' && oneLine[i+1]=='/')
				{
					i += 1;
					comment = false;
				}
			}
		}
        if(strlen(wBuf)>0)
        {
            {
                if(strcmp(wBuf,"int") == 0||strcmp(wBuf,"while") == 0||strcmp(wBuf,"if") == 0||strcmp(wBuf,"void") == 0||strcmp(wBuf,"else") == 0||strcmp(wBuf,"return") == 0)
                {
                    //out << "\t" << linecnt <<": reserved word: "<<wBuf<<endl;
                    lineSave.tokenType = RESERVED;
                }
                else if (num)
                {
                    //out << "\t" << linecnt <<": Num, val= "<<wBuf<<endl;
                    lineSave.tokenType = NUM;
                }
                else if(bufPos > 0)
                {
                    //out << "\t" << linecnt <<": ID, name= "<<wBuf<<endl;
                    lineSave.tokenType = ID;
                }
                strcpy(lineSave.textOfLine, wBuf);
                sourceline.push_back(lineSave);
                //out << "\t" << linecnt <<": Error: "<<oneLine[i]<<endl;
                //err << linecnt <<": Error: "<<oneLine[i]<<endl;
                strncpy(wBuf, bClr,bufPos);
                bufPos = 0;
                num = false;
                letter = false;
            }
        }
		//lineSave.tokenType = ENDL;
        //strcpy(lineSave.textOfLine, "<endl>");
        //sourceline.push_back(lineSave);
		
	}
	//out << "\t" << linecnt+1 <<": EOF"<<endl;
    lineSave.tokenType = ENDF;
    strcpy(lineSave.textOfLine, "<eof>");
    sourceline.push_back(lineSave);
	


	in.close();
	
    return sourceline;
}