// Baha Jiyan Yılmaz 19070006010
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Node{
public:
    char data;
    Node* next;
};

Node* addNewNode(int data) //Adding new node to link list
{
    Node* new_node = new Node();
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node* stringTOLinkedList(string str, Node* head) //Converting string to linked list.
{
    int firstNo;
    stringstream ss;            // changing data type  of string to int for adding calculation
    ss << str[0];
    ss>>firstNo;
    head = addNewNode(firstNo);
    Node* curr = head;

    for (int i = 1; i < str.size(); i++) // Adding big numbers digits to link list as an int node
    {   int num;
        stringstream sd; //converting string to int
        sd << str[i];
        sd>>num;
        curr->next = addNewNode(num);
        curr = curr->next;
    }
    return head;
}

Node* reverse(Node* head)  //Reversing the big number for summation
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    Node* rest = reverse(head->next);
    head->next->next = head;
    head->next = NULL;
    return rest;
}

Node* sumOfTwoLists(Node* first, Node* second, bool flag) //Function that calculate the sum of two link list and creates a new list
{
    Node* res = NULL;
    Node *temp, *prev = NULL;
    int carry = 0, sum;

    string rev=""; //temporary value for printing the final result.

    while (first != NULL || second != NULL)
    {
        sum = carry + (first ? first->data : 0) + (second ? second->data : 0);
        carry = (sum >= 10) ? 1 : 0;
        sum = sum % 10;
        temp = addNewNode(sum);

        stringstream se;  //converting int to string for printing.
        se<<sum;
        rev+=se.str();

        if (res == NULL)
        {
            res = temp;
        }
        else
        {
            prev->next = temp;
        }
        prev = temp;
        if (first)
        {
            first = first->next;
        }
        if (second)
        {
            second = second->next;
        }
    }
    if (carry > 0)
    {
        temp->next = addNewNode(carry);
    }
    if(flag==true)  // I put a flag for seeing the final result with reversed version
    {   //if its final big number (line 100) flag is true else its false
        std::string copy(rev);
        std::reverse(copy.begin(), copy.end());
        copy.pop_back();
        cout<<endl<<copy;
    }
    return res;
}

void printList(Node* head) //prints the linked list
{
   Node* curr=head;
   while(curr!= NULL)
   {
       cout<<curr->data<<" -> " ;
       curr=curr->next;
   }
   cout<<endl;
}

int main()
{
    //file reading
    cout << endl << "*Reading From File" << endl;
    ifstream read_file;
    read_file.open("../numbers.txt");
    if (!read_file.is_open())
    {
        cerr << "File  could not be opened" << endl;
        exit(1);
    }
    string line;
    string numbers[100];
    int lineNo=0;
    while (getline(read_file, line))
    {
        numbers[lineNo]=line; // copying every line to string.Every string element is one big number.
        lineNo++;
    }
    read_file.close();

    Node* head = NULL;
    Node* headTwo=NULL;
    Node* res = NULL;

    bool flag=false;
    string firstNo=numbers[0]; //Copying the first number to another string
    string secondNo=numbers[1]; // Copying the second number to another string

    head = stringTOLinkedList(firstNo, head);
    headTwo= stringTOLinkedList(secondNo,headTwo);
    // printList(head);

    head= reverse(head);
    headTwo= reverse(headTwo);

    res= sumOfTwoLists(head, headTwo, flag); // summation of first two line
    res = reverse(res); //Reversing the final list to get the true result.

    for (int x =2 ; x < 100; ++x)  // starting from 3. number and adding to res to line by line.
    {
        string num =numbers[x];
        head = stringTOLinkedList(num, head);
        head = reverse(head);
        if(x==99)
        {
            flag=true; //last line and flag becomes true and it prints the final result.
        }
        res= sumOfTwoLists(res, head, flag);
        res = reverse(res);
    }
    cout<<endl;
    cout << "Final linked list is ";
    printList(head);
    return 0;
}



