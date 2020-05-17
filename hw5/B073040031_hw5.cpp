#include<iostream>
using namespace std;

//	Author		���P�� B073040031
//	Date		2019/10/31
//	Purpose		addition and multiplication implement of polynomial with linked-list

class node
{
    public:
        node(int x, int y) : coefficient(x), exponent(y), next(NULL) {}     //constructor
        int coefficient, exponent;
        node *next; 
};

class polynomial
{
    private:
        node *head;
    public:
        polynomial() : head(NULL) {}        //constructor
        ~polynomial() {}                    //destructor

        friend ostream& operator <<(ostream&, const polynomial&);   //output overload
        polynomial operator +(const polynomial&);                   //addition overload
        polynomial operator *(const polynomial&);                   //multiplication overload

		node* find(int);                    //find the right place to insert
		void insert(int,int);               //insert the node into list
        void remove();            //remove node of zero-coefficient term 
};

int main()
{
    int p, q, c, e;
    while(true)             
    {
        polynomial P, Q;

        cin>>p;        
        for(int i=0;i<p;i++)
        {
            cin>>c>>e;
            P.insert(c,e); 
        }
        cin>>q;
        for(int i=0;i<q;i++)
        {
            cin>>c>>e;
            Q.insert(c,e);
        }

        if(p==0 && q==0)        //input 0 0 to exit
            break;
        
        cout<<endl<<"ADD"<<endl<<P+Q<<endl;
        cout<<"MULTIPLE"<<endl<<P*Q<<endl;
    }
	return 0;
}

ostream& operator <<(ostream& o, const polynomial &output)
{
    node *current = output.head;
    if(current == NULL)         //if nothing in the list means 0
    {
        cout<<endl<<"0 0";
        return o;
    }
    while(current != NULL)      //from head to last traversaling and output the value
    {
        o<<current->coefficient<<" "<<current->exponent<<endl;
        current = current->next;
    }
    return o;
}

polynomial polynomial :: operator*(const polynomial &multiplier)
{
    polynomial product;         //final product
    node *multiplicand = this->head;
    while(multiplicand != NULL)     //multiply one by one and then plus them all
    {
        node *current = multiplier.head;
        polynomial operand;
        while(current != NULL)
        {
            operand.insert(multiplicand->coefficient * current->coefficient, multiplicand->exponent + current->exponent);       //coefficient *, exponent + 
            current = current->next;
        }
        product = product + operand;//note: plus is here
        multiplicand = multiplicand-> next;
    }
    return product;
}

polynomial polynomial :: operator+(const polynomial &addend)        //the raseon why I just put augend and addend (node) into sum is I have sorted and delt with exception when inserting
{
    polynomial sum;             //final sum
    node* current = this->head;
    while(current != NULL)      //put all nodes of augend into sum
    {
        sum.insert(current->coefficient,current->exponent);
        current = current->next;
    }
    current = addend.head;
    while(current != NULL)      //put all nodes of addend into sum
    {
        sum.insert(current->coefficient,current->exponent);
        current = current->next;
    }
    sum.remove();               //remove zero-coefficient term node
    return sum;                             
}

void polynomial :: remove()
{
    node *current = this->head, *previous = this->head;
    while(current != NULL)
    {
        if(current->coefficient == 0)   //0 coefficient node
        {
            if(current == this->head)   //0 is at head
            {
                if(current->next == NULL)   //only a node in the list
                {
                    this->head = NULL;
                    delete current;
                    return;         //if sum.head points to NULL,represent its result is 0 0;
                }
                else
                {
                    this->head = this->head->next;
                    delete current;
                    current = previous = this->head;
                }
            }
            else
            {
                current = current->next;
                delete previous->next;                
                previous->next = current;
            }
        }
        else                            //not 0 coefficien, keeping traversaling
        {
            previous = current;
            current = current->next;
        }
    }
}

node* polynomial :: find(int e)
{
    if(this->head->next == NULL || e > this->head->exponent)    //only a node in the list _and_ the exponent of node will be inserted is bigger than all nodes in the list return head pointer
        return this->head;
    else
    {
        node *current = this->head;
        while(current->next != NULL)                            
        {
            if(current->exponent == e)                          //find the same exponent
                return current;
            else if(current->exponent > e && current->next->exponent < e)
                return current;                                 //suit place for newnode

            current = current->next;                            //keeping traversaling
        }
        return current;                                         //next node is the last node
    }
}

void polynomial :: insert(int x,int y)
{
    node *newnode = new node(x,y);

    if(head == NULL)                                            //nothing in the list
        head = newnode;
    else
    {
        node *current = find(y);
        if(current->exponent == y)                              //the same exponent term, add thier coefficient
            current->coefficient = current->coefficient + newnode->coefficient;
        else if(current == head && y > current->exponent)       //the exponent of newnode is the biggest 
        {
                newnode->next = current;
                head = newnode;
        }
        else if(current->next == NULL)                          //newnode added at the end of list(exponent is the least) 
                current->next = newnode;
        else                                                    //normal insert at the middle of list
        {
            newnode->next = current->next;
            current->next = newnode;
        }
    }
    remove();                                                   //remove zero term 
}