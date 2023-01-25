
#include <stdio.h>
#define BUFFERSIZE 1024

struct Post{
	char* author;
	char* text;
	int id;
	int like;
};
typedef struct Post Post;

struct postNode{
	Post data;
	struct postNode *next;
};
typedef struct postNode postNode;


struct User{
	char* username;
	char* password;
};
typedef struct User User;

struct userNode{
	User data;
	struct userNode *next;
};
typedef struct userNode userNode;

postNode *headPosts=NULL , *lastPosts=NULL;
userNode *headUsers=NULL , *lastUsers=NULL;

int counter=1;
int loginState=0;
User currentUser;

void insertPost(Post);
void insertUser(User);
char* findUser(char*);
void showPosts(char*);
int deletePost(int);
int isStringsEqual(char*, char*);
void updateLoginState();
void signup();
void login();
void logout();
void post();
char *trimWhitespace(char *str);
void like();
void likeUserPost(char* username,int postId);
void info();
void showUserPost();
void deleteUserPost();
void writeTofile();

int main(){
	
	while(1){
		char command[50];		
		scanf("%s",&command);
		
		if(isStringsEqual(command,"signup"))
			signup();
		else if(isStringsEqual(command,"login"))
			login();
		else if(isStringsEqual(command,"post"))
			post();
		else if(isStringsEqual(command,"like"))
			like();
		else if(isStringsEqual(command,"logout"))
			logout();
		else if(isStringsEqual(command,"delete"))
			deleteUserPost();
		else if(isStringsEqual(command,"info"))
			info();
		else if(isStringsEqual(command,"find_user"))
			showUserPost();
		else if(isStringsEqual(command,"exit")){
			writeTofile();
			break;

		}
		else
			printf("\ninvalid command!\n");
		
	}
}

void login(){
	
	if(loginState==1){
		printf("\nlogout to login to another account!\n");
		return;
	}
	currentUser.username = (char*)calloc(BUFFERSIZE, sizeof(char));
	currentUser.password = (char*)calloc(BUFFERSIZE, sizeof(char));
	
	scanf("%s",currentUser.username);
	scanf("%s",currentUser.password);
	
	
	if(isStringsEqual(findUser(currentUser.username),currentUser.password)){
		printf("\nsuccessfully logged in!\n");
		updateLoginState();
		
	}else{
		printf("\nusername or password incorrect!\n");
	}
	
}

void signup(){
	
	if(loginState==1){
		printf("\nyou should logout to signup a new account!\n");
		return;
	}
	
	User user;
	user.username = (char*)calloc(BUFFERSIZE, sizeof(char));
	user.password = (char*)calloc(BUFFERSIZE, sizeof(char));
	
	scanf("%s",user.username);
	scanf("%s",user.password);
	
	if(!findUser(user.username)){
		insertUser(user);
		printf("\nsuccessfully added!\n");
	}
	else
		printf("\nusername already exist!\n");
}

void insertPost(Post post){
	
    postNode *node;
    node = (postNode *)malloc(sizeof(postNode));

    node->data=post;
    node->next=NULL;

    if(headPosts==NULL)
    {
        headPosts=node;
        lastPosts=node;
    }
    else
    {
        lastPosts->next=node;
        lastPosts=node;
    }

}

void insertUser(User user){
	
	userNode *node;
    node = (userNode *)malloc(sizeof(userNode));

    node->data=user;
    node->next=NULL;

    if(headUsers==NULL)
    {
        headUsers=node;
        lastUsers=node;
    }
    else
    {
        lastUsers->next=node;
        lastUsers=node;
    }
}

void showPosts(char*username){
	
    postNode *myList;
    myList = headPosts;

    while(myList!=NULL)
    {
		if(!username){	  
		  
		printf("\npost id : %d\npost likes : %d\nauthor : %s\ntext : %s\n"
		,myList->data.id,myList->data.like,myList->data.author,myList->data.text);
		}else{
			
			if(isStringsEqual(username,myList->data.author)){
				printf("\npost id : %d\npost likes : %d\nauthor : %s\ntext : %s\n"
				,myList->data.id,myList->data.like,myList->data.author,myList->data.text);
			}
		}	

        myList = myList->next;
    }
}

char* findUser(char*username){
	
    userNode *myList;
    myList = headUsers;

    while(myList!=NULL)
    {
    	if(isStringsEqual(myList->data.username,username))
    		return myList->data.password;	
		myList = myList->next;
	
    }
    
    return NULL;
}

int deletePost(int id){
	
    postNode* myNode = headPosts, *previous=NULL;
    int flag = 0;

    while(myNode!=NULL)
    {
        if(myNode->data.id==id)
        {
            if(previous==NULL)
                headPosts = myNode->next;
            else
                previous->next = myNode->next;

            flag = 1;
            free(myNode); //need to free up the memory to prevent memory leak
            
            return myNode->data.id;
                    
		}

        previous = myNode;
        myNode = myNode->next;
    }

    if(flag==0)
        return NULL;
}

int isStringsEqual(char* x, char* y){
	
	if(x==NULL || y==NULL)
		return 0;
		
    int flag = 0;
 
    // Iterate a loop till the end
    // of both the strings
    while (*x != '\0' || *y != '\0') {
        if (*x == *y) {
            x++;
            y++;
        }
 
        // If two characters are not same
        // print the difference and exit
        else if ((*x == '\0' && *y != '\0')
                 || (*x != '\0' && *y == '\0')
                 || *x != *y) {
                 	
            return 0;
        }
    }
 
    // If two strings are exactly same
    if (flag == 0)
    	return 1;
}

void updateLoginState(){
	
	loginState=loginState==0?1:0;
}

void logout(){
	
	if(loginState!=0)
	{
		loginState=0;
		printf("\nsuccessfully loggout!\n");

	}
	else
		printf("\nalready logged out!\n");
}

void post(){
	
	if(loginState==0){
		printf("\nyou should log in to post!\n");
		return;
	}
	
	Post post;
	post.author=currentUser.username;
	post.id=counter++;
	post.like=0;
	
	post.text = (char*)calloc(BUFFERSIZE, sizeof(char));
	scanf("%[^\n]s", post.text);
	post.text=trimWhitespace(post.text);
	fflush(stdin);
	
	
	insertPost(post);
	
	printf("\nposted successfully!\n");
}

char *trimWhitespace(char *str){
	
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

void like(){
	if(loginState==0){
		printf("\nyou should log in to like any post!\n");
		return;
	}
	char* username = (char*)calloc(BUFFERSIZE, sizeof(char));
	int postId;
		
	scanf("%s",username);
	scanf("%d",&postId);
	
	likeUserPost(username,postId);
}


void likeUserPost(char* username,int postId){
	
	if(findUser(username)){
		
		postNode *myList;
    	myList = headPosts;

	    while(myList!=NULL)
	    {
	    	if( isStringsEqual(myList->data.author,username) && 
				myList->data.id==postId ) {
					
	    		myList->data.like++;
	    		printf("\nliked successfully!\n");
	    		return;
			}
	        myList = myList->next;
	    }
	    
	    printf("\nuser dont have post with id:%d\n",postId);
	    return;
	}
	
	printf("\nuser is not exist!\n");
}

void info(){
	
	printf("\nusername : %s , password : %s\n",
	currentUser.username,currentUser.password);
	
	printf("\n--------------------- Posts --------------------------\n");
	showPosts(NULL);
	printf("\n--------------------- Posts --------------------------\n");	
}

void showUserPost(){
	char* username = (char*)calloc(BUFFERSIZE, sizeof(char));
	scanf("%s",username);
	
	if(findUser(username))
		showPosts(username);
	else
		printf("\nuser not found!\n");
	
}

void deleteUserPost(){
	if(loginState==0){
		printf("\nyou should log in to delete post!\n");
		return;
	}
	int postId;
	scanf("%d",&postId);
	
	postNode *myList;
    myList = headPosts;

	while(myList!=NULL)
	{
	    if( isStringsEqual(myList->data.author,currentUser.username) && 
			myList->data.id==postId ) {
					
			deletePost(postId);
			printf("\ndeleted successfully!\n");
	    	return;
		}
	    myList = myList->next;
	
	}
	
	printf("\nyou dont have post with id:%d\n",postId);
}

void writeTofile(){
	FILE *fptr;
    fptr = fopen("accounts.txt","w");

   if(fptr == NULL)
   {
      printf("error while opening file");   
      exit(1);             
   }
	
	userNode *myList;
    myList = headUsers;

    while(myList!=NULL)
    {
    	//traverse userlist
    	fprintf(fptr,"%s %s\n",myList->data.username,myList->data.password);
    	
    	//find this users post
    	postNode *myPosts;
    	myPosts = headPosts;

	    while(myPosts!=NULL)
	    {
			if(isStringsEqual(myList->data.username,myPosts->data.author)){
					fprintf(fptr,"%d %s %d\n",
					myPosts->data.id,myPosts->data.text,myPosts->data.like);
				}	
	        myPosts = myPosts->next;
	    }
	    
		fprintf(fptr,"\n--------------------------\n");
	    myList = myList->next;

    }
    
    fclose(fptr);
}
