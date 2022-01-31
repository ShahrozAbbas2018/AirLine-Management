#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <cstdio>

#include <windows.h>
#include <conio.h>

#include<vector>
#include<list>
#include<iterator>
using namespace std;




class Edge{
	private:
		int DestinationVertexID;
		string stName;
		int weight;
	public:
		Edge() {}
		Edge(int destVID,string n, int w) 
		{
			DestinationVertexID = destVID;
			stName = n;
    		weight = w;
		}
		void setEdgeValues(int destVID,string n, int w) 
		{
    		DestinationVertexID = destVID;
    		stName = n;
    		weight = w;
		}
		void setWeight(int w)
		{
    		weight = w;
		}
		
		string getStateName()
		{
			return stName;
		}
		int getDestinationVertexID() 
		{
    		return DestinationVertexID;
		}
		int getWeight() 
		{
    		return weight;
		}
};

class Vertex{
	public:
    	int state_id;
		string state_name;
		
		list<Edge>edgeList;

		Vertex()
		{
	    	state_id = 0;
	    	state_name = "";
		}
	
		Vertex(int id, string sname)
		{
	    	state_id = id;
	    	state_name = sname;
		}
	
		int getStateID()
		{
	    	return state_id;
		}
		string getStateName()
		{
	    	return state_name;
		}
		void setID(int id)
		{
	    	state_id = id;
		}
		void setStateName(string sname)
		{
	    	state_name = sname;
		}
	
		list<Edge>getEdgeList()
		{
	    	return edgeList;
		}
		
		void printEdgeList()
		{
	    	cout << "[";
	    	for (auto it = edgeList.begin(); it != edgeList.end(); it++)
			{
				cout << it->getStateName() << "(" << it->getWeight() << ")--> ";
			}
	    	cout<<"]"<<endl;
		}
	
		void updateVertexName(string sname)
		{
	    	state_name = sname;
	    	cout << "\t\t\t\t\t\tVertex Name Updated Successfully";
		}

};
int VVertax=0;
class Graph{
	private:
		vector < Vertex > vertices;

	public:

    	bool checkIfVertexExistByID(int vid) 
		{
			bool flag = false;
		
			for (int i = 0; i < vertices.size(); i++)
			{
	        	if (vertices.at(i).getStateID() == vid) 
				{
					return true;
	        	}
			}
			return flag;
		}
		

		void addVertex(Vertex newVertex)
		{
	    	bool check = checkIfVertexExistByID(newVertex.getStateID());
	    	if (check == true)
			{
				cout << "\t\t\t\t\t\tVertex with this ID already exist" << endl;
				VVertax++;
			}
			else 
			{
				vertices.push_back(newVertex);
	    	}
		}

		Vertex getVertexByID(int vid)
		{
    		Vertex temp;
    		for (int i = 0; i < vertices.size(); i++)
			{
				temp = vertices.at(i);
				if (temp.getStateID() == vid)
				{
        			return temp;
				}
			}
			return temp;
		}

		bool checkIfEdgeExistByID(int fromVertex, int toVertex)
		{
    		Vertex v = getVertexByID(fromVertex);
    		list < Edge > e;
    		e = v.getEdgeList();
    		bool flag = false;
    		for(auto it = e.begin(); it != e.end(); it++)
			{
				if(it->getDestinationVertexID() == toVertex)
				{
        			flag = true;
        			return flag;
        			break;
				}
			}
    		return flag;
		}

		void addEdgeByID(int fromVertex, int toVertex, int weight)
		{
			string sName;
	    	bool check1 = checkIfVertexExistByID(fromVertex);
	    	bool check2 = checkIfVertexExistByID(toVertex);
	
	    	bool check3 = checkIfEdgeExistByID(fromVertex, toVertex);
	    	if((check1 && check2 == true))
			{
				if(check3 == true)
				{
	        	cout << "\t\t\t\t\t\tEdge between " << getVertexByID(fromVertex).getStateName() << "(" << fromVertex << ") and " << getVertexByID(toVertex).getStateName() << "(" << toVertex << ") Already Exist" << endl;
				}
				else
				{
	        		for (int i = 0; i < vertices.size(); i++)
					{
						if (vertices.at(i).getStateID() == fromVertex)
						{
							sName = getVertexByID(toVertex).getStateName();
	            			Edge e(toVertex,sName, weight);
	            			vertices.at(i).edgeList.push_back(e);
						}
						else if(vertices.at(i).getStateID() == toVertex)
						{
							sName = getVertexByID(fromVertex).getStateName();
	            			Edge e(fromVertex,sName, weight);
	            			vertices.at(i).edgeList.push_back(e);
						}
					}
				}
	    	}
			else
			{
	    		cout << "\t\t\t\t\t\tInvalid Vertex ID entered.";
			}
		}

		void updateEdgeByID(int fromVertex, int toVertex, int newWeight)
		{
    		bool check = checkIfEdgeExistByID(fromVertex, toVertex);
    		if(check == true)
			{
    			for (int i = 0; i < vertices.size(); i++)
				{
        			if (vertices.at(i).getStateID() == fromVertex)
					{
        				for(auto it=vertices.at(i).edgeList.begin();it!=vertices.at(i).edgeList.end();it++) 
						{
            				if (it -> getDestinationVertexID() == toVertex)
							{
            					it -> setWeight(newWeight);
            					break;
            				}
          				}
        			}
					else if(vertices.at(i).getStateID() == toVertex)
					{
        				for (auto it=vertices.at(i).edgeList.begin();it!=vertices.at(i).edgeList.end();it++)
						{
            				if (it -> getDestinationVertexID() == fromVertex)
							{
            					it -> setWeight(newWeight);
            					break;
            				}
        				}
        			}
    			}
    			cout<<"\t\t\t\t\t\tEdge Weight Updated Successfully "<<endl;
    		}
			else
			{
    			cout<<"\t\t\t\t\t\tEdge between "<<getVertexByID(fromVertex).getStateName()
				<<"("<<fromVertex<<") and "<<getVertexByID(toVertex).getStateName()
				<<"("<<toVertex<<") DOES NOT Exist"<<endl;
    		}
		}

		void deleteEdgeByID(int fromVertex, int toVertex)
		{
			bool check = checkIfEdgeExistByID(fromVertex, toVertex);
    		if(check == true)
			{
				for(int i = 0; i < vertices.size(); i++)
				{
        			if (vertices.at(i).getStateID() == fromVertex)
					{
        				for(auto it=vertices.at(i).edgeList.begin();it!=vertices.at(i).edgeList.end();it++)
						{
            				if (it -> getDestinationVertexID() == toVertex)
							{
            					vertices.at(i).edgeList.erase(it);
            					break;
            				}
        				}
        			}
        			if (vertices.at(i).getStateID() == toVertex)
					{
        				for (auto it=vertices.at(i).edgeList.begin();it!=vertices.at(i).edgeList.end();it++)
						{
            				if (it -> getDestinationVertexID() == fromVertex)
							{
            					vertices.at(i).edgeList.erase(it);
            					break;
            				}
        				}
        			}
				}
    			cout<<"\t\t\t\t\t\tEdge Between "<<fromVertex<<" and "<<toVertex<<" Deleted Successfully."<<endl;
    		}
    		else
    		{
    			cout<<"\t\t\t\t\t\tID not Found."<<endl;
			}
		}

		void deleteVertexByID(int vid)
		{
    		int vIndex = 0;
    		for(int i = 0; i < vertices.size(); i++)
			{
    			if (vertices.at(i).getStateID() == vid)
				{
        			vIndex = i;
    			}
    		}
    		for (int i = 0; i < vertices.size(); i++)
			{
    			for(auto it=vertices.at(i).edgeList.begin();it!=vertices.at(i).edgeList.end();it++)
				{
        			if(it -> getDestinationVertexID() == vid)
					{
        				vertices.at(i).edgeList.erase(it);
        				break;
        			}
    			}
    		}
    		vertices.erase(vertices.begin() + vIndex);
    		cout << "\t\t\t\t\t\tVertex Deleted Successfully" << endl;
		}
		
		int findRouteFare(int fromVertex, int toVertex) 
		{
			Vertex temp;
			Vertex v = getVertexByID(fromVertex);
			list < Edge > e;
			list < Edge > tmp;
			e = v.getEdgeList();
			bool flag = false;
			for (auto it = e.begin(); it != e.end(); it++)
			{
				if (it->getDestinationVertexID() == toVertex) 
				{
					return(it->getWeight());
				}
				temp = getVertexByID(it->getDestinationVertexID());
				tmp = temp.getEdgeList();
				for(auto tp = tmp.begin(); tp != tmp.end();tp++)
				{
					if (tp->getDestinationVertexID() == toVertex) 
					{
						return((it->getWeight()+tp->getWeight()));
					}
				}
			}
		}
		

		void printGraph()
		{
    		for(int i = 0; i < vertices.size(); i++)
			{
				Vertex temp;
				temp = vertices.at(i);
				cout <<"\t\t\t\t\t\t"<< temp.getStateName() << " (" << temp.getStateID() << ") --> ";
				temp.printEdgeList();
    		}
		}

};




class Node{
	private:
		string name,nat,reg,seat;
		Node* Next;
	public:
		Node()
		{
			Next = NULL;
		}
		
		void setNext(Node* n)
		{
			Next = n;
		}
		void setName(string n)
		{
			name = n;
		}
		
		void setNationality(string N)
		{
			nat = N;
		}
		
		void setReg(string re)
		{
			reg = re;
		}
		
		void setSeats(string Se)
		{
			seat = Se;
		}
		
		string getName()
		{
			return name;
		}
		
		string getReg()
		{
			return reg;
		}
		
		string getNationality()
		{
			return nat;
		}
		string getSeats()
		{
			return seat;
		}
		
		Node* getNext()
		{
			return Next;
		}
};



bool logi;

class Main{
	private:
		int pin;
		string username;
		string password;
		bool Log;
		string choise;
		Node* head;
		Node* current;
		char a;
		char b;
		char d[6];
		
	public:
		
		Main()
		{
			a=250;
			b=248;
			for(int i=0;i<6;i++)
			{
				d[i]=248;
			}
			head = NULL;
			Log = false;
			pin = 1234;
		}
		
		void setLog(bool l)
		{
			Log = l;
		}
		void Logo()
		{
			cout<<"\n\n\n\n\t\t\t\t\t\tAirline Management System\n";
			cout<<"\n\t\t\t\t\t\tPresented By:\n";
			cout<<"\t\t\t\t\t\tShahroz Abbas & Mueez Ur Rehman";
			sleep(2);
			system("cls");
		}
		
		void LogIn()
		{
			
			string Read;
			ifstream ReadFile("LogIn.txt");
			
			int zz =0;
			cout<<"\n\t\t\t\t\t\tEnter Username: ";
			cin>>username;
			cout<<"\n\t\t\t\t\t\tEnter Password: ";
			cin>>password;
			
			Loading();
			system("color 70");
			while(getline(ReadFile, Read))
			{
				if(username == Read)
				{
					getline(ReadFile, Read);
				
					if(password == Read)
					{
						zz++;
						Log = true;
					}
				}
				
				
			}
			if(zz==0)
				{
					cout<<"\n\t\t\t\t\t\tIncorrect Username or Password";
					cout<<"\n\n\t\t\t\t\t\t";
					system("pause");
					logi = false;
					system("cls");
					exit(0);
				}
				
				ReadFile.close();
		
		}
		
			void Display(int j)
		{
			j=j*j;
	HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);
	system("CLS");

	cout<<"\n\n\n\n\n\n\n\n\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),124);
	
	cout<<"\t\t\t\t\t\tLoading.."<<j<<" %";
	cout<<"\n\n\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),126);
	cout<<"\t\t\t\t\t\t"<<d[0]<<" ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),124);
	cout<<d[1]<<" ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),121);
	cout<<d[2]<<" ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),112);
	cout<<d[3]<<" ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),121);
	cout<<d[4]<<" ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),127);
	cout<<d[5]; 
	cout<<"\n\n\n"; 
		}
		//Setter and getters of Loading
		void setD1(int z)
		{
			d[z] = a;
		}
		void setD2(int z)
		{
			d[z]=b;
		}
		char getA()
		{
			return a;
		}
		char getB()
		{
			return b;
		}
		char getd(int z)
		{
			return d[z];
		}
		
		void Loading()
		{
			system("cls");
			system("color 70");
			int j=5;
			HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),112);
			for(int i=0;i<=5;i++)
			{
				cout<<getB();
				Display(j);
				setD1(i);
				Sleep(400);
				Display(j);
				setD2(i);
				setD1(i+1);
				Sleep(400);
				Display(j);
				j++;
			}
					system("CLS");
			SetConsoleTextAttribute(color, 8);	
			system("cls");
		}
		void SignUp()
		{
			
			int vpin;
			cout<<"\n\t\t\t\t\tEnter Pin For Admin Verification: ";
			cin>>vpin;
			if(vpin == pin)
			{
			
				ofstream MyFile;
			
				MyFile.open("LogIn.txt", ios::app);
				cout<<"\n\t\t\t\t\tEnter The UserName: ";
				cin>>username;
				cout<<"\n\t\t\t\t\tEnter The Password: ";
				cin>>password;
				  Loading();
				  system("color 70");
				MyFile<<endl;
				MyFile<<username;
				MyFile<<endl;
				MyFile<<password;
			
				cout<<"\n\t\t\t\t\tUser Successfully Created..!!\n";
			
		}
		}
		
		void Menu()
		{
			
			Graph g;
			Vertex v1;
			string sname;
			int id1, id2, w;
			int option;
			bool check;
	
			int fid,fid1,fid2,fw;
			string fname;
	
			fstream vertex;
			fstream edge;
			ofstream temp;
			ofstream temp1;
	
			vertex.open("vertex.txt", ios::in);
			edge.open("edge.txt", ios::in);
	
			while(!vertex.eof())
			{
				vertex >> id1;
    			vertex >> sname;
   			 	v1.setID(id1);
    			v1.setStateName(sname);
    			g.addVertex(v1);
			}
			vertex.close();
	
			while(!edge.eof())
			{
				edge >> fid1;
				edge >> fid2;
    			edge >> fw;
    			g.addEdgeByID(fid1, fid2, fw);
			}
				edge.close();
				bool hold =true;
			do
			{
			
			cout<<"\n\n\n\n\n\t\t\t\t\t\tPress 1 To Add AirLine";
			cout<<"\n\t\t\t\t\t\tPress 2 To Show All AirLines";
			cout<<"\n\t\t\t\t\t\tPress 3 To Find AirLine";//
			cout<<"\n\t\t\t\t\t\tPress 4 To Add City";
			cout<<"\n\t\t\t\t\t\tPress 5 To Delete City";
			cout<<"\n\t\t\t\t\t\tPress 6 To Add Connection(Edge)";
			cout<<"\n\t\t\t\t\t\tPress 7 To Update Connection(Edge)";
			cout<<"\n\t\t\t\t\t\tPress 8 To Delete Connection(Edge)";
			cout<<"\n\t\t\t\t\t\tPress 9 To Print Route";
			cout<<"\n\t\t\t\t\t\tPress 10 To View Fare";
			cout<<"\n\t\t\t\t\t\tPress 0 To Exit";
			cout<<"\n\n\t\t\t\t\t\tChoise: ";
			cin>>choise;
			if(choise=="1")
			{
				bool hold1 = true;
				
				
				while(hold1 == true)
				{
					string c1;
					bool c2 = false;
					Node* temp;
					temp = new Node;
					string name,nat,reg,seat;
					system("cls");
					do{
					
					cout<<"\n\n\n\t\t\t\t\t\tAdding AirCraft";
					cout<<"\n\n\n\t\t\t\t\t\tType of AirCraft: ";
					cout<<"\n\t\t\t\t\t\tPress 1 for Turboprop Aircraf"; 
					cout<<"\n\t\t\t\t\t\tPress 2 for Jumbo Jet"; 
					cout<<"\n\t\t\t\t\t\tPress 3 for AirBus";
					cout<<"\n\n\t\t\t\t\t\tChoise: ";
					cin>>c1;
					if(c1=="1")
					{
						name = "Turboprop";
						break;
					}
					else if(c1=="2")
					{
						name = "JumboJet";
						break;
					}
					else if(c1=="3")
					{
						name = "AirBus";
						break;
					}
					}while(c2 == false);
					
					cout<<"\n\t\t\t\t\t\tEnter Nationality: ";
					cin>>nat;
					cout<<"\n\t\t\t\t\t\tEnter Registeration No. ";
					cin>>reg;
					if(name == "Turboprop")
					{
						cout<<"\n\t\t\t\t\t\tNo. Of Seats: 50\n";
						seat = "50";
					}
					else if(name == "JumboJet")
					{
						cout<<"\n\t\t\t\t\t\tNo. Of Seats: 150\n";
						seat = "150";
					}
					else if(name == "AirBus")
					{
						cout<<"\n\t\t\t\t\t\tNo. Of Seats: 800\n";
						seat = "800";
					}
					
					if(head == NULL)
					{
						head = new Node();
						head->setName(name);
						head->setNationality(nat);
						head->setReg(reg);
						head->setSeats(seat);
						save(head);
					}
					else if(head !=NULL)
					{
						current = head;
						while(current->getNext()!=NULL)
						{
							current = current->getNext();
						}
						temp->setName(name);
						temp->setNationality(nat);
						temp->setReg(reg);
						temp->setSeats(seat);
						current->setNext(temp);
						save(temp);
						delete temp;
						
						
					}
					string chois;
					bool inval = true;
					do{
					
					cout<<"\n\n\t\t\t\t\t\tDo You Want To Register More Planes? ";
					cout<<"\n\t\t\t\t\t\tPress 1 for Yess";
					cout<<"\n\t\t\t\t\t\tPress 2 For No\n";
					cout<<"\n\n\t\t\t\t\t\tChoise: ";
					cin>>chois;
					if(chois == "1")
					{
						inval = false;
					}
					else if(chois=="2")
					{
					
						inval = false;
						hold1 = false;
					}
					else
					{
						cout<<"\n\n\t\t\t\t\t\tInvalid input Enter Again";
					}		
				}while(inval == true);
				system("cls");
				
				}
			}
			else if(choise=="2")
			{
				string Read;
				ifstream ReadFile("AirLine.txt");
				cout<<"\n\n\t\t\t\t\t\t<---------------->\n\t\t\t\t\t\tPrinting Aircrafts\n\t\t\t\t\t\t<---------------->\n\n";
				int a=0;
				int b=2;
				int c=1;
				int d=0;
				getline(ReadFile, Read);
				while(getline(ReadFile, Read))
				{
					if(c==1)
					{
						cout<<"\t\t\t\t\t\t"<<c<<")\n";
						c++;
					}
					a++;
					if(d==0)
					{
						cout<<"\t\t\t\t\t\t"<<"Plan Type: ";
						d++;
					}
					else if(d==1)
					{
						cout<<"\t\t\t\t\t\t"<<"Manufacturer: ";
						d++;
					}
					else if(d==2)
					{
						cout<<"\t\t\t\t\t\t"<<"Registeration ID: ";
						d++;
					}
					else if(d==3)
					{
						cout<<"\t\t\t\t\t\t"<<"No of Seats: ";
						d=0;
					}
					cout<<Read;
					cout<<endl;
					if(a==4)
					{
						a=0;
						cout<<"\n\t\t\t\t\t\t"<<b<<")\n";
						b++;
					}
				}
				cout<<"\n\t\t\t\t\t\t";
				system("pause");
				system("cls");
			}
			else if(choise == "3")
			{
				cout<<"\n\t\t\t\t\t\tEnter AirLine Registeration: ";
				string Re;
				cin>>Re;
				int count=0;
				bool found=false;
				string Read;
				ifstream ReadFile("AirLine.txt");
				getline(ReadFile, Read);
				while(getline(ReadFile, Read))
				{
					getline(ReadFile, Read);
					getline(ReadFile, Read);
					if(Re == Read)
					{
						cout<<"\n\t\t\t\t\t\tFound..!";
						found = true;
						break;
					}
					getline(ReadFile, Read);
					count++;
				}
				ReadFile.close();
				if(found == true)
				{
				
					ifstream Readfile("AirLine.txt");
					getline(Readfile, Read);
					for(int i=0;i<count;i++)
					{
						getline(Readfile, Read);
						getline(Readfile, Read);
						getline(Readfile, Read);
						getline(Readfile, Read);
					}
					cout<<endl;
					cout<<endl;
					int d=0;
					for(int i=0;i<4;i++)
					{
						getline(Readfile, Read);
						
						if(d==0)
						{
							cout<<"\t\t\t\t\t\tCraft Type: ";
							d++;
						}
						else if(d==1)
						{
							cout<<"\t\t\t\t\t\tManufacturer: ";
							d++;
						}
						else if(d==2)
						{
							cout<<"\t\t\t\t\t\tRegisteration ID: ";
							d++;
						}
						else if(d==3)
						{
							cout<<"\t\t\t\t\t\tNo of Seats: ";
							d = 0;
						}
						cout<<Read;
						cout<<endl;
					}
					Readfile.close();
				}
				else
				{
					cout<<"\n\n\t\t\t\t\t\tNo Plane Found..!\n";
				}
					cout<<"\n\t\t\t\t\t\t";
					system("pause");
			}
			else if(choise == "4")
			{
				vertex.open("vertex.txt", ios::out|ios::app);
		    	cout << "\t\t\t\t\t\tAdd Vertex Operation -" << endl;
		    	cout << "\t\t\t\t\t\tEnter State ID :";
		    	cin >> id1;
		    	cout << "\t\t\t\t\t\tEnter State Name :";
		    	cin >> sname;
		    	v1.setID(id1);
		    	v1.setStateName(sname);
		    	g.addVertex(v1);
		    	vertex<<endl<<id1<<endl;
		    	vertex<<sname;
		    	if(VVertax==0)
		    	{
				
					cout << "\t\t\t\t\t\tNew Vertex Added Successfully" << endl;
				}
				vertex.close();
				cout<<"\t\t\t\t\t\t";
		    	system("pause");
		    	system("cls");
			}
			else if(choise == "5")
			{
				vertex.open("vertex.txt", ios::in);
		    	temp.open("temp.txt",ios::out|ios::app);
		    	
		    	cout << "\t\t\t\t\t\tDelete Vertex Operation -" << endl;
		    	cout << "\t\t\t\t\t\tEnter ID of Vertex(State) to Delete : ";
		    	cin >> id1;
		    	g.deleteVertexByID(id1);
		    	while(vertex>>fid>>fname)
				{
			    	if(fid==id1)
			    	{
			    		cout<<"\n";
					}
					else
					{
						temp<<endl<<fid<<endl;
						temp<<fname;
					}
				    	
				}
				
		    	vertex.close();
				temp.close();
				
				//REMOVING AND RENAMING
				remove("vertex.txt");
				rename("temp.txt", "vertex.txt");
		    	
		    	cout<<"\t\t\t\t\t\t";
		    	system("pause");
		    	system("cls");
			}
			else if(choise == "6")
			{
				edge.open("edge.txt", ios::out|ios::app);
		    	cout << "\t\t\t\t\t\tAdd Edge Operation -" << endl;
		    	cout << "\t\t\t\t\t\tEnter ID of Source Vertex(State): ";
		    	cin >> id1;
		    	cout << "\t\t\t\t\t\tEnter ID of Destination Vertex(State): ";
		    	cin >> id2;
		    	cout << "\t\t\t\t\t\tEnter Weight of Edge: ";
		    	cin >> w;
		    	g.addEdgeByID(id1, id2, w);
		    	edge<<endl<<id1<<endl;
		    	edge<<id2<<endl;
		    	edge<<w;
		    	cout << "\n\t\t\t\t\t\tEdge added Successfully." << endl;
		    	edge.close();
		    	cout<<"\t\t\t\t\t\t";
		    	system("pause");
		    	system("cls");
			}
			else if(choise == "7")
			{
					edge.open("edge.txt", ios::in);
		    	temp1.open("temp1.txt",ios::out|ios::app);
		    	
		    	cout << "\t\t\t\t\t\tUpdate Edge Operation -" << endl;
		    	cout << "\t\t\t\t\t\tEnter ID of Source Vertex(State): ";
		    	cin >> id1;
		    	cout << "\t\t\t\t\t\tEnter ID of Destination Vertex(State): ";
		    	cin >> id2;
		    	cout << "\t\t\t\t\t\tEnter UPDATED Weight of Edge: ";
		    	cin >> w;
		    	g.updateEdgeByID(id1, id2, w);
		    	
		    	while(edge>>fid1>>fid2>>fw)
				{
			    	if(fid1==id1&&fid2==id2)
			    	{
			    		temp1<<endl<<fid1<<endl;
						temp1<<fid2<<endl;
						temp1<<w;
					}
					else
					{
						temp1<<endl<<fid1<<endl;
						temp1<<fid2<<endl;
						temp1<<fw;
					}
				    	
				}
				
		    	edge.close();
				temp1.close();
				
				//REMOVING AND RENAMING
				remove("edge.txt");
				rename("temp1.txt", "edge.txt");
		    	cout<<"\t\t\t\t\t\t";
		    	system("pause");
		    	
			}
			else if(choise =="8")
			{
				edge.open("edge.txt", ios::in);
		    	temp1.open("temp1.txt",ios::out|ios::app);
		    	
				cout << "\t\t\t\t\t\tDelete Edge Operation -" << endl;
				cout << "\t\t\t\t\t\tEnter ID of Source Vertex(State): ";
				cin >> id1;
				cout << "\t\t\t\t\t\tEnter ID of Destination Vertex(State): ";
				cin >> id2;
				g.deleteEdgeByID(id1, id2);
				
				while(edge>>fid1>>fid2>>fw)
				{
			    	if((fid1==id1||fid1==id2)&&(fid2==id2||fid2==id1))
			    	{
			    		cout<<"\n";
					}
					else
					{
						temp1<<endl<<fid1<<endl;
						temp1<<fid2<<endl;
						temp1<<fw;
					}
				    	
				}
				
		    	edge.close();
				temp1.close();
				
				//REMOVING AND RENAMING
				remove("edge.txt");
				rename("temp1.txt", "edge.txt");
		    	cout<<"\t\t\t\t\t\t";					
		    	system("pause");
		    	system("cls");
			}
			else if(choise == "9")
			{
				cout<<"\t\t\t\t\t\t----------------------------------\n";
				cout << "\t\t\t\t\t\tPrint Graph Operation -" << endl;
				cout<<"\t\t\t\t\t\t----------------------------------\n";
				g.printGraph();
				cout<<"\t\t\t\t\t\t----------------------------------\n";
		    	cout<<"\t\t\t\t\t\t";
				system("pause");
				system("cls");
			}
			else if(choise =="10")
			{
				cout<<"\t\t\t\t\t\t----------------------------------\n";
				cout << "\t\t\t\t\t\tFind Fare Operation -" << endl;
				cout<<"\t\t\t\t\t\t----------------------------------\n";
				cout << "\t\t\t\t\t\tEnter ID of Source Vertex(State): ";
				cin >> id1;
				cout << "\t\t\t\t\t\tEnter ID of Destination Vertex(State): ";
				cin >> id2;
				cout<<"\t\t\t\t\t\tFare is: Rs."<<g.findRouteFare(id1,id2);
				cout<<"\n\t\t\t\t\t\t----------------------------------\n";
		    	cout<<"\t\t\t\t\t\t";
				system("pause");
				system("cls");
			}
			else if(choise=="0")
			{
				exit(0);
			}
			else
			{
				cout<<"\n\n\t\t\t\t\t\tInvalid Input\n";
				cout<<"\t\t\t\t\t\t";
				system("pause");
				system("cls");
			}
			}
			while(hold ==true);
		}
		
		
		
		
		Node* GetHead()
		{
			current = head;
			return current;
		}
		
		void save(Node* C)
		{
				ofstream MyFile;
			
				MyFile.open("AirLine.txt", ios::app);
				while(C!=NULL)
				{
					MyFile<<endl;
					MyFile<<C->getName();
					MyFile<<endl;
					MyFile<<C->getNationality();
					MyFile<<endl;
					MyFile<<C->getReg();
					MyFile<<endl;
					MyFile<<C->getSeats();
					
					C = C->getNext();
				}
				
				MyFile.close();
		}
		
		bool GetLog()
		{
			return Log;
		}
};



int main()
{
	system("color 70");
	Main intro;
	string choise;
	logi = false;
	bool load = true;
	intro.Logo();
	bool hold = true;
	
	while(hold == true)
	{
		if(logi==false)
		{
		
		cout<<"\n\n\n\n\n\t\t\t\t\t\tPress 1 To LogIn";
		cout<<"\n\t\t\t\t\t\tPress 2 To SignUp";
		cout<<"\n\t\t\t\t\t\tChoise: ";
		cin>>choise;
		if(choise == "1")
		{

			logi = true;
			intro.LogIn();
		}
		else if (choise == "2")
		{
			intro.SignUp();
		}
		else
		{
			cout<<"\n\t\t\t\t\t\tInvalid Input";
			cout<<"\n\n\t\t\t\t\t\t";
			system("pause");
			system("cls");
		}
		}
		if(intro.GetLog()==true)
			{
				if(load == true)
				{
					system("cls");
					cout<<"\n\n\n\n\n\t\t\t\t\t\tWelcome..!!";
					sleep(2);
					system("cls");
					
					load = false;
				}
				intro.Menu();
				intro.setLog(false);
				logi = false;
				system("cls");
			}
		}
}

