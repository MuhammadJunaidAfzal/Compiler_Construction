#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

struct Symbol_Table
{
	string type;
	string identifer;
	string value;
	int adreess;
};
struct C 
{
	int col[4];
};

int ds[INT16_MAX];
vector<Symbol_Table> symboltable;

int size = 0;
int new_adreees = 20;
int tempindex = 0;
int quad_index = 1;

int check_int(string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{

		}
		else
		{
			return 0;
		}
	}
	Symbol_Table temp;
	temp.identifer = "tt" + to_string(tempindex++);

	temp.adreess = new_adreees++;
	temp.type = "INT";
	temp.value = str;
	symboltable.push_back(temp);

	return temp.adreess;
}
void populate_ST()
{
	Symbol_Table temp;

	temp.identifer = "=";
	temp.adreess = 1;
	temp.type = "operator";
	temp.value = "";
	symboltable.push_back(temp);

	temp.identifer = "<";
	temp.adreess = 2;
	temp.type = "operator";
	temp.value = "";
	symboltable.push_back(temp);

	temp.identifer = ">";
	temp.adreess = 3;
	temp.type = "operator";
	temp.value = "";
	symboltable.push_back(temp);

	temp.identifer = "<=";
	temp.adreess = 4;
	temp.type = "operator";
	temp.value = "";
	symboltable.push_back(temp);

	temp.identifer = ">=";
	temp.adreess = 5;
	temp.type = "operator";
	temp.value = "";
	symboltable.push_back(temp);

	temp.identifer = "~=";
	temp.adreess = 6;
	temp.type = "operator";
	temp.value = "";
	symboltable.push_back(temp);

	temp.identifer = "+";
	temp.adreess = 16;
	temp.type = "operator";
	temp.value = "";
	symboltable.push_back(temp);

	temp.identifer = "-";
	temp.adreess = 17;
	temp.type = "operator";
	temp.value = "";
	symboltable.push_back(temp);

	temp.identifer = "*";
	temp.adreess = 18;
	temp.type = "operator";
	temp.value = "";
	symboltable.push_back(temp);

	temp.identifer = "/";
	temp.adreess = 19;
	temp.type = "operator";
	temp.value = "";
	symboltable.push_back(temp);

	ifstream file;
	file.open("symbol_table.txt");
	if (!file.is_open())
	{
		cout << "Error..File not opened.!";
	}

	while (!file.eof())
	{
		Symbol_Table temp;
		
		file >> temp.identifer >> temp.value >> temp.type >> temp.adreess;

		symboltable.push_back(temp);
		new_adreees++;
	}
	file.close();


	
}
int get_adresses(string str)
{
	for (auto itr = symboltable.begin(); itr != symboltable.end(); itr++)
	{
		if (itr.operator*().identifer == str)
		{
			return itr.operator*().adreess;
		}
	}

	return new_adreees;
}
bool check_adresses(string str)
{
	for (auto itr = symboltable.begin(); itr != symboltable.end(); itr++)
	{
		if (itr.operator*().identifer == str)
		{
			return true;
		}
	}

	return false;
}
void populate_quad(vector<C> &quad)
{
	ifstream file;

	file.open("TAC.txt");
	if (!file.is_open())
	{
		cout << "Error..File not opened.!";
	}
	string word , semicolon;

	while (!file.eof())
	{
		file >> word;
		//cout << word << '\n';


		if (word == "out")
		{
			quad[quad_index].col[0] = 13;
			//quad[0][quad_index][0] = 13;
			getline(file, word);
			string process;
			if (word[1] == '"')
			{
				Symbol_Table temp;
				string newstring;

				for (int zz = 2; zz < word.size() - 2; zz++)
				{
					newstring = newstring + word[zz];
				}

				temp.value = newstring;
				temp.adreess = new_adreees++;
				temp.type = "CHAR";
				symboltable.push_back(temp);
				quad[quad_index].col[1] = temp.adreess;
				// store the string in symbol table and write its adresses
			}
			else
			{
				string ptr;
				int i = 1;
				while (word[i] != ';')
				{
					ptr = ptr + word[i];
					i++;
				}
				quad[quad_index].col[1] = get_adresses(ptr);
			}
			quad_index++;
		}
		else if (word == "in")
		{
			quad[quad_index].col[0] = 12;
			file >> word;
			quad[quad_index].col[1] = get_adresses(word);
			file >> semicolon;
			quad_index++;
		}
		else if (word == "goto")
		{

			quad[quad_index].col[0] = 11;
			file >> word;

			quad[quad_index].col[1] = stoi(word);
		//	file >> semicolon; 
			quad_index++;
		}
		else if (word == "if")
		{
			string a, b, c, d, e, temp;
			file >> a >> b >> c >> d >> e;

			quad[quad_index].col[0] = get_adresses(b);


			int temp1 = check_int(a);
			if (temp1 == 0)
			{
				quad[quad_index].col[1] = get_adresses(a);
			}
			else
			{
				quad[quad_index].col[1] = temp1;
			}

			temp1 = check_int(c);
			if (temp1 == 0)
			{
				quad[quad_index].col[2] = get_adresses(c);
			}
			else
			{
				quad[quad_index].col[2] = temp1;
			}
			quad[quad_index].col[3] = stoi(e);
			quad_index++;
		}
		else if (word == "goto")
		{
			file >> word;
			quad[quad_index].col[0] = 11;
			quad[quad_index].col[1] = stoi(word);
			quad_index++;
		}
		else if (word == "ret")
		{
			string a;
			file >> a;
			quad[quad_index].col[0] = 14;

			int temp1 = check_int(a);
			if (temp1 == 0)
			{
				quad[quad_index].col[1] = get_adresses(a);
			}
			else
			{
				quad[quad_index].col[1] = temp1;
			}

			quad_index++; 
			 file >> semicolon;
		}
		else
		{
			string a, b, c, d, e, temp;
			file >> b >> c >> d;
			a = word;
			if (d != ";")
			{
				file >> e; file >> semicolon;

				quad[quad_index].col[0] = get_adresses(d);

				int temp1 = check_int(c);
				if (temp1 == 0)
				{
					quad[quad_index].col[1] = get_adresses(c);
				}
				else
				{
					quad[quad_index].col[1] = temp1;
				}


				temp1 = check_int(e);
				if (temp1 == 0)
				{
					quad[quad_index].col[2] = get_adresses(e);
				}
				else
				{
					quad[quad_index].col[2] = temp1;
				}
				if (check_adresses(a) == false)
				{
					Symbol_Table temp;
					temp.identifer = a;
					temp.adreess = new_adreees;
					temp.type = "INT";
					temp.value = "0";
					symboltable.push_back(temp);
					int aaa= get_adresses(a);
					quad[quad_index].col[3] = get_adresses(a);

					new_adreees++;
				}
				else
				{
					quad[quad_index].col[3] = get_adresses(a);
				}
			}
			else
			{
				
				quad[quad_index].col[0] = 7; // for assinging value to single variable

				int temp1 = check_int(c);
				if (temp1 == 0)
				{
					int ccc = get_adresses(c);
 					quad[quad_index].col[1] = get_adresses(c);
				}
				else
				{
					quad[quad_index].col[1] = temp1;
				}
				quad[quad_index].col[3] = get_adresses(a);
				//file >> semicolon;
			}
			quad_index++;
		}
	}
}
void Compile(vector<C> quad)
{
	int pc = 0; int line = quad[pc].col[0];
	while ( pc < quad_index)
	{
		
		if (quad[pc].col[0] == 1) // =
		{
			int i = quad[pc].col[1];
			int j = quad[pc].col[2];
			if (ds[i] == ds[j])
			{
				pc = quad[pc].col[3];
				continue;
			}
		}
		else if (quad[pc].col[0] == 2) // <
		{
			int i = quad[pc].col[1];
			int j = quad[pc].col[2];
			if (ds[i] < ds[j])
			{
				pc = quad[pc].col[3];
				continue;
			}
		}
		else if (quad[pc].col[0] == 3) // >
		{
			int i = quad[pc].col[1];
			int j = quad[pc].col[2];
			if (ds[i] > ds[j])
			{
				pc = quad[pc].col[3];
				continue;
			}
		}
		else if (quad[pc].col[0] == 4) // <=
		{
			int i = quad[pc].col[1];
			int j = quad[pc].col[2];
			if (ds[i] <= ds[j])
			{
				pc = quad[pc].col[3];
				continue;
			}
		}
		else if (quad[pc].col[0] == 5) // >=
		{
			int i = quad[pc].col[1];
			int j = quad[pc].col[2];
			if (ds[i] >= ds[j])
			{
				pc = quad[pc].col[3];
				continue;
			}
		}
		else if (quad[pc].col[0] == 6) // ~=
		{
			int i = quad[pc].col[1];
			int j = quad[pc].col[2];
			if (ds[i] != ds[j])
			{
				pc = quad[pc].col[3];
				continue;
			}
		}
		else if (quad[pc].col[0] == 7)
		{
			int i = quad[pc].col[1];
			int k = quad[pc].col[3];

			ds[k] = ds[i];
		}
		else if (quad[pc].col[0] == 11)
		{
			pc = quad[pc].col[1]  ;
			continue;
		}
		else if (quad[pc].col[0] == 12) // ~=
		{
			int i = quad[pc].col[1];
			int input = 0;
			cin >> input;
			ds[i] = input;
		}
		else if (quad[pc].col[0] == 13) // out
		{
			int i = quad[pc].col[1];

			for (auto itr = symboltable.begin(); itr != symboltable.end(); itr++)
			{
				if (i == itr.operator*().adreess && itr.operator*().type == "INT")
				{
					cout << ds[itr.operator*().adreess];// << endl;
					break;
				}
				if (i == itr.operator*().adreess && itr.operator*().type == "CHAR")
				{
					string output = itr.operator*().value;// << endl;
					if (output[0] == '\\' && output[1] == 'n')
					{
						cout << endl;
						for (int iii = 2; iii < output.size(); iii++)
						{
							cout << output[iii];
						}
					}
					else
						cout << output;
					
					if (output[output.size() - 1] == 'n')
					{

						cout << endl;
					}
					break;
				}
			}

		}

		else if (quad[pc].col[0] == 14) // ret
		{
			break;
		}
		else if (quad[pc].col[0] == 16) // +
		{
			int i = quad[pc].col[1];
			int j = quad[pc].col[2];
			int k = quad[pc].col[3];
			ds[k] = ds[i] + ds[j];

		}
		else if (quad[pc].col[0] == 17)// -)
		{
			int i = quad[pc].col[1];
			int j = quad[pc].col[2];
			int k = quad[pc].col[3];

			ds[k] = ds[i] - ds[j];
			
		}
		else if (quad[pc].col[0] == 18)// *
		{
			int i = quad[pc].col[1];
			int j = quad[pc].col[2];
			int k = quad[pc].col[3];

			ds[k] = ds[i] * ds[j];
			
		}
		else if (quad[pc].col[0] == 19)// /
		{
			int i = quad[pc].col[1];
			int j = quad[pc].col[2];
			int k = quad[pc].col[3];

			ds[k] = ds[i] / ds[j];
			
		}
		pc++;

		//for (auto itr = symboltable.begin(); itr != symboltable.end(); itr++)
		//{
		//	if (itr.operator*().adreess != 0)
		//	{
		//		//cout <<"( "<< itr.operator*().adreess << "," << ds[itr.operator*().adreess] << ")";	
		//		cout <<  ds[itr.operator*().adreess] << ",";
		//	}
		//}
		//cout << endl;
	}
}

int main()
{
	int size = 1;
	ifstream file;
	file.open("TAC.txt");
	if (!file.is_open())
	{
		cout << "Error..File not opened.!";
	}
	string line;
	while (getline(file, line))
	{
		size++;
	}file.close();

	vector<C> quad;
	for (int i = 0; i < size; i++)
	{
		C dumy;
		dumy.col[0] = 0;
		dumy.col[1] = 0;
		dumy.col[2] = 0;
		dumy.col[3] = 0;
		quad.push_back(dumy);
	}

	populate_ST();

	populate_quad(quad);
	int asd;
	for (auto itr = symboltable.begin(); itr != symboltable.end(); itr++)
	{
		if (itr.operator*().type == "INT")
		{
			asd = stoi(itr.operator*().value);

			ds[itr.operator*().adreess] = stoi(itr.operator*().value);
		}
	}

	for (int i = 0; i < size; i++)
	{
		cout << quad[i].col[0] << " " << quad[i].col[1] << " " << quad[i].col[2] << " " << quad[i].col[3] << " \n";
	}

	for (auto itr = symboltable.begin(); itr != symboltable.end(); itr++)
	{
		cout << itr.operator*().identifer << "\t " << itr.operator*().value << "\t " << itr.operator*().type << "\t " << itr.operator*().adreess << endl;
	}
	
	/*for (auto itr = symboltable.begin(); itr != symboltable.end(); itr++)
	{
		if (itr.operator*().adreess !=  0)
		{
			cout << itr.operator*().adreess <<" " << ds[itr.operator*().adreess]<<endl;
		}
	}*/

	Compile(quad);
	//for (auto itr = symboltable.begin(); itr != symboltable.end(); itr++)
	//{
	//	if (itr.operator*().adreess !=  0)
	//	{
	//		cout << itr.operator*().adreess <<" " << ds[itr.operator*().adreess]<<endl;
	//	}
	//}
	system("pause");
}
// 1 =
// 2 <
// 3 > 
// 4 <= 
// 5 >=
// 6 ~=
// 7 assignmnet
// 8
// 9
// 10 if
// 11 goto
// 12 in
// 13 out
// 14 ret
// 15
// 16 +
// 17 -
// 18 *
// 19 /
//