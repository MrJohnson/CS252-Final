#include <stdio.h>
#include <stdlib.h>
#include <synch.h>

struct List {
  int val;
  int next;
};

struct List * head = NULL;

// More variables


main()
{

 sema_t sem;





}

void insert( int val )
{


  List tmp = new List;


  tmp->val = val;


  tmp->next = head;


  head = tmp;


}

Struct List * removeFirst()
{


  List tmp = head;



  head = tmp->next;


  return tmp;

}