#include <iostream>
#include <string>
#include <stack>
using namespace std;
//Class of Mind Thrashing Containing the information
template<class T, class S>
class Mind_Thrashing
{
public:
    S stage_name;
    T points, stage_time,index;

    Mind_Thrashing()
    {
         stage_name = "";
         points = 0;
         stage_time = 0;
         index =0;
    }
    Mind_Thrashing(S const&stage_name,T const&points, T const&stage_time,T const&index)
    {
        this->stage_name = stage_name ;
        this->points = points;
        this->stage_time = stage_time;
        this->index = index;
    }

    template<class t>
    friend class Node;
};
// Class of each Node
template<class T>
class Node{
    T data;
    Node* next;
public:
    Node() // Default constructor
    {
        data.stage_time = 0;
        data.points = 0;
        data.stage_name ="";
        data.index = 0;
        next = nullptr;
    }
    Node( T  const&data, Node<T>* next) // Overloaded constructor
    {
        this->data = data;
        this->next = next;
    }
    template<class t>
    friend class List;
    friend class Stack;
};
// Class of the List
template<class T>
class List
{
private:
    Node<T>* head;
    int Size;
public:
    List()  // Default constructor
    {
        head = nullptr;
        Size = 0;
    }
    void operator = (const List<T> &D )
     {
        head = D.head;
        Size = D.Size;
    }
    T Top() // Return the top of the stack list
    {
        return  head->data;
    }
    int size()  // Returns the size of the stack list
    {
        return Size;
    }
    bool is_Empty()     // Check if the  stack list is empty
    {
        if (Size == 0)
        {
            return true;
        }
        else {
            return false;
        }
    }
    // Function to insert at start
    void push(T const&elements)
    {
        if (Size == 0)
        {
            head = new Node<T>(elements, nullptr);
        }
        else
        {
            head = new Node<T>(elements, head);
        }
        Size = Size + 1;
    }
    // Function to Delete at start
    void pop()
    {
        if (Size == 0) {
            cout << "Stack is Empty" << endl;
        }
        else
        {
            Node<T> *Temp = head;
            head = Temp->next;
            delete Temp;
            Size = Size - 1;
        }
    }
    friend class Stack;
};

// Class of Stack
//template<class T>
class Stack
{
    int player_time;
    int Max_points;
    Mind_Thrashing<int,string> temp;
    List<Mind_Thrashing<int,string>> S;
public:

    Stack() // Default constructor
    {
        Max_points =0;
        temp.stage_time = 0;
        player_time =0;
    }
    Stack(int player_time)
    {
        this->player_time = player_time;
    }
    Mind_Thrashing<int,string> Top()    // Return the stack top
    {
        return S.Top();
    }
    int size(){  // return the stack size
        return S.size();
    }
    bool is_Empty()
    {
        return S.is_Empty();
    }
    void push(Mind_Thrashing<int,string> const& element) {  // Function to insert in the stack
        S.push(element);
    }
    void pop(){         // Fucntion to delete from the stack
        S.pop();
    }
    void print()
    {
        cout << "stage_name : " <<S.Top().stage_name << endl;
        cout << "points : " << S.Top().points << endl;
        cout << "stage_time : "<< S.Top().stage_time << endl;
    }

    Stack sortStack(Stack Sort_stack)   // Function to Sort the Stack
    {
        Stack Tmp_stack;
        while (!Sort_stack.is_Empty())
        {
            Mind_Thrashing<int,string> tmp = Sort_stack.Top();
            Sort_stack.pop();
            while (!Tmp_stack.is_Empty() && Tmp_stack.Top().stage_time < tmp.stage_time)
            {
                Sort_stack.push(Tmp_stack.Top());
                Tmp_stack.pop();
            }
            Tmp_stack.push(tmp);
        }
        return Tmp_stack;
    }
    void Check()
    {
        Stack new_stack;
        Stack new_stack2;
        //-------------------------------------------------------------------------------
        // Printing all possible games individually which a player can play within given time
        while (!S.is_Empty())
        {
            if (S.Top().stage_time <= player_time) // Comparing the player time and stage time
            {
                cout << " Stage number : " << S.Top().index << " can only be played with points : "
                << S.Top().points << endl;
                if(Max_points < S.Top().points)
                {
                    Max_points = S.Top().points;
                }
                new_stack.push(S.Top()); //copying the stack to other stack for other checks
                new_stack2.push(S.Top()); //copying the stack to other stack for other checks
            }
            S.pop();
        }

      //------------------------------------------------------------------------------------
      // Printing all possible games collectively which a player can play within given time
        new_stack2 = new_stack2.sortStack(new_stack2);
        int Tmp = 0, n =0, n1 =0;
        cout << " Stage number : ";
        while (!new_stack2.is_Empty())
        {

            Tmp = new_stack2.Top().stage_time + Tmp;
            if(Tmp <= player_time)
            {
                cout << new_stack2.Top().index  << " and ";
                n = new_stack2.Top().points + n;
                if(Max_points < n)
                {
                    Max_points = n;
                }
            }
            else
            {
                n1 = new_stack2.Top().points;
                break;
            }
            new_stack2.pop();
        }
        cout << "can played with the points " << n << " ----It can be the Best Choice "<< endl;
        if(n < n1)
        {
            cout << "Best Choice Stage No : "<< new_stack2.Top().index << " with points  "<< Max_points << endl;
        }

        //------------------------------------------------------------------------------------
        // Printing all possible games collectively which a player can play within given time
        Stack new_stack1;
        while (!new_stack.is_Empty())
        {
            temp = new_stack.Top();
            new_stack.pop();
           if(!new_stack.is_Empty())
           {
                new_stack1 = new_stack ;//------
           }
            while(!new_stack1.is_Empty())
            {
                if((temp.stage_time + new_stack1.Top().stage_time) <= player_time)
                {
                    if(Max_points < temp.points+ new_stack1.Top().points)
                    {
                        Max_points = temp.points+ new_stack1.Top().points;
                    }
                    cout << " Stage number : " << temp.index << " and "<< new_stack1.Top().index  <<
                    " can only be played with points : " << temp.stage_time + new_stack1.Top().stage_time<< endl;
                }
                new_stack1.pop();
            }
        }

    }

    template<class g>
    friend class List;
    template<class k>
    friend class Node;
};
int main()
{
    Node<Mind_Thrashing<int,string>> N;
    List<Mind_Thrashing<int,string>> L;
    int stages ,i = 1;
    string stage_name;
    int points;
    int stage_time = 0, player_time = 0;
    cout << " HOW MANY NUMBER OF STAGES OF MIND THRASHING GAME ARE OFFER THIS WEEK : " ;
    cin >> stages;
    cout << "HOW MUCH TIME DO YOU HAVE TO PLAY THE GAME : ";
    cin >> player_time;
    Stack STACK(player_time);
    cout << endl;
    if(stages == 0)
    {
        cout << "RETRY AGAIN " << endl;
    }
    else
    {
        while(i <= stages)
        {
            cout << " ENTER THE "<< i  << " NAME OF STAGE : " ;
            cin >> stage_name;
            cout << " ENTER THE POINTS OF THIS STAGE : ";
            cin >> points;
            cout << " ENTER THE REQUIRED TIME OF THIS STAGE : " ;
            cin >> stage_time;
            cout << endl;
            Mind_Thrashing<int,string> M(stage_name,points,stage_time,i);
            STACK.push(M);
            i++;
        }
    }
    STACK.Check();
    return 0;
}


