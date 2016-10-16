#include <bits/stdc++.h>

using namespace std;

int bucket_size = 2, currentLength = 0;

int bit_length=4;

string doBinary(int rem)
{
    int i, tmp;
    char c;
    string binary = "";
    vector <int> v;

    for(i=rem; i>0; i/=2)
        v.push_back(i%2);

    if(v.size() < bit_length)
    {
        tmp = bit_length - v.size();
        for(i=1; i<=tmp; i++)
            v.push_back(0);
    }

    while(!v.empty())
    {
        tmp = v.back();
        v.pop_back();
        c = tmp + 48;
        binary = binary + c;
    }
    return binary;
}

struct Node
{
    string val;
    Node *next;
    Node *sibling;
    vector <int> bucket;
    int cnt;
};

class dynamicHash
{
    public:
        dynamicHash();
        void insertVal(int input);
        void display();

    private:
        Node *root;
        void insertVal(int input, Node *hashNode);
        void splitNode(int input, Node *hashNode);
        void splitSibling(int input, Node *hashNode);
        void display(Node *hashNode);
};

dynamicHash::dynamicHash()
{
    root = NULL;
}

void dynamicHash::insertVal(int input)
{
    if(currentLength==0)
    {
        Node *temp1, *temp2;
        currentLength++;
        temp1 = new Node;
        temp2 = new Node;
        temp1->val = "0";
        temp2->val = "1";
        temp1->next = temp2;
        temp2->next = NULL;
        temp1->sibling = NULL;
        temp2->sibling = NULL;
        temp1->cnt = temp2->cnt = 1;
        root = temp1;
    }
    insertVal(input, root);
}

void dynamicHash::insertVal(int input, Node *hashNode)
{
    int i;
    string binary = "";
    Node *exp = new Node;
    Node *exp2 = new Node;

    binary = doBinary(input%(int)pow(2,bit_length));
    for(exp = hashNode; exp!=NULL; exp = exp->next)
    {
        for(i=0; i<exp->cnt; i++)
        {
            if(exp->val[i]==binary[i]) continue;
            else break;
        }
        if(i==exp->cnt)
        {
            if(exp->bucket.size()==bucket_size)
            {
                if(exp->cnt==currentLength)
                    splitNode(input, exp);
                else
                    splitSibling(input, exp);
            }
            else
            {
                for(exp2 = exp; exp2!=NULL; exp2 = exp2->sibling)
                    exp2->bucket.push_back(input);
            }
            break;
        }
    }
}

void dynamicHash::splitNode(int input, Node *hashNode)
{
    Node *exp = new Node;
    vector <int> v;
    string binary = "";
    int data, i;

    for(exp = root; exp!=NULL; exp = exp->next)
    {
        Node *temp1 = new Node;
        if(exp->val.compare(hashNode->val)==0)
        {
            temp1->next = exp->next;
            exp->next = temp1;
            exp->cnt++;
            temp1->cnt = exp->cnt;
            temp1->sibling = NULL;
            temp1->val = exp->val + "1";
            exp->val = exp->val + "0";
            currentLength++;
            v = exp->bucket;
            while(!exp->bucket.empty()) exp->bucket.pop_back();
            v.insert(v.begin(), input);

            while(!v.empty())
            {
                data = v.back();
                v.pop_back();
                binary = doBinary(data%(int)pow(2,bit_length));
                for(i=0; i<exp->cnt; i++)
                {
                    if(exp->val[i]==binary[i]) continue;
                    else break;
                }

                if(i==exp->cnt)
                    exp->bucket.push_back(data);
                else
                    temp1->bucket.push_back(data);
            }

            exp = exp->next;
        }

        else
        {
            temp1->next = exp->next;
            exp->next = temp1;
            temp1->cnt = exp->cnt;
            temp1->sibling = exp->sibling;
            exp->sibling = temp1;
            temp1->val = exp->val + "1";
            exp->val = exp->val + "0";
            temp1->bucket = exp->bucket;
            exp = exp->next;
        }
    }
}

void dynamicHash::splitSibling(int input, Node *hashNode)
{
    Node *exp = new Node;
    vector <int> v;
    int data, i;

    v = hashNode->bucket;
    v.push_back(input);

    for(exp = hashNode; exp!=NULL; exp = exp->sibling)
    {
        exp->cnt++;
        data = exp->cnt;
        while(!exp->bucket.empty())
            exp->bucket.pop_back();
    }
    for(exp = hashNode; exp!=NULL; exp = exp->sibling)
        for(i=0; i<data; i++)
            if(exp->val[i]!=exp->sibling->val[i]) exp->sibling = NULL;

    while(!v.empty())
    {
        insertVal(v.back());
        v.pop_back();
    }
}

void dynamicHash::display()
{
    Node *exp = new Node;
    int i;

    for(exp = root; exp!=NULL; exp = exp->next){
        cout << "node " << exp->val << "  ->  ";
        if(exp->bucket.size()==0)
        {
            cout << "empty!!" << endl;
            continue;
        }
        for(i=0; i<exp->bucket.size(); i++)
        {
            if(i==exp->bucket.size()-1) cout << exp->bucket[i];
            else cout << exp->bucket[i] << " , ";
        }
        cout  << endl;
    }
}

int main()
{
    dynamicHash obj;
    int n;
    while(true)
    {
        cout << "\nenter value to insert : ";
        cin >> n;
        obj.insertVal(n);
        obj.display();
    }

    return 0;
}
