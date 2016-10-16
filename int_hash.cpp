#include<bits/stdc++.h>
#include<stdio.h>
#define bucket_capasity 2
#define mod_val 8
class hash_address;
class bucket;
class Hash_Lib;
using namespace std;

int prefix_length=0;
int address_table_size=0;

int bucket_num=0;



class bucket
{


public:
    int bit_length;
    int num;
    int count_value=0;
    int value[bucket_capasity];

    bucket* next_bucket=NULL;
    int parent_length=0;
    hash_address* parent_address[10];


};
class hash_address
{

public:
    int prefix_val;
    bucket* ptr;
    hash_address* next=NULL;


};

hash_address* address_table_root=NULL;

void print_hash_table()
{

    cout << "Print val" << endl;

    if(address_table_root==NULL)
    {

        cout << "Hash Table is empty" << endl;

    }
    else
    {
        hash_address* temp_address=address_table_root;

        while(temp_address)
        {
            cout << "Address Table"<< endl;
            if(temp_address->ptr!=NULL)
            {
                bucket* temp_bucket=temp_address->ptr;

                while(temp_bucket)
                {
                    cout << "address = " << temp_address->prefix_val << "   bucket ---> " << temp_bucket->num<< endl;

                    for(int i=0; i<bucket_capasity ; i++)
                    {
                        cout << i << "--->" <<temp_bucket->value[i] << endl;
                    }


                    temp_bucket=temp_bucket->next_bucket;
                }

            }
            temp_address=temp_address->next;

        }

    }


}

class Hash_Lib
{



public:

    void redistribute(int value)
    {
        hash_address* last_half_address;
        int new_prefix_start=pow(2,prefix_length);
        hash_address* temp1_previous;
        hash_address* address_pre;

        int i=0;
        hash_address* temp_address=address_table_root;

        while(temp_address!=NULL)
        {
            cout << "val = " <<temp_address->prefix_val<< "  " << i << endl;

            hash_address* temp1=new hash_address();
            temp1->prefix_val=new_prefix_start;
            new_prefix_start++;
            temp1->ptr=temp_address->ptr;
            temp1->ptr->parent_address[temp1->ptr->parent_length++]=temp1;
            temp1->next=NULL;



            //cout << "ok line = 247"<< endl;

            if(i==0)
            {

                last_half_address=temp1;

                i++;
            }
            else
            {
                temp1_previous->next=temp1;
            }

            temp1_previous=temp1;
            address_pre=temp_address;


            temp_address=temp_address->next;



        }

        cout << "ok line = 2499"<< endl;

        prefix_length+=1;
        cout <<"---pre---"<<address_pre->prefix_val << endl;
        address_pre->next=last_half_address;

        int rem_old_table=value%(int)pow(2,prefix_length-1);
        hash_address* temp_loop=address_table_root;

        while(temp_loop!=NULL){

            if(temp_loop->prefix_val==rem_old_table)
            {
                break;
            }
            temp_loop=temp_loop->next;
        }


        int redist_array[bucket_capasity+1];
        int j=0;
        for(j=0;j<bucket_capasity;j++)
        {
            redist_array[j]=temp_loop->ptr->value[j];
            temp_loop->ptr->value[j]=0;

        }
        redist_array[j]=value;
        temp_loop->ptr->count_value=0;

        //--------------------------------------------------------
        for(int p=0;p<temp_loop->ptr->parent_length;p++)
        {
            cout <<"ppp" << endl;
            (temp_loop->ptr->parent_address[p])->ptr=NULL;

        }
        temp_loop->ptr->parent_length=0;
        temp_loop->ptr->count_value=0;
        //--------------------------------------------------------


        for(j=0;j<=bucket_capasity;j++)
        {
            cout <<"again insert = " << redist_array[j] << endl;
            this->insert_value(redist_array[j]);
        }



    }


    void insert_value(int value)
    {
        cout <<"Ins = "<< value << endl;
        if(address_table_root==NULL)
        {

            hash_address* temp0=new hash_address();
            hash_address* temp1=new hash_address();
            temp0->prefix_val=0;
            temp1->prefix_val=1;
            temp0->next=temp1;
            prefix_length+=1;
            address_table_size=pow(2,1);

            int rem=value%address_table_size;
            bucket* bct=new bucket();
            bucket_num+=1;
            bct->num=bucket_num;

            bct->bit_length=1;
            bct->value[bct->count_value]=value;
            bct->count_value+=1;
            bct->next_bucket=NULL;
            if(rem==0)
            {

                temp0->ptr=bct;




            }
            else
            {

                temp1->ptr=bct;


            }


            address_table_root=temp0;

        }
        else // has  root
        {

            int rem=value%(int)pow(2,prefix_length);
            cout << "prefix_length = " << prefix_length<< endl;
            hash_address* temp_address=address_table_root;

            while(temp_address->prefix_val!=rem)
            {
                temp_address=temp_address->next;
            }
            cout << "133 test" << endl;

            if(temp_address->ptr==NULL)
            {
                bucket* new_bucket=new bucket();



                new_bucket->bit_length=prefix_length;
                new_bucket->next_bucket=NULL;
                bucket_num++;
                new_bucket->num=bucket_num;
                new_bucket->value[new_bucket->count_value]=value;
                new_bucket->count_value+=1;
                temp_address->ptr=new_bucket;
                cout << "add new bucket to address" << endl;


            }
            else
            {
                cout << "add a extra bucket or spilt" << endl;
                bucket* temp_bucket=temp_address->ptr;
                if(temp_address->ptr->count_value!=bucket_capasity)
                {

                    temp_bucket->value[temp_bucket->count_value]=value;
                    temp_bucket->count_value+=1;



                }
                else
                {
                    int all_value_equal=1;
                    for(int i=0; i<temp_bucket->count_value; i++)
                    {
                        if(value!=temp_bucket->value[i])//--------------------???
                        {
                            all_value_equal=0;
                            break;
                        }
                    }
                    if(all_value_equal)
                    {

                        cout << "All value are equals" << endl;

                        //insert  same value in a bucket
                        while(temp_bucket->count_value==bucket_capasity && temp_bucket->next_bucket!=NULL)
                        {
                            temp_bucket=temp_bucket->next_bucket;

                        }
                        if(temp_bucket->count_value!=bucket_capasity)
                        {


                            temp_bucket->value[temp_bucket->count_value]=value;
                            temp_bucket->count_value+=1;


                        }
                        else
                        {
                            //when the bucket is full create a new bucket and add it to the current bucket

                            bucket* new_bucket=new bucket();
                            new_bucket->bit_length=temp_bucket->bit_length;
                            new_bucket->next_bucket=NULL;
                            bucket_num++;
                            new_bucket->num=bucket_num;
                            new_bucket->value[new_bucket->count_value]=value;
                            new_bucket->count_value+=1;
                            temp_bucket->next_bucket=new_bucket;

                        }


                    }
                    else
                    {
                        //need to increase the address table size

                        cout << "Do somthing Else" << endl;



                            this->redistribute(value);
                            print_hash_table();









                    }



                }




            }
        }
    }

};



int main()
{

    cout << "my name is Mahmud"<< endl;

    Hash_Lib HL;



    int flag=1;

    while(flag)
    {
        cout << "\n\nInsert--->1" << endl;
        cout << "print---->2" << endl;
        cout << "exit---->3\n\n" << endl;
        int cmd;
        cin >> cmd;
        int value;
        if(cmd==1)
        {
            cout << "Give Value to Insert:" << endl;
            cin >> value;
            cout << "value = " << value << endl;
            HL.insert_value(value);
        }
        else if(cmd==2)
        {
            print_hash_table();

        }
        else if(cmd==3)
        {
            flag=0;

            cout << "Exit"<< endl;

        }





    }





    return 0;
}

