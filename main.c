#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define NUM_CHAR 256
#define WORDLEN 40


typedef struct trienode{
bool terminal;
struct trienode *children[NUM_CHAR];
int mangos;
int nodeTotal;


}trienode;

trienode *createnode(){//to create node used in inserting ords
  trienode *newnode =malloc(sizeof *newnode);

  for(int i=0;i<NUM_CHAR; i++){
    newnode->children[i]=NULL;
    
  }
  newnode->terminal=false;
  return newnode;
}

bool trieinsert(trienode **root, char *signedtext, int mangos){//to insert words 
  if(*root==NULL){
    *root=createnode();//base 
  }
  unsigned char *text = (unsigned char *)signedtext;
  trienode *tmp=*root;
  int length =strlen(signedtext);

  for(int i=0;i<length;i++){
    if(tmp->children[text[i]]==NULL){//should be empty and add child
      tmp->children[text[i]]=createnode();
    }
    tmp=tmp->children[text[i]];//make tmp child
    
  }
  if(tmp->terminal)
  {return false;
    }
  else{//
    tmp->mangos=mangos;//get mangos
    tmp->terminal=true;//set true so node exists
    
    return true;
    }
}


int add_mangosrec(trienode *node, unsigned char *prefix, int length, char *second){
  int mangos=0;//add mangos of nodes with this substring not working correctly
  unsigned char newprefix[length+2];
  memcpy(newprefix, prefix, length);
  newprefix[length+1]=0;

  if(node->terminal&&strstr(prefix, second)){
   mangos+=node->mangos;
  }
  for(int i =0; i<NUM_CHAR; i++){
    if(node->children[i]!=NULL){
      newprefix[length]=i;
      add_mangosrec(node->children[i], newprefix, length+1, second);
    }
  }
}





bool node_has_children(trienode *node){//check if has children used in search
  if(node==NULL) return false;

  for (int i=0;i<NUM_CHAR; i++){
    if(node->children[i]!=NULL){//if there true
      return true;
    }
  }
  return false;
}

int searchtrie(trienode *root, char *signedtext){//search and get mango amount
  unsigned char *text = (unsigned char *) signedtext;
  int length = strlen(signedtext);
  trienode * tmp =root;

  for (int i=0; i<length;i++){
    if(tmp->children[text[i]]==NULL){
      return 0;
    }
  
  tmp = tmp->children[text[i]];
    }
  return tmp->mangos;
    }





trienode* delete_rec(trienode *node, unsigned char *text, bool *deleted){//delete method
  if(node==NULL) return node;

  if(*text=='\0'){
    if(node->terminal){
      node->terminal=false;
      *deleted = true;

      if(node_has_children(node)==false){
        free(node);
        node=NULL;
      }
    }
    return node;
  }

  node->children[text[0]]= delete_rec(node->children[text[0]], text+1, deleted);
  if(*deleted && node_has_children(node)==false && node->terminal == false){
    free(node);
    node=NULL;
  }
  return node;

  
  
}

bool deleteword(trienode ** root, char *signedtext){
  unsigned char *text = (unsigned char *)signedtext;
  bool result = false;


  if(*root ==NULL) return false;



  

  *root=delete_rec(*root, text, &result);
  return result;
}



int main(void) {
  trienode *root = NULL;
  int n, e;
 scanf("%d %d", &n, &e);
  
  //printf("%d %d", n , e);

  

 


  
    //enter n # orang and e # events
  for(int i=0;i<e;i++){//loop e times

    //starting items

     char second[WORDLEN];
    int num;
    char third[WORDLEN];
    int eaten;
    printf("\nsentence\n");

    scanf("%d %s", &num, &*second);
    if(num==2){
    scanf("%s", &*third);
      }
     else if(num==1){
    scanf("%d", &eaten);
      }
   
    printf("\n");

    if(num==1){
      
      trieinsert(&root,&*second, eaten);//insert
      
    }
    else if(num==2){// if option 2
     
      

      int copymang=searchtrie(root, &*second);//search for this to get mango
      trieinsert(&root, &*third, copymang );//insert new w mango amt
      deleteword(&root, &*second);//delete old
      
    }
    else if(num==3){
      
      int mangs=add_mangosrec(root, NULL, 0, second);//this fnctn not workins want to
         
         printf("%d", mangs);
       
    }


  }
  
}