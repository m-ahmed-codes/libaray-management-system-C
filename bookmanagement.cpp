#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


struct login{
  // username and password  are saved already
  char	username[50] = "kiet" ;
  char	password[50]=	"kiet123";
} login;



struct books{
  //  This is used to store the data of books and author name
  int id ;
  char bookName[50];
  char authorName[50];
  char date[50];
  
} books;

struct student{
  //  This is used to store the data of student who borrowed the books
  int id ;
  char Student_Name[50];
  char Student_class[50];
  char Student_roll[50];
  char Book_name[50];
  char date[50];
  
} student;

void Intro_Message()
{
    system("cls");
    printf("\n");
    printf("\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-*");
    printf("\n\t\t\t**-**-**-**-                                                   **-**-**-**-*");
    printf("\n\t\t\t**-**-**-**-      Book management System Project in C          **-**-**-**-*");
    printf("\n\t\t\t**-**-**-**-                                                   **-**-**-**-*");
    printf("\n\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-*");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\t\t\t\t\t    BY \n");
    printf("\n\t\t\t----------------------------------------------------------------------------\n");
    printf("\t\t\t Syed Kariz Ali ~~~~~~~~~~   Mohammad Ahmed  ~~~~~~~~~~ Syed Hashir Jawaid ");
    printf("\n\t\t\t----------------------------------------------------------------------------");
}
void welcome_Message()
{
    Intro_Message();
    printf("\n\n\n");
    printf("\n\t\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t\t        =                   TO                      =");
    printf("\n\t\t\t\t        =                  BOOK                     =");
    printf("\n\t\t\t\t        =               MANAGEMENT                  =");
    printf("\n\t\t\t\t        =                 SYSTEM                    =");
    printf("\n\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
}



int head_message(const char *message){
	system("cls");
    Intro_Message();
    printf("\n\n");
	printf("\n\t\t\t----------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t %s",message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
    printf("\n\n");
}


FILE *file;


int checkID(int id){	
	int a=1;
		file = fopen("library.txt","rb");
		
	 while(fread(&books, sizeof(books), 1, file) ){
        if(id == books.id){
           printf("\n\n\t\t\t Id is Already in Use");
           a=0;
           break;
        }else{
        	a=1;
		}
		}
		

fclose(file);



return a;
	
}

int addBookInDataBase(){
	int id , a ;
	system("cls");
	head_message("Add New Book");
	
	time_t c_time = time(NULL);

    // add date when the book is add	
	struct tm time = *localtime(&c_time);
	sprintf(books.date,"%d/%d/%d",time.tm_mday,time.tm_mon+1,time.tm_year + 1900);
	
	
	printf("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
	printf("\n\t\t\t---------------------------------------------------------------------------\n");
	
	

	
	printf("\n\t\t\tBook ID NO  = ");
	scanf("%d",&books.id);
	id = books.id;
	
	
	
   a =	checkID(id);
   books.id  = id;
   
if(a){
	file = fopen("library.txt","ab");
	printf("\n\t\t\tBook Name  = ");
	fflush(stdin);
	gets(books.bookName);
	


	printf("\n\t\t\tAuthor Name  = ");
	fflush(stdin);
	gets(books.authorName);

	
	printf("\n\t\t\tNew Book Added Successfully\n");
	printf("\n\t\t\tPress Enter to go Back to menu\n");
	
	
	fwrite(&books,sizeof(books),1,file);
	
	fclose(file);
}
	

	getch();
}

int deleteBooks(){
	system("cls");
	head_message("Delete Book");
	
	int ids, f=0;
	printf("\n\t\t\tEnter ID NO to delete Book = ");
	scanf("%d",&ids);
	
	FILE *filedel;

	
	file = fopen("library.txt","rb");
	
	filedel = fopen("temp.txt","wb");
	
	while(fread(&books, sizeof(books), 1, file) == 1){
		
        if(ids == books.id){
//        	printf("books id %d",books.id);
            f=1;
        }else{
            fwrite(&books, sizeof(books), 1, filedel);
        }
    }
	
	 if(f==1){
        printf("\n\nDeleted Successfully.");
    }else{
        printf("\n\nRecord Not Found !");
    }

    fclose(file);
    fclose(filedel);
    
    
    
    remove("library.txt");
    rename("temp.txt", "library.txt");
    
    
	
	getch();
}

int viewBooks(){

	system("cls");
	head_message("Available Books");
	
	

    file = fopen("library.txt", "rb");
    
    if(fread(&books ,sizeof(books), 1, file)==1){
    	printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");
    	file = fopen("library.txt", "rb");
    	while(fread(&books ,sizeof(books), 1, file)==1 ){
        printf("%-10d %-30s %-20s %s\n", books.id, books.bookName, books.authorName, books.date);
        
         } 
    	
	}else{
		printf("\t\t\tThere is No book In The system \n\n \t\t\tPlease Enter A book in the system");
	}
    
      

    fclose(file);
	getch();
}

int searchBooks(){
	char input[100];
	int found =0;
	
	system("cls");
	head_message("Search Books");
	
	
	file = fopen("library.txt", "rb");
	
	printf("\t\t\tEnter the Book Name to search in the libary: ");
	fflush(stdin);
	gets(input);
    strlwr(input);
    fflush(stdin);
    
    printf("\n\n");


	while(fread(&books,sizeof(books),1,file)){
         strlwr(books.bookName);
         fflush(stdin);
		if(!strcmp(books.bookName,input) ){
			found =1 ;
			printf("\t\t\t%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");
	 		printf("\t\t\t%-10d %-30s %-20s %s\n", books.id, books.bookName, books.authorName, books.date);
		}
	}
	
	if(!found){
		printf("\t\t\t Record Not Found ");

	} 

	
	
	fclose(file);
	printf("\n\n\n\t\t\tPress any key to go to main menu.....");
	getch();
}


int checkIssueBook(int id,int found){
	int a =1 ;
	file = fopen("issueBook.txt","rb");
	
	while(fread(&student,sizeof(student),1,file)){
		if(id == student.id){
			
			printf("\n\t\t\t Book is already Issued..");

           a=2;
           break;
		}
	}
	
		if(found==0){
		a=0;
	}

	
	fclose(file);
	return a;
	
}

int IssueBook(){
	
	int found =0,id;
	system("cls");
	head_message("Issue Book");
	
	time_t s_time = time(NULL);

    // add date when the book is add	
	struct tm time = *localtime(&s_time);
	sprintf(student.date,"%d/%d/%d",time.tm_mday,time.tm_mon+1,time.tm_year + 1900);
	
	
	printf("\t\t\t\tEnter the Id of the Book To Issue to the student : ");
	scanf("%d",&student.id);
	
	
	file = fopen("library.txt","rb");
	
	while(fread(&books,sizeof(books),1,file)){
		if(books.id == student.id){
			found=1;
			break;
		}else{
			
			found=0;
		}
	}

	
	id = student.id;
    
	found = checkIssueBook(id,found);	
	student.id = id;
	
	
	
	if(found==1 ){
		file = fopen("library.txt","rb");
	
		char book[100];
		while(fread(&books,sizeof(books),1,file)){
		if(books.id == student.id){
			strcpy(book,books.bookName);
			break;
		}
	}
	 
	file = fopen("issueBook.txt","ab");
	strcpy(student.Book_name,book);
	
	printf("\n\t\t\t Enter the Student Name : ");
	fflush(stdin);
	gets(student.Student_Name);
	
	printf("\n\t\t\t Enter the Student Class : ");
	fflush(stdin);
	gets(student.Student_class);

	
	printf("\n\t\t\t Enter the Student Roll No : ");
	fflush(stdin);
	gets(student.Student_roll);
	
	
	printf("\n\t\t\t  Book Issued Successfully\n");
	printf("\n\t\t\t  Please Enter to Go to The Menu \n");
	getch();
	
	fwrite(&student,sizeof(student),1,file);
	fclose(file);
		
		
		
	}
	else if(found==2){
		getch();
	}
	else{
	printf("\n\n\t\t\t No book Found with this id\n\n");
	printf("\t\t\t Please Try again...");
	getch();	
	}
	
	
		
}

int IssueBooklist(){
	
	system("cls");
	head_message("Issued Books List");
	printf("%-10s %-20s %-20s %-20s %-20s %s\n\n", "Book id", "Book Name", "Name", "Class", "Roll", "Date");

    file = fopen("issueBook.txt", "rb");
    
    while(fread(&student ,sizeof(student), 1, file)==1 ){
        printf("%-10d %-20s %-20s %-20s %-20s %s\n", student.id, student.Book_name, student.Student_Name, student.Student_class, student.Student_roll , student.date);
    }   

    fclose(file);
	getch();
	
}


int ReturnIssuedBook(){
	system("cls");
	head_message("Return Book");
	
	int ids, f=0;
	printf("\n\t\t\tEnter Book ID NO that want to Return  = ");
	scanf("%d",&ids);
	
	FILE *filedell;

	
	file = fopen("issueBook.txt","rb");
	
	filedell = fopen("tempp.txt","wb");
	
	while(fread(&student, sizeof(student), 1, file) == 1){
		
        if(ids == student.id){
//        	printf("books id %d",books.id);
            f=1;
        }else{
            fwrite(&student, sizeof(student), 1, filedell);
        }
    }
	
	 if(f==1){
        printf("\n\n Returened Successfully.");
    }else{
        printf("\n\nRecord Not Found !");
    }

    fclose(file);
    fclose(filedell);
    
    
    
    remove("issueBook.txt");
    rename("tempp.txt", "issueBook.txt");
    
    
	
	getch();
	
}
int menu(){
	 int choice = 0;
    do
    {
        head_message("MAIN MENU");
        printf("\n\n\n\t\t\t1.Add Books");
        printf("\n\t\t\t2.Delete Book");
        printf("\n\t\t\t3.View Books");
        printf("\n\t\t\t4.Search Book");
        printf("\n\t\t\t5.Issue book");
        printf("\n\t\t\t6.Issued books List ");
        printf("\n\t\t\t7.Returned Issued book ");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            addBookInDataBase();
            break;
        case 2:
        	deleteBooks();   
            break;
        case 3:
            viewBooks();
            break;
        case 4:
            searchBooks();
            break;
        case 5:
        	IssueBook();
            break;
        case 6:
        	IssueBooklist();  
            break;
        case 7:
        	ReturnIssuedBook();  
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);  
}


int Login(){
    //	calling head_message to diplay login design in cmd
	head_message("Login");
  	char username[50] ;
	char password[50] ;
	
    // taking username and password from user	
	printf("\nEnter Username : ");
	gets(username);
	printf("\nEnter Password : ");
	gets(password);
	
    // Checking user input details to presaved details	
	if( (!strcmp(username,login.username)) && (!strcmp(password,login.password))  ){
		menu();

	}else{
		printf("Please Enter correct Username and Password");
	}
}


int main (){

//headMessage();
welcome_Message();
Login();

return 0;
	
   	
}


