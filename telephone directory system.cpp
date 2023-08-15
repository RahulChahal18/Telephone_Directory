#include <bits/stdc++.h>
using namespace std;


class Node{
    //Using a doubly linked list for storing the contacts
    public:
    string Name;
    long long PhoneNo;
    Node* next;
    Node* prev;

    Node(string name, long long Phoneno){
        this->Name = name;
        this->PhoneNo = Phoneno;
        this->next = NULL;
        this->prev = NULL;
    }
    
};

class ContactBook{
    
    Node* head;
    string name;
    long long Phoneno;
    
    public:
    ContactBook(){
        head = NULL;
        name = "";
        Phoneno = 0;
    }

    void OflineSave()
    	{
    		Node* temp=head;
    		ofstream myfile ("contactbook.txt");
            if (myfile.is_open())
            {
            	while(temp!=NULL)
	        	{
	        	    myfile<<temp->Name<<endl;
		        	myfile<<temp->PhoneNo<<endl;
    		    	temp=temp->next;		
	        	}
                myfile.close();
                return;
            }
            else
            {
            	cout<<"  Thanks file is empty."<<endl;
			}
		}

    void reopenCB()
		{
			bool isEmpty;
			ifstream myfile ("contactbook.txt");
            if (myfile.is_open() & myfile.peek() != EOF)
            {
                int i=0;
                while(getline(myfile,name))
                {	
                    if(i % 2 == 0)
					{
						if(head==NULL)
	                    {
    	                  Node *newer= new Node(name, 0);		         
	                      head=newer;
		                }
						else
						{
							Node *newer= new Node(name, 0);				
							Node *temp=head;
		                	while(temp->next!=NULL)
		                	{
		                		temp=temp->next;
		                	}
		                	temp->next=newer;
		                	newer->prev=temp;		
						} 
                    }
                   else
                    {
                    	Node *temp=head;
                    	if(temp->PhoneNo==0)
                    	{
                    		
                    		 stringstream convert(name);
			       	         convert>>Phoneno;
                             temp->PhoneNo=Phoneno;
						}
						else
						{
							Node *temp=head;
		                	while(temp->next!=NULL)
		                	{
		                		temp=temp->next;
		                	}
		                	
		                	stringstream convert(name);
			       	        convert>>Phoneno;
		                	temp->PhoneNo=Phoneno;
							
						}
                       
				    }
                    i++;
                }
            	myfile.close();
            }
            else
            {
            	cout<<"  File is Empty so Cannot open...Sorry"<<endl;
			}
		}

    void Search(){
        cout<<"Press 1 to search by Name. Press 2 to seach by number."<<endl;
        cout<<"Press 0 to exit."<<endl;
        cout<<endl;
        int n;
        cin>>n;
        
        if(n==0){
            cout<<endl;
            return;
        }
        else{
            Node* temp = head;
            if(temp==NULL){
                cout<<"Contact list is empty. No Contacts to search."<<endl;
                cout<<endl;
                return;
            }
            if(n==1){
                cout<<"Enter Name: ";
                cin>>name;
                while(temp!=NULL){
                    if(temp->Name == name){
                        cout<<"Contact found"<<endl;
                        cout<<endl;
                        cout<<"Name: "<<temp->Name<<endl;
                        cout<<"Number: "<<temp->PhoneNo<<endl;
                        cout<<endl;
                        return;
                    }
                }
                if(temp==NULL){
                    cout<<"Contact not found. Try again"<<endl;
                    cout<<endl;
                    Search();
                }
            }
            else if(n==2){
                cout<<"Enter Phone Number: ";
                cin>>Phoneno;
                while(temp!=NULL){
                    if(temp->PhoneNo == Phoneno){
                        cout<<"Contact found"<<endl;
                        cout<<endl;
                        cout<<"Name: "<<temp->Name<<endl;
                        cout<<"Number: "<<temp->PhoneNo<<endl;
                        cout<<endl;
                        return;
                    }
                }
                if(temp==NULL){
                    cout<<"Contact not found. Try again"<<endl;
                    cout<<endl;
                    Search();
                }
            }
        }


    }


    void BubbleSort(){
        Node* temp = head;
        if(head == NULL){
            return;
        }
        
        Node *i, *j;
        for(i=head;i->next!=NULL; i=i->next){
            for(j=i->next; j!=NULL ; j=j->next){
                if(i->Name > j->Name){
                    string n = i->Name;
                    i->Name = j->Name;
                    j->Name = n;

                    long long no = i->PhoneNo;
                    i->PhoneNo = j->PhoneNo;
                    j->PhoneNo = no;
                }
            }
        }
        return;
    }
    void AddContact(){
        //Take input
        cout<<"Enter Name: ";
        cin>>name;
        cout<<"Enter Phone Number :";
        cin>>Phoneno;

        //if the contact book is empty in the beginnning
        if(head ==  NULL){
            Node* newNode = new Node(name, Phoneno);
            head = newNode;
        }
        //if the contact book is not empty
        else{
            Node* newNode = new Node(name, Phoneno);
            Node* temp = head;
            while(temp->next!=NULL){
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
        cout<<endl;

        cout<<"Contact Successfully added. "<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Number: "<<Phoneno<<endl;
        BubbleSort();
        cout<<endl;
        return;

    }

    void DeleteContact(){
        if(head == NULL){
            cout<<"Contact list is empty. Nothing to delete"<<endl;
            cout<<endl;
            return;
        }
        else{
            //take input
            cout<<"Enter Name of Contact to Delete: ";
            cin>>name;
            cout<<"Enter PhoneNo: ";
            cin>>Phoneno;

            //create a temp node so that it can traverse and find the required node
            Node* temp = head;
            Node* previous = NULL;
            bool found = false;
            
            while(temp!=NULL){
                if(temp->Name == name && temp->PhoneNo == Phoneno){
                    found = true;
                    break;
                }
                previous = temp;
                temp = temp->next;
            }
            if(!found){
                cout<<"Contact not found. Kindly try again with correct name and number"<<endl;
                cout<<endl;
                return;
            }
            else if(found){
                cout<<"Contact found. Press 2 to delete"<<endl;
                int n;
                cin>>n;
                if(n==2){
                    //handling special case - head needs to be deleted
                    if(temp == head){
                        head = head->next;
                        temp->next = NULL;
                        head->prev = NULL;
                        delete temp;
                        cout<<"Contact Successfully deleted"<<endl;
                        BubbleSort();
                        cout<<endl;
                        return; 
                    }

                    //handling special case - tail needs to be deleted
                    else if(temp->next == NULL){
                        previous->next = NULL;
                        temp->prev = NULL;
                        delete temp;
                        cout<<"Contact Successfully deleted"<<endl;
                        BubbleSort();
                        cout<<endl;
                        return;
                    }
                    else{
                        previous->next = temp->next;
                        temp->next->prev = previous;
                        temp->next = NULL;
                        temp->prev = NULL;
                        delete temp;
                        cout<<"Contact Successfully deleted"<<endl;
                        BubbleSort();
                        cout<<endl;
                        return; 
                    }
                }
                else{
                    cout<<endl;
                    cout<<"Invlaid Command. Try again."<<endl;
                    cout<<endl;
                    return;
                }   
            }
        }
    }

    void EditContact(){
        cout<<"Enter name of Contact to Edit: ";
        cin>>name;
        Node* temp = head;
        while(temp!=NULL){
            if(temp->Name == name){
                cout<<"Contact found."<<endl;
                break;
            }
            temp = temp->next;
        }
        if(temp==NULL){
            cout<<"Contact not found. Kindly try again with correct name"<<endl;
            EditContact();
        }
        else{
            cout<<"Name: "<<temp->Name<<endl;
            cout<<"Phone number: "<<temp->PhoneNo<<endl;
            cout<<"To edit name press 1 and to edit number press 2"<<endl;
            cout<<"To exit press 0"<<endl;
            int n;
            cin>>n;
            if(n==1){
                cout<<"Enter new Name: ";
                cin>>name;
                temp->Name = name;
                cout<<"Name successfully modified"<<endl;
                cout<<"Name: "<<temp->Name<<endl;
                BubbleSort();
                cout<<endl;
                return;
            }
            else if(n==2){
                cout<<"Enter new Number: ";
                cin>>Phoneno;
                temp->PhoneNo = Phoneno;
                cout<<"Phone number successfully modified"<<endl;
                cout<<"Number: "<<temp->PhoneNo<<endl;
                cout<<endl;
                return;
            }
            else{
                cout<<endl;
                return;
            }
        }
    }

    void ViewContact(){
        Node* temp = head;
        if(head==NULL){
            cout<<"Contact book is empty. No contacts to display."<<endl;
            cout<<endl;
            return;
        }
        int count = 0;
        cout<<"Name:           "<< "Number: "<<endl;
        while(temp!=NULL){
            cout<<temp->Name<<"           "<<temp->PhoneNo<<endl;
            count++;
            temp = temp->next;
        }
        cout<<endl;
        cout<<"Total "<<count<<" contacts present."<<endl;
        cout<<endl;
        return;
    }


    void deleteAllContacts(){
        if(head==NULL){
            cout<<"Contact list is empty. No contacts to delete."<<endl;
            cout<<endl;
            return;
        }
        Node* temp = head; 
        while(head!=NULL){
            head = head->next;
            temp->next = NULL;
            delete temp;
            Node* temp = head;
        }
        if(head == NULL){
            cout<<"Contacts successfully deleted. Contact list is now empty."<<endl;
            cout<<endl;
            return;
        }
    }

    void Intro(){
        
        cout<<"Kindly choose from the following options to proceed: "<<endl;
        cout<<"1. Add a new Contact"<<endl;
        cout<<"2. Delete an existing Contact"<<endl;
        cout<<"3. Edit an existing Contact"<<endl;
        cout<<"4. View all Contacts"<<endl;
        cout<<"5. Delete all Contacts"<<endl;
        cout<<"6. Search Contacts"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<endl;
    }

};

int main(){
    cout<<"Welcome to Telephone Directory"<<endl;
    ContactBook cb;
    cb.reopenCB();
    cb.Intro();

    int n;
    cin>>n;
    while(n!=0){
        switch (n){
            case 1:
                cb.AddContact();
                cb.OflineSave();
                break;
            case 2: 
                cb.DeleteContact();
                cb.OflineSave();
                break;
            case 3:
                cb.EditContact();
                cb.OflineSave();
                break;
            case 4: 
                cb.ViewContact();
                break;
            case 5:
                cb.deleteAllContacts(); 
                cb.OflineSave();
                break;
            case 6:
                cb.Search();
                break;
            default:
                cout<<"Invalid Command. Try again."<<endl;
                break;
        }
        cb.Intro();
        cin>>n;
    }
    cout<<endl;
    cout<<"Thank you for using Telephone Directory"<<endl;
}
